//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hyperware Base Application
//      (c) Copyright 2006
//
// File Name:
//      VisaHost.hpp
//
// File Contents:
//      Declaration of the class VisaHost
//
//=============================================================================
#if !defined(_VISAHOST_HPP_)
#define _VISAHOST_HPP_

#if defined(__GNUC__)
#pragma interface
#endif

#include "Visa_Financial.hpp"
#include "Visa_Settle.hpp"
#include "Visa_Message.hpp"
#include "BasicHost.hpp"
#include <HypCTransport.hpp>
#include <HypCPOSConfig.hpp>

//=============================================================================
// Public defines and typedefs
//=============================================================================


//=============================================================================
// Forward definitions
//=============================================================================
class HypCVisa_Transaction;
class HypCTransactionData;

//=============================================================================
//!
//! \brief
//!      This class implements the Hypercom Visa host.
//!
//! \sa
//!      HypCHost, HypCHostInterface, BasicHost
//!
//=============================================================================
class VisaHost : public BasicHost
{
//=============================================================================
// Member structures, enumerations, and class definitions
//=============================================================================
	protected:
		
//=============================================================================
// Member functions
//=============================================================================
	public:
		//! Constructor
		VisaHost();

		//! Destrcutor
		~VisaHost();

	protected:

		//! Checks for offline, floor, reversal, etc. before sending the 
		//! request to the host
		HypEHostResult DoPreProcessing ( HypCTransactionData &TransData );

		//! Build the Visa packet out of the transaction data
		HypEHostResult DoEncodeRequest( HypCTransactionData &TransData, 
		                                unsigned char * const pData, size_t& len );
		
		//! Decodes the incoming Visa buffer
		HypEHostResult DoDecodeResponse( HypCTransactionData &TransData,
		                                 unsigned char * const pData, size_t len );

		//! Set response text
		void SetResponseText( const char *pRspCode, bool settle );

		//! Returns true if host reponse code indicates approval
		HypEHostResult IsHostApproved( HypCTransactionData& TransData );

		//! set the type of transaction
		bool SetVisaTransaction ( HypCTransactionData &TransData );

		//! process settlement
		HypEHostResult DoSettle();

		//! True if pre-transaction reversal processing allowed
		bool AllowReversalProcessing();

//=============================================================================
// Member variables
//=============================================================================
	private:
		//! Visa request message container
		Visa_Message* p_m_VisaMessage;

		//! message object for financial transactions
		Visa_Financial*  m_pFinRequestMessage;		

		//! message object for settlement packets
		Visa_Settle*     m_pSettleRequestMessage;

}; 
// VisaHost

#endif // #if !defined(_VISAHOST_HPP_)

