//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hyperware Base Application
//      (c) Copyright 2006
//
// File Name:
//      BasicHost.cpp
//
// File Description:
//      Implementation of the Class BasicHost
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
#include <HypCApplication.hpp>
#include <HypCTransportAddressSet.hpp>
#include "YemekSepetiTags.h"
#include "BasicHost.hpp"


//=============================================================================
// Public defines and typedefs
//=============================================================================


//-----------------------------------------------------------------------------
//!
//!      Constructor
//!
//! \return
//!      void
//!
//! \note
//!
BasicHost::BasicHost() :
	HypCHost(),
	m_AcqRecord(0),
	m_IssRecord(0)
{
}

//-----------------------------------------------------------------------------
//!
//!      Destructor
//!
//! \return
//!      void
//!
//! \note
//!
BasicHost::~BasicHost()
{
}

//-----------------------------------------------------------------------------
//!
//!      Configures the HypCComunication object with setup communication
//!      parameters.
//!
//! \param
//!      Comm            reference to HypCHostMLTransport object
//! \param
//!      bSettlement     determines whether to configure for settlement
//!
//! \return
//!      true, on success
//!
//! \note
//!
bool BasicHost::DoConfigureCommuncations( HypCMLTransport& Comm, bool bSettlement )
{
	// create address
	HypCTransportAddressSet Addr;
	bool bUseTCPIP = true;
    bool bUseHLAN = false;
    bool bUseGPRS = false;

	HypCString attempts,timeout, port, modem;
	HString address, ATPhoneNum;
	HypCString HostNameStr( HostName() );

	// set acquire record handles
	m_AcqRecord = POSConfig().FindTableRow( AcquirerTag::ACQUIRER_TABLE,
											AcquirerTag::NAME, 
											HostNameStr );

	if( !m_AcqRecord )
	{
		return false;
	}

	const char* sModemModeTag;
	const char*	sAddressTag;
	const char* sPrimaryNumberTag;
	const char* sSecondaryNumberTag;
	const char* sPrimaryDialAttemptsTag;
	const char* sSecondaryDialAttemptsTag;
	const char* sPrimaryConnTimeTag;
	const char* sSecondaryConnTimeTag;
	const char* sTcpIpPortTag;

	//**********
	// Determine the set of tags to use to read data from the profile
	if( bSettlement )
	{
		sModemModeTag 			= AcquirerTag::ACQ_MODEM_MODE_SETTL;
		sAddressTag   			= AcquirerTag::ACQ_SETTL_URL;
		sPrimaryNumberTag 		= AcquirerTag::ACQ_PRIM_SETTL_DIAL;
		sSecondaryNumberTag 	= AcquirerTag::ACQ_SEC_SETTL_DIAL;      
		sPrimaryDialAttemptsTag = AcquirerTag::ACQ_PRIM_SETTL_DIAL_ATTEMPTS;
		sSecondaryDialAttemptsTag = AcquirerTag::ACQ_SEC_SETTL_DIAL_ATTEMPTS;
		sPrimaryConnTimeTag		= AcquirerTag::ACQ_PRIM_SETTL_CONN_TIME;
		sSecondaryConnTimeTag	= AcquirerTag::ACQ_SEC_SETTL_CONN_TIME;
		sTcpIpPortTag			= AcquirerTag::ACQ_SETTL_PORT;
	}
	else	// Not settlement, use transaction settings
	{
		sModemModeTag           = AcquirerTag::ACQ_MODEM_MODE;
		sAddressTag             = AcquirerTag::ACQ_URL;
		sPrimaryNumberTag       = AcquirerTag::PRI_PHONE;
		sSecondaryNumberTag     = AcquirerTag::SEC_PHONE;
		sPrimaryDialAttemptsTag = AcquirerTag::PRI_DIAL_ATTEMPTS;
		sSecondaryDialAttemptsTag = AcquirerTag::SEC_DIAL_ATTEMPTS;
		sPrimaryConnTimeTag     = AcquirerTag::PRI_TIMEOUT;
		sSecondaryConnTimeTag   = AcquirerTag::SEC_TIMEOUT;
		sTcpIpPortTag			= AcquirerTag::ACQ_PORT;
	}

	// Read parameters from the profile.

	modem = POSConfig().GetParam( m_AcqRecord, sModemModeTag );
	address = POSConfig().GetParam( m_AcqRecord, sAddressTag );

	// check URL address , if empty default to dial
	address.Trim();
	bUseTCPIP = !address.empty();

    if( !bUseTCPIP )
    {
        address = POSConfig().GetParam( m_AcqRecord, AcquirerTag::ACQ_HLAN_ADDRESS );
        address.Trim();

        bUseHLAN = ( !address.empty() ) && ( (HypCString(address)).AsInt() > 0 ) && ( (HypCString(address)).AsInt() < 255 );
    }

	if( bUseTCPIP )
	{
		// Get the TCP/IP port
		port = POSConfig().GetParam( m_AcqRecord, sTcpIpPortTag );
		// add data to address, Addr
		Addr.AddAddress( address.c_str(), port.AsInt() );
	}
	else  // Dial up or HLAN
	{
        if( !bUseHLAN )
        {
            // Dial up connection

            // Get the primary phone number
    		address = POSConfig().GetParam( m_AcqRecord, sPrimaryNumberTag );
    		if( address.empty() )
    		{
    			// try the secondary number
    			address = POSConfig().GetParam( m_AcqRecord, sSecondaryNumberTag );
    			if( address.empty() )
    			{
    				// The terminal profile did not include any numbers!!
    				return 	false;
    			}
    			else
    			{
    				attempts = POSConfig().GetParam( m_AcqRecord, sSecondaryDialAttemptsTag );
    				timeout = POSConfig().GetParam( m_AcqRecord, sSecondaryConnTimeTag );
    			}
    		}
    		else
    		{
    			attempts = POSConfig().GetParam( m_AcqRecord, sPrimaryDialAttemptsTag );
    			timeout = POSConfig().GetParam( m_AcqRecord, sPrimaryConnTimeTag );
    		}
    		// convert address to AT style dial string
    		HypCTransportAddressSet::ConvertDialString( ATPhoneNum, address );
    
    		// convert dial attempt to dial retries ( Addr uses retries, not attempts )
    		int retries = attempts.AsInt();
    		if( retries > 0 )
    		{
    			retries--;
    		}
    		Addr.AddAddress( ATPhoneNum.c_str(), retries, timeout.AsInt()*1000 );
        }
        else
            Addr.AddAddress( address.c_str(), 0 );
	}

    // Check validity of the adress
    if( !Comm.SetDestination( Addr ) )
    {
        return false;
    }

    if( bUseTCPIP )
	{   
        bUseGPRS = POSConfig().IsOptionSet( m_AcqRecord, ACQ_USE_GPRS );
        // setup for TCPIP, use Hypercom TCPIP protocol, 
		// where sent data packets are prefixed with length bytes
		// and received packets are stripped of length bytes
		if( !Comm.SetMode( LINE_TCPIP,
						   PROTO_HYPERCOM_TCPIP,
						   0, bUseGPRS ? "GPRS": "", "" ) )
		{
			// invalid mode
			return false;
		}
	}
	else
	{
        if( bUseHLAN )
        {
            Comm.SetMode( LINE_HLAN_HIGH, PROTO_HLAN, 0, "", "" );
        }
        else
        {
    		// simple dialup with legacy modem mode
    
    		// convert modem mode to hex  
    		uint8_t mmode = BinBcdB( static_cast<uint8_t>(modem.AsInt()) );
    
    		if( !Comm.SetMode( LINE_DIALUP, mmode ) )
    		{
    			// invalid mode
    			return false;
    		}
        }
	}

	return true;
}

