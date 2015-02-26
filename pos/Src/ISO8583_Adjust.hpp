//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hypercom Foundation Classes 
//      (c) Copyright 2006
//
// File Name:
//      ISO8583_Adjust.hpp
//
// File Contents:
//      Interface for the ISO8583_Adjust class. This is the ADJUST transaction
//      for the ISO host.
//
//=============================================================================
#if !defined(_HYPCISO8583_ADJUST_HPP_)
#define _HYPCISO8583_ADJUST_HPP_

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
//!      Creates or parses ISO8583 adjustment transaction packet.
//!
//!      The class creates or parses a IS08583 message packet for a
//!      Adjust transaction.
//!
//! \sa
//!      HypCISO8583_Transaction, HypCISO8583_Message
//!
//=============================================================================
class ISO8583_Adjust : public HypCISO8583_Transaction
{
//=============================================================================
// Member structures, enumerations, and class definitions
//=============================================================================

//=============================================================================
// Member functions
//=============================================================================

	public:
		//! Constuctor
		ISO8583_Adjust ( bool sale );

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
		//! determines, whether it's sale or refund transaction
		bool bSale;
}; 
// ISO8583_Adjust

#endif // #if !defined(_HYPCISO8583_ADJUST_HPP_)
