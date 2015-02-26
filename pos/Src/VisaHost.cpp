//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hyperware Base Application
//      (c) Copyright 2006
//
// File Name:
//      VisaHost.cpp
//
// File Description:
//      Implementation of the Class VisaHost
//
//=============================================================================
#if defined(__GNUC__)
#pragma implementation
#endif

#include <compiler.h>
#include "Visa_Financial.hpp"
#include "Visa_Message.hpp"
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
#include "YemekSepetiTags.h"
#include "VisaHost.hpp"
#include <HypCHostInterface.hpp>

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
VisaHost::VisaHost() :
	BasicHost(  ),
	p_m_VisaMessage( 0 ),
	m_pFinRequestMessage( 0 ),
	m_pSettleRequestMessage( 0 )
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
VisaHost::~VisaHost()
{
	if ( m_pFinRequestMessage )
	{
		delete m_pFinRequestMessage;
	}
	if ( m_pSettleRequestMessage ) 
	{
		delete m_pSettleRequestMessage;
	}
}

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
HypEHostResult VisaHost::DoPreProcessing( HypCTransactionData &TransData )
{
	// set issuer and acquire record handles
	HypCString HostNameStr( HostName() );

	m_AcqRecord = POSConfig().FindTableRow( AcquirerTag::ACQUIRER_TABLE,
		                               AcquirerTag::NAME, HostNameStr );

	if( !m_AcqRecord )
	{
		return 	HOST_INCOMPLETE_TRANS;
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

			// set to ISO response code to APPROVED
			TransData.insert( TransactionTag::ISO_RESPONSE_CODE, "00" );

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

	if ( !SetVisaTransaction( TransData ) )
	{
		m_bContactHost = false;
		return HOST_UNSUPPORTED_TRANSACTION;
	}

	m_bContactHost = true;
	return HOST_OK;
}

//-----------------------------------------------------------------------------
//!
//!		create a specific message object according to type of transaction
//!
//! \param
//!      TransData       transaction record with stored "settlement type" and
//!                      "transaction type" fields
//!
//! \return
//!      true if object created successfully, false - if not
//!
//! \note
//!
bool VisaHost::SetVisaTransaction ( HypCTransactionData &TransData )
{
	const HypCData* p_data = TransData.get( TransactionTag::SETTLE_TYPE ); 
	if ( p_data )
	{
		if ( !m_pSettleRequestMessage ) 
		{
			m_pSettleRequestMessage = new Visa_Settle( this );
		}
		p_m_VisaMessage = m_pSettleRequestMessage->Init( &TransData, p_data->AsString(  ) );

		return true;
	}
	else if ( ( p_data = TransData.get( TransactionTag::TYPE_NAME ) ) != 0 )
	{
		HString ttype = p_data->AsString(  );
		if ( ttype == "SALE CREDIT" || ttype == "REFUND" )
		{
			if ( !m_pFinRequestMessage ) 
			{
				m_pFinRequestMessage = new Visa_Financial();
			}
			p_m_VisaMessage = m_pFinRequestMessage->Init( &TransData );

			return true;
		}
	}
	return false;
}

//-----------------------------------------------------------------------------
//!
//!      Build the Visa packet out of the transaction data
//!
//! \param
//!      TransData       reference to transaction data container
//! \param
//!      pData           pointer to buffer where encoded data is to be placed
//! \param
//!      len             maximum length of encoded data on input, set to actual
//!                      length on output
//!
//! \return
//!      HOST_OK for success else other result for error.
//!
//! \note
//!
HypEHostResult VisaHost::DoEncodeRequest( HypCTransactionData &TransData,
												  unsigned char* const pData,
                                                  size_t& len )
{
	const HypCData* s_type = TransData.get( TransactionTag::SETTLE_TYPE );
	// pass repeating fields only for financial transactions and in settlement header only
	if ( !s_type || s_type->AsString(  ) == TransactionTag::SETTLE_CLBATCH )
	{
		HYP_CFG_HANDLE  termRecord = POSConfig(  ).GetTable( TermConfigTag::TERMINAL_TABLE );
		HString str =  POSConfig(  ).GetParam( termRecord, TermConfigTag::TERM_CONFIG_OPTIONS );
		TransData.insert( TermConfigTag::TERM_CONFIG_OPTIONS, new HypCInt8(str) );

		// for report
		// set the TID for this transaction
		TransData.insert ( TransactionTag::TERMINAL_ID,
						POSConfig().GetParam( m_AcqRecord, AcquirerTag::TERMINAL_ID ) );
		// set the card acceptor id
		TransData.insert ( TransactionTag::CARD_ACCEPTOR_ID,
		POSConfig().GetParam( m_AcqRecord, AcquirerTag::ACCEPTOR_ID ));

		HString AcqID = POSConfig().GetParam( m_AcqRecord, AcquirerTag::ID );
		if ( !AcqID.empty(  ) )
		{
			int MerchRecord = POSConfig().FindTableRow( VisaIITag::TABLE,
				VisaIITag::ACQUIRER_ID, HypCString( AcqID ) );
			if ( MerchRecord )
			{
				TransData.insert( VisaIITag::ACQUIRER_BIN, POSConfig().GetParam( MerchRecord, VisaIITag::ACQUIRER_BIN ) );
				TransData.insert( VisaIITag::MERCH_NUMBER, POSConfig().GetParam( MerchRecord, VisaIITag::MERCH_NUMBER ) );
				TransData.insert( VisaIITag::STORE_NUM, POSConfig().GetParam( MerchRecord, VisaIITag::STORE_NUM ) );
				TransData.insert( VisaIITag::TERM_NUM, POSConfig().GetParam( MerchRecord, VisaIITag::TERM_NUM ) );
				TransData.insert( VisaIITag::TERMINAL_SERIAL_NUM, POSConfig().GetParam( MerchRecord, VisaIITag::TERMINAL_SERIAL_NUM ) );
				TransData.insert( VisaIITag::MERCH_CURRENCY, POSConfig().GetParam( MerchRecord, VisaIITag::MERCH_CURRENCY ) );
				TransData.insert( VisaIITag::MERCH_COUNTRY, POSConfig().GetParam( MerchRecord, VisaIITag::MERCH_COUNTRY ) );
				TransData.insert( VisaIITag::MERCH_CITY, POSConfig().GetParam( MerchRecord, VisaIITag::MERCH_CITY ) );
				TransData.insert( VisaIITag::TIME_ZONE_DIFF, POSConfig().GetParam( MerchRecord, VisaIITag::TIME_ZONE_DIFF ) );
				TransData.insert( VisaIITag::MERCH_CAT, POSConfig().GetParam( MerchRecord, VisaIITag::MERCH_CAT ) );
				TransData.insert( VisaIITag::MERCH_NAME, POSConfig().GetParam( MerchRecord, VisaIITag::MERCH_NAME ) );
				TransData.insert( VisaIITag::MERCH_CITY_STATE, POSConfig().GetParam( MerchRecord, VisaIITag::MERCH_CITY_STATE ) );
				TransData.insert( VisaIITag::MERCH_LOCATION, POSConfig().GetParam( MerchRecord, VisaIITag::MERCH_LOCATION ) );

				// CLBATCH specific
				TransData.insert( VisaIITag::AGENT_BIN, POSConfig().GetParam( MerchRecord, VisaIITag::AGENT_BIN ) );
				TransData.insert( VisaIITag::AGENT_CHAIN_NUM, POSConfig().GetParam( MerchRecord, VisaIITag::AGENT_CHAIN_NUM ) );
			}
		}
	}

	// set the STAN for this transaction
	SetSystemTraceNumber( TransData );

	// get message buffer and send to host
	if ( p_m_VisaMessage->CreateMessagePacket( ( char * ) pData, len ) )
	{
		return HOST_OK;
	}
	else
	{
		char buf[128];
		sprintf( buf, "Encoding (Visa): field %d has not been moved", p_m_VisaMessage->GetNotMovedBit(  ) );
		m_pHostInterface->SetErrDesc( buf );
		return HOST_INCOMPLETE_TRANS;
	}
}


//-----------------------------------------------------------------------------
//!
//!      Decodes the host's response
//!
//! \param
//!      TransData       reference to transaction data container
//! \param
//!      pData           pointer to buffer of data to decode
//! \param
//!      len             length of decoded data
//!
//! \return
//!      HOST_OK for success else other result for error.
//!
//! \note
//!
HypEHostResult VisaHost::DoDecodeResponse( HypCTransactionData &TransData, 
                                                   unsigned char* const pData,
                                                   size_t len )
{
	if ( p_m_VisaMessage->DecodeMessagePacket( reinterpret_cast<char*>( pData ), len ) )
	{
		const HypCData* settle = TransData.get( TransactionTag::SETTLE_TYPE );
		SetResponseText( 0, settle ? true : false );
		return HOST_OK;
	}
	else
	{
		const HypCData* p_err_data = TransData.get( "ERR_MSG" );
		if ( p_err_data ) 
		{
			m_pHostInterface->SetErrDesc( p_err_data->AsString(  ).c_str(  ) );
		}
		return HOST_FAIL;
	}
}

//-----------------------------------------------------------------------------
//!
//!      Set the response text for given code. Test is placed in transaction
//!      data with tag TransactionTag::RESPONSE_TEXT
//!
//! \param
//!      pRspCode        two character ISO repsonse code
//! \param
//!      settle          whether the current operation is settlement
//!
//! \return
//!      None
//!
//! \note
//!
void VisaHost::SetResponseText( const char *pRspCode, bool settle )
{
	HString msg = "";
	const HypCData* ptr;
	if ( !pRspCode )
	{
		ptr = Transaction(  ).TransactionData(  ).get( TransactionTag::RESPONSE_TEXT );
		if ( ptr )
		{
			msg = ptr->AsString(  );
		}
	}
	else
	if ( pRspCode[0]=='0' && pRspCode[1]=='0' )
	{
		msg = "Approved";
	}
	if ( settle )
	{
		ptr = Transaction(  ).TransactionData(  ).get( TransactionTag::CARD_ACCEPTOR_NAME );
	}
	if ( settle )
	{
		Transaction(  ).TransactionData(  ).insert( 
			( HString( TransactionTag::RESPONSE_TEXT ) + "_" + m_HostName ).c_str(  ), msg.c_str(  ) );
		Transaction(  ).TransactionData(  ).erase( TransactionTag::RESPONSE_TEXT );
	}
	else
	{
		Transaction(  ).TransactionData(  ).insert(	TransactionTag::RESPONSE_TEXT, msg );
	}
}

//-----------------------------------------------------------------------------
//!
//!      Checks if the response code indicates approval. The response
//!      code is excpected in TransactionTag::ISO_RESPONSE_CODE
//!
//! \param
//!      TransData       reference to transction data container
//!
//! \return
//!      true if code indicates an approval, else false
//!
//! \note
//!
HypEHostResult VisaHost::IsHostApproved( HypCTransactionData& TransData )
{
	const HypCData* ptr = TransData.get( TransactionTag::ISO_RESPONSE_CODE );
	
	if ( !ptr )
	{
		return HOST_INCOMPLETE_TRANS;
	}
	// if no value present, it means no response from host
	if ( ptr->AsString(  ) == "00" )
	{
		return HOST_OK;
	}
	else
	{
		return HOST_FAIL;
	}
}

//-----------------------------------------------------------------------------
//!
//!      process settlement action
//!
//! \return
//!      HOST_OK - if transaction succeeded
//!      HOST_INCOMPLETE_TRANS - 
//!        1. if amount doesn't match even after processing of settlement trailer
//!        2. if "status flags" field not found in journal
//!      HOST_JOURNAL_FAIL - if couldn't open the journal
//!
//! \note
//!
HypEHostResult VisaHost::DoSettle()
{
	HypEHostResult res;
	const HypCData* data;
	HypCOptions* popts;
	HYP_CFG_HANDLE tableAcq, rowAcq = 0;
	HypCString Acq, Num;
	HypCPOSConfig* pCfg = static_cast <HypCPOSConfig*> ( &Transaction(  ).POSConfig(  ) );
	uint64_t CurBatNum( 1 ), NextBatNum( 2 );
	HString BatNumStr;
	HypCJournal* batch_jrn = Transaction(  ).GetApplication(  )->GetJournal( JournalTags::BATCH_REC );
	HypCTransactionData BatchData, TransCopy;
	HypCTransactionData& TransData = Transaction(  ).TransactionData(  );
	bool batch_new = true;
	HypCDateTime ct;

	// delete previously settled transactions from journal
	DeleteSettled(  );

	// get the current and the next batch number from configuration
	tableAcq = pCfg -> GetTable( AcquirerTag::ACQUIRER_TABLE );
	if ( tableAcq ) 
	{
		rowAcq = pCfg -> GetTableRow( tableAcq, HypCPOSConfig::FIRST );
							
		while ( rowAcq &&  ( (Acq = pCfg -> GetParam( rowAcq, AcquirerTag::ID )) != ""  ) )
		{
			if ( ( Acq = pCfg -> GetParam( rowAcq, AcquirerTag::NAME )) != "" )
			{
				if ( m_HostName == Acq )
				{
					// get the current batch number from configuration DB
					if ( ( Num = pCfg -> GetParam( rowAcq, AcquirerTag::BATCH_CURRENT ) ) != "" )
					{
						CurBatNum = Num.AsInt(  );
					}
					// get the next batch number from configuration DB
					if ( ( Num = pCfg -> GetParam( rowAcq, AcquirerTag::BATCH_NEXT ) ) != "" )
					{
						NextBatNum = Num.AsInt(  );
					}
					// ensure, that we now have valid current batch number
					if ( 0 == CurBatNum || 999999 == CurBatNum ) 
					{
						if ( 0 == NextBatNum || 999999 == NextBatNum )
						{
							CurBatNum = 1;
							NextBatNum = 2;
						}
						else
						{
							CurBatNum = NextBatNum;
							NextBatNum ++;
						}
					}
					// left padding with zeroes, if neccesary
					BatNumStr = HypCString( CurBatNum );
					if( BatNumStr.length() < 6 )
					{
						BatNumStr.insert(  0, 6 - BatNumStr.length(), '0' );
					}
					// make the current batch number available for packet encoder
					TransData.insert( TransactionTag::BATCH_NUMBER,  BatNumStr.c_str(  ) );

					break;
				}
			}
			rowAcq = pCfg -> GetTableRow( tableAcq, HypCPOSConfig::NEXT );
		}
	}

	// find batch record for the current acquirer in the batch records DB
	if ( !batch_jrn->Open(  ) )
	{
		return HOST_JOURNAL_FAIL;
	}

	// prepare settlement dates
	ct.CurrentTime(  );

	// search for the record with a given acquirer
	while ( !batch_jrn->Eof(  ) )
	{
		batch_jrn->GetData( BatchData );
		data = BatchData.get( TransactionTag::CARD_ACCEPTOR_NAME );
		if ( data && m_HostName == data->AsString(  ) )
		{
			// found, update last settlement attempt field
			BatchData.insert( TransactionTag::LAST_SETL_ATT, ct );
			batch_jrn->SetData( BatchData );
			batch_jrn->UpdRecord(  );
			batch_new = false;
			break;
		}
		
		batch_jrn->Next(  );
	}
	// record with a given acquirer not found, create it
	if ( batch_new )
	{
		BatchData.clear(  );
		BatchData.insert( TransactionTag::CARD_ACCEPTOR_NAME, new HypCString( m_HostName.c_str() ) );
		BatchData.insert( TransactionTag::LAST_SETL_ATT, new HypCDateTime( ct ) );
		if( !batch_jrn->ValidateRecord( BatchData ) )
		{
			batch_jrn->FillMissingFields( BatchData );
		}
		batch_jrn->SetData( BatchData );
		batch_jrn->InsRecord(  );
	}
	batch_jrn->Close(  );

	// clear previous attributes
	TransData.insert( TransactionTag::TRANSACTION_ATTRIBUTES, new HypCOptions(  ) );

	// attributes for settlement request
	SetAttribute( Transaction(  ), TransactionTag::NOACCT );
	SetAttribute( Transaction(  ), TransactionTag::NORECEIPT );
	SetAttribute( Transaction(  ), TransactionTag::NOCAPTURE );
	SetAttribute( Transaction(  ), TransactionTag::PREADV );
	SetAttribute( Transaction(  ), TransactionTag::SETTLE );
	SetAttribute( Transaction(  ), TransactionTag::NOINPUT );
	SetAttribute( Transaction(  ), TransactionTag::BATPEND );
	SetAttribute( Transaction(  ), TransactionTag::NOPINDSP );

	// send settlement request
	TransData.insert( TransactionTag::SETTLE_TYPE,  TransactionTag::SETTLE_CLBATCH ) ;

	res = PerformTransaction( Transaction(  ) );

	// communication error, abort
	if ( res != HOST_OK )
	{
		return res;
	}
	// if bad host result, cancel
	if ( IsHostApproved( TransData ) == HOST_FAIL )
	{
		return HOST_FAIL;
	}

	// send settlement parameters request
	TransData.insert( TransactionTag::SETTLE_TYPE, TransactionTag:: SETTLE_CLTERM ) ;

	res = PerformTransaction( Transaction(  ) );

	// communication error, abort
	if ( res != HOST_OK )
	{
		return res;
	}
	// if bad host result, cancel
	if ( IsHostApproved( TransData ) == HOST_FAIL )
	{
		return HOST_FAIL;
	}

	// save transaction properties for settlement trailer
	TransCopy = TransData;

	HypCJournal *jrn = Transaction(  ).GetJournal( m_HostName.c_str() );
	bool prev_open = jrn->IsOpen(  );
	bool bres = prev_open || jrn->Open(  );	

	if ( bres )
	{
		if ( prev_open )
		{
			jrn->First(  );
		}
		// send to host all unsettled transactions
		while ( !jrn->Eof(  ) )
		{
			//TransData.clear();
			jrn->GetData( TransData );

			data = TransData.get( TransactionTag::STATUS_FLAGS );
			if ( !( data && ( popts = (HypCOptions*)data ) ) )
			{
				if ( !prev_open )
				{
					jrn->Close(  );
				}
				return HOST_INCOMPLETE_TRANS;
			}

			HypCOptions& flags = *popts;
			if ( !( flags[TransactionTag::HOST_SETTLED] || flags[TransactionTag::REVERSAL] ) )
			{
				// next settlement phase
				TransData.insert( TransactionTag::SETTLE_TYPE,  TransactionTag::SETTLE_RUPLOAD );

				// unspecified mode
				TransData.insert( TransactionTag::POS_ENTRY_MODE, "000" );

				// clear previous attributes
				TransData.insert( TransactionTag::TRANSACTION_ATTRIBUTES, new HypCOptions(  ) );

				// make the current batch number available for packet encoder
				TransData.insert( TransactionTag::BATCH_NUMBER,  BatNumStr.c_str(  ) );

				// set attributes for batch upload
				SetAttribute( Transaction(  ), TransactionTag::NOCAPTURE );
				SetAttribute( Transaction(  ), TransactionTag::SETTLE );
				SetAttribute( Transaction(  ), TransactionTag::NOINPUT );

				// clone & copy STAN
				TransData.insert( TransactionTag::ORIGINAL_STAN, TransData.get( TransactionTag::STAN )->Clone() );

				// send previously stored transaction to the host
				res = PerformTransaction( Transaction(  ) );

				// communication error
				if ( res != HOST_OK || IsHostApproved( TransData ) == HOST_FAIL )
				{
					if ( !prev_open )
					{
						jrn->Close(  );
					}

					if ( res == HOST_OK )
					{
						return HOST_FAIL;
					}
					else
					{
						return res;
					}
				}
			}
			jrn->Next(  );
		}
		if ( !prev_open )
		{
			jrn->Close(  );
		}
	}
	else
	{
		return HOST_JOURNAL_FAIL;
	}

	// restore transaction attributes
	TransData = TransCopy;

	SetAttribute( Transaction(  ), TransactionTag::BATPEND );

	// send settlement trailer
	TransData.insert( TransactionTag::SETTLE_TYPE,  TransactionTag::SETTLE_CLBATCHE );

	res = PerformTransaction( Transaction(  ) );
	// communication error, abort
	if ( res != HOST_OK )
	{
		return res;
	}
	
	// if amounts don't match
	if ( IsHostApproved( TransData ) == HOST_OK )
	{
		SetTransactionDateTime( TransData );
	}
	else
	{
		return HOST_FAIL;
	}
	
	// update batch numbers in DB
	CurBatNum = NextBatNum;
	if ( 999999 == NextBatNum )
	{
		NextBatNum = 1;
	}
	else
	{
		NextBatNum ++;
	}
	SaveBatchNum( pCfg, rowAcq, AcquirerTag::BATCH_CURRENT, CurBatNum );
	SaveBatchNum( pCfg, rowAcq, AcquirerTag::BATCH_NEXT, NextBatNum );

	// update last successful settlement attempt field in the batch records DB
	if ( !batch_jrn->Open(  ) )
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
			// found, update last successful settlement attempt field
			BatchData.insert( TransactionTag::LAST_SETL_SUCC, ct );
			batch_jrn->SetData( BatchData );
			batch_jrn->UpdRecord(  );
			break;
		}
		
		batch_jrn->Next(  );
	}
	batch_jrn->Close(  );

	return res;
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
bool VisaHost::AllowReversalProcessing()
{
	return false;
}

