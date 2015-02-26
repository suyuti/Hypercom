//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hyperware Base Application
//      (c) Copyright 2006
//
// File Name:
//      AmexHost.cpp
//
// File Description:
//      Implementation of the Class AmexHost
//
//=============================================================================
#if defined(__GNUC__)
#pragma implementation
#endif

#include <compiler.h>
#define _INCLUDE_NUCLEUS_FILE_
#include <hycddl.h>
#include <time.h>
#include <HypCCurrency.hpp>
#include <HypCDateTime.hpp>
#include <HypCMLTransport.hpp>
#include <HypCDocumentManager.hpp>
#include <HypCPOSConfig.hpp>
#include <HypCTimer.hpp>
#include <HypCJournal.hpp>
#include <BCDUtil.h>
#include <HypCTransaction.hpp>
#include <HypCTransactionData.hpp>
#include <HypCInt64.hpp>
#include <HypCString.hpp>
#include <HypCISO8583_Message.hpp>
#include "YemekSepetiTags.h"
#include "AmexHost.hpp"


//=============================================================================
// Public defines and typedefs
//=============================================================================


//-----------------------------------------------------------------------------
//!
//!      Checks for offline, floor, reversal, etc. before sending the
//!      request to the host
//!
//! \param
//!      TransData       reference to a transaction data container
//!
//! \return
//!      HOST_OK     If ....
//!
//! \note
//!       This function is responsible for setting class member m_ContactHost.
//!       Set to true if host is to be contacted ( transaction performed ),
//!       else false. Generally the host is not contacted for offline
//!       transactions or for transactions where amount is lower than some
//!       preset limit.
//!
HypEHostResult AmexHost::DoPreProcessing( HypCTransactionData &TransData )
{
	HYP_CFG_HANDLE issRecord = POSConfig().GetTable( IssuerTag::ISSUER_TABLE );

	// check, whether capture card range is set
	if ( !TransData.get( TransactionTag::SETTLE_TYPE ) )
	{
		const HypCData* ptr = TransData.get( TransactionTag::TYPE_NAME );
		if ( ptr )
		{
			HString transStr = ptr->AsString();
			
			if ( ( transStr == "SALE CREDIT" && 
					!POSConfig(  ).IsOptionSet( issRecord, ISS_CAPTURE_CARD_RANGE ) ) ||
				 ( transStr == "AUTH" && 
					POSConfig(  ).IsOptionSet( issRecord, ISS_CAPTURE_CARD_RANGE ) ) )
			{
				m_bContactHost = false;
				return HOST_OK;
			}
		}
		else
		{
			return HOST_INCOMPLETE_TRANS;
		}
	}

	// set issuer and acquire record handles
	HypCString HostNameStr( HostName() );

	m_AcqRecord = POSConfig().FindTableRow( AcquirerTag::ACQUIRER_TABLE,
											AcquirerTag::NAME, HostNameStr );

	if( !m_AcqRecord )
	{
		return HOST_INCOMPLETE_TRANS;
	}

	const HypCData* ptr;
	const HypCData* settle;
	HString settle_str;

	settle = TransData.get( TransactionTag::SETTLE_TYPE );
	if ( !settle || ( ( settle_str = settle->AsString(  ) ) == TransactionTag::SETTLE_RUPLOAD ) )
	{
		if( !(ptr =  TransData.get( TransactionTag::ISSUER_NAME )) )
		{
			return HOST_INCOMPLETE_TRANS;
		}

		m_IssRecord = POSConfig().FindTableRow( IssuerTag::ISSUER_TABLE,
												IssuerTag::NAME, *ptr );
		if( !m_IssRecord )
		{
			return 	HOST_INCOMPLETE_TRANS;
		}

		// batch upload phase
		if ( settle )
		{
			// set the STAN for this transaction and increment
			SetSystemTraceNumber( TransData );

			// now set the current time/date
			SetTransactionDateTime( TransData );

			HString str;
			if( !POSConfig().IsOptionSet( m_IssRecord,
										  ISS_GENERATE_6_DIGIT_AUTH ) )
			{
				GenerateAuthCode(6, str);
			}
			else
			{
				GenerateAuthCode(2, str);
			}

			// set AUTH CODE
			TransData.insert( TransactionTag::AUTH_ID, str.c_str() );
		}
	}

	// see if this should be processed offline
	if ( Offline( Transaction(  ).TransactionData(  ) ) )
	{
		// set the STAN for this transaction and increment
		SetSystemTraceNumber( TransData );

		// now set the current time/date
		SetTransactionDateTime( TransData );

		// set to ISO response code to APPROVED
		TransData.insert( TransactionTag::ISO_RESPONSE_CODE,
						  "00" );

		// set the response text
		SetResponseText( "00", settle ? true : false );

		// set additional response data to offline
		TransData.insert( TransactionTag::ADDITIONAL_RESPONSE_DATA,
						  "06" );

		// set advice bit
		Transaction().SaveDataOption( TransactionTag::STATUS_FLAGS,
									  TransactionTag::SEND_ADVICE, true );

		// no need to contact host
		m_bContactHost = false;

		return HOST_OK;
	}


	// are we below floor limit
	if ( BelowFloorLimit( Transaction(  ).TransactionData(  ), 
		Transaction(  ).POSConfig(  ) ) )
	{
		// do we have a valid expiration date?
		if( ValidExpirationDate( Transaction(  ), 
			Transaction(  ).POSConfig(  ) ) )
		{
			// yes so process as advice
			// set the STAN for this transaction and increment
			SetSystemTraceNumber( TransData );

			// now set the current time/date
			SetTransactionDateTime( TransData );

			// set to ISO response code to APPROVED
			TransData.insert( TransactionTag::ISO_RESPONSE_CODE, "00" );

			// set POS Condition Code
			TransData.insert( TransactionTag::POS_CONDITION_CODE, "06" );

			// generate an AUTH Code and put in TransactionTag::AUTH_ID
			HString str;
		
				if( !POSConfig().IsOptionSet( m_IssRecord,
					  ISS_GENERATE_6_DIGIT_AUTH ) )
			{
				GenerateAuthCode(6, str);
			}
			else
			{
				GenerateAuthCode(2, str);
			}

			// set AUTH CODE
			TransData.insert( TransactionTag::AUTH_ID, str.c_str() );

			// set the response text
			SetResponseText( "00", settle ? true : false );

			// set Advice Bit
			Transaction().SaveDataOption( TransactionTag::STATUS_FLAGS,
										  TransactionTag::SEND_ADVICE, true );

			// set Additional Response Data to Floor
			TransData.insert( TransactionTag::ADDITIONAL_RESPONSE_DATA,
							  "03" );

			// fake an online transaction, just wait for 3 seconds
			SetState ( WaitingForResponse );
			Notify();

			// wait 3 seconds
			HypCEvent ev;
			HypCEventInfo ei;
			ev.Wait( ei, 3000 );

			// no need to contact host
			m_bContactHost = false;
			return HOST_OK;
		}
	}

	// set the transaction
	if( !SetISO8583Transaction( TransData ) )
	{
		return HOST_UNSUPPORTED_TRANSACTION;
	}

	m_bContactHost = true;
	return HOST_OK;
}

