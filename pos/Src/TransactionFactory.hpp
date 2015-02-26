//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hyperware Base Application
//      (c) Copyright 2006
//
// File Name:
//      TransactionFactory.hpp
//
// File Description:
//      TransactionFactory declaration
//
//=============================================================================
#if !defined( _TRANSACTIONFACTORY_HPP_ )
#define _TRANSACTIONFACTORY_HPP_

#include <compiler.h>
#include <HypCTransactionFactory.hpp>

//=============================================================================
// Public defines and typedefs
//=============================================================================

// Contains pointers to the names of transactions
struct TransactionNameTag
{
    static const char* TRANS_SIPARISLER;
    static const char* TRANS_MODEM_TEST;

    static const char* TRANS_ANKET_YAP;
    static const char* TRANS_RAPORLAR;
    static const char* TRANS_GUNSONU;
    static const char * QUIT_APP;
};


//=============================================================================
//! \brief
//!      Creates transaction objects.
//!
//!      This class provides a factory that creates a transaction based
//!      on a given name. The transactions are added
//!      by calling CreateAssociations().
//!
//!      Use base class member CreateInstance( const string& sTransName )
//!      to create a transaction
//!
//! \sa
//!      HypCTransactionFactory
//!
//=============================================================================
class TransactionFactory : public HypCTransactionFactory
{
	public:
		//! Contructor
		TransactionFactory( HypCTransactionStepFactory *pTrStepFact,
		     HypCTransactionManager* pTransactionManager );
		
		//! Destructor
		virtual ~TransactionFactory(){};

	
	protected:
	
		//! Create a Transaction object
		HypCTransaction *DoCreateTransaction( const char *sTransactionName );	

};
// TransactionFactory

#endif // #if !defined( _TRANSACTIONFACTORY_HPP_ )