//-----------------------------------------------------------------------------
//!
//!      Processes the host response. 
//!
//! \param
//!      TransData       reference to transaction data container
//!
//! \return
//!      result of operation of type HypEHostResult
//!
//! \note
//!
HypEHostResult BasicHost::DoProcessResponse( HypCTransactionData& /*TransData*/ )
{
	return HOST_OK;
}


//-----------------------------------------------------------------------------
//!
//!      Test response options to see if reversal is cleared.
//!      Free the reversal if response option is set to clear.
//!      Perform special processing
//!
//! \param
//!      TransData       reference to transaction data container
//!
//! \return
//!      result of operation, type HypEHostResult
//!
//! \note
//!
HypEHostResult BasicHost::DoPostProcessing( HypCTransactionData& TransData,
											HypEHostResult res ) 
{
	// if no status flags in map, then add them
	if( !TransData.get( TransactionTag::STATUS_FLAGS ) )
	{
		// add status flags to map - nothing set
		HypCOptions opt;
		opt.reset();
		TransData.insert( TransactionTag::STATUS_FLAGS, opt );
	}

	const HypCData* p_settle_type = TransData.get( TransactionTag::SETTLE_TYPE );
	if ( p_settle_type )
	{
		if ( HOST_RESPONSE_TIMEOUT == res && 
			p_settle_type->AsString(  ) != TransactionTag::SETTLE_CLBATCHE &&
			m_HostName == "VISAII" )
		{
			// special processing for VISA settlement
			return HOST_OK;
		}
		else
		{
			return res;
		}
	}
	else
	{
		const HypCData* data = TransData.get( TransactionTag::STATUS_FLAGS );
		HypCOptions* flags = const_cast<HypCOptions*>(static_cast<const HypCOptions*>(data));

		if ( res != HOST_OK && !( (*flags)[TransactionTag::SEND_ADVICE] || (*flags)[TransactionTag::ADJUSTED] ) )
		{
			Transaction().SaveDataOption( TransactionTag::STATUS_FLAGS, TransactionTag::REVERSAL, true );
		}

		if ( !IsAttributeSet( Transaction().TransactionData(), TransactionTag::NOCAPTURE ) && 
			 m_bContactHost )
		{
			const HypCData* pData = TransData.get( TransactionTag::TYPE_NAME );
			if ( pData )
			{
				HString type = pData->AsString();
				// reversed transactions will be deleted later
				// adjust, offline advices will be updated separately
				if ( type != "REVERSAL" && type.substr( 0, 2 ) != "AD" )
				{
					if( !SaveToJournal( TransData ) )
					{
						return HOST_JOURNAL_FAIL;
					}
				}
			}
		}

		return res;	
	}
}


