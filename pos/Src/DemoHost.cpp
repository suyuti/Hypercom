///=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hyperware Base Application
//      (c) Copyright 2006
//
//  File Name:
//      DemoHost.cpp
//
//  File Description:
//       Declaration of the class DemoHost
//
//=============================================================================
#if defined(__GNUC__)  // GNU compiler
#pragma implementation
#endif

#include <HypCMLTransport.hpp>
#include <HypCDocumentManager.hpp>
#include <HypCPOSConfig.hpp>
#include <HypCTimer.hpp>
#include <HypCJournal.hpp>
#include <HypCOptions.hpp>
#include "DemoHost.hpp"
#include "YemekSepetiTags.h"

//-----------------------------------------------------------------------------
//!
//!      The constructor is accesible only to the HostFactory
//!
//! \return
//!      void
//!
//! \note
//!
DemoHost::DemoHost( ) :
	HypCHost( ),
	m_nFakeProcessingTime ( 3 ),   // 3 seconds
	m_nFakeConnectTime ( 3 ),  	   // 3 seconds
	m_nFakeSettlementTime( 10 )    // 10 seconds ( usually much longer, demo only )
{
}

//-----------------------------------------------------------------------------
//!
//!      Configures the HypCComunication object with setup communication
//!	    parameters.
//!
//! \param
//!      Comm            reference to HypCMLTransport object
//! \param
//!      bool            flag: settle of not
//!
//! \return
//!      true
//!
//! \note
//!
bool DemoHost::DoConfigureCommuncations( HypCMLTransport& /*Comm*/, bool/*SETTLE or not*/ )
{
	// do nothing for demo
	return true;
}

//-----------------------------------------------------------------------------
//!
//!      Simulates a host settlement process
//!
//! \return
//!      HOST_OK
//!
//! \note
//!
HypEHostResult DemoHost::DoSettle()
{

	// just wait for some time
	HypCEvent ev;
	HypCEventInfo ei;
	ev.Wait(ei,m_nFakeSettlementTime * 1000);

	// always return good
	return HOST_OK;
}



//-----------------------------------------------------------------------------
//!
//!      Sets initial values for the transaction
//!
//! \param
//!      TransData       reference to transaction data container
//!
//! \return
//!      HOST_OK if the transaction was succesfull, or another error code if
//!      there was a problem.
//!
//! \note
//!       This function is responsible for setting class member m_ContactHost.
//!       Set to true if host is to be contacted ( transaction performed ),
//!       else false. Generally the host is not contacted for offline
//!       transactions or for transactions where amount is lower than some
//!       preset limit.
//!
HypEHostResult DemoHost::DoPreProcessing( HypCTransactionData& /*TransData*/ )
{
	HypEHostResult res = HOST_OK;
	m_bContactHost = true;
	return res;
}

//-----------------------------------------------------------------------------
//!
//!      No need to encode anything for this host.
//!
//! \param
//!      TransData       reference to transaction data container
//! \param
//!      pData           pointer to buffer where encoded data is to be placed
//! \param
//!      len             maximum length of encoded data on input, set to actual
//!                      length on output
//!
//! \return
//!      HOST_OK for success else other result for error.
//!      Always HOST_OK for DemoHost.
//!
//! \note
//!      No need to encode anything for this host
//!
HypEHostResult DemoHost::DoEncodeRequest( HypCTransactionData& /*TransData*/,
                                    		  unsigned char* const /*pData*/,
											  size_t& len )
{
	len = 0;
	return HOST_OK;
}


//-----------------------------------------------------------------------------
//!
//!      Fakes sending the transaction request to a host.
//!
//! \param
//!      pData           not used
//! \param
//!      len             not used
//!
//! \return
//!      HOST_OK
//!
//! \note
//!      The overrides same function in HypCHost
//!
HypEHostResult DemoHost::SendRequest( unsigned char * const /*pData*/, size_t /*len*/ )
{

	HypCEvent ev;
	HypCEventInfo ei;

	SetState ( SendingRequest );
	Notify();

	ev.Wait(ei,m_nFakeProcessingTime * 1000);

	// eventually need special function for this
	// HFC_Wait( nFakeProcessingTime );

	return HOST_OK;
}

