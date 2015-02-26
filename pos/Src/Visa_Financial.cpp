//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hypercom Foundation Classes
//      (c) Copyright 2006
//
//  File Name:
//     Visa_Financial.cpp
//
//  File Description:
//     Implementation of the Class Visa_Financial
//
//=============================================================================
#if defined(__GNUC__)
#pragma implementation
#endif

#include <compiler.h>     // for memset support
#include "Visa_Financial.hpp"
#include <HString.hpp>       // for memset support
#include <HypCDateTime.hpp>
#include <HypCString.hpp>
#include <HypCOptions.hpp>
#include "YemekSepetiTags.h"

//=============================================================================
// Public defines and typedefs
//=============================================================================

// field separator
#define FS  0x1C

// initialize movers table
const Visa_Financial::rec Visa_Financial::TAB_Fields[] =
{
	{ &Visa_Financial::MoveFormat, 3, FIXED },				// 1-3-record format, type, delimiter
	{ &Visa_Financial::MoveAcquirerNum, 6, FIXED },         // 4-acquirer bin
	{ &Visa_Financial::MoveMerchantNum, 12, FIXED},         // 5-merchant number
	{ &Visa_Financial::MoveStoreNum, 4, FIXED},			    // 6-store number
	{ &Visa_Financial::MoveTerminalNum, 4, FIXED},          // 7-terminal number
	{ &Visa_Financial::MoveDevice, 1, FIXED},				// 8-device code
	{ &Visa_Financial::MoveIndustry, 1, FIXED},			    // 9-industry code
	{ &Visa_Financial::MoveCurrency, 3, FIXED},			    // 10-currency code
	{ &Visa_Financial::MoveCountry, 3, FIXED},			    // 11-country code
	{ &Visa_Financial::MoveCity, 9, FIXED},				    // 12-city code (zip)
	{ &Visa_Financial::MoveLang, 2, FIXED},				    // 13-language indicator
	{ &Visa_Financial::MoveTimeZoneDiff, 3, FIXED},         // 14-time zone differential
	{ &Visa_Financial::MoveMerchCategory, 4, FIXED},        // 15-merchant category code
	{ &Visa_Financial::MoveReqACI, 1, FIXED},				// 16-requested ACI
	{ &Visa_Financial::MoveTranSeqNum, 4, FIXED},           // 17-tran sequence number
	{ &Visa_Financial::MoveAuthTranCode, 2, FIXED},         // 18-auth transaction code
	{ &Visa_Financial::MoveCardholderID, 1, FIXED},         // 19-cardholder ID code
	{ &Visa_Financial::MoveAccDataSrc, 1, FIXED},           // 20-account data source
	{ &Visa_Financial::MoveCustDataField, 76, VARIABLE},    // 21-customer data field
	{ &Visa_Financial::MoveFS, 3, FIXED},					// 22-24-FS
	{ &Visa_Financial::MoveAmount, 12, VARIABLE},			// 25-transaction amount
	{ &Visa_Financial::MoveFS, 3, FIXED},					// 22-24-FS
	{ &Visa_Financial::MoveMerchName, 25, FIXED},			// 29-merchant name
	{ &Visa_Financial::MoveMerchLocState, 15, FIXED},		// 30-merchant location/city
	{ &Visa_Financial::MoveFS, 3, FIXED},					// 32-33-FS
	{ &Visa_Financial::MoveGroup3Version, 7, FIXED},		// 34-Group III version number
};

