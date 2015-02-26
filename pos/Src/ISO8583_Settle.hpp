//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hypercom Foundation Classes 
//      (c) Copyright 2006
//
// File Name:
//      ISO8583_Settle.hpp
//
// File Contents:
//      Interface for the ISO8583_Settle class. This is the SETTLE transaction
//      for the ISO host.
//
//=============================================================================
#if !defined(_HYPCISO8583_SETTLE_HPP_)
#define _HYPCISO8583_SETTLE_HPP_

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
//!      Creates or parses ISO8583 settlement transaction packet
//!
//!      The class creates or parses a IS08583 message packet for a
//!      Settle transaction.
//!
//! \sa
//!      HypCISO8583_Transaction, HypCISO8583_Message
//!
//=============================================================================
class ISO8583_Settle : public HypCISO8583_Transaction
{
//=============================================================================
// Member structures, enumerations, and class definitions
//=============================================================================

//=============================================================================
// Member functions
//=============================================================================

	public:
		//! Constuctor
		ISO8583_Settle ();

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
// ISO8583_Settle

#endif // #if !defined(_HYPCISO8583_SETTLE_HPP_)
