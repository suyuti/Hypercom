//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hypercom Foundation Classes
//      (c) Copyright 2006
//
//  File Name:
//     Visa_Message.cpp
//
//  File Description:
//     Implementation of the Class Visa_Message
//
//=============================================================================
#if defined(__GNUC__)
#pragma implementation
#endif

#include <compiler.h>     // for memset support
#include "Visa_Message.hpp"
#include <HString.hpp>
#include <HypCDateTime.hpp>
#include <HypCString.hpp>
#include <HypCOptions.hpp>
#include "YemekSepetiTags.h"

//=============================================================================
// Public defines and typedefs
//=============================================================================

//-----------------------------------------------------------------------------
//!
//!      Create a message packet to send to host. Uses the table of "mover"
//!      functions of specific message objects derived from this class 
//!
//! \param
//!      pTransData     data source
//! \param
//!      pData          where message data is to be placed.
//!                     Can be NULL, if caller chooses to use
//!                     only buffer pointer returned by this function
//!
//! \param
//!      length         total length of data, set to actual message
//!                     length on exit
//!
//! \return
//!      true, if a packet if successfully created
//!
//! \note
//!
bool Visa_Message::CreateMessagePacket( char* const pData, size_t& length )
{
	if ( m_TransData )
	{
		bool bRes = true;
		for ( m_MoverIdx = 0, m_Off = 0, m_Buff = pData; 
				bRes && m_MoverIdx < NumMovers(  );
					m_MoverIdx++ )
		{
			bRes = Mover( m_MoverIdx );
			if ( FieldAttr( m_MoverIdx ) == Visa_Message::FIXED )
			{
				m_Off += MoverSize( m_MoverIdx );
			}
		}
		length = m_Off;
		return bRes;
	}
	else
	{
		return false;
	}
}

//-----------------------------------------------------------------------------
//!
//!      Returns a string from transaction data
//!
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
HString Visa_Message::GetTransTag( const char *Tag )
{
	HString strRetValue;		// Default constructor creates an empty HString

	HypCData* pData = (HypCData* ) m_TransData->get( Tag );

	if ( pData )
	{
		// Check if field is currency
		if ( pData->GetClassName(  ) == "HypCCurrency" )
		{
			// Converts to string without decimal point
			strRetValue = HypCString( pData->AsInt() );
	
			// Left padding with '0' till width 12
			// This is standard format for amounts for HypercomHost
			if( strRetValue.length() < 12 )
			{
				strRetValue.insert( 0, 12 - strRetValue.length(), '0' );
			}
	
			return strRetValue;
		} 
		else
		{
			strRetValue = pData->AsString();
		}
	}
	return strRetValue;
}

//-----------------------------------------------------------------------------
//!
//!      Move data identified by the Tag parameter and using description of
//!      the current field in the table of fields to be moved
//!
//! \param
//!      Tag             identificator for field in the map from where to take
//!                      value for the current field
//! \param
//!      align           determines, which align to use and whether to use 
//!                      padding with zeroes for the field
//!
//! \return
//!      A string representation of data, if Tag present, else empty string.
//!      If Tag is HypCCurrency object, it is formated according to Hypercom
//!      message specification - 12 symbols wide, left padding with '0', without
//!      any separators and currency symbols.
//!
//! \note
//!
bool Visa_Message::Move( const char* Tag, Visa_Message::AlignType align )
{
	const HypCData* pData =  m_TransData->get( Tag );
	uint16_t i = 0;
	if ( pData )
	{
		HString strRetValue = pData->AsString(  );
		if ( align != Visa_Message::NONE )
		{
			if ( align == Visa_Message::NONULLS )
			{
				for ( ; strRetValue.c_str(  )[i]=='0'; i++ )
					;
			}
			else
			if ( strRetValue.length(  ) < MoverSize( m_MoverIdx ) )
			{
				if ( align == Visa_Message::RIGHT )
				{
					strRetValue.insert( 0, MoverSize( m_MoverIdx ) - strRetValue.length(), '0' );
				}
				else
				{
					strRetValue.insert( strRetValue.length(  ), MoverSize( m_MoverIdx ) - strRetValue.length(), ' ' );
				}
			}
			else
			if ( strRetValue.length(  ) > MoverSize( m_MoverIdx ) )
			{
				if ( align == Visa_Message::RIGHT )
				{
					strRetValue = strRetValue.substr( strRetValue.length(  ) - MoverSize( m_MoverIdx ),
													MoverSize( m_MoverIdx ) );	
				}
				else
				{
					strRetValue = strRetValue.substr( 0, MoverSize( m_MoverIdx ) );
				}
			}
		}
		strcpy( m_Buff + m_Off, strRetValue.c_str(  ) + i );
		m_MovedSize = strRetValue.length(  );
		return true;
	}
	else
	{
		return false;
	}		
}

