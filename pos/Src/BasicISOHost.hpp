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
//      Declaration of the class BasicISOHost
//
//=============================================================================
#if !defined(_BASICISOHOST_HPP_)
#define _BASICISOHOST_HPP_

#if defined(__GNUC__)
#pragma interface
#endif

#include "BasicHost.hpp"
#include <HypCTransport.hpp>
#include <HypCISO8583_Message.hpp>
#include <HypCPOSConfig.hpp>

//=============================================================================
// Public defines and typedefs
//=============================================================================


//=============================================================================
// Forward definitions
//=============================================================================
class HypCISO8583_Transaction;
class HypCTransactionData;

//=============================================================================
//!
//! \brief
//!      Base class for ISO8583 type host modules.
//!
//!      This class implements the functions common for all ISO hosts.
//!
//! \sa
//!      HypCHost, HypCHostInterface, BasicHost
//!
//=============================================================================
class BasicISOHost : public BasicHost
{
//=============================================================================
// Member structures, enumerations, and class definitions
//=============================================================================
	protected:

		//! host responses: codes and descriptions
		typedef struct responseText 
		{
			const char *code;
			const char *text;
		} RESPONSE_TEXT;

//=============================================================================
// Member functions
//=============================================================================
	public:
		//! Constructor
		BasicISOHost();

		//! Destructor
		~BasicISOHost();

	protected:

		//! Build the ISO8583 packet out of the transaction data
		HypEHostResult DoEncodeRequest( HypCTransactionData &TransData, 
		                                unsigned char * const pData, size_t& len );

		//! Decodes the incoming ISO 8583 buffer
		HypEHostResult DoDecodeResponse( HypCTransactionData &TransData,
		                                 unsigned char * const pData, size_t len );

		//! Set the HypCISO8583_Transaction object
		bool SetISO8583Transaction( HypCTransactionData &TransData );

		//! Set response text
		void SetResponseText( const char *pRspCode, bool settle );

		//! Get host reponse code
		const HString GetResponseCode( HypCTransactionData& TransData );

		//! Adds BCD encoded length of ID and data, table ID and data to string
		HString& PrepareB63Field( HString& result, HString TableID, HString field );

		//! Returns only data from private field string
		//! TableID is used for looking up neccesary value
		HString ProcessB63Field( HString& result, HString TableID );

		//! Prepares the private fields before building ISO8583 message
		void PreparePrivateFields( HypCTransactionData& TransData );		

		//! Prepares bit 60 field for ISO8583 request message
		void PrepareB60( HypCTransactionData& TransData );

		//! Prepares bit 61 field for ISO8583 request message
		void PrepareB61( HypCTransactionData& TransData );

		//! Prepares bit 62 field for ISO8583 request message
		//! ( typically invoice number )
		void PrepareB62( HypCTransactionData& TransData );

		//! Prepares bit 63 field for IS8583 request message
		void PrepareB63( HypCTransactionData& TransData );

		//! Prepares batch number for settlement trailer
		bool PrepareB60BatchNumber( HString& Bit60, HypCTransactionData& TransData );

		//! Prepares original message data for settlement upload
		bool PrepareB60OriginalData( HString& Bit60, HypCTransactionData& TransData );

		//! Prepares original amount for adjust transactions
		bool PrepareB60OriginalAmount( HString& Bit60, HypCTransactionData& TransData );

		//! Prepares cashier data and till number (10)
		bool PrepareB63Cashier( HString& Bit63, HypCTransactionData& TransData );

		//! Prepares level II comercial card indicator (15)
		bool PrepareB63LVL2Indicator( HString& Bit63, HypCTransactionData& TransData );

		//! Prepares card verification value two (16)
		bool PrepareB63CVV2( HString& Bit63, HypCTransactionData& TransData );

		//! Prepares payment services 2000 data (20, 21)
		bool PrepareB63PS2000( HString& Bit63, HypCTransactionData& TransData );

		//! Prepares host reference data (31)
		bool PrepareB63HostRefData( HString& Bit63, HypCTransactionData& TransData );