//-----------------------------------------------------------------------------
//!
//!      Saves transaction record to Hypercom host journal
//!
//! \param
//!      TransData       The current transaction data.
//!
//! \return
//!      true for successful, else false
//!
//! \note
//!
bool BasicHost::SaveToJournal( HypCTransactionData& TransData )
{
	bool bRetVal = false;
	HypCJournal *jrn = Transaction().GetJournal(m_HostName.c_str());

	if ( jrn && jrn->Open() )
	{
		DBFieldDescriptor fields;
		fields.push_back( DBFieldDescr( TransactionTag::SETTLE_TYPE, TYPE_STRING, 0 ) );
		jrn->SetExcludedFields( fields );
		if( !jrn->ValidateRecord( TransData ) )
		{
			jrn->FillMissingFields( TransData );
		}
		jrn->SetData( TransData );
		jrn->InsRecord();
		jrn->Close();
		bRetVal = true;
	}
	return bRetVal;
}


//-----------------------------------------------------------------------------
//!
//!      Make sure the Reversal is sent to Host first
//!
//! \return
//!      bool        True  - pre-transaction reversal processing allowed
//!                  False - reversals are not processed for this host
//! \note
//!
bool BasicHost::AllowReversalProcessing()
{
	return true;
}

//-----------------------------------------------------------------------------
//!
//!      delete settled transactions
//!
//! \return
//!      void
//!
//! \note
//!
void BasicHost::DeleteSettled(  )
{
	HypCJournal *m_jrn = Transaction(  ).GetJournal( m_HostName.c_str() );
	HypCTransactionData TransData;
	const HypCData* data;
	HypCOptions* popts = NULL;
	bool deleted = false;
	if ( m_jrn && m_jrn->IsOpen(  ) )
	{
		m_jrn->First(  );
	}
	else
    if ( !( m_jrn && m_jrn->Open(  ) ) )
	{
		return;
	}

	while ( !m_jrn->Eof(  ) )
	{
		m_jrn->GetData( TransData );

		data = TransData.get(TransactionTag::STATUS_FLAGS);
		if ( !( data && ( popts = (HypCOptions*)data ) ) )
		{
			return;
		}

		HypCOptions& flags = *popts;
		if ( flags[TransactionTag::HOST_SETTLED] )
		{
			m_jrn->DelRecord(  );
			deleted = true;
		}
		m_jrn->Next(  );
	}
	m_jrn->Close(  );
}

