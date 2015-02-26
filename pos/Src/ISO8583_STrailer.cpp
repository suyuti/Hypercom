//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hypercom Foundation Classes
//      (c) Copyright 2006
//
// File Name:
//      ISO8583_STrailer.cpp
//
// File Contents:
//      Implementation of the ISO8583_STrailer class.
//
//=============================================================================
#if defined(__GNUC__)
#pragma implementation
#endif

#include <compiler.h>
#include "ISO8583_STrailer.hpp"
#include "YemekSepetiTags.h"

// Bit fields to be processed for the transaction request message
const uint8_t ISO8583_STrailer::RequestBitArray[] =
{
	3,  // Processing Code
	11, // Systems Trace Audit Number
	24, // Network International Identifier
	41, // Terminal Id
	42, // Acceptor Id
	53, // security control info
	60, // batch number
	63, // Private Field 63
	64, // Private Field 64
	0
};

// Bit fields to be processed for the transaction repsonse message
const uint8_t ISO8583_STrailer::ResponseBitArray[] =
{
	3,  // Processing Code
	11, // Systems Trace Audit Number
	12, // Time, Transaction
	13, // Date, Transaction
	24, // Network International Identifier
	37, // Retrieval Reference Number
	39, // response code
	41, // Terminal Id
	48, // Additional data - private
	53, // PIN number
	63, // Private Field 63
	64, // Message Auth Code
	0
};

//-----------------------------------------------------------------------------
//!
//!      Basic constructor.The Settle transaction is saved to the journal and
//!      the message type ID for request is 0x0500. It uses the fields defined
//!      by the table m_SettleFunctions
//!
//! \return
//!      void
//!
//! \note
//!
ISO8583_STrailer::ISO8583_STrailer() :
	HypCISO8583_Transaction ( ISO8583_CardAccReconReq, RequestBitArray,
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
//!      For settle processing code = 96 00 0x 
//!      a = account selection, x = processing flow	 
//!
bool ISO8583_STrailer::MovB3ProcCode ( )
{
	unsigned char Buffer[3];

	if( m_bIsRequesting )
	{
		
		Buffer[0] = 0x96;	// Settlement trailer

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

