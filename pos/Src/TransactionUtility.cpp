//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hypercom Foundation Classes
//      (c) Copyright 2006
//
// File Name:
//      TransactionUtility.cpp
//
// File Contents:
//      Implementation of the Class TransactionUtility
//
//=============================================================================
#if defined(__GNUC__)
#pragma implementation
#endif

#include <compiler.h>
#include <HypCApplication.hpp>
#include <HypCTransaction.hpp>
#include "TransactionUtility.hpp"
#include <HypCTransactionStep.hpp>
#include <HypCTransactionFactory.hpp>
#include <HypCTransactionStepFactory.hpp>
#include <HypCTransactionManager.hpp>
#include <HypCPOSConfig.hpp>
#include "YemekSepetiTags.h"
#include <HypCString.hpp>
#include <HypCDateTime.hpp>
#include <HypCCurrency.hpp>
#include <HypCJournal.hpp>
#include <HypCHost.hpp>
#include <HypCInfoBox.hpp>
#include <HypCUserInterface.hpp>
#include <HypCPrinter.hpp>
#include <HypCMultiLang.hpp>
#include <hypcpds.hpp>
#include "PromptsDef.h"

//-----------------------------------------------------------------------------
//!
//!      Checks if attribute is set for this transaction
//!
//! \param
//!      transRecord    transaction record of the transaction to be checked
//! \param
//!      AttributeID    attribute identifier from enum TransactionAttributes
//!
//! \return
//!      true, if the attribute is set, false otherwise 
//!
//! \note
//!
bool TransactionUtility::IsAttributeSet( HypCTransRecord& transRecord, int AttributeID )
{
    bool bRetVal = false;
	const HypCData *ptr = transRecord.get( TransactionTag::TRANSACTION_ATTRIBUTES );
	if ( ptr )
	{
		const HypCOptions *pOpt = static_cast< const HypCOptions *>( ptr );
		if( pOpt )
		{
			bRetVal = pOpt->IsSet( AttributeID );
		}
	}
	return bRetVal;
}

//-----------------------------------------------------------------------------
//!
//!      Set the attributes associated with this transaction,
//!
//! \param
//!      trans          transaction object
//! \param
//!      AttributeID    attribute identifier from enum TransactionAttributes
//!
//! \return
//!      void
//!
//! \note
//!
void TransactionUtility::SetAttribute( HypCTransaction& trans, int AttributeID )
{
	trans.SaveDataOption( TransactionTag::TRANSACTION_ATTRIBUTES,
                          AttributeID, true );
}

//-----------------------------------------------------------------------------
//!
//!      Returns true if this transaction can be processed offline
//!
//! \param
//!      transRecord    transaction record of the transaction to be checked
//!
//! \return
//!      true if this transaction can be processed offline, else false
//!
//! \note
//!
bool TransactionUtility::Offline( HypCTransRecord& transRecord )
{
    // is this an offline transaction ?
	return ( IsAttributeSet( transRecord, TransactionTag::OFFLINE ) );
}


//-----------------------------------------------------------------------------
//!
//!      Checks if current total amount is below floor limit and
//!      floor limit processing is allowed.
//!
//! \param
//!      transRecord    transaction record of the transaction to be checked
//! \param
//!      posConfig      reference to the configuration DB object
//!
//! \return
//!      true if the current total amount is below floor limit and
//!      floor limit processing is allowed, else false
//!
//! \note
//!
bool TransactionUtility::BelowFloorLimit( HypCTransRecord& transRecord, 
                                          HypCPOSConfig& posConfig )
{
	bool bApproved = false;

	// Are floor limits approved for this transaction
	if ( !IsAttributeSet( transRecord, TransactionTag::FLOOR ) )
	{
		return bApproved;
	}

	const HypCData *ptr = transRecord.get( TransactionTag::ISSUER_NAME );

	if( ptr )
	{
		// Get the floor limit amount
		HYP_CFG_HANDLE issRecord;
		
		issRecord = posConfig.FindTableRow( IssuerTag::ISSUER_TABLE,
                                            IssuerTag::NAME, *ptr );
	
		HString str = posConfig.GetParam( issRecord, IssuerTag::FLOOR_LIMIT );

		if( str != "" )
		{
			HypCString Floor = str;
			const HypCCurrency *pData
				= static_cast< const HypCCurrency *>( transRecord.get( TransactionTag::TOTAL_AMOUNT ));

			if( pData )
			{
				HypCCurrency  Floor( Floor.AsInt());
		
				// if total less than floor
				if( *pData <= Floor )
				{
					// Approved
					bApproved = true;
				}
			}
		}
	}

	return bApproved;

}