//-----------------------------------------------------------------------------
//!
//!      Save batch number in configuration
//!
//! \param
//!      pCfg            pointer to the configuration object
//! \param
//!      row             handle to the configuration DB row
//! \param
//!      paramName       name of the parameter to be stored in configuration
//! \param
//!      batch_number    batch number to save
//!
//! \return
//!      Void
//!
//! \note
//!
void BasicHost::SaveBatchNum ( HypCPOSConfig* pCfg, const HYP_CFG_HANDLE row, 
		const char * paramName, const uint64_t batch_number )
{
	HString BatNumStr = HypCString( batch_number );
	if ( BatNumStr.length(  ) < 6 )
	{
		BatNumStr.insert( 0, 6 - BatNumStr.length(  ), '0' );
	}
	pCfg -> SetParam( row, paramName, HypCString( BatNumStr ) );
}

//-----------------------------------------------------------------------------
//!
//!      Generate AUTH Code (2 or 6 digits) and put in transaction data.
//!
//! \param
//!      digitCount      digit count 2 or 6
//! \param
//!      str             where to put authcode ( numeric ASCII )
//!
//! \return
//!      Nothing
//!
//! \note
//!      2 digit AUTH Code is calculated as follows:
//!
//!      first digit = 4
//!      second digit is number between 0 and 7.
//!
void BasicHost::GenerateAuthCode( int digitCount, HString& str )
{
	int number;

	// plant random number seed
	// note: srand() should probably be called on app startup
	srand( time(0) );

	// get a random number
	number = rand();

	// create the 6 digit code
	if ( digitCount == 6 )
	{
		for( int i=0;i<2;i++ )
		{
			// get 3 digits from first number
			str += (number%10)|0x30;
			number/=10;
			str += (number%10)|0x30;
			number/=100;
			str += (number%10)|0x30;

			if( i==1 )
			{
				break;
			}
			// generate 3 more digits
			number = rand();
		}
	}
	else
	{
		str  = "4";
		str += (number%7)|0x30;	// number from 0->7
	}

}

//-----------------------------------------------------------------------------
//!
//!      Returns a string from transaction data
//!
//! \param
//!      TransData       Reference to data map containing transaction data
//! \param
//!      Tag             The name of the lookup atribute
//!
//! \return
//!      A string representation of data, if Tag present, else empty string.
//!      If Tag is HypCCurrency object, it is formated according to Hypercom
//!      message specification - 12 symbols wide, left padding with '0', without
//!      any separators and currency symbols.
//!
//! \note
//!
HString BasicHost::GetTransTag( HypCTransactionData& TransData, const char *Tag )
{
	HString strRetValue;		// Default constructor creates an empty HString
	strRetValue.reserve( 12 );

	const HypCData* pData = TransData.get( Tag );

	if ( pData )
	{
		// Check if field is currency
		if ( pData->GetClassName(  ) == "HypCCurrency" )
		{
			// Converts to string without decimal point
			strRetValue = HypCString( pData->AsInt() );
	
			// Left padding with '0' till width 12
			// This is standard format for amounts for BasicHost
			if( strRetValue.length() < 12 )
			{
				strRetValue.insert( 0, 12 - strRetValue.length(), '0' );
			}
	
			return strRetValue;
		} else
		{
			strRetValue = pData->AsString();
		}
	}
	return strRetValue;
}

