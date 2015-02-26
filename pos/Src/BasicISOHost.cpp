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
//      Implementation of the Class BasicISOHost
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
#include <HypCHostInterface.hpp>
#include "YemekSepetiTags.h"
#include "BasicISOHost.hpp"
#include "ISO8583_Sale.hpp"
#include "ISO8583_Auth.hpp"
#include "ISO8583_Refund.hpp"
#include "ISO8583_Settle.hpp"
#include "ISO8583_BatchUpload.hpp"
#include "ISO8583_STrailer.hpp"
#include "ISO8583_Reversal.hpp"
#include "ISO8583_Adjust.hpp"
#include "ISO8583_Offline.hpp"


//=============================================================================
// Public defines and typedefs
//=============================================================================

// messages associated with host responses
const BasicISOHost::RESPONSE_TEXT BasicISOHost::RspText[] = 
{
	// "00"
	{
	"00",
	"APPROVAL      authno",
	},

	// "01"
	{
		"01",
		" PLEASE CALL        ",
	},
	// "02"
	{
		"02",
		" REFERRAL     authno",
	},
	// "03"
	{
		"03",
		"ERR-CALL HELP-SN    ",
	},
	// "04"
	{
		"04",
		"    PICKUP CARD     ",
	},
	// "05"
	{
		"05",
		"DO NOT HONOUR       ",
	},
	// "08"
	{
		"08",
		"APPROVAL      authno",
	},
	// "12"
	{
		"12",
		"ERR-CALL HELP-TR    ",
	},
	// "13"
	{
		"13",
		"ERR-CALL HELP-AM    ",
	},
	// "14"
	{
		"14",
		"ERR-CALL HELP-RE    ",
	},
	// "19"
	{
		"19",
		"RE-ENTER TRANSACTION",
	},
	// "25"
	{
		"25",
		"ERR-CALL HELP-NT    ",
	},
	// "30"
	{
		"30",
		"ERR-CALL HELP-FE    ",
	},
	// "31"
	{
		"31",
		"CALL HELP - NS      ",
	},
	// "41"
	{
		"41",
		"PLEASE CALL     - LC",
	},
	// "43"
	{
		"43",
		"PLEASE CALL     - CC",
	},
	// "51"
	{
		"51",
		"    DECLINED        ",
	},
	// "54"
	{
		"54",
		"  EXPIRED CARD      ",
	},
	// "55"
	{
		"55",
		"  INCORRECT PIN     ",
	},
	// "58"
	{
		"58",
		"INVALID TRANSACTION ",
	},
	// "76"
	{
		"76",
		"ERR-CALL HELP-DC    ",
	},
	// "77"
	{
		"77",
		" RECONCILE ERROR    ",
	},
	// "78"
	{
		"78",
		"TRANS. NOT FOUND    ",
	},
	// "79"
	{
		"79",
		"   DECLINED - CVV2  ",
	},
	// "80"
	{
		"80",
		"BAD BATCH NUMBER    ",
	},
	// "82"
	{
		"82",
		"NO CLOSED SOC SLOTS ",
	},
	// "83"
	{
		"83",
		"NO SUSP. SOC SLOTS  ",
	},
	// "85"
	{
		"85",
		" RECEIPT NOT FOUND  ",
	},
	// "89"
	{
		"89",
		"BAD TERMINAL ID.    ",
	},
	// "91"
	{
		"91",
		"ERR-CALL HELP-NA    ",
	},
	// "94"
	{
		"94",
		"ERR-CALL HELP-SQ    ",
	},
	// "95"
	{
		"95",
		"BATCH TRANSFER, WAIT",
	},
	// "96"
	{
		"96",
		"ERR-CALL HELP-SE    ",
	},
	// "AA"
	{
		"AA",
		"CARD CAP TYPE INVLD ",
	},
	// "aa"
	{
		"aa",
		"CARD CAP TYPE INVLD ",
	},
	// "RB"
	{
		"RB",
		"ERR-CALL HELP-DESK  ",
	},
	// "EB"
	{
		"EB",
		"ERR-BAD BIO-RESPONSE",
	},
	// "NB"
	{
		"NB",
		"INV BAL/SETL        ",
	},
	// "BH"
	{
		"BH",
		"CALL HELP-BAD HOST",
	},
	// "BD"
	{
		"BD",
		"BUSY. DAY BALANCING ",
	},
	// "BB"
	{
		"BB",
		"BATCH BALANCING     ",
	},
	// "UN"
	{
		"UN",
		"ERROR - WRONG TRAN  ",
	},
	// "LC"
	{
		"LC",
		"PLEASE TRY AGAIN -LC",
	},
	// "CE"
	{
		"CE",
		"PLEASE TRY AGAIN -CE",
	},
	// "NC"
	{
		"NC",
		" NMS CALL COMPLETE  ",
	},
	// "TO"
	{
		"TO",
		"PLEASE TRY AGAIN -TO",
	},
	// "ND"
	{
		"ND",
		"PLEASE TRY AGAIN -ND",
	},
	// "**"
	{
		"**",
		"ERROR - INVLD 39  rr",
	}
};

//! checking host response for code "00" & "08"(approved)
#define HOST_APPROVED(data)		(GetResponseCode( data ) == RspText[0].code	\
								|| GetResponseCode( data ) == RspText[6].code)
//! checking host response for code "95" (Reconcile error, Batch upload started)
#define BATCH_UPLOAD(data)		(GetResponseCode( data ) == RspText[31].code)
//! checking host response for code "80" (Batch number not found)
#define BAD_BATCH_NUMBER(data)	(GetResponseCode( data ) == RspText[24].code)

//-----------------------------------------------------------------------------
//!
//!      Constructor
//!
//! \return
//!      void
//!
//! \note
//!
BasicISOHost::BasicISOHost() :
	BasicHost(),
	m_ISO8583Trans(0)
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
BasicISOHost::~BasicISOHost()
{
	if( m_ISO8583Trans )
	{
		delete m_ISO8583Trans;
		m_ISO8583Trans = NULL;
	}
}

//-----------------------------------------------------------------------------
//!
//!      Build the ISO8583 packet out of the transaction data
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
HypEHostResult BasicISOHost::DoEncodeRequest( HypCTransactionData &TransData,
												  unsigned char* const pData,
                                                  size_t& len )
{
	const HypCData* pDataPtr = NULL;
	// clear any previous request
	m_ISO8583RequestMessage.ResetMessage();
	
	// assume POS condition code is 00
	TransData.insert ( TransactionTag::POS_CONDITION_CODE,
					   "00" );

	// set the NII for this transaction
	TransData.insert ( TransactionTag::NII,
					   POSConfig().GetParam( m_AcqRecord,AcquirerTag::NII ) );

	// set the TID for this transaction
	TransData.insert ( TransactionTag::TERMINAL_ID,
					   POSConfig().GetParam( m_AcqRecord, AcquirerTag::TERMINAL_ID ) );

	// set the STAN for this transaction
	SetSystemTraceNumber( TransData );

	if( !TransData.get( TransactionTag::SETTLE_TYPE ) )
	{
		// get the account id, if was not retrieved earlier from pinpad
		pDataPtr = TransData.get( TransactionTag::ACCOUNT_ID );
	
		// if we do not have an account id, get default
		if ( !pDataPtr )
		{
			// get the issuer record
			if( !(pDataPtr =  TransData.get( TransactionTag::ISSUER_NAME )) )
			{
				m_pHostInterface->SetErrDesc( "Issuer not found" );
				return 	HOST_INCOMPLETE_TRANS;
			}

			TransData.insert ( TransactionTag::ACCOUNT_ID,
							   POSConfig().GetParam( m_IssRecord, IssuerTag::DEFAULT_ACCOUNT_ID ) );
		}
	}

	// set the card acceptor id
	TransData.insert ( TransactionTag::CARD_ACCEPTOR_ID,
	   POSConfig().GetParam( m_AcqRecord, AcquirerTag::ACCEPTOR_ID ));

	
	// prepare private fields
	PreparePrivateFields( TransData );


	// get the NII
	pDataPtr = TransData.get( TransactionTag::NII );

	if( pDataPtr )
	{
		HString str=pDataPtr->AsString();

		unsigned int i;
		// change leading zeros to spaces so AsWord() below will work
		for( i = 0; i < str.length(  ); i++)
		{
			if( str[i] == '0' )
			{
				str[i] = ' ';
			}
			else
			{
				break;
			}
		}
		HypCString Str(str);
		m_ISO8583RequestMessage.SetDestAddr( static_cast<uint16_t>(Str.AsWord()));

	}
	else
	{
		m_pHostInterface->SetErrDesc( "NII field not found" );
		return HOST_INCOMPLETE_TRANS;
	}

	// build the ISO8583 message
	if( !m_ISO8583Trans->BuildTransaction( TransData,
										   m_ISO8583RequestMessage,
										   HypCISO8583_Transaction::Request,
										   pData, len ) )
	{
		const HypCData* p_err_data = TransData.get( "ERR_MSG" );
		if ( p_err_data ) 
		{
			m_pHostInterface->SetErrDesc( p_err_data->AsString(  ).c_str(  ) );
		}
		return 	HOST_INCOMPLETE_TRANS;
	}

	return HOST_OK;

}


