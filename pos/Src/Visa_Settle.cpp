//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hypercom Foundation Classes
//      (c) Copyright 2006
//
//  File Name:
//     Visa_Settle.cpp
//
//  File Description:
//     Implementation of the Class Visa_Settle
//
//=============================================================================
#if defined(__GNUC__)
#pragma implementation
#endif

#include <compiler.h>     // for memset support
#include "Visa_Settle.hpp"
#include <HString.hpp>       // for memset support
#include <HypCDateTime.hpp>
#include <HypCString.hpp>
#include <HypCOptions.hpp>
#include "VisaHost.hpp"
#include "YemekSepetiTags.h"

//=============================================================================
// Public defines and typedefs
//=============================================================================

// block marker
#define	ETB 0x17

// SETTLEMENT RESPONSE CODES
#define RSPQD   	"QD"
#define RSPQD_OUR	"77"		// DUPLICATE BATCH - RECONCILE ERROR
#define RSPGB		"GB"
#define RSPGB_OUR	"00"		// APPROVED
#define RSPRB		"RB"
#define RSPRB_OUR	"77"		// REJECTED BATCH - RECONCILE ERROR

// movers table for settlement header requests
const Visa_Settle::rec Visa_Settle::TAB_Header[] =
{
	{ &Visa_Settle::MoveFormatH, 4, FIXED },				// 1-4-record format, type, delimiter, X.25 routing
	{ &Visa_Settle::MoveRecTypeH, 5, FIXED },				// 5-9-record type
	{ &Visa_Settle::MoveAcquirerNum, 6, FIXED },			// 10-15-acquirer bin
	{ &Visa_Settle::MoveAgentBankNum, 6, FIXED },			// 16-21-agent bin
	{ &Visa_Settle::MoveAgentChainNum, 6, FIXED },			// 22-27-agent chain num
	{ &Visa_Settle::MoveMerchantNum, 12, FIXED},			// 28-39-merchant number
	{ &Visa_Settle::MoveStoreNum, 4, FIXED},			    // 40-43-store number
	{ &Visa_Settle::MoveTerminalNum, 4, FIXED},				// 44-47-terminal number
	{ &Visa_Settle::MoveDevice, 1, FIXED},					// 48-device code
	{ &Visa_Settle::MoveIndustry, 1, FIXED},			    // 49-industry code
	{ &Visa_Settle::MoveCurrency, 3, FIXED},			    // 50-52-currency code
	{ &Visa_Settle::MoveLang, 2, FIXED},				    // 53-54-language indicator
	{ &Visa_Settle::MoveTimeZoneDiff, 3, FIXED},			// 55-57-time zone differential
	{ &Visa_Settle::MoveBatchTransDate, 4, FIXED},			// 58-61-tran sequence number
	{ &Visa_Settle::MoveBatchNum, 3, FIXED},				// 62-64-tran sequence number
	{ &Visa_Settle::MoveBlockingID, 1, FIXED},				// 65-tran sequence number
	{ &Visa_Settle::MoveETB, 1, FIXED}						// 66-end of block marker
};

// movers table for settlement parameter requests
const Visa_Settle::rec Visa_Settle::TAB_Params[] =
{
	{ &Visa_Settle::MoveFormatH, 4, FIXED },				// 1-4-record format, type, delimiter, X.25 routing
	{ &Visa_Settle::MoveRecTypeP, 5, FIXED },				// 5-9-record type
	{ &Visa_Settle::MoveCountry, 3, FIXED},					// 10-12-country code
	{ &Visa_Settle::MoveCity, 9, FIXED},				    // 13-21-city code (zip)
	{ &Visa_Settle::MoveMerchCategory, 4, FIXED},			// 22-25-merchant category code
	{ &Visa_Settle::MoveMerchName, 25, FIXED},				// 26-50-merchant name
	{ &Visa_Settle::MoveMerchLocState, 15, FIXED},			// 51-65-merchant location/state
	{ &Visa_Settle::MoveMerchLocation, 4, FIXED},			// 66-70-merchant location code
	{ &Visa_Settle::MoveTermSerial, 8, FIXED},				// 71-78-terminal serial
	{ &Visa_Settle::MoveETB, 1, FIXED}						// 79-end of block marker
};

