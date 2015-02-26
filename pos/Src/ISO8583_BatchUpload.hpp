//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hypercom Foundation Classes 
//      (c) Copyright 2006
//
// File Name:
//      ISO8583_BatchUpload.hpp
//
// File Contents:
//      Interface for the ISO8583_BatchUpload class. This is the BATCHUPLOAD transaction
//      for the ISO host.
//
//=============================================================================
#if !defined(_HYPCISO8583_BATCHUPLOAD_HPP_)
#define _HYPCISO8583_BATCHUPLOAD_HPP_

#if defined(__GNUC__)
#pragma interface
#endif

#include <HypCISO8583_Transaction.hpp>

//=============================================================================
// Public defines and typedefs
//=============================================================================

//=============================================================================
// Forward definitions
//=============================================================================

//=============================================================================
//!
//! \brief
//!      Creates or parses ISO8583 batch upload transaction packet
//!
//!      The class creates or parses a IS08583 message packet for a
//!      batch upload ( part of the settlement transaction ).
//!
//! \sa
//!      HypCISO8583_Transaction, HypCISO8583_Message
//!
//=============================================================================
class ISO8583_BatchUpload : public HypCISO8583_Transaction
{
//=============================================================================
// Member structures, enumerations, and class definitions
//=============================================================================

//=============================================================================
// Member functions
//=============================================================================

	public:
		//! Constuctor
		ISO8583_BatchUpload ();

		//! mov message authorization code
		short MovMsgAuthCode (  );

	protected:
		//! Processing Code                  
		virtual bool MovB3ProcCode (  );

		
		//! Called when a bit is NOT moved
		virtual bool BitNotFoundError( int /*FailedBit*/, 
									   enum Direction /*Direction*/ )
		{ 
			return false;
		}
				
		//! Called when a data match has failed
		virtual bool DataMatchFailed( int /*FailedBit*/ )
		{ 
			return false;
		}


//=============================================================================
// Member variables
//=============================================================================
	private:
		//! array of request bits
		static const uint8_t RequestBitArray[];
		//! array of response bits
		static const uint8_t ResponseBitArray[];
}; 
// ISO8583_BatchUpload

#endif // #if !defined(_HYPCISO8583_BATCHUPLOAD_HPP_)
