//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hypercom Foundation Classes
//      (c) Copyright 2006
//
// File Name:
//      ISO8583_BatchUpload.cpp
//
// File Contents:
//      Implementation of the ISO8583_BatchUpload class.
//
//=============================================================================
#if defined(__GNUC__)
#pragma implementation
#endif

#include <compiler.h>
#include "ISO8583_BatchUpload.hpp"
#include "YemekSepetiTags.h"

// Bit fields to be processed for the transaction request message
const uint8_t ISO8583_BatchUpload::RequestBitArray[] =
{
	2,	// Primary account number
	3,  // Processing Code
	4,  // Amount
	11, // Systems Trace Audit Number
	12, // Time
	13, // Date
	14, // PAN Expiration date
	22, // POS entry mode
	24, // Network International Identifier
	25, // POS condition code
	37, // Retrieval reference number
	38, // Authorization ID response
	39, // Response code
	41, // Terminal Id
	42, // Acceptor Id
	53, // Security control info
	54, // Additional amounts
	60, // Batch number
	61, // Product codes
	62, // Invoice/ECR reference number
	63, // Private Field 63
	64, // Private Field 64
	0
};

// Bit fields to be processed for the transaction repsonse message
const uint8_t ISO8583_BatchUpload::ResponseBitArray[] =
{
	3,  // Processing Code
	4,  // Amount
	11, // Systems Trace Audit Number
	12, // Time, Transaction
	13, // Date, Transaction
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
//!      Basic constructor.The Settle transaction is saved to the journal and
//!      the message type ID for request is 0x0320. It uses the fields defined
//!      by the table m_SettleFunctions
//!
//! \return
//!      void
//!
//! \note
//!
ISO8583_BatchUpload::ISO8583_BatchUpload() :
	HypCISO8583_Transaction ( ISO8583_FileUpdTrAdv, RequestBitArray,
	                          ResponseBitArray )
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
//!      For settle processing code = 92 00 0x 
//!      a = account selection, x = processing flow	 
//!
bool ISO8583_BatchUpload::MovB3ProcCode ( )
{
	unsigned char Buffer[3];

	if( m_bIsRequesting )
	{
		
		Buffer[0] = 0x92;	// Settle transaction

		Buffer[1] = 0x00;
		
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