// movers table for settlement details requests
const Visa_Settle::rec Visa_Settle::TAB_Details[] =
{
	{ &Visa_Settle::MoveFormatH, 4, FIXED },				// 1-4-record format, type, delimiter, X.25 routing
	{ &Visa_Settle::MoveRecTypeD, 5, FIXED },				// 5-9-record type
	{ &Visa_Settle::MoveAuthTranCode, 2, FIXED},			// 10-11-auth transaction code
	{ &Visa_Settle::MoveCardholderID, 1, FIXED},			// 19-cardholder ID code
	{ &Visa_Settle::MoveAccDataSrc, 1, FIXED},				// 20-account data source
	{ &Visa_Settle::MoveAccNumber, 22, FIXED},				// 21-42-cardholder account number
	{ &Visa_Settle::MoveReqACI, 1, FIXED},					// 43-requested ACI
	{ &Visa_Settle::MoveRetACI, 1, FIXED},					// 44-returned ACI
	{ &Visa_Settle::MoveAuthSrcCode, 1, FIXED},				// 45-authorization source code
	{ &Visa_Settle::MoveTranSeqNum, 4, FIXED},				// 46-49-transaction sequence number
	{ &Visa_Settle::MoveRespCode, 2, FIXED},				// 50-51-response code
	{ &Visa_Settle::MoveAuthCode, 6, FIXED},				// 52-57-authorization code
	{ &Visa_Settle::MoveTranDateTime, 10, FIXED},			// 58-67-local transaction date & time
	{ &Visa_Settle::MoveAVSResult, 1, FIXED},				// 68-AVS result code
	{ &Visa_Settle::MoveTranID, 15, FIXED},					// 69-83-Transaction identifier
	{ &Visa_Settle::MoveValidCode, 4, FIXED},				// 84-87-validation code
	{ &Visa_Settle::MoveVoidInd, 1, FIXED},					// 88-88-Void indicator
	{ &Visa_Settle::MoveTranStatCode, 2, FIXED},			// 89-90-Transaction status code
	{ &Visa_Settle::MoveReimb, 1, FIXED},					// 91-reimbursement attribute
	{ &Visa_Settle::MoveSettleAmt, 12, FIXED},				// 92-103-settlement amount
	{ &Visa_Settle::MoveAuthAmt, 12, FIXED},				// 104-115-authorized amount 
};

// movers table for settlement trailers requests
const Visa_Settle::rec Visa_Settle::TAB_Trail[] =
{
	{ &Visa_Settle::MoveFormatH, 4, FIXED },				// 1-4-record format, type, delimiter, X.25 routing
	{ &Visa_Settle::MoveRecTypeT, 5, FIXED },				// 5-9-record type
	{ &Visa_Settle::MoveBatchTransDate, 4, FIXED},			// 10-13-batch transmission date
	{ &Visa_Settle::MoveBatchNum, 3, FIXED},				// 14-16-batch number
	{ &Visa_Settle::MoveRecCount, 9, FIXED},				// 17-25-batch record count
	{ &Visa_Settle::MoveHashTotal, 16, FIXED},				// 26-41-batch hashing total
	{ &Visa_Settle::MoveCashTotal, 16, FIXED},				// 42-57-cashback total
	{ &Visa_Settle::MoveBatchNetDeposit, 16, FIXED},		// 58-73-batch net deposit
};

//-----------------------------------------------------------------------------
//!
//!      call the specific mover function
//!
//! \param
//!      idx             index of the entry in the movers table
//!
//! \return
//!      true, on success
//!
//! \note
//!
bool Visa_Settle::Mover( uint16_t idx ) 
{
	return ( this->*p_m_UsedTAB[idx].MoveF )(  );
}

//-----------------------------------------------------------------------------
//!
//!      get the number of entries in the movers table
//!
//! \return
//!      number of entries
//!
//! \note
//!
uint16_t Visa_Settle::NumMovers(  )
{
	return static_cast<uint16_t> ( m_TabSize / sizeof ( p_m_UsedTAB[0] ) );
}

//-----------------------------------------------------------------------------
//!
//!      get the size of the field identified by idx-entry 
//!
//! \param
//!      idx             index of the entry
//!
//! \return
//!      size of the field
//!
//! \note
//!
uint16_t Visa_Settle::MoverSize( uint16_t idx ) 
{ 
	return p_m_UsedTAB[idx].Size; 
}

//-----------------------------------------------------------------------------
//!
//!      get the attribute of the field identified by idx-entry 
//!
//! \param
//!      idx             index of the entry
//!
//! \return
//!      attribute of the field
//!
//! \note
//!
Visa_Financial::SizeAttr Visa_Settle::FieldAttr( uint16_t idx ) 
{ 
	return p_m_UsedTAB[idx].Type; 
}