//-----------------------------------------------------------------------------
//!
//!      Do reversals processing
//!
//! \param
//!      host            identifier of the host
//!
//! \return
//!      An error code that indicates if the operation was succesful.
//!
//! \note
//!
HypEHostResult BasicHost::ProcessReversals( const char* host )
{
	HypEHostResult res = HOST_OK;
	HypCString type, acquirer;
	const HypCData* data;
	HypCJournal *jrn = Transaction(  ).GetJournal( m_HostName.c_str() );
	HypCTransactionData trans;
	bool deleted = false;
	uint64_t NumReversals( 0 );
	HypCJournal* batch_jrn = Transaction().GetApplication()->GetJournal( JournalTags::BATCH_REC );
	HypCTransactionData BatchData;
	HypCOptions flags;

	// open the journal if it hasn't been open before
	if ( jrn && jrn->IsOpen(  ) )
	{
		jrn->First(  );
	}
	else
	{
		if ( !( jrn && jrn->Open(  ) ) )
		{
			return HOST_JOURNAL_FAIL;
		}
		
		jrn->First(  );
	}

	// go through all transactions
	for ( ; !jrn->Eof(  ); jrn->Next(  ) )
	{
		HypCInt64 *ptr64 = static_cast< HypCInt64 *>( jrn->GetHdrFieldData( TransactionTag::STATUS_FLAGS ) );
		if( !ptr64 )
		{
			continue;
		}
		
		flags = static_cast<uint64_t>(*ptr64 );
		// look only for reversed, not offline and unsettled transactions
		// of the specified acquirer: clean such records
		if ( flags[TransactionTag::REVERSAL] &&
			 !( flags[TransactionTag::SEND_ADVICE] || flags[TransactionTag::HOST_SETTLED] ) )
		{	
		
			jrn->GetData( trans );
			// get acquirer
			data = trans.get( TransactionTag::CARD_ACCEPTOR_NAME );
			if ( data )
			{
				acquirer = data->AsString(  );
			} 
			else
			{
				continue;
				//return HOST_JOURNAL_FAIL;
			}

			if( acquirer.AsString(  ) != host )
			{
				continue;
			}

			trans.insert( TransactionTag::TYPE_NAME, "REVERSAL" );
			if ( ( res = DoTransaction( trans ) ) == HOST_OK )
			{
				NumReversals++;
				jrn->DelRecord(  );
				deleted = true;
			}
			else
			{
				break;
			}
		}

	}

	jrn->Close(  );

	// the following code updates last time reversed transactions count
	// currently, update only during the settlement
	const HypCData* settle = m_pTransaction->GetTransData( )->get( TransactionTag::SETTLE_TYPE );
	if ( settle )
	{
		if ( !( batch_jrn && batch_jrn->Open(  ) ) )
		{
			return HOST_JOURNAL_FAIL;
		}

		// search for the record with a given acquirer
		while ( !batch_jrn->Eof(  ) )
		{
			batch_jrn->GetData( BatchData );
			data = BatchData.get( TransactionTag::CARD_ACCEPTOR_NAME );
			if ( data && m_HostName == data->AsString(  ) )
			{
				// found, update reversal field
				BatchData.insert( TransactionTag::REV_COUNT, HypCInt64( NumReversals ) );
				batch_jrn->SetData( BatchData );
				batch_jrn->UpdRecord(  );
				break;
			}
			
			batch_jrn->Next(  );
		}

		batch_jrn->Close(  );
	}

	return res;
}

