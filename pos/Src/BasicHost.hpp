//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hyperware Base Application
//      (c) Copyright 2006
//
// File Name:
//      HypercomHost.hpp
//
// File Contents:
//      Declaration of the class HypercomHost
//
//=============================================================================
#if !defined(_BASICHOST_HPP_)
#define _BASICHOST_HPP_

#if defined(__GNUC__)
#pragma interface
#endif

#include <HypCHost.hpp>
#include <HypCTransport.hpp>
#include <HypCPOSConfig.hpp>

//=============================================================================
// Public defines and typedefs
//=============================================================================


//=============================================================================
// Forward definitions
//=============================================================================
class HypCTransactionData;

//=============================================================================
//!
//! \brief
//!      Base class for all host modules.
//!
//!      This class implements the functions common for all hosts.
//!
//! \sa
//!      HypCHost, HypCHostInterface
//!
//=============================================================================
class BasicHost : public HypCHost
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
		BasicHost();

		//! Destructor
		~BasicHost();

		//! Check attribute
		bool IsAttributeSet( HypCTransactionData& transRecord, int AttributeID );

		//! Is this transaction processed offline
		bool Offline( HypCTransactionData& transRecord );

		//! Is total amount below floor limit
		bool BelowFloorLimit( HypCTransactionData& transRecord, 
											HypCPOSConfig& posConfig );

		//! Is the expiration date valid
		bool ValidExpirationDate( HypCTransaction& trans, HypCPOSConfig& posConfig );
		
		//! Set the attributes associated with this transaction
		void SetAttribute( HypCTransaction& trans, int AttributeID );
		
	protected:

		//! Processes the host response
		HypEHostResult DoProcessResponse( HypCTransactionData &TransData );

		//! Returns transaction tag value if present, else empty string
		HString GetTransTag( HypCTransactionData& TransData, const char *Tag );

		//! Save batch number in configuration
		void SaveBatchNum ( HypCPOSConfig* pCfg, const HYP_CFG_HANDLE row, 
				const char * paramName, const uint64_t batch_number );

		//! delete settled transactions from journal
		void DeleteSettled(  );

		//! Setup the comm object for connection
		bool DoConfigureCommuncations( HypCMLTransport &Comm, bool bSettlement );

		//! Test response options to see if reversal is cleared.
		//! Free the reversal if response option is set to clear.
		//! Perform special processing
		HypEHostResult DoPostProcessing( HypCTransactionData &TransData,
										 HypEHostResult res );

		//! Saves transaction record to Hypercom host journal
		bool SaveToJournal( HypCTransactionData& TransRecord );

		//! Make sure the Reversal is sent to Host first
		virtual bool AllowReversalProcessing();

		//! Settlement operation
		virtual HypEHostResult DoSettle() = 0;
	
		//! Generate a random authorization id
		void GenerateAuthCode( int digitCount, HString& str );
		
		//! Do reversals processing
		HypEHostResult ProcessReversals( const char* host );

		//! Do adjusts and offlines processing
		HypEHostResult ProcessAdjustsOfflines( const char* host );

		//! Perform a financial transaction
		virtual HypEHostResult PerformTransaction( HypCTransaction& transaction );

		//! Sets the system trace number and increments
		void SetSystemTraceNumber( HypCTransactionData& TransData );
	
		//! Sets the transaction date time to current date time
		virtual void SetTransactionDateTime( HypCTransactionData& TransData );

		//! Sets the system date time to date time stored in Transdata
		void SetSystemDateTime( HypCTransactionData& TransData );
//=============================================================================
// Member variables
//=============================================================================
	protected:

		//! Handle to acquirer record
		int m_AcqRecord;

		//! Handle to issuer record;
		int m_IssRecord;

	private:

}; 
// BasicHost

#endif // #if !defined(_BASICHOST_HPP_)