//-----------------------------------------------------------------------------
//!
//!      calls a specific mover function by its index in the table
//!
//! \param
//!      idx             index of the moving function
//!
//! \return
//!      true, on success
//!
//! \note
//!
bool Visa_Financial::Mover( uint16_t idx ) 
{
	return ( this->*TAB_Fields[idx].MoveF )(  );
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
uint16_t Visa_Financial::NumMovers(  )
{
	return sizeof( TAB_Fields ) / sizeof ( TAB_Fields[0] );
}

//-----------------------------------------------------------------------------
//!
//!      get the size of the field to be moved identified by entry in the movers 
//!      table indexed by the idx function argument
//!
//! \param
//!      idx             index of the entry in the movers table
//!
//! \return
//!      size
//!
//! \note
//!
uint16_t Visa_Financial::MoverSize( uint16_t idx ) 
{ 
	return TAB_Fields[idx].Size; 
}

//-----------------------------------------------------------------------------
//!
//!      get the attribute of the field to be moved identified by entry in 
//!      the movers table indexed by the idx function argument
//!
//! \param
//!      idx             index of the entry in the movers table
//!
//! \return
//!      size
//!
//! \note
//!
Visa_Financial::SizeAttr Visa_Financial::FieldAttr( uint16_t idx ) 
{ 
	return TAB_Fields[idx].Type; 
}

//-----------------------------------------------------------------------------
//!
//!      move the message format identifier to the output buffer
//!
//! \return
//!      true
//!
//! \note
//!
bool Visa_Financial::MoveFormat(  )
{
	strcpy( m_Buff + m_Off, "D0." );
	return true;
}

//-----------------------------------------------------------------------------
//!
//!      move the cardholder ID
//!
//! \return
//!      true
//!
//! \note
//!
bool Visa_Financial::MoveCardholderID(  )
{
	m_Buff[m_Off] = '@';
	return true;
}

//-----------------------------------------------------------------------------
//!
//!      move the customer data field
//!
//! \return
//!      true, if the field is successfully moved
//!
//! \note
//!
bool Visa_Financial::MoveCustDataField(  )
{
	bool bRes = false;
	const HypCData* pData = static_cast <const HypCData*> ( m_TransData->get( TransactionTag::POS_ENTRY_MODE ) );
	if ( pData && pData->AsString(  ) == "012" )
	{
		bRes = Move( TransactionTag::PAN, Visa_Message::NONE );
		if ( bRes )
		{
			m_Off += m_MovedSize;
			m_Buff[m_Off++] = FS;
			pData = m_TransData->get( TransactionTag::EXPIRATION_DATE );
			if ( pData )
			{
				HString strDate = static_cast<const HypCDateTime*>( pData )->Format( "%m%y" );
				strcpy( m_Buff + m_Off, strDate.c_str(  ) );
				m_Off += 4;
			}
			else
			{
				bRes = false;
			}
			m_Buff[m_Off++] = FS;
		}
	}
	else
	{
		bRes = Move( TransactionTag::TRACK2, Visa_Message::NONE );
		if ( bRes ) 
		{
			m_Off += m_MovedSize;
		}
	}
	return bRes;
}

//-----------------------------------------------------------------------------
//!
//!      move the certain number of field separators
//!
//! \return
//!      true, if the field is successfully moved
//!
//! \note
//!
bool Visa_Financial::MoveFS(  )
{
	uint16_t endOff = m_Off + TAB_Fields[m_MoverIdx].Size;
	for ( uint16_t i = m_Off; i < endOff; i++ )
	{
		m_Buff[i] = FS;
	}
	return true;
}

//-----------------------------------------------------------------------------
//!
//!      move the amount field
//!
//! \return
//!      true, if the field is successfully moved
//!
//! \note
//!
bool Visa_Financial::MoveAmount(  )
{
	bool bRes = Move( TransactionTag::TOTAL_AMOUNT, Visa_Message::NONULLS );
	if ( bRes )
	{
		m_Off += m_MovedSize;
	}
	return bRes;
}

//-----------------------------------------------------------------------------
//!
//!      move the group III version field
//!
//! \return
//!      true, if the field is successfully moved
//!
//! \note
//!
bool Visa_Financial::MoveGroup3Version(  )
{
	strcpy( m_Buff + m_Off, "001!010" );
	return true;
}

//-----------------------------------------------------------------------------
//!
//!      decode the incoming packet
//!
//! \param
//!      pTransData      destination, where to put parsed data
//! \param
//!      pData           buffer of raw data to decode
//! \param
//!      length          size of the buffer pData
//!
//! \return
//!      true, if the field is successfully moved
//!
//! \note
//!
bool Visa_Financial::DecodeMessagePacket( char* pData, size_t length )
{
	if ( !m_TransData )
	{
		return false;
	}
	bool bRes = false;
	do
	{
		if ( length < 69 ) 
		{
			break;	
		}
		m_Off = 0; 

		// skip the first 3 fields
		m_Off += 3;
		pData[m_Off + 1] = '\0';

		m_TransData->insert( TransactionTag::ACI, pData + m_Off );

		// skip the next 2 fields
		m_Off += 9;
		pData[m_Off + 1] = '\0';

		m_TransData->insert( TransactionTag::AUTH_SRC, pData + m_Off );

		// skip the sequence number 
		m_Off += 5;
		pData[m_Off + 2] = '\0';

		m_TransData->insert( TransactionTag::ISO_RESPONSE_CODE, pData + m_Off );

		// skip approval code
		m_Off += 8;

		char* p = pData + m_Off;
		HypCDateTime* dtp = new HypCDateTime( get2CInt( p + 4 ), get2CInt( p ), get2CInt( p + 2 ) );
		dtp->SetTime( get2CInt( p + 6 ), get2CInt( p + 8 ), get2CInt( p + 10 ), 0 );

		m_TransData->insert( TransactionTag::DATE_TIME, dtp );

		m_Off += 12;

		HypCString AVS_Res = pData[m_Off + 16];
		pData[m_Off + 16]='\0';

		m_TransData->insert( TransactionTag::RESPONSE_TEXT, pData + m_Off );
	
		m_TransData->insert( TransactionTag::AVS_RESPONSE, AVS_Res );

		m_Off += 17;

		pData[m_Off + 12]='\0';
		m_TransData->insert( TransactionTag::RETRIEVAL_REF_NUM, pData + m_Off );

		m_Off += 13;

		if ( !( p = static_cast<char*>( memchr( pData + m_Off, FS, 16 ) ) ) )
		{
			break;
		}
			*p = '\0';
			m_TransData->insert( TransactionTag::KEY, pData + m_Off );

		m_Off = p - pData + 1;

		if ( !( p = static_cast<char*>( memchr( pData + m_Off, FS, 5 ) ) ) )
		{
			break;
		}
			*p = '\0';
			m_TransData->insert( TransactionTag::VALIDATION_CODE, pData + m_Off );

		bRes = true;
	} while ( 0 );
	if ( !bRes ) 
	{
		m_TransData->insert( "ERR_MSG", 
							 HypCString( "Decoding (Visa): invalid packet" ) );
	}
	return bRes;
}

