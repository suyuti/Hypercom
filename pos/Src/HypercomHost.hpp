//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hyperware Base Application
//      (c) Copyright 2006
//
// File Name:
//      HypercomHost.hpp
//
// File Contents:
//      Declaration of the class HypercomHost
//
//=============================================================================
#if !defined(_HYPERCOMHOST_HPP_)
#define _HYPERCOMHOST_HPP_

#if defined(__GNUC__)
#pragma interface
#endif

#include <HypCTransport.hpp>
#include "BasicISOHost.hpp"

//=============================================================================
// Public defines and typedefs
//=============================================================================


//=============================================================================
// Forward definitions
//=============================================================================
class HypCTransactionData;

//=============================================================================
//!
//! \brief
//!      Implements transaction processing for Hypercom host.    
//!
//!      This class implements the Hypercom ISO8583 host.
//!
//! \sa
//!      HypCHost, HypCHostInterface, BasicISOHost, BasicHost
//!
//=============================================================================
class HypercomHost : public BasicISOHost
{
//=============================================================================
// Member structures, enumerations, and class definitions
//=============================================================================
		
//=============================================================================
// Member functions
//=============================================================================
	public:
		//! Constructor
		HypercomHost() { }

		//! Destrcutor
		~HypercomHost() { }

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
// HypercomHost

#endif // #if !defined(_HYPERCOMHOST_HPP_)

