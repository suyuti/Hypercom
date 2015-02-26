//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hyperware Base Application
//      (c) Copyright 2006
//
// File Name:
//      BasicTransaction.hpp
//
// File Description:
//      BasicTransaction declaration
//
//=============================================================================
#if !defined( _BASICTRANSACTION_HPP_ )
#define _BASICTRANSACTION_HPP_

#include <compiler.h>
#include <HypCTransaction.hpp>
#include <HypCJournal.hpp>

//=============================================================================
// Public defines and typedefs
//=============================================================================

//=============================================================================
// Forward definitions
//=============================================================================

//=============================================================================
//!
//! \brief
//!      Basic transaction class containig common functionality for all
//!      application classes.
//!
//! \sa
//!      HypCTransaction
//!
//=============================================================================
class BasicTransaction : public HypCTransaction
{
//=============================================================================
// Member functions
//=============================================================================
	public:
		//! Constructor, class intended to be created only by 
		//! TransactionFactory
		BasicTransaction();

		inline HypCJournal* SetJournal( HypCJournal* jrn );

		inline HypCJournal* GetJournal(  );

	protected:

		//! execution method common for all application transaction
		Exec_Action DoExecute();

	private:
		//! the default journal 
		HypCJournal* m_jrn;
};
// BasicTransaction

inline HypCJournal* BasicTransaction::SetJournal( HypCJournal* jrn )
{
	HypCJournal* old_one = m_jrn;
	m_jrn = jrn;
	return old_one;
}

// obtain journal of this transaction
inline HypCJournal* BasicTransaction::GetJournal(  )
{
	if ( m_jrn )
	{
		return m_jrn;
	}
	else
	{
		return HypCTransaction::GetJournal();
	}
}

#endif // #if !defined( _BASICTRANSACTION_HPP_ )


