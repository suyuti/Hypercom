//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hyperware Base Application
//      (c) Copyright 2006
//
// File Name:
//      StepHostCommunicate.hpp
//
// File Description:
//      StepHostCommunicate declaration
//
//=============================================================================
#if !defined( _STEPHOSTCOMMUNICATE_HPP_ )
#define _STEPHOSTCOMMUNICATE_HPP_

#include <compiler.h>
#include <HypCTransactionStep.hpp>
//#include <HypCMultiLang.hpp>

//=============================================================================
// Public defines and typedefs
//=============================================================================

//=============================================================================
// Forward definitions
//=============================================================================

//=============================================================================
//!
//! \brief
//!      Communicates with card processing host.
//!
//!      This class provides a transaction step that accomplishes actual 
//!      communication with the host. The step is used in the following 
//!      transactions:
//!      TransactionAuth,
//!      TransactionSaleCredit,
//!      TransactionRefundCredit,
//!      TransactionSettle
//!
//! \sa
//!      HypCTransactionStep
//!
//=============================================================================
class StepHostCommunicate : public HypCTransactionStep
{
//=============================================================================
// Member functions
//=============================================================================
	public:
		//! Constructor, class intended to be created only by StepFactory
		StepHostCommunicate() : HypCTransactionStep() {}

		//! Returns host string based on host state from HypCHostInterface
		static const char* GetHostStateText( int state, HypCMultiLang* );
			
		//! Return string based on result retured by HypCHostInterface
		static void GetHostErrorText( int Result, HString& str, HypCUserInterface* );
		
	protected:
		//! Execute the step
		virtual bool doExecute();

};
// StepHostCommunicate


#endif // #if !defined( _STEPHOSTCOMMUNICATE_HPP_ )


