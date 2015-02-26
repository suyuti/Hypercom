//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hyperware Base Application
//      (c) Copyright 2006
//
// File Name:
//      TransportFactory.hpp
//
// File Contents:
//      Definition of TransportFactory class
//
//=============================================================================
#if !defined( _TRANSPORTFACTORY_HPP_ )
#define _TRANSPORTFACTORY_HPP_

#include <compiler.h>
#include <HypCMLTransport.hpp>
#include <HypCTransportAddressSet.hpp>
#include <HypCMultiLang.hpp>
//=============================================================================
// Public defines and typedefs
//=============================================================================

//=============================================================================
// Forward definitions
//=============================================================================
class HypCTransport;
class HypCSerialPort;
class HypCModem;
#ifdef PLATFORM_M4100
class HypCGPRS;
#endif

//=============================================================================
//!
//! \brief
//!      Creates multi-layered transaport objects used for host communication.
//!
//!      Implementation of a HypCMLTransport class type used for HFC host 
//!      communication. 
//!
//!      Refer to HypCMLTransport for using the methods of this class.
//!
//! \sa
//!      HypCMLTransport
//!
//=============================================================================
class TransportFactory : public HypCMLTransport
{
//=============================================================================
// Member structures, enumerations, and class definitions
//=============================================================================
	public:

	private:
		#define DATA8N1	0
		#define DATA7E1	1

		struct mode
		{
			//! Legacy mode
			uint8_t  legacyMode;
			//! Modem API mode definiton
			int ModemAPIMode;	
			//! baud rate to modem ( not line )	
			int BaudRate;
			//! Interval timeout in 10s of ms
			uint8_t InterCharTimeout;  
			//! associated protocol
			HypEProtocol protocol;
			//! 8N1 = 0, 7E1 = 1
			uint8_t dataMode;
		};

	
//=============================================================================
// Member functions
//=============================================================================
	public:
		//! Constructor
		explicit TransportFactory( int Transport_ID );

		//! Destructor
		virtual ~TransportFactory();

		//! Access the current lower level transport object
		virtual HypCTransport* SubTransport();

        void SetInterface( HypCUserInterface *pInterface,  
                           HypCMultiLang* pMultiLang );
	protected:
		
		//! Create the transport object, called from base class
		virtual HypCTransport *DoCreateTransport( );

		//! Return true is mode paramters acceptable, called from base class
		virtual bool ValidateInitByMode( HypETransport transportType, 
			                         int mode );

		//! Return true if mode parameters acceptable, called from base class
		virtual bool ValidateInitByProtocol(  HypETransport transportType,
					                 HypEProtocol  protocol,
					           const HypSSerialParameters *pSerialInit = 0,
					           const char *connect = "",
					           const char *disconnect = "" );
		
		//! Delete transport object and any layers
		virtual void DoDeleteTransportObjects();		

        
		//! Creates and initializes protocol transport
		virtual bool CreateProtocol( HypCTransport *pULTransport );
		
		//! Create the transport objects
		virtual bool CreateTransportObjects( int transport,
						int protocol,
						const HypSSerialParameters *pSerialInit,
						const char *connect,
						const char *disconnect );

		//! Return Modem API protocol mode based on legacy mode
		int GetModemAPIProtocol( int mode );	

		//! Return poiinter to info for givne klegacy modem mode
		const TransportFactory::mode *GetModeInfo( int mode );

		//! Implementation of GetModem()
		virtual HypCModem* DoGetModem( );

        //! Is GPRS set?
        bool IsGPRS();


	private:
	
//=============================================================================
// Member variables
//=============================================================================
	private:
		//! Protocol
		HypCTransport *m_pProtocol;

		//! Layer below protocol
		HypCTransport *m_pTransport;

		//! Sub-transport (normally only modem use subtransport)
		HypCSerialPort *m_pSubTransport;

		//! Protocol ID ( HypEProtocol )
		int m_UseProtocol;

		//! Transport ID ( HypETrasnport )
		int m_UseTransport;

		//! legacy mode to Modem API protocol cross ref
		static const mode mode_table[];

#ifdef PLATFORM_M4100
        //! pointer to GPRS
        HypCGPRS* m_pGPRS;
#endif

		//! pointer directly to modem, if used
		HypCModem* m_pModem;

        // true if GPRS is set
        bool b_UseGPRS;

        //! pointer to User Interface
        HypCUserInterface* m_pInterface;

        //! pointer to Multilang 
        HypCMultiLang* m_pMultiLang;

};
// TransportFactory

#endif // #if !defined( _TRANSPORTFACTORY_HPP_ )