//-----------------------------------------------------------------------------
//!
//!      set the type for this message object
//!
//! \param
//!      tt              string identifier - type of the settlement request
//!
//! \return
//!      void
//!
//! \note
//!
void Visa_Settle::SetTransType( HString& tt )
{
	if ( tt == TransactionTag::SETTLE_CLBATCH )
	{
		p_m_UsedTAB = const_cast<rec*>( TAB_Header );
		m_TabSize = sizeof( TAB_Header );
	}
	else 
	if ( tt == TransactionTag::SETTLE_CLTERM )
	{
		p_m_UsedTAB = const_cast<rec*>( TAB_Params );
		m_TabSize = sizeof( TAB_Params );
	}
	else 
	if ( tt == TransactionTag::SETTLE_RUPLOAD )
	{
		p_m_UsedTAB = const_cast<rec*>( TAB_Details );
		m_TabSize = sizeof( TAB_Details );
	}
	else 
	if ( tt == TransactionTag::SETTLE_CLBATCHE )
	{
		p_m_UsedTAB = const_cast<rec*>( TAB_Trail );
		m_TabSize = sizeof( TAB_Trail );
	}
}

//-----------------------------------------------------------------------------
//!
//!      move format field for CLBATCH request
//!
//! \return
//!      true
//!
//! \note
//!
bool Visa_Settle::MoveFormatH(  )
{
	strcpy( m_Buff + m_Off, "K1.Z" );
	return true;
}

//-----------------------------------------------------------------------------
//!
//!      move record type field for CLBATCH request
//!
//! \return
//!      true
//!
//! \note
//!
bool Visa_Settle::MoveRecTypeH(  )
{
	strcpy( m_Buff + m_Off, "H@@@@" );
	return true;
}

//-----------------------------------------------------------------------------
//!
//!      move record type field for CLTERM request
//!
//! \return
//!      true
//!
//! \note
//!
bool Visa_Settle::MoveRecTypeP(  )
{
	strcpy( m_Buff + m_Off, "P@@@@" );
	return true;
}

//-----------------------------------------------------------------------------
//!
//!      move record type field for CLBATCHA request
//!
//! \return
//!      true
//!
//! \note
//!
bool Visa_Settle::MoveRecTypeT(  )
{
	strcpy( m_Buff + m_Off, "T@@@@" );
	return true;
}

//-----------------------------------------------------------------------------
//!
//!      move record type field for RUPLOAD request
//!
//! \return
//!      true
//!
//! \note
//!
bool Visa_Settle::MoveRecTypeD(  )
{
	strcpy( m_Buff + m_Off, "D@@@@" );
	return true;
}

//-----------------------------------------------------------------------------
//!
//!      move agent's bank number
//!
//! \return
//!      true, on success
//!
//! \note
//!
bool Visa_Settle::MoveAgentBankNum(  )
{
	return Move( VisaIITag::AGENT_BIN, Visa_Message::RIGHT );
}

//-----------------------------------------------------------------------------
//!
//!      move agent's chain number
//!
//! \return
//!      true, on success
//!
//! \note
//!
bool Visa_Settle::MoveAgentChainNum(  )
{
	return Move( VisaIITag::AGENT_CHAIN_NUM, Visa_Message::RIGHT );
}

//-----------------------------------------------------------------------------
//!
//!      move batch transaction date
//!
//! \return
//!      true
//!
//! \note
//!
bool Visa_Settle::MoveBatchTransDate(  )
{
	HypCDateTime cur( 0, 0, 0, 0 );
	HString strDate = cur.Format( "%m%d" );
	strcpy( m_Buff + m_Off, strDate.c_str(  ) );
	return true;
}

//-----------------------------------------------------------------------------
//!
//!      move batch number
//!
//! \return
//!      true, on success
//!
//! \note
//!
bool Visa_Settle::MoveBatchNum(  )
{
	return Move( TransactionTag::BATCH_NUMBER, Visa_Message::RIGHT );
}

//-----------------------------------------------------------------------------
//!
//!      move blocking ID
//!
//! \return
//!      true
//!
//! \note
//!
bool Visa_Settle::MoveBlockingID(  )
{
	m_Buff[m_Off] = '0';
	return true;
}

//-----------------------------------------------------------------------------
//!
//!      move ETB field
//!
//! \return
//!      true
//!
//! \note
//!
bool Visa_Settle::MoveETB(  )
{
	m_Buff[m_Off] = ETB;
	return true;
}

//-----------------------------------------------------------------------------
//!
//!      move returned ACI field
//!
//! \return
//!      true
//!
//! \note
//!
bool Visa_Settle::MoveRetACI(  )
{
	return Move( TransactionTag::ACI, Visa_Message::NONE );
}