		//! Prepares key serial number (33)
		bool PrepareB63KeySN( HString& Bit63, HypCTransactionData& TransData );

		//! Prepares additional prompt data (35)
		bool PrepareB63AdditionalPrompt( HString& Bit63, HypCTransactionData& TransData );

		//! Prepares batch number (37)
		bool PrepareB63BatchNumber( HString& Bit63, HypCTransactionData& TransData );

		//! Prepares tip amount (38)
		bool PrepareB63TipAmount( HString& Bit63, HypCTransactionData& TransData );

		//! Prepares tax amount #1 (39)
		bool PrepareB63TaxAmount1( HString& Bit63, HypCTransactionData& TransData );

		//! Prepares tax amount #2 (40)
		bool PrepareB63TaxAmount2( HString& Bit63, HypCTransactionData& TransData );

		//! Prepares cashback amount (41)
		bool PrepareB63CashbackAmount( HString& Bit63, HypCTransactionData& TransData );

		//! Prepares EBT specific data (47)
		bool PrepareB63EBT( HString& Bit63, HypCTransactionData& TransData );

		//! Prepares miscellaneous amount (53)
		bool PrepareB63MiscAmount( HString& Bit63, HypCTransactionData& TransData );

		//! Prepares address verification data (address and zip code) (54)
		bool PrepareB63AVSData( HString& Bit63, HypCTransactionData& TransData );

		//! Prepares level 2 comercial card data (73)
		bool PrepareB63LVL2Data( HString& Bit63, HypCTransactionData& TransData );

		// Prepares issuer script results card data (SR)
		bool PrepareB63IssScript( HString& Bit63, HypCTransactionData& TransData );

		// Parse private fields after receiving ISO8583 message
		void ProcessPrivateFields( HypCTransactionData& TransData );

		//! Processes private fields in bit62
		void ProcessB62( HypCTransactionData& TransData );

		//! Processes private fields in bit63
		void ProcessB63( HypCTransactionData& TransData );

		//! Processes level II comercial card indicator (15) response
		bool ProcessB63LVL2Indicator( HString& Bit63, HypCTransactionData& TransData );

		//! Processes card verification value II (16) result code
		bool ProcessB63CVV2ResultCode( HString& Bit63, HypCTransactionData& TransData );

		//! Processes payment services 2000 data (20)
		bool ProcessB63PS2000( HString& Bit63, HypCTransactionData& TransData );

		//! Processes alternate host respone (22)
		bool ProcessB63AltHostResponse( HString& Bit63, HypCTransactionData& TransData );

		//! Processes additional host print data (29)
		bool ProcessB63HostPrintData( HString& Bit63, HypCTransactionData& TransData );

		//! Processes host reference data (31)
		bool ProcessB63HostRefData( HString& Bit63, HypCTransactionData& TransData );

		//! Processes scheduled command data (42)
		bool ProcessB63ScheduleCommand( HString& Bit63, HypCTransactionData& TransData );

		//! Processes surcharge amount (44)
		bool ProcessB63SurchargeAmount( HString& Bit63, HypCTransactionData& TransData );

		//! Processes EBT response data (48)
		bool ProcessB63EBT( HString& Bit63, HypCTransactionData& TransData );

		//! Processes address verification response code (55)
		bool ProcessB63AVS( HString& Bit63, HypCTransactionData& TransData );

		//! Prepares standard totals(00-11), required by settlement
		virtual bool PrepareB63StandardTotals( HString& Bit63, HypCTransactionData& TransData ) = 0;

		//! do settlement
		HypEHostResult DoSettle();

//=============================================================================
// Member variables
//=============================================================================

	protected:

		//! ISO8583 request message container
		HypCISO8583_Message m_ISO8583RequestMessage;		

		//! ISO8583 response message container
		HypCISO8583_Message m_ISO8583ResponseMessage;		

		//! Current ISO8583 transaction
		HypCISO8583_Transaction* m_ISO8583Trans;

	private:

		//! Host response text data
		static const RESPONSE_TEXT RspText[];
}; 
// BasicISOHost

#endif // #if !defined(_BASICISOHOST_HPP_)