//-----------------------------------------------------------------------------
//!
//!      Do adjusts and offlines processing
//!
//! \param
//!      host            the host to connect to
//!
//! \return
//!      An error code that indicates if the operation was succesful.
//!
//! \note
//!
HypEHostResult BasicHost::ProcessAdjustsOfflines( const char* host )
{
	HypEHostResult res = HOST_OK;
	HypCString type, acquirer;
	const HypCData* data = NULL;
	HypCJournal *jrn = Transaction(  ).GetJournal( m_HostName.c_str() );
	uint64_t NumAdjusted( 0 ), NumOfflines( 0 );
	HypCJournal* batch_jrn = Transaction(  ).GetApplication(  )->GetJournal( JournalTags::BATCH_REC );
	bool type_adjust;
	HypCTransactionData BatchData, trans, transCopy;
	HypCOptions flags;

	// open the journal if it hasn't been open before
	if ( jrn && jrn->IsOpen(  ) )
	{
		jrn->First(  );
	}
	else
	{
		if ( !( jrn && jrn->Open(  ) ) )
		{
			return HOST_JOURNAL_FAIL;
		}
	}

	// go through all transactions
	for ( ; !jrn->Eof(  ); jrn->Next(  ) )
	{
		
		HypCInt64 *ptr64 = static_cast< HypCInt64 *>( jrn->GetHdrFieldData( TransactionTag::STATUS_FLAGS ) );
		if( !ptr64 )
		{
			continue;
		}

		flags = static_cast<uint64_t>(*ptr64 );
        
		// look only for offline and adjusted transactions
		// of the specified acquirer
		if ( ( flags[TransactionTag::SEND_ADVICE] || flags[TransactionTag::ADJUSTED] ) ) 
		{


			jrn->GetData( trans );
			// get acquirer
			data = trans.get( TransactionTag::CARD_ACCEPTOR_NAME );
			if ( data )
			{
				acquirer = data->AsString(  );
			} 
			else
			{
				continue;
				//return HOST_JOURNAL_FAIL;
			}

			if( acquirer.AsString(  ) != host )
			{
				continue;
			}

			// save for the future transaction record
			transCopy = trans;

			data = trans.get( TransactionTag::TYPE_NAME );
			if ( data )
			{
				type = data->AsString(  );
			}
			// offline transaction
			if ( flags[TransactionTag::SEND_ADVICE] )
			{
				// update transaction type of the found record
				if ( type.AsString(  ) == "REFUND" )
				{
					trans.insert( TransactionTag::TYPE_NAME, "ADVREFUND" );
				}
				else
				{
					trans.insert( TransactionTag::TYPE_NAME, "ADVSALE" );
				}

				type_adjust = false;
			}
			// adjusted transaction
			else
			{
				if ( type.AsString(  ) == "REFUND" )
				{
					trans.insert( TransactionTag::TYPE_NAME, "ADJREFUND" );
				}
				else
				{
					trans.insert( TransactionTag::TYPE_NAME, "ADJSALE" );
				}

				type_adjust = true;
			}
			// send transaction to the host
			if ( ( res = DoTransaction( trans ) ) == HOST_OK )
			{
				// clear the both flags for the transaction
				transCopy.SaveDataOption( TransactionTag::STATUS_FLAGS, TransactionTag::ADJUSTED, false );
				transCopy.SaveDataOption( TransactionTag::STATUS_FLAGS, TransactionTag::SEND_ADVICE, false );
				jrn->SetData( transCopy );
				jrn->UpdRecord(  );

				if ( type_adjust )
				{
					NumAdjusted++;
				}
				else
				{
					NumOfflines++;
				}
			}
			else
			{
				break;
			}
		}

	}

	jrn->Close(  );

	// the following code updates last time adjusted, offline transactions count
	// currently, update only during the settlement
	const HypCData* settle = m_pTransaction->GetTransData( )->get( TransactionTag::SETTLE_TYPE );
	if ( settle )
	{
		if ( !( batch_jrn && batch_jrn->Open(  ) ) )
		{
			return HOST_JOURNAL_FAIL;
		}

		// search for the record with a given acquirer
		while ( !batch_jrn->Eof(  ) )
		{
			batch_jrn->GetData( BatchData );
			data = BatchData.get( TransactionTag::CARD_ACCEPTOR_NAME );
			if ( data && m_HostName == data->AsString(  ) )
			{
				// found, update fields
				BatchData.insert( TransactionTag::ADJ_COUNT, HypCInt64( NumAdjusted ) );
				BatchData.insert( TransactionTag::ADV_COUNT, HypCInt64( NumOfflines ) );
				batch_jrn->SetData( BatchData );
				batch_jrn->UpdRecord(  );
				break;
			}
			
			batch_jrn->Next(  );
		}

		batch_jrn->Close(  );
	}

	return res;
}

//-----------------------------------------------------------------------------
//!
//!      Perform transaction (with reversals)
//!
//! \param
//!      transaction     reference to transaction requesting the host contact
//!
//! \return
//!      An error code that indicates if the operation was succesful.
//!
//! \note
//!
HypEHostResult BasicHost::PerformTransaction( HypCTransaction& transaction )
{
	SetState ( StartTransaction );
	Notify();

	HypEHostResult res = HOST_OK;
	// set the transaction
	m_pTransaction = &transaction;

	HypCTransactionData& TransData = *m_pTransaction->GetTransData( );

	const HypCData* settle = TransData.get( TransactionTag::SETTLE_TYPE );

	// if settlement, then process reversals only before the first send
	if ( ( !settle || settle->AsString(  ) == TransactionTag::SETTLE_CLBATCH ) && 
		 m_HostName != "VISAII" )
	{
		if ( !IsAttributeSet( Transaction(  ).TransactionData(  ), TransactionTag::NOPREREV ) )
		{
			if( AllowReversalProcessing() )
			{
				res = ProcessReversals( m_HostName.c_str(  ) );
			}
		}
		if ( res == HOST_OK )
		{
			res = ProcessAdjustsOfflines( m_HostName.c_str(  ) );
		}
	}

	if ( res == HOST_OK )
	{
		res = DoTransaction( TransData );
	}

	if ( !settle || settle->AsString(  ) == TransactionTag::SETTLE_CLBATCHE )
	{
		// disconnect, if connected
    	Disconnect(  );
		// clear the transaction
		m_pTransaction = 0;
	}
	return res;
}