//-----------------------------------------------------------------------------
//!
//!      Decodes the incoming ISO 8583 buffer
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
HypEHostResult BasicISOHost::DoDecodeResponse( HypCTransactionData &TransData, 
                                                   unsigned char* const pData,
                                                   size_t len )
{
	
	HypCTransactionData ResponseData;
	const HypCData* settle = TransData.get( TransactionTag::SETTLE_TYPE );

	if( !m_ISO8583ResponseMessage.SetMessagePacket(  pData, len ) )
	{
		m_pHostInterface->SetErrDesc( "Invalid packet" );
		// we have an invalid packet
		return HOST_FAIL;
	}

	// Check if an NMS Message
	if( 0x68 == m_ISO8583ResponseMessage.GetTPDUId( ) )
	{
        const char strRespText[] = "91";
		// Set to Host Not Available Response
		TransData.insert( TransactionTag::ISO_RESPONSE_CODE,
					   strRespText );

		SetResponseText( strRespText, settle ? true : false );
		
		// Response is Done
		return HOST_OK;
	}

	// Check if ISO Format Message
	if( 0x60 != m_ISO8583ResponseMessage.GetTPDUId( ) )
	{
		// Not ISO format, wait for another response
		return HOST_RESPONSE_CONTINUE;
	}


	// make sure response message type is request message type + 10
	ISO8583_MsgType mt = m_ISO8583ResponseMessage.GetMessageType( );

	if ( mt != ( m_ISO8583RequestMessage.GetMessageType ( ) + 0x10 ) )
	{
		// wait for another response
		return HOST_RESPONSE_CONTINUE;
	}


	// parse the ISO8583 message
	if( !m_ISO8583Trans->BuildTransaction( ResponseData, m_ISO8583ResponseMessage,
										   HypCISO8583_Transaction::Response,
										   pData, len ) )
	{
		const HypCData* p_err_data = TransData.get( "ERR_MSG" );
		if ( p_err_data ) 
		{
			m_pHostInterface->SetErrDesc( p_err_data->AsString(  ).c_str(  ) );
		}
		// parse error, one or more required bits not present
		return HOST_FAIL;	
		// should we wait for another one until timeout??
	}

	// Parse private fields 62-63
	ProcessPrivateFields( ResponseData );

	// move reponse data into transaction record as required

	// check if date & time present
	const HypCData* pDataPtr = ResponseData.get( TransactionTag::DATE_TIME );

	// if we have date & time from host
	if ( pDataPtr )
	{
		// check if we ignore host time
		if( POSConfig().IsOptionSet( m_AcqRecord,
									 ACQ_IGNORE_HOST_TIME ) )
		{
			// ignore host time , set transaction time to current
			SetTransactionDateTime( TransData );
			
			// remove time from response so it will not get copied into
			// transaction data later
			ResponseData.erase( TransactionTag::DATE_TIME );
		}	
		else	// use time from host
		{	
			// Are we allowed to use host time for this transaction?
			const HypCData* ptr = TransData.get( TransactionTag::TRANSACTION_ATTRIBUTES );
			if ( ptr )
			{
				const HypCOptions *pOpt = static_cast<const HypCOptions *>( ptr );
				if( pOpt )
				{
					if( !pOpt->IsSet( TransactionTag::NOTIME ) )
					{
						// if got approved code , go ahead an update time
						if ( HOST_APPROVED( ResponseData ) )
						{
							SetSystemDateTime( ResponseData );
						}
					}
				}
			}
		}			
	}				
	

	// copy all matching fields from response data to transaction data
	if( !ResponseData.empty() )
	{
		ResponseData.rewind();
		do 
		{
			TransData.insert( ResponseData.index().c_str(), ResponseData.data()->Clone() );		
		} 
		while ( ResponseData.next() );
	}
		
	const HypCData* ptr = TransData.get( TransactionTag::ISO_RESPONSE_CODE );

	if ( ptr ) 
	{
		SetResponseText( ptr->AsString(  ).c_str(  ), settle ? true : false );	
	}
	
	return HOST_OK;
}