//-----------------------------------------------------------------------------
//!
//!     Overrides default ReceiveResponse to do a fake 3 second response time.
//!
//! \param
//!      pData           where to put response data
//! \param
//!      len             maximum length of repsonse data buffer, on exit
//!                      contains actual length
//! \return
//!      HOST_OK
//!
//! \note
//!      Wait until we get a response from the communication process
//!
HypEHostResult DemoHost::ReceiveResponse( unsigned char * const /*pData*/,
											  size_t& /*len*/ )
{
	HypCEvent ev;
	HypCEventInfo ei;

	SetState ( WaitingForResponse );
	Notify();

	ev.Wait(ei, 3 * 1000);

	return HOST_OK;

}

//-----------------------------------------------------------------------------
//!
//!      Puts some fake data in the Transaction record as if the transaction
//!      was processed.
//!
//! \param
//!      TransData       reference to transaction data container
//!
//! \return
//!      HOST_OK
//!
//! \note
//!
HypEHostResult DemoHost::DoProcessResponse( HypCTransactionData &TransData )
{
	// put some bogus data in for storing in journal and printing receipt

	// set the current time/date
	SetTransactionDateTime( TransData );
	

	// add status flags to map - nothing set
	HypCOptions opt;
	opt.reset();
	TransData.insert( TransactionTag::STATUS_FLAGS, opt.Clone() );

	// set an AUTH CODE
	TransData.insert( TransactionTag::AUTH_ID, "000000" );

	// set an RRN
	TransData.insert( TransactionTag::RETRIEVAL_REF_NUM, 
		"000000000012" );

	
	// set a TID
	TransData.insert ( TransactionTag::TERMINAL_ID,
		"30000003" );

	// set a card acceptor id
	TransData.insert ( TransactionTag::CARD_ACCEPTOR_ID,
		"300000000000003" );
	

	// set to ISO response code to APPROVED
	TransData.insert( TransactionTag::ISO_RESPONSE_CODE,
			"00" );

	// add some response text
	TransData.insert( TransactionTag::RESPONSE_TEXT,
			"Approved" );
		
	return HOST_OK;
}

//-----------------------------------------------------------------------------
//!
//!      This is an empty operation for the Demo host.
//!
//! \param
//!      TransData       reference to transaction data container
//!
//! \return
//!      HOST_OK
//!
//! \note
//!      The function is not declared inline because it will not be called
//!      very often and we do not care about speed here.
//!
HypEHostResult DemoHost::DoPostProcessing ( HypCTransactionData& TransData,
											HypEHostResult res )
{
	
	SaveToJournal ( TransData );
	return HOST_OK;
}


//-----------------------------------------------------------------------------
//!
//!      Saves the data to the Journal.
//!
//! \param
//!      TransData		Not used.
//!
//! \return
//!      true, on sucess
//!
//! \note
//!
bool DemoHost::SaveToJournal ( HypCTransactionData& TransData )
{
	bool bRetVal = false;

	// store record to journal
	HypCJournal *jrn = Transaction().GetJournal(m_HostName.c_str());
	if ( jrn && jrn->Open() )
	{
		if( !jrn->ValidateRecord( TransData ) )
		{
			jrn->FillMissingFields( TransData );
		}
		jrn->SetData( TransData );
		jrn->InsRecord();
		jrn->Close();
		bRetVal = true;
	}
	return bRetVal;
}

//-----------------------------------------------------------------------------
//!
//!      Connects to the communication device
//!
//! \return
//!      HOST_OK
//!
//! \note
//!      This overrides function in HypCHost because
//!      there is no real communicaiton fro demos host,
//!      but connection simulation is desired.
//!
HypEHostResult DemoHost::ConnectHost(  )
{
	HypEHostResult hresult = HOST_OK;

	HypCEvent ev;
	HypCEventInfo ei;
	ev.Wait(ei,m_nFakeConnectTime * 1000);

	return hresult;
}




//-----------------------------------------------------------------------------
//!
//!      Decodes repsonse from host. Nothing to do for DemoHost.
//!
//! \param
//!      TransData       reference to transaction data container
//! \param
//!      pData           pointer to buffer of data to decode
//! \param
//!      len             length of decoded data
//!
//! \return
//!      HOST_OK for success else other result for error.
//!      Always HOST_OK for DemoHost.
//!
//! \note
//!
HypEHostResult DemoHost::DoDecodeResponse ( HypCTransactionData& /*TransData*/,
												unsigned char* const /*pData*/,
												size_t /*len*/)
{
	return HOST_OK;
}