//-----------------------------------------------------------------------------
//!
//!      Sets the current system trace number in the transaction data record
//!      and then increments the system trace number.
//!      Uses TransactionTag::STAN
//!
//! \param
//!      TransData       reference to transaction data container
//!
//! \return
//!      Nothing
//!
//! \note
//!
void BasicHost::SetSystemTraceNumber( HypCTransactionData& TransData )
{
	HYP_CFG_HANDLE hCfg =  POSConfig().GetTable( SystemDataTag::SYSTEM_TABLE );

	HString str = POSConfig().GetParam( hCfg, SystemDataTag::SYSTEM_TRACE );

	if( !str.empty() )
	{
		TransData.insert( TransactionTag::STAN,
						  new HypCString(str) );

		// increment the stored system trace number
		// system trace is a 6 digit string 
		// with possible leading zeros
		
		// strip leading zeros
		str.LTrim('0');
		
		HypCInt32 i32( str );
		i32+=1;

		// Sets configuration parameter's value
		POSConfig().SetParam( hCfg, SystemDataTag::SYSTEM_TRACE, i32 );

	}
}

//-----------------------------------------------------------------------------
//!
//!      Sets transaction date & time to current system date & time.
//!      Data is placed in TransactionTag::DATE_TIME
//!
//! \param
//!      TransData       reference to transaction data container
//!
//! \return
//!      Nothing
//!
//! \note
//!
void BasicHost::SetTransactionDateTime( HypCTransactionData& TransData )
{
	HypCDateTime datetime;
	datetime.CurrentTime();
	TransData.insert( TransactionTag::DATE_TIME, datetime );
}

//-----------------------------------------------------------------------------
//!
//!      Sets system time to the time & date in transaction data.
//!      Data is taken from TransactionTag::DATE_TIME and then real time clock 
//!      is set to that time.
//!
//! \param
//!      TransData       reference to transaction data container
//!
//! \return
//!      Nothing
//!
//! \note
//!
void BasicHost::SetSystemDateTime( HypCTransactionData& TransData )
{
	const HypCDateTime* Ptr = 
		static_cast< const HypCDateTime *>( TransData.get( TransactionTag::DATE_TIME ));
	time_t l = static_cast<time_t>(Ptr->AsWord());
	time( &l );
}

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
bool BasicHost::IsAttributeSet( HypCTransactionData& transRecord, int AttributeID )
{
	const HypCData *ptr = transRecord.get( TransactionTag::TRANSACTION_ATTRIBUTES );
	if ( ptr )
	{
		const HypCOptions *pOpt = static_cast< const HypCOptions *>( ptr );
		if( pOpt )
		{
			return pOpt->IsSet( AttributeID );
		}
	}
	return false;
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
void BasicHost::SetAttribute( HypCTransaction& trans, int AttributeID )
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
bool BasicHost::Offline( HypCTransactionData& transRecord )
{
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
bool BasicHost::BelowFloorLimit( HypCTransactionData& transRecord, 
								 HypCPOSConfig& posConfig )
{
	bool bApproved = false;

	// Are floor limits approved for this transaction
	if ( !IsAttributeSet( transRecord, TransactionTag::FLOOR ) )
	{
		return false;
	}

	const HypCData *ptr = transRecord.get( TransactionTag::ISSUER_NAME );

	if( ptr )
	{
		// Get the floor limit amount
		HYP_CFG_HANDLE issRecord = posConfig.FindTableRow( IssuerTag::ISSUER_TABLE,
														   IssuerTag::NAME, 
														   *ptr );
	
		HString str = posConfig.GetParam( issRecord, IssuerTag::FLOOR_LIMIT );

		if( !str.empty() )
		{
			//HypCString Floor = str;
			const HypCData *pData = transRecord.get( TransactionTag::TOTAL_AMOUNT );

			if( pData )
			{
				HypCCurrency Floor( str );
				
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
bool BasicHost::ValidExpirationDate( HypCTransaction& trans, HypCPOSConfig& posConfig )
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
		                               IssuerTag::NAME, *ptr );
	
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