//-----------------------------------------------------------------------------
//!
//!      Prepares standard totals, required by settlement
//!
//! \param
//!      Bit63           String to which, formated totals are assigned
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      true if data was added, else false
//!
//! \note
//!
bool AmexHost::PrepareB63StandardTotals( HString& Bit63, HypCTransactionData& TransData )
{
	const char* count_tags[] = { TransactionTag::SALES_COUNT, 
								 TransactionTag::SALES_DEB_COUNT,  
								 0 };
	const char* amount_tags[] = { TransactionTag::SALES_AMOUNT, 
								  TransactionTag::SALES_DEB_AMOUNT, 
								  0 };

	const char ** count_tag, ** amount_tag;
	HString count, amount;
	bool saved = false;

	for ( count_tag = count_tags, amount_tag = amount_tags; 
			*amount_tag; count_tag++, amount_tag++, saved = true )
	{
		count = GetTransTag( TransData, ( HostName() + "_" + *count_tag ).c_str(  ) );
		if( count.length() < 3 )
		{
			count.insert( 0, 3 - count.length(), '0' );
		}
		Bit63 += count;

		amount = GetTransTag( TransData, ( HostName() + "_" + *amount_tag ).c_str(  ) );
		if( amount.length() < 12 )
		{
			amount.insert( 0, 12 - amount.length(), '0' );
		}
		Bit63 += amount;
	}
	count = GetTransTag( TransData, TransactionTag::REV_COUNT );
	if( count.length() < 3 )
	{
		count.insert( 0, 3 - count.length(), '0' );
		saved = true;
	}
	Bit63 += count;

	count = GetTransTag( TransData, TransactionTag::ADJ_COUNT );
	if( count.length() < 3 )
	{
		count.insert( 0, 3 - count.length(), '0' );
		saved = true;
	}
	Bit63 += count;

	return saved;
}

