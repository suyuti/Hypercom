//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hypercom Foundation Classes
//      (c) Copyright 2006
//
// File Name:
//      ISO8583_Offline.cpp
//
// File Contents:
//      Implementation of the ISO8583_Offline class.
//
//=============================================================================
#if defined(__GNUC__)
#pragma implementation
#endif

#include <compiler.h>
#include "ISO8583_Offline.hpp"
#include "YemekSepetiTags.h"

// Bit fields to be processed for the transaction request message
const uint8_t ISO8583_Offline::RequestBitArray[] =
{
	2,  // Primary Account Number
	3,  // Processing Code
	4,  // Amount, Transaction
	11, // Systems Trace Audit Number
	12, // Time, local trans.
	13, // Date, local trans.
	14, // Date, Expiry
	22, // POS Entry Mode
	24, // Network International Identifier
	25, // POS Condition Code
	38, // Auth. Id. Response
	41, // Terminal Id
	42, // Acceptor Id
	53, // Security control info
	61, // Private Field 61, Descriptors
	62, // Private Field 62, Invoice Number
	63, // Private Field 63
	64, // Message Auth. Code
	0
};

// Bit fields to be processed for the transaction repsonse message
const uint8_t ISO8583_Offline::ResponseBitArray[] =
{
	3,  // Processing Code
	4,  // Amount, Transaction
	11, // Systems Trace Audit Number
	24, // Network International Identifier
	37, // Retrieval Reference Number
	39, // response code
	41, // Terminal Id
	53, // PIN number
	63, // Private Field 63
	64, // Message Auth Code
	0
};

//-----------------------------------------------------------------------------
//!
//!      Basic constructor.The Offline transaction is saved to the journal and
//!      the message type ID for request is 0x0200. It uses the fields defined
//!      by the table m_OfflineFunctions
//!
//! \return
//!      void
//!
//! \note
//!
ISO8583_Offline::ISO8583_Offline( bool sale ) :
	HypCISO8583_Transaction ( ISO8583_FinTransAdv, RequestBitArray,
	                          ResponseBitArray ), bSale( sale )
{
	
}


//-----------------------------------------------------------------------------
//!
//!      Move the Processing Code to the buffer. Response direction is ignored
//!      since there is no place to put it in Transaction record
//!
//! \return
//!      true  -  The data was moved succesfully to the buffer     
//!      false -  No need to move data
//!
//! \note
//!  
//!      For sale processing code = 00 a0 0x 
//!      a = account selection, x = processing flow	 
//!
bool ISO8583_Offline::MovB3ProcCode ( )
{
	unsigned char Buffer[3];

	if( m_bIsRequesting )
	{
		if ( bSale )
		{
			Buffer[0] = 0x00;	// Offline sale transaction
		}
		else
		{
			Buffer[0] = 0x20;	// Offline refund transaction
		}

		// get the account ID
		const HypCData* pData = m_TransData->get( TransactionTag::ACCOUNT_ID );
		
		if(pData)
		{
			// yes
			Buffer[1] = ( static_cast<uint8_t>(pData->AsWord())  & 0x0f ) << 4;
		}
		
		Buffer[2] = 0x00;	

		m_pMessage->SetDataElementDirect( 3, Buffer , 3 );
		return true;

	}
	else
	{
		// call base class implementation
		return HypCISO8583_Transaction::MovB3ProcCode();
	}
}



