//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hyperware Base Application
//      (c) Copyright 2006
//
// File Name:
//      DemoHost.hpp
//
// File Contents:
//      Declaration of the class DemoHost
//
//=============================================================================
#if !defined(_HYPCDEMOHOST_HPP_)
#define _HYPCDEMOHOST_HPP_

#if defined(__GNUC__)
#pragma interface
#endif

#include <HypCHost.hpp>
#include <HypCTransport.hpp>

//=============================================================================
// Public defines and typedefs
//=============================================================================

//=============================================================================
// Forward definitions
//=============================================================================


//=============================================================================
//!
//! \brief
//!      Implements a simple simulated host for demonstrations.
//!
//!      This host fakes a transaction by just showing a small delay
//!      as processing time and sending always an "approved message" back
//!      to the transaction. It is used mainly when training users on
//!      how to use the terminal.
//!
//!      Host connection and settlement are also faked.
//!
//!      This class is intended to be used in association with a
//!      HypCHostInterface and HypCHostFactory classes.
//!
//!      The class type is added to a derived HypCHostFactory object
//!      and assigned a name using the HypCHostFactory::CreateAssociation
//!      method.  HypCHostInterface object then creates this class when
//!      needed and is utilized to perofrm the operations.
//!
//! \sa
//!      HypCHost, HypCHostInterface, HypCHostFactory
//!
//=============================================================================
class DemoHost : public HypCHost
{

//=============================================================================
// Member functions
//=============================================================================
	public:
		//! constructor
		DemoHost( );

		//! destructor
		virtual ~DemoHost() {};

	protected:

	private:

		//! Setup the comm object for connection
		bool DoConfigureCommuncations( HypCMLTransport& Comm, bool bSettlement );

		//! Processing to be done before sending the request to the host
		HypEHostResult DoPreProcessing ( HypCTransactionData &TransData );

		//! Converts HypCTransactionData to the binary stream suitable
		//! for sending to the host
		HypEHostResult DoEncodeRequest( HypCTransactionData &TransData, 
										unsigned char * const pData, 
										size_t& len );

		//! Sends the transaction to the host
		HypEHostResult SendRequest( unsigned char * const pData,
		                            size_t len );

		//! Wait until we get a response from the communication process
		HypEHostResult ReceiveResponse( unsigned char * const pData,
		                                size_t& len );

		//! Decode repsonse from host
		HypEHostResult DoDecodeResponse( HypCTransactionData &TransData, 
										 unsigned char * const pData, 
										 size_t len );

		//! Processes the response from the host
		HypEHostResult DoProcessResponse( HypCTransactionData &TransData );

		//! Do any post processing
		HypEHostResult DoPostProcessing ( HypCTransactionData &TransData,
										  HypEHostResult res );

		//! Save data to journal
		bool SaveToJournal ( HypCTransactionData& TransRecord );

		//! The list of tags we expect in the transaction record
		void SetInputTags();

		//! The tags this host will modify in the transaction record
		void SetOutputTags();

		//! Settlement operation
		HypEHostResult DoSettle();

		//! Connect to host
		virtual HypEHostResult ConnectHost();

		
//=============================================================================
// Member variables
//=============================================================================
	public:

	private:
		//! Time to fake processing
		const int m_nFakeProcessingTime;

		//! Time to fake a connect
		const int m_nFakeConnectTime;

		//! Time to fake a settlement
		const int m_nFakeSettlementTime;

};
// DemoHost

#endif // #if !defined(_DEMOHOST_HPP_)

