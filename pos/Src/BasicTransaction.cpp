//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hyperware Base Application
//      (c) Copyright 2006
//
// File Name:
//      BasicTransaction.cpp
//
// File Contents:
//      Implementation of BasicTransaction
//
//=============================================================================
#include <compiler.h>
#include "YemekSepetiMain.hpp"
#include "BasicTransaction.hpp"

//-----------------------------------------------------------------------------
//!
//!      Default constructor. Typically, to be used by
//!      HypCTransaction factory only.
//!
//! \return
//!      void
//!
//! \note
//!
BasicTransaction::BasicTransaction():
	HypCTransaction(), m_jrn( 0 )
{
}

//-----------------------------------------------------------------------------
//!
//!      Execution method common for all application transactions
//!
//! \return
//!      ExecAction, returned from the base class
//!
//! \note
//!
Exec_Action BasicTransaction::DoExecute()
{
	/*if ( !GetMultiLang()->GetPromptsObj().GetFile().IsOpen() )
	{
		GetMultiLang()->GetPromptsObj().GetFile().Open();
	}
	*/

	Exec_Action ea = HypCTransaction::DoExecute();

	if ( m_jrn && m_jrn->IsOpen() ) 
	{
		m_jrn->Close();
	}

	return ea;
}


