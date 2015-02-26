//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hyperware Base Application
//      (c) Copyright 2006
//
// File Name:
//      TransactionFactory.cpp
//
// File Contents:
//      Implementation of TransactionFactory
//
//=============================================================================
#include <compiler.h>
#include "YemekSepetiTags.h"
#include "TransactionFactory.hpp"
#include "TransAnketYap.hpp"
#include "TransModemTest.hpp"
#include "TransSiparisler.hpp"


const char* TransactionNameTag::TRANS_SIPARISLER    = "TrSiparisler";
const char* TransactionNameTag::TRANS_ANKET_YAP     = "tr anket yap";
const char* TransactionNameTag::QUIT_APP			= "Quit";
const char* TransactionNameTag::TRANS_MODEM_TEST    = "tr modemtest";

//-----------------------------------------------------------------------------
//!
//!      TransactionFactory constructer. Initializes pointer to step table and
//!      table entry count
//!
//! \return
//!      Nothing
//!
//! \note
//!
TransactionFactory::TransactionFactory( HypCTransactionStepFactory *pTrStepFact, 
				    HypCTransactionManager* pTransactionManager ):
		HypCTransactionFactory( pTrStepFact, pTransactionManager )

{
}



//-----------------------------------------------------------------------------
//!
//!      Creates a transaction based on transaction id.
//!
//! \param
//!      TransactionId    transaction identifier
//!
//! \return
//!      pointer to the newly created Transaction object
//!
//! \note
//!
HypCTransaction *TransactionFactory::DoCreateTransaction( const char *sTransactionName )			
{

	HString TransactionName = sTransactionName;

    if( TransactionName == TransactionNameTag::TRANS_ANKET_YAP )
    {
        return new CTransAnketYap();
    }

    if( TransactionName == TransactionNameTag::TRANS_MODEM_TEST )
    {
        return new CTransModemTest();
    }
    if( TransactionName == TransactionNameTag::TRANS_SIPARISLER )
    {
        return new CTransSiparisler();
    }

/*	if( TransactionName == TransactionNameTag::TRANS_SEARCH_INVOICE )
	{
		return new TransactionInvoice( );
	}
*/
	//return = new StepShowNoStepError();
	return 0;

}