//-----------------------------------------------------------------------------
//!
//!      Copy acquirer number from the transaction data to the message packet
//!
//! \return
//!      true, if the field is successfully moved
//!
//! \note
//!
bool Visa_Message::MoveAcquirerNum(  )
{
	return Move( VisaIITag::ACQUIRER_BIN, Visa_Message::NONE );
}

//-----------------------------------------------------------------------------
//!
//!      Copy merchant number from the transaction data to the message packet
//!
//! \return
//!      true, if the field is successfully moved
//!
//! \note
//!
bool Visa_Message::MoveMerchantNum(  )
{
	return Move( VisaIITag::MERCH_NUMBER, Visa_Message::RIGHT );
}

//-----------------------------------------------------------------------------
//!
//!      Copy store number from the transaction data to the message packet
//!
//! \return
//!      true, if the field is successfully moved
//!
//! \note
//!
bool Visa_Message::MoveStoreNum(  )
{
	return Move( VisaIITag::STORE_NUM, Visa_Message::RIGHT );
}

//-----------------------------------------------------------------------------
//!
//!      Copy terminal number from the transaction data to the message packet
//!
//! \return
//!      true, if the field is successfully moved
//!
//! \note
//!
bool Visa_Message::MoveTerminalNum(  )
{
	return Move( VisaIITag::TERM_NUM, Visa_Message::NONE );
}

//-----------------------------------------------------------------------------
//!
//!      Copy device code from the transaction data to the message packet
//!
//! \return
//!      true, if the field is successfully moved
//!
//! \note
//!
bool Visa_Message::MoveDevice(  )
{
	m_Buff[m_Off] = 'D';
	return true;
}

//-----------------------------------------------------------------------------
//!
//!      Copy industry code from the transaction data to the message packet
//!
//! \return
//!      true, if the field is successfully moved
//!
//! \note
//!
bool Visa_Message::MoveIndustry(  )
{
	HypCData* opt = const_cast<HypCData*> ( m_TransData->get( TermConfigTag::TERMINAL_OPT1 ) );

	// See if transaction, has it's own STATUS_FLAGS
	if ( opt )
	{
		if ( static_cast <HypCOptions*>( opt )->IsSet( TC1_REST ) )
		{
			m_Buff[m_Off] = 'F';
		}
		else
		{
			m_Buff[m_Off] = 'R';
		}
		return true;
	}
	else
	{
		return false;
	}
}

//-----------------------------------------------------------------------------
//!
//!      Copy currency code from the transaction data to the message packet
//!
//! \return
//!      true, if the field is successfully moved
//!
//! \note
//!
bool Visa_Message::MoveCurrency(  )
{
	return Move( VisaIITag::MERCH_CURRENCY, Visa_Message::NONE );
}

//-----------------------------------------------------------------------------
//!
//!      Copy country code from the transaction data to the message packet
//!
//! \return
//!      true, if the field is successfully moved
//!
//! \note
//!
bool Visa_Message::MoveCountry(  )
{
	return Move( VisaIITag::MERCH_COUNTRY, Visa_Message::NONE );
}

//-----------------------------------------------------------------------------
//!
//!      Copy city from the transaction data to the message packet
//!
//! \return
//!      true, if the field is successfully moved
//!
//! \note
//!
bool Visa_Message::MoveCity(  )
{
	return Move( VisaIITag::MERCH_CITY, Visa_Message::LEFT );
}

//-----------------------------------------------------------------------------
//!
//!      Copy language code from the transaction data to the message packet
//!
//! \return
//!      true, if the field is successfully moved
//!
//! \note
//!
bool Visa_Message::MoveLang(  )
{
	strcpy( m_Buff + m_Off, "00" );
	return true;
}

//-----------------------------------------------------------------------------
//!
//!      Copy time zone difference from the transaction data into the message 
//!      packet
//!
//! \return
//!      true, if the field is successfully moved
//!
//! \note
//!
bool Visa_Message::MoveTimeZoneDiff(  )
{
	return Move( VisaIITag::TIME_ZONE_DIFF, Visa_Message::NONE );
}

//-----------------------------------------------------------------------------
//!
//!      Copy merchant category from the transaction data to the message 
//!      packet
//!
//! \return
//!      true, if the field is successfully moved
//!
//! \note
//!
bool Visa_Message::MoveMerchCategory(  )
{
	return Move( VisaIITag::MERCH_CAT, Visa_Message::NONE );
}