//-----------------------------------------------------------------------------
//!
//!      move authorization source code
//!
//! \return
//!      true
//!
//! \note
//!
bool Visa_Settle::MoveAuthSrcCode(  )
{
	return Move( TransactionTag::AUTH_SRC, Visa_Message::NONE );
}

//-----------------------------------------------------------------------------
//!
//!      move record count
//!
//! \return
//!      true, on success
//!
//! \note
//!
bool Visa_Settle::MoveRecCount(  )
{
	if ( m_VisaHost )
	{
		HString strRecCount = HypCString( m_RecCount );
		strRecCount.insert( 0, p_m_UsedTAB[m_MoverIdx].Size - strRecCount.length(), '0' );
		strcpy( m_Buff + m_Off, strRecCount.c_str(  ) );
		return true;
	}
	else
	{
		return false;
	}
}

//-----------------------------------------------------------------------------
//!
//!      move hash total field
//!
//! \return
//!      true, on success
//!
//! \note
//!
bool Visa_Settle::MoveHashTotal(  )
{
	if ( m_VisaHost )
	{
		HString strRecCount = HypCString( m_HashTotal );
		strRecCount.insert( 0, p_m_UsedTAB[m_MoverIdx].Size - strRecCount.length(), '0' );
		strcpy( m_Buff + m_Off, strRecCount.c_str(  ) );
		return true;
	}
	else
	{
		return false;
	}
}

//-----------------------------------------------------------------------------
//!
//!      move cashback amount field
//!
//! \return
//!      true, on success
//!
//! \note
//!
bool Visa_Settle::MoveCashTotal(  )
{
	if ( m_VisaHost )
	{
		HString strRecCount = HypCString( m_CashTotal );
		strRecCount.insert( 0, p_m_UsedTAB[m_MoverIdx].Size - strRecCount.length(), '0' );
		strcpy( m_Buff + m_Off, strRecCount.c_str(  ) );
		return true;
	}
	else
	{
		return false;
	}
}

//-----------------------------------------------------------------------------
//!
//!      move batch net deposit amount
//!
//! \return
//!      true, on success
//!
//! \note
//!
bool Visa_Settle::MoveBatchNetDeposit(  )
{
	if ( m_VisaHost )
	{
		HString strRecCount = HypCString( m_NetDeposit );
		strRecCount.insert( 0, p_m_UsedTAB[m_MoverIdx].Size - strRecCount.length(), '0' );
		strcpy( m_Buff + m_Off, strRecCount.c_str(  ) );
		return true;
	}
	else
	{
		return false;
	}
}

//-----------------------------------------------------------------------------
//!
//!      move account number
//!
//! \return
//!      true, on success
//!
//! \note
//!
bool Visa_Settle::MoveAccNumber(  )
{
	return Move( TransactionTag::PAN, Visa_Message::LEFT );
}

//-----------------------------------------------------------------------------
//!
//!      move authorization code
//!
//! \return
//!      true, on success
//!
//! \note
//!
bool Visa_Settle::MoveAuthCode(  )
{
	return Move( TransactionTag::AUTH_ID, Visa_Message::LEFT );
}

//-----------------------------------------------------------------------------
//!
//!      move response code
//!
//! \return
//!      true
//!
//! \note
//!
bool Visa_Settle::MoveRespCode(  )
{
	strcpy( m_Buff + m_Off, "  " );
	return true;
}

//-----------------------------------------------------------------------------
//!
//!      move transaction date and time
//!
//! \return
//!      true, on success
//!
//! \note
//!
bool Visa_Settle::MoveTranDateTime(  )
{
	const HypCData* pData = m_TransData->get( TransactionTag::DATE_TIME );
	if ( pData )
	{
		HString strDateTime = static_cast<const HypCDateTime*>( pData )->Format( "%m%d%H%M%S" );
		strcpy( m_Buff + m_Off, strDateTime.c_str(  ) );
		return true;
	}
	else
	{
		return false;
	}
}

//-----------------------------------------------------------------------------
//!
//!      move AVS result field
//!
//! \return
//!      true
//!
//! \note
//!
bool Visa_Settle::MoveAVSResult(  )
{
	return Move( TransactionTag::AVS_RESPONSE, Visa_Message::NONE );
}

//-----------------------------------------------------------------------------
//!
//!      move transaction ID field
//!
//! \return
//!      true
//!
//! \note
//!
bool Visa_Settle::MoveTranID(  )
{
	return Move( TransactionTag::KEY, Visa_Message::LEFT );
}

