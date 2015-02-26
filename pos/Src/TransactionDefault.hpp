//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hyperware Base Application
//      (c) Copyright 2006
//
// File Name:
//      TransactionDefault.hpp
//
// File Description:
//      TransactionDefault declaration
//
//=============================================================================
#if !defined( _TRANSACTIONDEFAULT_HPP_ )
#define _TRANSACTIONDEFAULT_HPP_

#include <compiler.h>
#include <HypCTransaction.hpp>
#include "BasicTransaction.hpp"

//=============================================================================
// Public defines and typedefs
//=============================================================================

//=============================================================================
// Forward definitions
//=============================================================================

//=============================================================================
//!
//! \brief
//!      Default transaction.
//!
//!      This class provides a default transaction.
//!
//! \sa
//!      HypCTransaction
//!
//=============================================================================
class TransactionDefault : public BasicTransaction
{
	public:
//=============================================================================
// Member functions
//=============================================================================
		//! Constructor, class intended to be created only by 
		//! TransactionFactory
		TransactionDefault();


	protected:
		virtual void DoAssignSteps();

};
// TransactionDefault


#endif // #if !defined( _TRANSACTIONDEFAULT_HPP_ )



