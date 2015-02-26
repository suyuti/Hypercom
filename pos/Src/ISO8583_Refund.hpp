//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hypercom Foundation Classes 
//      (c) Copyright 2006
//
// File Name:
//      ISO8583_Refund.hpp
//
// File Contents:
//      Interface for the ISO8583_Refund class. This is the REFUND transaction
//      for the ISO host.
//
//=============================================================================
#if !defined(_HYPCISO8583_REFUND_HPP_)
#define _HYPCISO8583_REFUND_HPP_

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
//!      Creates or parses ISO8583 refund transaction packet
//!
//!      The class creates or parses a IS08583 message packet for a
//!      Refund transaction.
//!
//! \sa
//!      HypCISO8583_Transaction, HypCISO8583_Message
//!
//=============================================================================
class ISO8583_Refund : public HypCISO8583_Transaction
{
//=============================================================================
// Member structures, enumerations, and class definitions
//=============================================================================

//=============================================================================
// Member functions
//=============================================================================

	public:
		//! Constuctor
		ISO8583_Refund ();

		//! mov message authorization code
		short MovMsgAuthCode (  );

	protected:
		//! Processing Code                  
		virtual bool MovB3ProcCode (  );

		
		//! Called when a bit is NOT moved
		virtual bool BitNotFoundError( int /* FailedBit */, 
		      enum Direction /* Direction */ )
		{ 
			return false;
		}
				
		//! Called when a data match has failed
		virtual bool DataMatchFailed( int /* FailedBit */ )
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
// ISO8583_Refund

#endif // #if !defined(_HYPCISO8583_REFUND_HPP_)
