//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hyperware Base Application
//      (c) Copyright 2006
//
// File Name:
//      AmexHost.hpp
//
// File Contents:
//      Declaration of the class AmexHost
//
//=============================================================================
#if !defined(_AMEXHOST_HPP_)
#define _AMEXHOST_HPP_

#if defined(__GNUC__)
#pragma interface
#endif

#include "BasicISOHost.hpp"
#include <HypCTransport.hpp>
#include <HypCISO8583_Message.hpp>
#include <HypCPOSConfig.hpp>

//=============================================================================
// Public defines and typedefs
//=============================================================================

//=============================================================================
// Forward definitions
//=============================================================================
class HypCISO8583_Transaction;
class HypCTransactionData;

//=============================================================================
//!
//! \brief
//!      Implements AMEX host transaction processing.
//!
//!      This class implements the Amex ISO8583 host.
//!
//! \sa
//!      HypCHost, HypCHostInterface, BasicHost
//!
//=============================================================================
class AmexHost : public BasicISOHost
{
//=============================================================================
// Member structures, enumerations, and class definitions
//=============================================================================
		
//=============================================================================
// Member functions
//=============================================================================
	public:
		//! Constructor
		AmexHost() { }

		//! Destrcutor
		~AmexHost() { }

	protected:

		//! Checks for offline, floor, reversal, etc. before sending the 
		//! request to the host
		HypEHostResult DoPreProcessing ( HypCTransactionData &TransData );

		//! Prepares standard totals(00-11), required by settlement
		bool PrepareB63StandardTotals( HString& Bit63, HypCTransactionData& TransData );

//=============================================================================
// Member variables
//=============================================================================
	private:
		
}; 
// AmexHost

#endif // #if !defined(_AMEXHOST_HPP_)