//-----------------------------------------------------------------------------
//!
//!      Copy request ACI from the transaction data to the message 
//!      packet
//!
//! \return
//!      true, if the field is successfully moved
//!
//! \note
//!
bool Visa_Message::MoveReqACI(  )
{
	m_Buff[m_Off] = 'Y';
	return true;
}

//-----------------------------------------------------------------------------
//!
//!      Copy transaction sequence number from the transaction data to the 
//!      message packet
//!
//! \return
//!      true, if the field is successfully moved
//!
//! \note
//!
bool Visa_Message::MoveTranSeqNum(  )
{
	return Move( TransactionTag::STAN, Visa_Message::RIGHT );
}

//-----------------------------------------------------------------------------
//!
//!      Copy cardholder ID from the transaction data to the 
//!      message packet
//!
//! \return
//!      true, if the field is successfully moved
//!
//! \note
//!
bool Visa_Message::MoveCardholderID(  )
{
	m_Buff[m_Off] = '@';
	return true;
}

//-----------------------------------------------------------------------------
//!
//!      Copy merchant name from the transaction data to the message packet
//!
//! \return
//!      true, if the field is successfully moved
//!
//! \note
//!
bool Visa_Message::MoveMerchName(  )
{
	return Move( VisaIITag::MERCH_NAME, Visa_Message::LEFT );
}

//-----------------------------------------------------------------------------
//!
//!      Copy merchant location state from the transaction data to the
//!      message packet
//!
//! \return
//!      true, if the field is successfully moved
//!
//! \note
//!
bool Visa_Message::MoveMerchLocState(  )
{
	return Move( VisaIITag::MERCH_CITY_STATE, Visa_Message::NONE );
}

//-----------------------------------------------------------------------------
//!
//!      Copy merchant location from the transaction data to the
//!      message packet
//!
//! \return
//!      true, if the field is successfully moved
//!
//! \note
//!
bool Visa_Message::MoveMerchLocation(  )
{
	HString fcl = GetTransTag( VisaIITag::FIRST_CHAR_LOCATION );
	if ( fcl.c_str(  )[0] <= 0x20 )
	{
		m_Buff[m_Off++] = '0';
	}
	else
	{
		m_Buff[m_Off++] = fcl.c_str(  )[0];
	}
	return Move( VisaIITag::MERCH_LOCATION, Visa_Message::NONE );
}

//-----------------------------------------------------------------------------
//!
//!      Copy terminal serial from the transaction data to the
//!      message packet
//!
//! \return
//!      true, if the field is successfully moved
//!
//! \note
//!
bool Visa_Message::MoveTermSerial(  )
{
	return Move( VisaIITag::TERMINAL_SERIAL_NUM, Visa_Message::NONE );
}

//-----------------------------------------------------------------------------
//!
//!      Copy authorization transaction code from the transaction data to the
//!      message packet
//!
//! \return
//!      true, if the field is successfully moved
//!
//! \note
//!
bool Visa_Message::MoveAuthTranCode(  )
{
	const HypCData* p_data = m_TransData->get( TransactionTag::TYPE_NAME ); 
	if ( p_data )
	{	
		if ( p_data->AsString(  ) == "SALE CREDIT" )
		{
			strcpy( m_Buff + m_Off, "54" );
			return true;
		}
		else
		if ( p_data->AsString(  ) == "REFUND" )
		{
			strcpy( m_Buff + m_Off, "CR" );
			return true;
		}
	}
	return false;
}

//-----------------------------------------------------------------------------
//!
//!      Copy account data source from the transaction data to the
//!      message packet
//!
//! \return
//!      true, if the field is successfully moved
//!
//! \note
//!
bool Visa_Message::MoveAccDataSrc(  )
{
	const HypCData* pData = static_cast <const HypCData*> ( m_TransData->get( TransactionTag::POS_ENTRY_MODE ) );
	if ( pData && pData->AsString(  ) == "012" )
	{
		m_Buff[m_Off] = 'T';
	}
	else
	{
		m_Buff[m_Off] = 'D';
	}
	return true;
}

//-----------------------------------------------------------------------------
//!
//!		convert 2-digit number string representation into integer
//!
//! \return
//!      true, if the field is successfully moved
//!
//! \note
//!
uint16_t Visa_Message::get2CInt( const char* pAsc )
{
	return static_cast <uint16_t>( pAsc[0] - '0' ) * 10 + static_cast <uint16_t>( pAsc[1] - '0' );
}
