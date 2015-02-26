//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hyperware Base Application
//      (c) Copyright 2006
//
// File Name:
//      TransactionDefault.cpp
//
// File Contents:
//      Implementation of TransactionDefault
//
//=============================================================================
#include <compiler.h>
#include "TransactionDefault.hpp"
#include "YemekSepetiTags.h"


//-----------------------------------------------------------------------------
//!
//!      Default constructor. Intended to be used by TransactionFactory
//!      only.
//!
//! \return
//!      void
//!
//! \note
//!
TransactionDefault::TransactionDefault(): BasicTransaction()
{
	// Set transaction title
	SetTitle("DEFAULT TRANSACTION");
	
	// Set fixed attributes for this transaction
}


//-----------------------------------------------------------------------------
//!
//!      Assign steps for this transaction
//!
//! \return
//!      None
//!
//! \note
//!
void TransactionDefault::DoAssignSteps()
{
	// assign steps for the transaction
	//AddStep( StepNameTag::STEP_TRANS_SELECT );
}



