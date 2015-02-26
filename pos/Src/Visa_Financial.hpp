//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hypercom Foundation Classes
//      (c) Copyright 2006
//
// File Name:
//      Visa_Financial.hpp
//
// File Contents:
//      Declaration of the class Visa_Financial
//
//=============================================================================
#if !defined(_VISA_FINANCIAL_HPP_)
#define _VISA_FINANCIAL_HPP_

#if defined(__GNUC__)
#pragma interface
#endif

#include <compiler.h>
#include <HypCTransactionData.hpp>
#include "Visa_Message.hpp"
//=============================================================================
// Forward definitions
//=============================================================================

class Visa_Financial;

//=============================================================================
// Public defines and typedefs
//=============================================================================

//=============================================================================
//!
//! \brief
//!      Provides fucntionality for VISA financial transactions.
//!
//!      This class implements the functionality used by financial 
//!      Visa host transactions
//!
//! \sa
//!      Visa_Message, VisaHost
//!
//=============================================================================
class Visa_Financial : public Visa_Message
{

//=============================================================================
// Member structures, enumerations, and class definitions
//=============================================================================
	private:

		//! pointer to a function to be called from a script
		typedef bool (Visa_Financial::*MoverFunction)();

		//! description of moved fields
		struct rec
		{
			MoverFunction MoveF;
			uint16_t	  Size;	// Max or fixed Length
			SizeAttr	  Type;
		} ;

	protected:


//=============================================================================
// Member functions
//=============================================================================
	public:
		//! Initialize members
		Visa_Financial(  );

		//! Virtual destructor
		virtual ~Visa_Financial();

		//! decode a message packet
		bool DecodeMessagePacket( char* pData, size_t length );

		//! move format field
		bool MoveFormat(  );

		//! move cardholder ID field
		bool MoveCardholderID(  );

		//! move customer data field
		bool MoveCustDataField(  );

		//! move field separator(s)
		bool MoveFS(  );

		//! move amount field
		bool MoveAmount(  );

		//! move group III version
		bool MoveGroup3Version(  );

		//! launch a specific mover function by it's index
		bool Mover( uint16_t idx );

		//! get number of moving functions to call
		uint16_t NumMovers(  );

		//! get size of a specific moved field
		uint16_t MoverSize( uint16_t idx );

		//! get attribute of a specific field to move
		SizeAttr FieldAttr( uint16_t idx );

	protected:

//=============================================================================
// Member variables
//=============================================================================

	protected:

		//! table of mover-functions
		static const rec TAB_Fields[];

	private:
};
// Visa_Financial

//-----------------------------------------------------------------------------
//!
//!      constructor
//!
//! \return
//!      Nothing
//!
//! \note
//!
inline Visa_Financial::Visa_Financial(  )
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
inline Visa_Financial::~Visa_Financial()
{
}

#endif // !defined(_VISA_FINANCIAL_HPP_)

