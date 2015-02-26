//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hypercom Foundation Classes
//      (c) Copyright 2006
//
// File Name:
//      TransactionUtility.hpp
//
//
// File Contents:
//      Declaration of the class TransactionUtility
//
//=============================================================================
#if !defined(_TRANSACTIONUTILITY_HPP_)
#define _TRANSACTIONUTILITY_HPP_

#if defined(__GNUC__)
#pragma interface
#endif

#include <compiler.h>
#include <HString.hpp>
#include <HypCOptions.hpp>
#include <HypCTransactionData.hpp>
#include <HypCTransactionStep.hpp>
#include <HypCPCL.hpp>

//=============================================================================
// Public defines and typedefs
//=============================================================================
const char * const LastReceiptFile = "D:\\lastprint.bin";


//=============================================================================
// Forward definitions
//=============================================================================
enum Exec_Action;
class HypCTransactionManager;
class HypCApplication;
class HypCJournal;
class HypCPOSConfig;
class HypCPrinter;
class HypCTransactionStepFactory;

//=============================================================================
//!
//! \brief
//!      Commonly used transaction utilities.
//!
//!      A service class that implements some Hyperware-specific functions of 
//!      HypCTransaction class. The class is used by high-level transaction 
//!      classes (really, by their steps).
//!
//! \sa
//!      HypCTransaction
//!
//=============================================================================
class TransactionUtility
{

//=============================================================================
// Member structures, enumerations, and class definitions
//=============================================================================
	public:
		//! The transaction record is data tagged by its name.
		typedef HypCTransactionData HypCTransRecord;

//=============================================================================
// Member functions
//=============================================================================
	public:
		//! Check attribute
		static bool IsAttributeSet( HypCTransRecord& transRecord, int AttributeID );

		//! Is this transaction processed offline
		static bool Offline( HypCTransRecord& transRecord );

		//! Is total amount below floor limit
		static bool BelowFloorLimit( HypCTransRecord& transRecord, 
											HypCPOSConfig& posConfig );

		//! Is the expiration date valid
		static bool ValidExpirationDate( HypCTransaction& trans, HypCPOSConfig& posConfig );

		//! Set the attributes associated with this transaction
		static void SetAttribute( HypCTransaction& trans, int AttributeID );

		//! print using the specified script
		static void PrintReceipt( HypCPCL* pPCL, HypCTransaction& trans,
			const char* receipt, bool save = false );
	protected:

    private:
		//! Prohibit this class from being copied...
		TransactionUtility ( const TransactionUtility& rhs );

		//! Prohibit this class from being copied...
		TransactionUtility& operator= ( const TransactionUtility& rhs );

//=============================================================================
// Member variables
//=============================================================================

	private:

};
// TransactionUtility

#endif // #if !defined(_TRANSACTIONUTILITY_HPP_)