//-----------------------------------------------------------------------------
//!
//!      Creates the needed HypCISO8583_Transaction object based on
//!      transaction type. Pointer to object is placed in m_ISO8583Trans.
//!
//! \param
//!      TransData       transaction record
//!
//! \return
//!      true if HypCISO8583_Transaction object created successfully, else false
//!
//! \note
//!
bool BasicISOHost::SetISO8583Transaction ( HypCTransactionData &TransData )
{
	HString transStr;

	if( m_ISO8583Trans )
	{
		delete m_ISO8583Trans;
		m_ISO8583Trans = 0;
	}
	const HypCData* ptr = TransData.get( TransactionTag::SETTLE_TYPE ); 
	if ( ptr )
	{
		transStr = ptr->AsString(  );

		if ( transStr == TransactionTag::SETTLE_CLBATCH )
		{
			m_ISO8583Trans = new ISO8583_Settle;
		}
		else if ( transStr == TransactionTag::SETTLE_RUPLOAD )
		{
			m_ISO8583Trans = new ISO8583_BatchUpload;
		}
		else if ( transStr == TransactionTag::SETTLE_CLBATCHE )
		{
			m_ISO8583Trans = new ISO8583_STrailer;
		}
		else
		{
			return false;
		}

		return true;
	}
	else if ( ( ptr = TransData.get( TransactionTag::TYPE_NAME ) ) != 0 )
	{
		transStr = ptr->AsString();
		
		if( transStr == "SALE CREDIT" || transStr == "SALE DEBIT" )
		{
			m_ISO8583Trans = new ISO8583_Sale;
		}
		else if ( transStr == "REFUND" )
		{
			m_ISO8583Trans = new ISO8583_Refund;
		}
		else if ( transStr == "AUTH" )
		{
			m_ISO8583Trans = new ISO8583_Auth;
		}
		else if ( transStr == "REVERSAL" )
		{
			m_ISO8583Trans = new ISO8583_Reversal;
		}
		else if ( transStr == "ADJSALE" )
		{
			m_ISO8583Trans = new ISO8583_Adjust( true );
		}
		else if ( transStr == "ADJREFUND" )
		{
			m_ISO8583Trans = new ISO8583_Adjust( false );
		}
		else if ( transStr == "ADVSALE" )
		{
			m_ISO8583Trans = new ISO8583_Offline( true );
		}
		else if ( transStr == "ADVREFUND" )
		{
			m_ISO8583Trans = new ISO8583_Offline( false );
		}
		else
		{
			return false;
		}
				
		return true;
	}
	return false;
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
void BasicISOHost::SetResponseText( const char *pRspCode, bool settle )
{
// use a table of text here for now, eventually this data may come
// from the POSConfig object - will have to determine later
	bool found = false;
	HString s1,text;
	size_t index = 0;
	const HypCData* ptr;

	if ( pRspCode )
	{
		for( unsigned int i = 0; i < sizeof (RspText)/sizeof(RESPONSE_TEXT);i++)
		{
			s1 = RspText[i].code;

			if( s1 == pRspCode )
			{
				text = RspText[i].text;
				found = true;
				break;
			}
		}
		
		if( !found )
		{
			text = "Resp not found: rr";
		}

		// Substitute any special fields in the response text
		if( ( index = text.find("authno") ) != HString::npos )
		{
			// replace with spaces first
			text.replace( index, 6, "      " );

			ptr = Transaction().TransactionData().get( TransactionTag::AUTH_ID );

			if( ptr )
			{
				// put in auth id
				text.replace( index, ptr->AsString().length(), ptr->AsString().c_str() );
			}

		}

		// Substitute any special fields in the response text
		if( ( index = text.find("rr") ) != HString::npos )
		{
			text.replace( index, 2, pRspCode );
		}
	}
	else
	{
		text = "FAILED";
	}

	if ( settle )
	{
		ptr = Transaction(  ).TransactionData(  ).get( TransactionTag::CARD_ACCEPTOR_NAME );
	}
	if ( settle )
	{
		Transaction(  ).TransactionData(  ).insert( 
			( HString( TransactionTag::RESPONSE_TEXT ) + "_" + m_HostName ).c_str(  ), text.c_str(  ) );
	}
	else
	{
		Transaction(  ).TransactionData(  ).insert(
				TransactionTag::RESPONSE_TEXT, text.c_str(  ) );
	}
}

//-----------------------------------------------------------------------------
//!
//!      Gets the response code. The response code is excpected in TransactionTag::ISO_RESPONSE_CODE
//!
//! \param
//!      TransData       reference to transction data container
//!
//! \return
//!      A result string comprised response code 
//!
//! \note
//!
const HString BasicISOHost::GetResponseCode( HypCTransactionData& data )
{
	return HString( data.get( TransactionTag::ISO_RESPONSE_CODE )->AsString() );
}

//-----------------------------------------------------------------------------
//!
//!      Formats Bit63 field according to Hypercom message specification:
//!      Two byte BCD encoded length of TableID and field itself
//!      Two byte Table ID
//!      Field data
//!      All this data is appended to result string
//!
//! \param
//!      result          String to which, total length, Table ID and data itself
//!                      will be added
//! \param
//!      TableID         Bit63 table/field identificator according to Hypercom
//!                      message specification.
//! \param
//!      TransData       reference to data map containing transaction data
//!
//! \return
//!      A reference to result string
//!
//! \note
//!
HString& BasicISOHost::PrepareB63Field( HString& result, HString TableID, HString field )
{
	char pBcdLen[2];
	int len = TableID.length() + field.length();

	// Puts BCD hundreds
	uint8_t hundreds = static_cast<uint8_t>( len / 100 );
	*pBcdLen = hundreds;

	// Puts BCD tens
    *( pBcdLen + 1 ) = BinBcdB( static_cast<uint8_t>( len % 100 ) );

	// Adds BCD lengths to result
	result.append( pBcdLen, sizeof( pBcdLen ) );

	result += TableID;
	result += field;

	return result;
}

//-----------------------------------------------------------------------------
//!
//!      Parses bit63 field. Searches for data with given TableID.
//!
//! \param
//!      result          String in which data lookup is made
//! \param
//!      TableID         Bit63 table/field identificator according to Hypercom
//!                      message specification.
//!
//! \return
//!      A string with data, if TableID present, else it returns empty string
//!
//! \note
//!
HString BasicISOHost::ProcessB63Field( HString& result, HString TableID )
{
	unsigned int pos = 0;
	int fldlen;
	HString retval;

	// Check TableID
	if( TableID.length() < 2)
	{
		// Wrong TableID
		return retval;
	}

	// There should be at least 4 bytes (2 byte BCD length + 2 byte TableID)
	while( pos + 4 <= result.length() )
	{
		// pos should point to 2-byte BCD encoded length of field including TableID
		// convert it to binary
		fldlen = BcdBin( reinterpret_cast<const uint8_t*>( result.c_str() ) + pos );

		// pos + 2 shoud point to 2-byte TableID
		if( result[pos + 2] == TableID[0] && result[pos + 3] == TableID[1] )
		{
			// Field found. Check the length and return it without TableID
			if( pos + 4 + fldlen - 2 <= result.length() )
			{
				retval = HString( result, pos + 4, fldlen - 2 );
				break;
			}
			else
			{
				// Buffer overrun
				break;
			}
		}

		// Move to next field
		pos += fldlen + 2;
	}

	return retval;
}

//-----------------------------------------------------------------------------
//!
//!      Prepares private field data 60-63.
//!      Intended to be called before building ISO8583 transaction using
//!      HypCIS08583_Transaction::BuildTransaction
//!
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      None
//!
//! \note
//!      Total length of each bit field is set using
//!      HypCISO8583_Message::SetDataElement. Each class derived from
//!      HypCISO8583_Message defines, which bits it will process, when 
//!      building message.
//!
void BasicISOHost::PreparePrivateFields( HypCTransactionData& TransData )
{
	PrepareB60( TransData );
	PrepareB61( TransData );
	PrepareB62( TransData );
	PrepareB63( TransData );
}

//-----------------------------------------------------------------------------
//!
//!      Puts data into private field 60. Usually type of data depends on 
//!      message type. It could contain one of the following: batch number, 
//!      software ID, original message data ( message type & STAN ), 
//!      original amount and logon request.
//!
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      None
//!
//! \note
//!      For detailed description of each field take a look at Hypercom Message
//!      specification.
//!
void BasicISOHost::PrepareB60( HypCTransactionData& TransData )
{
	HString typeName = GetTransTag( TransData, TransactionTag::TYPE_NAME );
	HString settleType = GetTransTag( TransData, TransactionTag::SETTLE_TYPE );
	HString Bit60;

	if( typeName == "SALE CREDIT" ||
	    typeName == "DEBIT" ||
	    typeName == "EBT" ||
	    typeName == "VOIDTRAN" ||
	    typeName == "REFUND" ||
	    typeName == "PRIOREBT" ||
	    typeName == "PRIOREFEBT" ||
	    typeName == "OPENTAB" ||
	    typeName == "REFDEBIT" ||
	    typeName == "REFEBT" ||
	    typeName == "SALCASH" ||
	    typeName == "DBCASH" )

	{
		const HypCData* pStatus = TransData.get( TransactionTag::STATUS_FLAGS );
		HypCOptions status;

		// See if transaction, has it's own STATUS_FLAGS
		if ( pStatus )
		{
			// Yes, let's use them
			status = *( (HypCOptions*)pStatus );
		}

		// Make sure, it is reversal advice
		if( status.IsSet( TransactionTag::SEND_ADVICE ) &&
		    status.IsSet( TransactionTag::REVERSAL ) )
		{
			PrepareB60OriginalData( Bit60, TransData );
		}
	}

	if( settleType == TransactionTag::SETTLE_RUPLOAD  )
	{
		PrepareB60OriginalData( Bit60, TransData );
	}

	if( typeName == "ADJSALE" ||
	    typeName == "ADJREFUND" )
	{
		PrepareB60OriginalAmount( Bit60, TransData );
	}

	if( settleType == TransactionTag::SETTLE_CLBATCH ||
	    settleType == TransactionTag::SETTLE_CLBATCHE )
	{
		PrepareB60BatchNumber( Bit60, TransData );
	}

	// do we have any data
	if( !Bit60.empty() )
	{
		// yes, copy it into private field 60
		// we can not use c_str(), because original message data can contain zeros in it
		TransData.insert( TransactionTag::PRIVATE_FIELD_BIT60, new HypCString( Bit60 ) );
	}
}

//-----------------------------------------------------------------------------
//!
//!      Puts data into private field 61. This field may contain information
//!      about product codes used to carry the descriptive information about
//!      items purchased. Up to four product codes per message.
//!
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      None
//!
//! \note
//!      For detailed description of field take a look at Hypercom Message
//!      specification.
//!
void BasicISOHost::PrepareB61( HypCTransactionData& /*TransData*/ )
{
}

//-----------------------------------------------------------------------------
//!
//!      Puts invoice number into private field 62 if it exists.
//!
//! \param
//!      TransData       Rreference to data map containing transaction data
//!
//! \return
//!      None
//!
//! \note
//!      For detailed description of field take a look at Hypercom Message
//!      specification.
//!
void BasicISOHost::PrepareB62( HypCTransactionData& TransData )
{
	HString invoice = GetTransTag( TransData, TransactionTag::INVOICE );

	// do we have an invoice number
	if( !invoice.empty() )
	{
		// yes, copy it into private field 62
		TransData.insert( TransactionTag::PRIVATE_FIELD_BIT62, invoice.c_str() );
	}
}

//-----------------------------------------------------------------------------
//!
//!      Puts data into private field 63. It could contain one of the following:
//!      reconsilation request totals (used in settlement), terminal statistics,
//!      check data or additional data.
//!
//! \param
//!      TransData       reference to data map containing transaction data
//!
//! \return
//!      None
//!
//! \note
//!      For detailed description of field take a look at Hypercom Message
//!      specification.
//!
void BasicISOHost::PrepareB63( HypCTransactionData& TransData )
{
	HString typeName = GetTransTag( TransData, TransactionTag::TYPE_NAME );
	HString settleType = GetTransTag( TransData, TransactionTag::SETTLE_TYPE );
	HString Bit63;

	// See if we need to set transaction totals in Bit63
	if( settleType == TransactionTag::SETTLE_CLBATCH  ||
		settleType == TransactionTag::SETTLE_CLBATCHA ||
		settleType == TransactionTag::SETTLE_CLBATCHE )
	{
		// Yes, add totals to Bit63
		PrepareB63StandardTotals( Bit63, TransData );
	}
	else
	{
		if( typeName == "TESTTRAN" )
		{
			// Note:  This will need to chek if in AutoTest mode when TESTTRAN
			return;
		}

		// Adds additional data items
		PrepareB63Cashier( Bit63, TransData );
		PrepareB63LVL2Indicator( Bit63, TransData );
		PrepareB63CVV2( Bit63, TransData );
		PrepareB63PS2000( Bit63, TransData );
		PrepareB63HostRefData( Bit63, TransData );
		PrepareB63KeySN( Bit63, TransData );
		PrepareB63AdditionalPrompt( Bit63, TransData );
		PrepareB63BatchNumber( Bit63, TransData );
		PrepareB63TipAmount( Bit63, TransData );
		PrepareB63TaxAmount1( Bit63, TransData );
		PrepareB63TaxAmount2( Bit63, TransData );
		PrepareB63CashbackAmount( Bit63, TransData );
		PrepareB63EBT( Bit63, TransData );
		PrepareB63MiscAmount( Bit63, TransData );
		PrepareB63AVSData( Bit63, TransData );
		PrepareB63LVL2Data( Bit63, TransData );	
		PrepareB63IssScript( Bit63, TransData );	
	}

	// Do we have some data to put in bit63 field 
	if( !Bit63.empty() )
	{
		// yes, copy it into bit63 field
		// we can not use c_str(), because Bit63 can contain zeros in it
		TransData.insert( TransactionTag::PRIVATE_FIELD_BIT63, new HypCString( Bit63 ) );
	}

}

//-----------------------------------------------------------------------------
//!
//!      Prepares batch number for settlement trailer
//!
//! \param
//!      Bit60           String to which, batch number is assigned
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      true if data was added, else false
//!
//! \note
//!
bool BasicISOHost::PrepareB60BatchNumber( HString& Bit60, HypCTransactionData& TransData )
{
	HString BatchNo = GetTransTag( TransData, TransactionTag::BATCH_NUMBER );

	// See if batch number is set
	if( !BatchNo.empty() )
	{
		Bit60 = BatchNo;
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
//!
//!      Prepares original message data (message type and STAN) for settlement
//!      upload.
//!
//! \param
//!      Bit60           String to which, data is assigned
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      true if data was added, else false
//!
//! \note
//!
bool BasicISOHost::PrepareB60OriginalData( HString& Bit60, HypCTransactionData& TransData )
{
	HString OrigMsgType = GetTransTag( TransData, TransactionTag::ORIGINAL_MSG_TYPE );
	HString OrigSTAN = GetTransTag( TransData, TransactionTag::ORIGINAL_STAN );

	Bit60 = OrigMsgType + OrigSTAN;

	// Right padding with spaces till width 22
	while( Bit60.length() < 22 )
	{
		Bit60 += ' ';
	}

	return true;
}

//-----------------------------------------------------------------------------
//!
//!      Prepares original amount for adjust and void transactions
//!
//! \param
//!      Bit60           String to which, amount is assigned
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      true if data was added, else false
//!
//! \note
//!
bool BasicISOHost::PrepareB60OriginalAmount( HString& Bit60, HypCTransactionData& TransData )
{
	HString OrigAmt = GetTransTag( TransData, TransactionTag::ORIGINAL_AMOUNT );

	// See if original amount is set
	if( !OrigAmt.empty() )
	{
		Bit60 = OrigAmt;
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
//!
//!      Prepares cashier data and till number (10)
//!
//! \param
//!      Bit63           String to which, total length, Table ID and data itself
//!                      will be added
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      true if data was added, else false
//!
//! \note
//!
bool BasicISOHost::PrepareB63Cashier( HString& Bit63, HypCTransactionData& TransData )
{
	HString Cashier = GetTransTag( TransData, TransactionTag::CASHIER );
	HString Tillno = GetTransTag( TransData, TransactionTag::TILLNO );
	HYP_CFG_HANDLE termRecord = POSConfig().GetTable( TermConfigTag::TERMINAL_TABLE );

	// See if cashier option is set
	if( POSConfig().IsOptionSet( termRecord, TC1_CASHIER ) )
	{
		// Right padding with spaces till four symbols
		while( Cashier.length() < 4 )
		{
			Cashier += ' ';
		}

		// Right padding with spaces till four symbols
		while( Tillno.length() < 4 )
		{
			Tillno += ' ';
		}

		PrepareB63Field( Bit63, "10", Cashier + Tillno );
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
//!
//!      Prepares level II comercial card indicator (15)
//!
//! \param
//!      Bit63           String to which, total length, Table ID and data itself
//!                      will be added
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      true if data was added, else false
//!
//! \note
//!
bool BasicISOHost::PrepareB63LVL2Indicator( HString& Bit63, HypCTransactionData& TransData )
{
	HString settleType = GetTransTag( TransData, TransactionTag::SETTLE_TYPE );
	const HypCData* pStatus = TransData.get( TransactionTag::STATUS_FLAGS );
	HypCOptions status;

	// See if transaction, has it's own STATUS_FLAGS
	if ( pStatus )
	{
		// Yes, let's use them
		status = *( (HypCOptions*)pStatus );
	}

	// Make sure, it is not advice or adjust
	if( !status.IsSet( TransactionTag::SEND_ADVICE ) &&
	    !status.IsSet( TransactionTag::ADJUSTED ) )
	{
		// Make sure, it is not UPLOAD
		if( settleType != TransactionTag::SETTLE_RUPLOAD )
		{
			// Check if Level II amount or PO Number enabled
			if( POSConfig().IsOptionSet( m_IssRecord, ISS_LEVEL2_AMOUNT_ENABLED ) ||
			    POSConfig().IsOptionSet( m_IssRecord, ISS_LEVEL2_PO_ENABLED ) )
			{
				PrepareB63Field( Bit63, "15", "1" );
				return true;
			}
		}
	}

	return false;
}

//-----------------------------------------------------------------------------
//!
//!      Prepares card verification value two (16)
//!
//! \param
//!      Bit63           String to which, total length, Table ID and data itself
//!                      will be added
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      true if data was added, else false
//!
//! \note
//!
bool BasicISOHost::PrepareB63CVV2( HString& Bit63, HypCTransactionData& TransData )
{
	HString Indicator = GetTransTag( TransData, TransactionTag::CVV2_INDICATOR );
	HString RespCode = GetTransTag( TransData, TransactionTag::CVV2_RESPONSE_CODE );
	HString Data = GetTransTag( TransData, TransactionTag::CVV2_DATA );
	HString settleType = GetTransTag( TransData, TransactionTag::SETTLE_TYPE );
	const HypCData* pStatus = TransData.get( TransactionTag::STATUS_FLAGS );
	HypCOptions status;

	// See if transaction, has it's own STATUS_FLAGS
	if ( pStatus )
	{
		// Yes, let's use them
		status = *( (HypCOptions*)pStatus );
	}

	// Make sure, it is not advice or adjust
	if( !status.IsSet( TransactionTag::SEND_ADVICE ) &&
	    !status.IsSet( TransactionTag::ADJUSTED ) ) 
	{
		// Make sure, it is not UPLOAD
		if( settleType != TransactionTag::SETTLE_RUPLOAD )
		{
			// Only if indicator is set add this data to result
			if( !Indicator.empty() && Indicator[0] > 0x20 )
			{
				// In CPOS this field was not used, but value zero was set
				if( RespCode.empty() )
				{
					RespCode += '0';
				}

				// Formating data according to specification
				if( '0' == Indicator[0] || '2' == Indicator[0] || '9' == Indicator[0] )
				{
					Data.clear();
				}
			
				// Left padding with spaces till width 4
				if( Data.length() < 4 )
				{
					Data.insert( 0, 4 - Data.length(), ' ' );
				}

				PrepareB63Field( Bit63, "16", Indicator + RespCode + Data );
				return true;
			}
		}
	}

	return false;
}

//-----------------------------------------------------------------------------
//!
//!      Prepares payment services 2000 data (20, 21)
//!
//! \param
//!      result          String to which, total length, Table ID and data itself
//!                      will be added
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      true if data was added, else false
//!
//! \note
//!
bool BasicISOHost::PrepareB63PS2000( HString& Bit63, HypCTransactionData& TransData )
{
	HString Indicator = GetTransTag( TransData, TransactionTag::PS2000_INDICATOR );
	HString TransID = GetTransTag( TransData, TransactionTag::TRANSACTION_IDENTIFIER );
	HString ValCode = GetTransTag( TransData, TransactionTag::VALIDATION_CODE );
	HString RespCode = GetTransTag( TransData, TransactionTag::VISA2_RESPONSE_CODE );
	HString PosEntry = GetTransTag( TransData, TransactionTag::VISA2_POS_ENTRY );
	HString AuthAmt = GetTransTag( TransData, TransactionTag::AUTHORISED_AMOUNT );
	HString settleType = GetTransTag( TransData, TransactionTag::SETTLE_TYPE );
	
	// Make sure, it is UPLOAD
	if( settleType == TransactionTag::SETTLE_RUPLOAD )
	{
		// See if indicator is present
		if( !Indicator.empty() && Indicator[0] > 0x20 )
		{
			PrepareB63Field( Bit63, "20", 
			                 Indicator + TransID + ValCode + RespCode + PosEntry );

			PrepareB63Field( Bit63, "21", AuthAmt );

			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------
//!
//!      Prepares host reference data (31)
//!
//! \param
//!      Bit63           String to which, total length, Table ID and data itself
//!                      will be added
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      true if data was added, else false
//!
//! \note
//!
bool BasicISOHost::PrepareB63HostRefData( HString& Bit63, HypCTransactionData& TransData )
{
	HString RefData = GetTransTag( TransData, TransactionTag::HOST_REF_DATA );
	HString settleType = GetTransTag( TransData, TransactionTag::SETTLE_TYPE );
	const HypCData* pStatus = TransData.get( TransactionTag::STATUS_FLAGS );
	HypCOptions status;

	// See if transaction, has it's own STATUS_FLAGS
	if ( pStatus )
	{
		// Yes, let's use them
		status = *( (HypCOptions*)pStatus );
	}

	// Make sure, it is advice or adjust or UPLOAD
	if( status.IsSet( TransactionTag::SEND_ADVICE ) ||
	    status.IsSet( TransactionTag::ADJUSTED ) ||
	    settleType == TransactionTag::SETTLE_RUPLOAD )
	{
		if ( !RefData.empty() )
		{	
			// In CPOS first two bytes contained length.
			// It's not neccesary in HFC. So we move just plain data.
			PrepareB63Field( Bit63, "31", RefData );
			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------
//!
//!      Prepares key serial number (33)
//!
//! \param
//!      Bit63           String to which, total length, Table ID and data itself
//!                      will be added
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      true if data was added, else false
//!
//! \note
//!
bool BasicISOHost::PrepareB63KeySN( HString& Bit63, HypCTransactionData& TransData )
{
	HString ksn = GetTransTag( TransData, TransactionTag::KEY_SN );
	char Buff[32];
	
	// See if we have Key Serial Number
	if ( !ksn.empty() )
	{
		// Converts ksn to ASCII format.
		memset( Buff, 0, sizeof( Buff ) );
		BfAscii( Buff, reinterpret_cast<const uint8_t*>( ksn.c_str() ), 
		         ksn.length() );

		// Left padding with 0xFF till width 20
		ksn.assign( Buff );
		if( ksn.length() < 20 )
		{
			ksn.insert( 0, 20 - ksn.length(), '\xff' );
		}
		
		PrepareB63Field( Bit63, "33", ksn );
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
//!
//!      Prepares additional prompt data (35)
//!
//! \param
//!      Bit63           String to which, total length, Table ID and data itself
//!                      will be added
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      true if data was added, else false
//!
//! \note
//!
bool BasicISOHost::PrepareB63AdditionalPrompt( HString& Bit63, HypCTransactionData& TransData )
{
	HString Prompt = GetTransTag( TransData, TransactionTag::ADDITIONAL_PROMPT );

	// See, if we have additional prompt data
	if( !Prompt.empty() )
	{
		PrepareB63Field( Bit63, "35", Prompt );
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
//!
//!      Prepares batch number from acquirer's info (37)
//!
//! \param
//!      Bit63           String to which, total length, Table ID and data itself
//!                      will be added
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      true if data was added, else false
//!
//! \note
//!
bool BasicISOHost::PrepareB63BatchNumber( HString& Bit63, HypCTransactionData& /*TransData*/ )
{
	HString Batch;

	// Check if is need to send batch number. It is defined by acquirer.
	if( POSConfig().IsOptionSet( m_AcqRecord, ACQ_SEND_BAT_NO ) )
	{
		// Get pointer to batch number from terminal configuration
		Batch = POSConfig().GetParam( m_AcqRecord, AcquirerTag::BATCH_CURRENT );

		if( !Batch.empty() )
		{
			// Batch number found, add it to result string
			PrepareB63Field( Bit63, "37", Batch );
			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------
//!
//!      Prepares tip amount (38)
//!
//! \param
//!      Bit63           String to which, total length, Table ID and data itself
//!                      will be added
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      true if data was added, else false
//!
//! \note
//!
bool BasicISOHost::PrepareB63TipAmount( HString& Bit63, HypCTransactionData& TransData )
{
	HString TipAmt = GetTransTag( TransData, TransactionTag::TIP_AMOUNT );

	// See if we have Tip Amount
	if( !TipAmt.empty() )
	{
		PrepareB63Field( Bit63, "38", TipAmt );
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
//!
//!      Prepares tax amount #1 (39)
//!
//! \param
//!      Bit63           String to which, total length, Table ID and data itself
//!                      will be added
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      true if data was added, else false
//!
//! \note
//!
bool BasicISOHost::PrepareB63TaxAmount1( HString& Bit63, HypCTransactionData& TransData )
{
	HString TaxAmt = GetTransTag( TransData, TransactionTag::TAX_AMOUNT1 );

	// See if we have Tax Amount #1
	if( !TaxAmt.empty() )
	{
		PrepareB63Field( Bit63, "39", TaxAmt );
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
//!
//!      Prepares tax amount #2 (40)
//!
//! \param
//!      Bit63           String to which, total length, Table ID and data itself
//!                      will be added
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      true if data was added, else false
//!
//! \note
//!
bool BasicISOHost::PrepareB63TaxAmount2( HString& Bit63, HypCTransactionData& TransData )
{
	HString TaxAmt = GetTransTag( TransData, TransactionTag::TAX_AMOUNT2 );

	// See if we have Tax Amount #2
	if( !TaxAmt.empty() )
	{
		PrepareB63Field( Bit63, "40", TaxAmt );
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
//!
//!      Prepares cashback amount (41)
//!
//! \param
//!      Bit63           String to which, total length, Table ID and data itself
//!                      will be added
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      true if data was added, else false
//!
//! \note
//!
bool BasicISOHost::PrepareB63CashbackAmount( HString& Bit63, HypCTransactionData& TransData )
{
	HString CBAmt = GetTransTag( TransData, TransactionTag::CASHBACK_AMOUNT );

	// See if we have Cachback Amount
	if( !CBAmt.empty() )
	{
		PrepareB63Field( Bit63, "41", CBAmt );
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
//!
//!      Prepares EBT specific data (47)
//!
//! \param
//!      Bit63           String to which, total length, Table ID and data itself
//!                      will be added
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      true if data was added, else false
//!
//! \note
//!
bool BasicISOHost::PrepareB63EBT( HString& Bit63, HypCTransactionData& TransData )
{
	HString Clerk = GetTransTag( TransData, TransactionTag::EBT_CLERK_ID );
	HString SuperVisor = GetTransTag( TransData, TransactionTag::EBT_SUPERVISOR_ID );
	HString Voucher = GetTransTag( TransData, TransactionTag::EBT_VOUCHER_NUMBER );
	HString Generation = GetTransTag( TransData, TransactionTag::EBT_GENERATION_NUMBER );

	// See if voucher number or generation number present
	if( !Voucher.empty() || !Generation.empty() )
	{
		// Right padding with spaces
		while( Clerk.length() < 10 )
		{
			Clerk += ' ';
		}

		while( SuperVisor.length() < 10 )
		{
			SuperVisor += ' ';
		}

		while( Voucher.length() < 15 )
		{
			Voucher += ' ';
		}

		while( Generation.length() < 6 )
		{
			Generation += ' ';
		}


		PrepareB63Field( Bit63, "47", Clerk + SuperVisor + Voucher + Generation );
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
//!
//!      Prepares miscellaneous amount (53)
//!
//! \param
//!      Bit63           String to which, total length, Table ID and data itself
//!                      will be added
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      true if data was added, else false
//!
//! \note
//!
bool BasicISOHost::PrepareB63MiscAmount( HString& Bit63, HypCTransactionData& TransData )
{
	HString MiscAmt = GetTransTag( TransData, TransactionTag::MISC_AMOUNT );

	// Check if miscellaneous amount present
	if( !MiscAmt.empty() )
	{
		PrepareB63Field( Bit63, "53", MiscAmt );
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
//!
//!      Prepares address verification data (address and zip code) (54)
//!      This data usually required in mail order transaction
//!
//! \param
//!      Bit63           String to which, total length, Table ID and data itself
//!                      will be added
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      true if data was added, else false
//!
//! \note
//!
bool BasicISOHost::PrepareB63AVSData( HString& Bit63, HypCTransactionData& TransData )
{
	HString Address = GetTransTag( TransData, TransactionTag::AVS_ADDRESS );
	HString Zip = GetTransTag( TransData, TransactionTag::AVS_ZIP );
	HString typeName = GetTransTag( TransData, TransactionTag::TYPE_NAME );

	// See if mail order transaction or 
	// Address Verification (AVS) allowed and 
	// address or zip code required 
	if( typeName == "MAIL_ORDER" ||
	    ( POSConfig().IsOptionSet( m_IssRecord, ISS_ADDRESS_VERIFICATION_ALLOWED ) &&
	    ( POSConfig().IsOptionSet( m_IssRecord, ISS_MAIL_ADDRESS_REQUIRED ) ||
	      POSConfig().IsOptionSet( m_IssRecord, ISS_AVS_ZIPCODE_REQUIRED ) ) ) )
	{
		// See if address or zip exists
		if( !Address.empty() || !Zip.empty() )
		{
			PrepareB63Field( Bit63, "54", Zip + Address );
			return true;
		}
	}

	return false;
}

//-----------------------------------------------------------------------------
//!
//!      Prepares level 2 comercial card data (73)
//!
//! \param
//!      Bit63           String to which, total length, Table ID and data itself
//!                      will be added
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      true if data was added, else false
//!
//! \note
//!
bool BasicISOHost::PrepareB63LVL2Data( HString& Bit63, HypCTransactionData& TransData )
{
	HString OptID = GetTransTag( TransData, TransactionTag::LVL2_OPT_AMOUNT_ID );
	HString OptAmt = GetTransTag( TransData, TransactionTag::LVL2_OPT_AMOUNT );
	HString PONumber = GetTransTag( TransData, TransactionTag::LVL2_PO_NUMBER );
	HString settleType = GetTransTag( TransData, TransactionTag::SETTLE_TYPE );

	// Make sure, it is UPLOAD
	if( settleType == TransactionTag::SETTLE_RUPLOAD )
	{
		// Check if Level II Optional Amount ID or PO Number exists
		if( ( !OptID.empty() && OptID[0] > 0x20 ) ||
		    ( !PONumber.empty() ) )
		{
			// Check if Level II Optional Amount ID exists
			if( OptID.empty() )
			{
				// No optional amount id present, so set default value
				OptID = "0";
			}

			// Check if Optional amount is present
			if( OptAmt.empty() )
			{
				// No optional amount present, so set default value
				OptAmt = "000000000000";
			}

			// PO number right padding with ' ' till width 17
			while( PONumber.length() < 17 )
			{
				PONumber += ' ';
			}

			PrepareB63Field( Bit63, "73", OptID + OptAmt + PONumber );
			return true;
		}
	}

	return false;
}


//-----------------------------------------------------------------------------
// Name:
//      BasicISOHost::PrepareB63IssScript
//
// Description:
//      Prepares issuer script results card data (SR)
//
// Parameters:
//      Bit63           String to which, total length, Table ID and data itself
//                      will be added
//      TransData       Reference to data map containing transaction data
//
// Returns:
//      true if data was added, else false
//
// Notes:
//
bool BasicISOHost::PrepareB63IssScript( HString& Bit63, HypCTransactionData& TransData )
{
	HString IssScript = GetTransTag( TransData, "ISSUER_SCRIPT_RES" );

	// Check if miscellaneous amount present
	if( !IssScript.empty() )
	{
		PrepareB63Field( Bit63, "SR", IssScript );
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
//!
//!      Processes data for bits 62, 63.
//!
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      None
//!
//! \note
//!      Nothing to process for bit 60 and bit 61 fields
//!      For detailed description of fields take a look at Hypercom Message
//!      specification.
//!
void BasicISOHost::ProcessPrivateFields( HypCTransactionData& TransData )
{
	// Process Bit 62
	ProcessB62( TransData );

	// Process Bit 63
	ProcessB63( TransData );
}

//-----------------------------------------------------------------------------
//!
//!      Processes data in bit field 62
//!
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      None
//!
//! \note
//!      For detailed description of fields take a look at Hypercom Message
//!      specification.
//!
void BasicISOHost::ProcessB62( HypCTransactionData& TransData )
{
	HString Bit62 = GetTransTag( TransData, TransactionTag::PRIVATE_FIELD_BIT62 );
	HString typeName = GetTransTag( TransData, TransactionTag::TYPE_NAME );
	HYP_CFG_HANDLE termRecord = POSConfig().GetTable( TermConfigTag::TERMINAL_TABLE );

	if( Bit62.empty() || typeName != "LOGON" )
	{
		// Empty Bit62 data or not a logon transaction response, so return
		return;
	}

	// See if data contains at least 2 keys (each 8 bytes) and 2 byte length field
	if( Bit62.length() < 18 )
	{
		return;
	}

	// Two byte length offset and 8 byte key length
	HypCString workKey( HString( Bit62, 2, 8 ) );
	// 10 bytes offset to next key and 8 byte key length
	HypCString macKey( HString( Bit62, 2 + 8, 8 ) );

	// Updates acquirer keys
	// POSConfig().SetParam( m_AcqRecord, "AcquirerTag::WORK_KEY", workKey );
	// POSConfig().SetParam( m_AcqRecord, "AcquirerTag::MAC_KEY", macKey );

	// See if more data (MerchantName1, MerchantName2, MarchantName3 )
	// each 23 bytes follows. 
	if( Bit62.length() > 18 )
	{
		HypCString name1( HString( Bit62, 18, 23 ) );
		POSConfig().SetParam( termRecord, TermConfigTag::TCNAM1, name1 );
	}

	if( Bit62.length() > 18 + 23 )
	{
		HypCString name2( HString( Bit62, 18 + 23, 23 ) );
		POSConfig().SetParam( termRecord, TermConfigTag::TCNAM2, name2 );
	}

	if( Bit62.length() > 18 + 23 + 23 )
	{
		HypCString name3( HString( Bit62, 18 + 23 + 23, 23 ) );
		POSConfig().SetParam( termRecord, TermConfigTag::TCNAM3, name3 );
	}
	
}

//-----------------------------------------------------------------------------
//!
//!      Processes data in bit field 63
//!
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      None
//!
//! \note
//!      Layout of alternate Host Response and/or
//!      PS2000 Data in Bit 63.
//!
//!      (Ignore spacing, only to clarify description).
//!
//!      AA L1 22 ZZZZZZZZZZZZZZZZZZZZ L2 20 B CCCCCCCCCCCCCCC DDDD EE FF
//!
//!         AA     Total length data in Bit 63           BCD
//!         L1     First field length                    BCD
//!         22     First field type                      ASCII
//!                ('22' for alternative Host Response)
//!         Z...Z  40 Digit Host Response Text           ASCII
//!         L2     Second field length                   BCD
//!         20     Second field type                     ASCII
//!                ('20' for PS2000 Data)
//!         B      1 Digit Payment Services Indicator    ASCII
//!         C...C  15 Digit Transaction Identifier       ASCII
//!         DDDD	  4 Digit Validation Code               ASCII
//!         EE     2 Character Visa II Response Code     ASCII
//!         FF     2 Character Visa II POS Entry Mode    ASCII
//!
void BasicISOHost::ProcessB63( HypCTransactionData& TransData )
{
	HString Bit63 = GetTransTag( TransData, TransactionTag::PRIVATE_FIELD_BIT63 );

	if( Bit63.empty() )
	{
		// Nothing to process, so return
		return;
	}

	ProcessB63LVL2Indicator( Bit63, TransData );
	ProcessB63CVV2ResultCode( Bit63, TransData );
	ProcessB63PS2000( Bit63, TransData );
	ProcessB63AltHostResponse( Bit63, TransData );
	ProcessB63HostPrintData( Bit63, TransData );
	ProcessB63HostRefData( Bit63, TransData );
	ProcessB63ScheduleCommand( Bit63, TransData );
	ProcessB63SurchargeAmount( Bit63, TransData );
	ProcessB63EBT( Bit63, TransData );
	ProcessB63AVS( Bit63, TransData );

}

//-----------------------------------------------------------------------------
//!
//!      Processes level II comercial card indicator (15) response
//!
//! \param
//!      Bit63           Result string from which data are going to be extracted
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      true if data is found and moved to TransData, else false
//!
//! \note
//!
bool BasicISOHost::ProcessB63LVL2Indicator( HString& Bit63, HypCTransactionData& TransData )
{
	HString lvl2ind = ProcessB63Field( Bit63, "15" );

	if( !lvl2ind.empty() )
	{
		// Response present, so save it to transaction data
		TransData.insert( TransactionTag::LVL2_INDICATOR, lvl2ind.c_str() );
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
//!
//!      Processes comercial card verification value II (16) result code
//!
//! \param
//!      Bit63           Result string from which data are going to be extracted
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      true if data is found and moved to TransData, else false
//!
//! \note
//!
bool BasicISOHost::ProcessB63CVV2ResultCode( HString& Bit63, HypCTransactionData& TransData )
{
	HString cvv2 = ProcessB63Field( Bit63, "16" );

	if( !cvv2.empty() )
	{
		// Response present, so save it to transaction data
		TransData.insert( TransactionTag::CVV2_RESULT_CODE, cvv2.c_str() );
		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
//!
//!      Processes payment services 2000 data (20)
//!
//! \param
//!      Bit63           Result string from which data are going to be extracted
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      true if data is found and moved to TransData, else false
//!
//! \note
//!
bool BasicISOHost::ProcessB63PS2000( HString& Bit63, HypCTransactionData& TransData )
{
	HString result = ProcessB63Field( Bit63, "20" );
	const HypCData* pData;

	if( !result.empty() && result.length() >= 24 )
	{
		// Gets fields from result string
		HString Indicator( result, 0, 1 );
		HString TransID( result, 1, 15 );
		HString ValCode( result, 16, 4 );
		HString RespCode( result, 20, 2 );
		HString PosEntry( result, 22, 2 );

		// Response present, so save it to transaction data
		TransData.insert( TransactionTag::PS2000_INDICATOR, Indicator.c_str() );
		TransData.insert( TransactionTag::TRANSACTION_IDENTIFIER, TransID.c_str() );
		TransData.insert( TransactionTag::VALIDATION_CODE, ValCode.c_str() );
		TransData.insert( TransactionTag::VISA2_RESPONSE_CODE, RespCode.c_str() );
		TransData.insert( TransactionTag::VISA2_POS_ENTRY, PosEntry.c_str() );
	
		// Just make sure, we have a TOTAL_AMOUNT present
		pData = TransData.get( TransactionTag::TOTAL_AMOUNT );
		if( pData )
		{
			// Inserts authorised amount if not present
			if( !TransData.get( TransactionTag::AUTHORISED_AMOUNT ) )
			{
				TransData.insert( TransactionTag::AUTHORISED_AMOUNT, pData->Clone() );
			}
		}

		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
//!
//!      Processes alternate host response data (22)
//!
//! \param
//!      Bit63           Result string from which data are going to be extracted
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      true if data is found and moved to TransData, else false
//!
//! \note
//!
bool BasicISOHost::ProcessB63AltHostResponse( HString& Bit63, HypCTransactionData& TransData )
{
	HString resp = ProcessB63Field( Bit63, "22" );

	if( !resp.empty() )
	{
		// Response present, so save it to transaction data
		TransData.insert( TransactionTag::ALT_HOST_RESPONSE, resp.c_str() );

		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
//!
//!      Processes additional host print data (29)
//!
//! \param
//!      Bit63           Result string from which data are going to be extracted
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      true if data is found and moved to TransData, else false
//!
//! \note
//!
bool BasicISOHost::ProcessB63HostPrintData( HString& Bit63, HypCTransactionData& TransData )
{
	HString data = ProcessB63Field( Bit63, "29" );

	if( !data.empty() )
	{
		// Data present, so save it to transaction data
		TransData.insert( TransactionTag::HOST_PRINT_DATA, data.c_str() );

		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
//!
//!      Processes host reference data (31)
//!
//! \param
//!      Bit63           Result string from which data are going to be extracted
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      true if data is found and moved to TransData, else false
//!
//! \note
//!
bool BasicISOHost::ProcessB63HostRefData( HString& Bit63, HypCTransactionData& TransData )
{
	HString data = ProcessB63Field( Bit63, "31" );

	if( !data.empty() )
	{
		// Data present, so save it to transaction data
		// we can not use c_str(), because we never know, what we gonna get here from host
		TransData.insert( TransactionTag::HOST_REF_DATA, new HypCString( data ) );

		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
//!
//!      Processes scheduled command data (42)
//!
//! \param
//!      Bit63           Result string from which data are going to be extracted
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      true if data is found and moved to TransData, else false
//!
//! \note
//!
bool BasicISOHost::ProcessB63ScheduleCommand( HString& Bit63, HypCTransactionData& /*TransData*/ )
{
	HString cmd = ProcessB63Field( Bit63, "42" );

	// Where to store it???

	return false;
}

//-----------------------------------------------------------------------------
//!
//!      Processes surcharge amount (44)
//!
//! \param
//!      Bit63           Result string from which data are going to be extracted
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      true if data is found and moved to TransData, else false
//!
//! \note
//!
bool BasicISOHost::ProcessB63SurchargeAmount( HString& Bit63, HypCTransactionData& TransData )
{
	HString amt = ProcessB63Field( Bit63, "44" );

	if( !amt.empty() )
	{
		// Amount present, so save it to transaction data
		TransData.insert( TransactionTag::SURCHARGE_AMOUNT, new HypCCurrency( amt ) );

		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
//!
//!      Processes EBT response data (48)
//!
//! \param
//!      Bit63           Result string from which data are going to be extracted
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      true if data is found and moved to TransData, else false
//!
//! \note
//!
bool BasicISOHost::ProcessB63EBT( HString& Bit63, HypCTransactionData& /*TransData*/ )
{
	HString ebt = ProcessB63Field( Bit63, "48" );

	// Where to store it???

	return false;
}

//-----------------------------------------------------------------------------
//!
//!      Processes address verification response code (55)
//!
//! \param
//!      Bit63           Result string from which data are going to be extracted
//! \param
//!      TransData       Reference to data map containing transaction data
//!
//! \return
//!      true if data is found and moved to TransData, else false
//!
//! \note
//!
bool BasicISOHost::ProcessB63AVS( HString& Bit63, HypCTransactionData& TransData )
{
	HString avs = ProcessB63Field( Bit63, "55" );

	if( !avs.empty() )
	{
		// Response present, so save it to transaction data
		TransData.insert( TransactionTag::AVS_RESPONSE, avs.c_str() );

		return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
//!
//!      Makes settlement process
//!
//! \return
//!      HOST_OK - if transaction succeeded
//!      HOST_INCOMPLETE_TRANS - 
//!        1. if amount doesn't match even after processing of settlement trailer
//!        2. if "status flags" field not found in journal
//!      HOST_JOURNAL_FAIL - if couldn't open the journal
//!		 HOST_BAD_BATCH_NUMBER - if batch number is not found
//!
//! \note
//!
HypEHostResult BasicISOHost::DoSettle()
{
	HypEHostResult res = HOST_OK;
	const HypCData* data = NULL;
	HypCOptions* popts = NULL;
	HYP_CFG_HANDLE tableAcq = 0, rowAcq = 0;
	HypCString Acq, Num;
	HypCPOSConfig* pCfg = static_cast <HypCPOSConfig*> ( &Transaction().POSConfig() );
	uint64_t CurBatNum( 1 ), NextBatNum( 2 );
	HString BatNumStr;
	HypCJournal* batch_jrn = Transaction().GetApplication()->GetJournal( JournalTags::BATCH_REC );
	HypCTransactionData BatchData, TransCopy;
	HypCTransactionData& TransData = Transaction().TransactionData();
	bool batch_new = true;
	HypCDateTime ct;

	// delete previously settled transactions from journal
	DeleteSettled(  );

	// get the current and the next batch number from configuration
	tableAcq = pCfg -> GetTable( AcquirerTag::ACQUIRER_TABLE );
	if ( tableAcq ) 
	{
		rowAcq = pCfg -> GetTableRow( tableAcq, HypCPOSConfig::FIRST );
		Acq = pCfg ->GetParam( rowAcq, AcquirerTag::ID );

		while ( rowAcq && !Acq.IsEmpty() )
		{
			Acq = pCfg -> GetParam( rowAcq, AcquirerTag::NAME );
			if ( !Acq.IsEmpty() && ( m_HostName == Acq ) )
			{
				// get the current batch number from configuration DB
				Num = pCfg -> GetParam( rowAcq, AcquirerTag::BATCH_CURRENT );
				if ( !Num.IsEmpty() )
				{
					CurBatNum = Num.AsInt(  );
				}
				// get the next batch number from configuration DB
				Num = pCfg -> GetParam( rowAcq, AcquirerTag::BATCH_NEXT );
				if ( !Num.IsEmpty() )
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
			// Next acquirer:
			rowAcq = pCfg -> GetTableRow( tableAcq, HypCPOSConfig::NEXT );
			if ( rowAcq )
			{
				Acq = pCfg ->GetParam( rowAcq, AcquirerTag::ID );	
			}
		}
	}

	// find batch record for the current acquirer in the batch records DB
	if ( !( batch_jrn && batch_jrn->Open() ) )
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

	res = PerformTransaction( Transaction() );

	// communication error, abort
	if ( res != HOST_OK )
	{
		return res;
	}

	// save transaction properties for settlement trailer
	TransCopy = TransData;

	if ( !HOST_APPROVED( TransData ) )
	{
    	// if amounts don't match
		if( BATCH_UPLOAD( TransData ) )
		{
			HypCJournal *jrn = Transaction(  ).GetJournal(m_HostName.c_str());
			bool prev_open = jrn && jrn->IsOpen(  );
			bool bres = prev_open || ( jrn && jrn->Open(  ) );	

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
						if ( res != HOST_OK )
						{
							if ( !prev_open )
							{
								jrn->Close(  );
							}
							return res;
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

			// make the current batch number available for packet encoder
			//TransData.insert( BATCH_NUMBER,  BatNumStr.c_str(  ) );

			res = PerformTransaction( Transaction(  ) );
			// communication error, abort
			if ( res != HOST_OK )
			{
				return res;
			}

			if ( !HOST_APPROVED( TransData ) )
			{
				// if amounts still don't match
				return HOST_INCOMPLETE_TRANS;
			}
		}
		else if( BAD_BATCH_NUMBER( TransData ) )
		{
			return HOST_BAD_BATCH_NUMBER;
		}
		else
		{
			return HOST_INCOMPLETE_TRANS;
		}
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
