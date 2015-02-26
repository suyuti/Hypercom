//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hypercom Foundation Classes
//      (c) Copyright 2006
//
// File Name:
//      Visa_Settle.hpp
//
// File Contents:
//      Declaration of the class Visa_Settle
//
//=============================================================================
#if !defined(_VISA_SETTLE_HPP_)
#define _VISA_SETTLE_HPP_

#if defined(__GNUC__)
#pragma interface
#endif

#include <compiler.h>
#include <HypCTransactionData.hpp>
#include "Visa_Financial.hpp"

//=============================================================================
// Forward definitions
//=============================================================================

class VisaHost;

//=============================================================================
// Public defines and typedefs
//=============================================================================

//=============================================================================
//!
//! \brief
//!      Provides functionality for VISA host settlement.
//!
//!      This class implements the functionality used only by settlement 
//!      requests to a Visa host
//!
//! \sa
//!      Visa_Financial, Visa_Message, VisaHost
//!
//=============================================================================
class Visa_Settle : public Visa_Financial
{

//=============================================================================
// Member structures, enumerations, and class definitions
//=============================================================================
	private:
		//! pointer to a function to be called from a script
		typedef bool (Visa_Settle::*MoverFunction)();

		//! table of movers
		struct rec
		{
			MoverFunction MoveF;
			uint16_t	  Size;	// Max or fixed Length
			SizeAttr	  Type;
		} ;

//=============================================================================
// Member functions
//=============================================================================
	public:
		//! Initialize members
		Visa_Settle( VisaHost* visa_host );

		//! Virtual destructor
		virtual ~Visa_Settle(  );

		//! initialize a settlement message
		Visa_Message* Init( HypCTransactionData* pTransData, HString tt );

		//! call the specific mover function
		bool Mover( uint16_t idx );

		//! get the number of entries in the movers table
		uint16_t NumMovers(  );

		//! get the size of the field identified by idx-entry 
		uint16_t MoverSize( uint16_t idx );

		//! get the attribute of the field identified by idx-entry 
		Visa_Financial::SizeAttr FieldAttr( uint16_t idx );

		//! set type for this message object
		void SetTransType( HString& tt );

		//! move format field for CLBATCH request
		bool MoveFormatH(  );

		//! move record type field for CLBATCH request
		bool MoveRecTypeH(  );

		//! move record type field for CLTERM request
		bool MoveRecTypeP(  );

		//! move record type field for CLBATCHA request
		bool MoveRecTypeT(  );

		//! move record type field for RUPLOAD request
		bool MoveRecTypeD(  );

		//! move agent's bank number
		bool MoveAgentBankNum(  );

		//! move agent's chain number
		bool MoveAgentChainNum(  );

		//! move batch transaction date
		bool MoveBatchTransDate(  );

		//! move batch number
		bool MoveBatchNum(  );

		//! move blocking ID
		bool MoveBlockingID(  );

		//! move ETB field
		bool MoveETB(  );

		//! move returned ACI field
		bool MoveRetACI(  );

		//! move authorization source code
		bool MoveAuthSrcCode(  );

		//! move record count
		bool MoveRecCount(  );

		//! move hash total field
		bool MoveHashTotal(  );

		//! move cashback amount field
		bool MoveCashTotal(  );

		//! move batch net deposit amount
		bool MoveBatchNetDeposit(  );

		//! move account number
		bool MoveAccNumber(  );

		//! move authorization code
		bool MoveAuthCode(  );

		//! move response code
		bool MoveRespCode(  );

		//! move transaction date and time
		bool MoveTranDateTime(  );

		//! move AVS result field
		bool MoveAVSResult(  );

		//! move transaction ID field
		bool MoveTranID(  );

		//! move validation code
		bool MoveValidCode(  );

		//! move void index field
		bool MoveVoidInd(  );

		//! move transaction state code
		bool MoveTranStatCode(  );

		//! move reimbursement attribute
		bool MoveReimb(  );

		//! move settlement amount
		bool MoveSettleAmt(  );

		//! move authorization amount
		bool MoveAuthAmt(  );

		//! translate reponse code to the unified format
		HString TransResponse( const HString& rsp );

		//! decode packet sent by host
		bool DecodeMessagePacket( char* pData, size_t length );
	protected:

//=============================================================================
// Member variables
//=============================================================================
	private:
		//! reference to the host host
		VisaHost* m_VisaHost;

		//! reference to the used movers table for a sepcific settlement request
		rec * p_m_UsedTAB;

		//! size of the movers table to walk through
		uint64_t m_TabSize;

		//! movers table for settlement header request
		static const rec TAB_Header[];

		//! movers table for settlement parameters request
		static const rec TAB_Params[];

		//! movers table for settlement details request
		static const rec TAB_Details[];

		//! movers table for settlement trailer request
		static const rec TAB_Trail[];

		//! number of packets sent
		uint64_t m_RecCount;

		//! hash total
		uint64_t m_HashTotal;

		//! cash total
		uint64_t m_CashTotal;

		//! net deposit
		uint64_t m_NetDeposit;
};
// Visa_Settle

//-----------------------------------------------------------------------------
//!
//!      Just initializes the data elements
//!
//! \param
//!      visa_host       reference to the host object, which created this
//!                      message
//!
//! \return
//!      Nothing
//!
//! \note
//!
inline Visa_Settle::Visa_Settle( VisaHost* visa_host ) :
		Visa_Financial(  ),
		m_VisaHost( visa_host ),
		p_m_UsedTAB( 0 ),
		m_TabSize( 0 ),
		m_RecCount( 0 ),
		m_HashTotal( 0 ),
		m_CashTotal( 0 ),
		m_NetDeposit( 0 )
{
}


//-----------------------------------------------------------------------------
//!
//!      destructor
//!
//! \return
//!      Nothing
//!
//! \note
//!
inline Visa_Settle::~Visa_Settle()
{
}


#endif // !defined(_VISA_SETTLE_HPP_)