//-----------------------------------------------------------------------------
//!
//!      move validation code
//!
//! \return
//!      true
//!
//! \note
//!
bool Visa_Settle::MoveValidCode(  )
{
	return Move( TransactionTag::VALIDATION_CODE, Visa_Message::LEFT );
}

//-----------------------------------------------------------------------------
//!
//!      move void index field
//!
//! \return
//!      true
//!
//! \note
//!
bool Visa_Settle::MoveVoidInd(  )
{
	m_Buff[m_Off] = ' ';
	return true;
}

//-----------------------------------------------------------------------------
//!
//!      move transaction state code
//!
//! \return
//!      true
//!
//! \note
//!
bool Visa_Settle::MoveTranStatCode(  )
{
	strcpy( m_Buff + m_Off, "00" );
	return true;
}

//-----------------------------------------------------------------------------
//!
//!      move reimbursement attribute
//!
//! \return
//!      true
//!
//! \note
//!
bool Visa_Settle::MoveReimb(  )
{
	// will be revised later for debit transactions
	m_Buff[m_Off] = '0';
	return true;
}

//-----------------------------------------------------------------------------
//!
//!      move settlement amount
//!
//! \return
//!      true, on success
//!
//! \note
//!
bool Visa_Settle::MoveSettleAmt(  )
{
	return Move( TransactionTag::TOTAL_AMOUNT, Visa_Message::RIGHT );
}

//-----------------------------------------------------------------------------
//!
//!      move authorization amount
//!
//! \return
//!      true, on success
//!
//! \note
//!
bool Visa_Settle::MoveAuthAmt(  )
{
	return Move( TransactionTag::TOTAL_AMOUNT, Visa_Message::RIGHT );
}

//-----------------------------------------------------------------------------
//!
//!      translate reponse code to the unified format
//!
//! \param
//!      rsp             response code received from a host
//!
//! \return
//!      translated code
//!
//! \note
//!
HString Visa_Settle::TransResponse( const HString& rsp )
{
	if ( rsp == RSPQD )
	{
		return RSPQD_OUR;
	}
	else if ( rsp == RSPGB )
	{
		return RSPGB_OUR;
	}
	else if ( rsp == RSPRB )
	{
		return RSPRB_OUR;
	}
	// no response found
	return HString( "" );
}

//-----------------------------------------------------------------------------
//!
//!      decode packet sent by host
//!
//! \param
//!      pTransData      destination, where to put parsed data
//! \param
//!      pData           buffer of raw data to decode
//! \param
//!      length          size of the buffer pData
//!
//! \return
//!      true, if message was successfully decoded
//!
//! \note
//!
bool Visa_Settle::DecodeMessagePacket( char* pData, size_t length )
{
	if ( m_TransData )
	{
		// skip over the first 7 fields
		m_Off = ( 1 + 1 + 1 + 1 + 5 + 9 + 16 );

		HString rsp_host;
		rsp_host.assign( pData + m_Off, 0, 2 );

		m_TransData->insert( TransactionTag::ISO_RESPONSE_CODE, TransResponse( rsp_host ) );

		m_Off += 7;
		pData[m_Off + 9] = 0;

		m_TransData->insert( TransactionTag::RESPONSE_TEXT, pData + m_Off );

		return true;
	}
	else
	{
		return false;
	}
}

//-----------------------------------------------------------------------------
//!
//!      initialize a settlement message
//!
//! \param
//!      tt              transaction type
//!
//! \return
//!      true, if the message was successfully initialized
//!
//! \note
//!
Visa_Message* Visa_Settle::Init( HypCTransactionData* pTransData, HString tt )
{
	Visa_Message::Init( pTransData );
	SetTransType( tt );

	if ( tt == TransactionTag::SETTLE_CLBATCH )
	{
		m_RecCount = 1;
		m_HashTotal = 0;
		m_NetDeposit = 0;
	}
	else
	{
		m_RecCount++;
		if ( tt == TransactionTag::SETTLE_RUPLOAD )
		{
			const HypCData* p_data = m_TransData->get( TransactionTag::TOTAL_AMOUNT );
			if ( p_data )
			{
				m_HashTotal += p_data->AsInt(  );
				p_data = m_TransData->get( TransactionTag::TYPE_NAME );
				if ( p_data->AsString(  ) == "SALE CREDIT" || p_data->AsString(  ) == "REFUND" )
				{
					m_NetDeposit -= p_data->AsInt(  );
				}
				else
				{
					m_NetDeposit += p_data->AsInt(  );
				}
			}
		}
	}

	return this;
}