//-----------------------------------------------------------------------------
//!
//!      Checks if the expiration date is valid against current date.
//!
//! \param
//!      trans          transaction for which to obtain the expiration date
//! \param
//!      posConfig      reference to the configuration DB object
//!
//! \return
//!      true if the expiration is required, exists, and valid,
//!      else false
//!
//! \note
//!
bool TransactionUtility::ValidExpirationDate( HypCTransaction& trans, HypCPOSConfig& posConfig )
{
	bool bRetVal = false;
	const HypCDateTime *pExpDate = static_cast< const HypCDateTime * >( trans.GetData ( TransactionTag::EXPIRATION_DATE ));

	if( !pExpDate )
	{
		// exp date not found

		// if we manually entered and expiration date is disabled
		// then having no expiration date is okay
		const HypCData *ptr = trans.TransactionData().get( TransactionTag::ISSUER_NAME );

		// Check options
		HYP_CFG_HANDLE issRecord;
		
		issRecord = posConfig.FindTableRow( IssuerTag::ISSUER_TABLE,
                                            IssuerTag::NAME, 
                                            *ptr );
	
		if( !posConfig.IsOptionSet( issRecord,
                                    ISS_EXPIRATION_DATE_ALLOWED ) )
		{
			// don't care about expiration date
			bRetVal = true;
		}
	}
	else
	{
		// get current time
		HypCDateTime Current;
		Current.CurrentTime();

		// if expiration date is valid
		if( *pExpDate > Current )
		{
			bRetVal = true;
		}
	}

	return bRetVal;
}

//-----------------------------------------------------------------------------
//!
//!      Interpret and print the script
//!
//! \param
//!      pPCL           pointer to created HypCPCL object
//! \param
//!      trans          transaction where a report is printed from
//! \param
//!      receipt        name of the file where script is stored
//!
//! \return
//!      none
//!
//! \note
//!      Give a message if printer is paper out
//!      Save last report in the file "lastprint.bin"
//!
void TransactionUtility::PrintReceipt( HypCPCL* pPCL, 
                                       HypCTransaction& trans,
                                       const char* receipt, 
                                       bool save )
{
	HYP_ASSERT ( pPCL != NULL );

    bool bOutOfPaper = false;

	HypCMultiLang* prompt = trans.GetMultiLang();

	// Run the interpreter. -1 means the receipt was not found.
    HypCPrinter *prn = trans.GetPrinter();
    if ( ( NULL != prn ) && ( -1 != pPCL->Interp( receipt ) ) )
	{
		const HString& str = pPCL->GetBuf(  );

        // Start printing asynchronously
        HypCEvent FinishedPrinting;
        HypCEventInfo   eventInfo;
        
        if ( PDS_OK != prn->Print( FinishedPrinting, str ) )
        {
            bOutOfPaper = true;
        }

        // Save the receipt meanwhile
		if ( save )
		{
			trans.SaveDataOption( TransactionTag::STATUS_FLAGS, TransactionTag::SF_REPRINT, true );

            // save PDS data (binary data) of report
            HypCFile::Delete( LastReceiptFile );

            HypCFile* m_fin = new HypCFile( LastReceiptFile, 
                                            F_CREATE | F_SHARE_READ, 
                                            F_WRITE | F_READ);

            if ( NULL != m_fin && m_fin->IsOpen(  ) )
            {
                unsigned int written;
                m_fin->Write( str.c_str(  ), str.length(  ), written );
                m_fin->Close(  );
            }
            if ( NULL != m_fin )
            {
                delete m_fin;
            }

			trans.SaveDataOption( TransactionTag::STATUS_FLAGS, TransactionTag::SF_REPRINT, false );
		}
        // Wait until the receipt in printed
        FinishedPrinting.Wait ( eventInfo );

        // then check if we ran out of paper
        bOutOfPaper |= (!prn->Status());
        if ( bOutOfPaper )
        {
			HypCEvent event;
			HypCEventInfo Ei;
            HypInfoParam dsc;
            HypCUserInterface *m_Interface = trans.GetUserInterface(  );
            dsc.Message = prompt->GetPrompt( Prompts::PAPER_OUT );
            dsc.Title = trans.GetTitle();
            if ( dsc.Title.empty() )
            {
                dsc.Title = "Report Error";
            }
#ifdef PLATFORM_M4100	
	   		m_Interface->InfoBox()->SetTextColor( clBlack ); 
			m_Interface->InfoBox()->SetMsgY( WIN_H/2 - 23 );
            m_Interface->InfoBox()->SetMsgH( 80 );
#endif
            m_Interface->InfoBox(  )->Show( event, dsc );
			// wait for timeout or user key
			if( !event.Wait(Ei, 2000) )
			{
				// we timed out
				m_Interface->InfoBox()->Cancel();
			}		
        }
	}
}

