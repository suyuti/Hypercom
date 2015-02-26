//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hypercom Foundation Classes
//      (c) Copyright 2006
//
// File Name:
//      Visa_Message.hpp
//
// File Contents:
//      Declaration of the class Visa_Message
//
//=============================================================================
#if !defined(_VISA_MESSAGE_HPP_)
#define _VISA_MESSAGE_HPP_

#if defined(__GNUC__)
#pragma interface
#endif

#include <compiler.h>
#include <HypCTransactionData.hpp>
#include <HypCHost.hpp>
//=============================================================================
// Forward definitions
//=============================================================================

class Visa_Message;

//=============================================================================
// Public defines and typedefs
//=============================================================================


//=============================================================================
//!
//! \brief
//!      Container for VISA message.
//!
//!      The class provides a container for a VISA message and allows
//!      user to set the various parts of an VISA message and then
//!      create a  data packet. The class can alternatevely be used to
//!      break an exist data packet into the various fields.
//!
//!      The format of a VISA message packet could be described by 
//!      the movers table for specific message classes derived from this class
//!
//!      Using this class to create or parse a message:
//!
//!      1. Create the HypCISO8583_Message object or use existing Visa_Message 
//!         object.
//!      2. Call the CreateMessagePacket() function to build a buffer containing the
//!         full message or
//!      3. call the DecodeMessagePacket() function to decode a packet received 
//!         from a host.
//!      4. Use init function to reset object's state and then repeat the step 2 or 3.
//!
//! \sa
//!      VisaHost
//!
//=============================================================================
class Visa_Message
{

//=============================================================================
// Member structures, enumerations, and class definitions
//=============================================================================
	public:
		//! How to move data into a 8583 message
		enum AlignType {
			NONE,
			LEFT,
			RIGHT,
			NONULLS
		};

		//! attributes of field to be encoded in request packets
		enum SizeAttr {
			FIXED,
			VARIABLE
		};
		
protected:

//=============================================================================
// Member functions
//=============================================================================
	public:
		//! constructor
		Visa_Message(  );

		//! Virtual destructor
		virtual ~Visa_Message(  );

		//! reset the object to the initial state
		Visa_Message* Init( HypCTransactionData* pTransData );

		//! receive field's string value by it's tag
		HString GetTransTag( const char *Tag );

		//! Create a message packet
		bool CreateMessagePacket( char* pData, size_t& length );

		//! decode a message packet
		virtual bool DecodeMessagePacket( char* pData, size_t length ) = 0;

		//! move specific field defined by it's tag
		bool Move( const char* Tag, Visa_Message::AlignType align );

		//! move acquirer number
		bool MoveAcquirerNum(  );

		//! move merchant number
		bool MoveMerchantNum(  );

		//! move store number
		bool MoveStoreNum(  );

		//! move terminal number
		bool MoveTerminalNum(  );

		//! move device code
		bool MoveDevice(  );

		//! move industry code
		bool MoveIndustry(  );

		//! move currency code
		bool MoveCurrency(  );

		//! move country code
		bool MoveCountry(  );

		//! move city
		bool MoveCity(  );

		//! move language ID
		bool MoveLang(  );

		//! move time zone difference
		bool MoveTimeZoneDiff(  );

		//! move merchant category
		bool MoveMerchCategory(  );

		//! move requested ACI
		bool MoveReqACI(  );

		//! move transaction sequence number
		bool MoveTranSeqNum(  );

		//! move authorization transaction code
		bool MoveAuthTranCode(  );

		//! move cardholder ID
		bool MoveCardholderID(  );

		//! move merchant name
		bool MoveMerchName(  );

		//! move merchant's location state
		bool MoveMerchLocState(  );

		//! move merchant's location
		bool MoveMerchLocation(  );

		//! move terminal's serial
		bool MoveTermSerial(  );

		//! move account data source
		bool MoveAccDataSrc(  );

		//! convert 2-digit number string representation into integer
		uint16_t get2CInt( const char* pAsc );

		//! mover function
		virtual bool Mover( uint16_t idx ) = 0;

		//! return number of moving functions for packet creation
		virtual uint16_t NumMovers(  ) = 0;

		//! size of the moving field
		virtual uint16_t MoverSize( uint16_t idx ) = 0;

		//! return field's attribute
		virtual SizeAttr FieldAttr( uint16_t idx ) = 0;

		//! get index of the field that hasn't been moved, on error while encoding
		inline uint16_t GetNotMovedBit(  );

	protected:

//=============================================================================
// Member variables
//=============================================================================
	
	protected:

		//! index of the "moving function"
		uint16_t m_MoverIdx;

		//! offset in sent/received packet
		uint16_t m_Off;

		//! buffer, for storing sent/received packet data
		char* m_Buff;

		//! size of the field to be moved
		uint16_t m_MovedSize;

		//! data source
		HypCTransactionData* m_TransData;

	private:
};
// Visa_Message

//-----------------------------------------------------------------------------
//!
//!      constructor
//!
//! \return
//!      Nothing
//!
//! \note
//!
inline Visa_Message::Visa_Message(  )
{
	Init( 0 );
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
inline Visa_Message::~Visa_Message()
{
}

//-----------------------------------------------------------------------------
//!
//!		reset the object to the initial state
//!
//! \return
//!      the object itself
//!
//! \note
//!
inline Visa_Message* Visa_Message::Init( HypCTransactionData* pTransData )
{
	m_MoverIdx = 0;
	m_Off = 0;
	m_Buff = 0;
	m_MovedSize = 0;
	m_TransData = pTransData;

	return this;
}

//-----------------------------------------------------------------------------
//!
//!		get index of the field that hasn't been moved, on error while encoding
//!
//! \return
//!     index of the field
//!
//! \note
//!
inline uint16_t Visa_Message::GetNotMovedBit(  )
{
	return m_MoverIdx;
}

#endif // !defined(_VISA_MESSAGE_HPP_)

