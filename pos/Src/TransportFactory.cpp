//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hyperware Base Application
//      (c) Copyright 2006
//
// File Name:
//      TransportFactory.cpp
//
// File Description:
//      Implmentation of TransportFactory class
//
//=============================================================================

#include <HypCString.hpp>
#include <HLAN/HypCHLANAdapter.hpp>
#include <HLAN/HypCHLAN.hpp>
#include <HypCSDLC.hpp>
#include <HypCModem.hpp>
#include <HypCFDR.hpp>
#include <HypCNova.hpp>
#include <HypCTelecheck.hpp>
#include <HypCNetClient.hpp>
#include <HypCTransaction.hpp>
#include <HypCInfoBox.hpp>
#include "PromptsDef.h"

#ifdef PLATFORM_M4100
#include <HypCGPRS.hpp>
#endif //PLATFORM_M4100

#include "TransportFactory.hpp"

#include <HypCModemAAE.hpp>

#include <HypTrace.h>
const char* CLASS_HYPERWARE = "Hyperware";
// Debug class for the HFC library
#define CLASS_HFC 			MAKE_HYC_CLASS( 0x80 )


const	TransportFactory::mode
		TransportFactory::mode_table[] =
{	
	{ 0x00,	Bell212A_1200_Bell_SDLC,	HYP_SBR_4800,	4,	PROTO_SDLC,		DATA8N1 },
	{ 0x01,	Bell212A_1200_Bell_ASYNC,	HYP_SBR_4800,	8,	PROTO_VISA,		DATA7E1 },
	{ 0x02,	V22_1200_CCITT_SDLC,		HYP_SBR_4800,	4,	PROTO_SDLC,		DATA8N1 },
	{ 0x03,	V22_1200_CCITT_ASYNC,		HYP_SBR_4800,	8,	PROTO_VISA,		DATA7E1 },
	{ 0x04,	Bell103_300_Bell_ASYNC,		HYP_SBR_4800,	8,	PROTO_VISA,		DATA7E1 },
	{ 0x05,	V21_300_CCITT_ASYNC,		HYP_SBR_4800,	8,	PROTO_VISA,		DATA7E1 },
	{ 0x06,	V22bis_2400_CCITT_SDLC,		HYP_SBR_4800,	4,	PROTO_SDLC,		DATA8N1 },
	{ 0x07,	V22bis_2400_CCITT_ASYNC,	HYP_SBR_4800,	8,	PROTO_VISA,		DATA7E1 },
	{ 0x08,	V22bis_2400_Bell_SDLC,		HYP_SBR_4800,	4,	PROTO_SDLC,		DATA8N1 },
	{ 0x09,	V22bis_2400_Bell_ASYNC,		HYP_SBR_4800,	8,	PROTO_VISA,		DATA7E1 },
	{ 0x12,	Bell103_300_Bell_ASYNC,		HYP_SBR_4800,	8,	PROTO_VISA,		DATA7E1 },
	{ 0x13,	V21_300_CCITT_ASYNC,		HYP_SBR_4800,	8,	PROTO_VISA,		DATA7E1 },
	{ 0x14,	Bell212A_1200_Bell_ASYNC,	HYP_SBR_4800,	8,	PROTO_VISA,		DATA7E1 },
	{ 0x15,	V22_1200_CCITT_ASYNC,		HYP_SBR_4800,	8,	PROTO_VISA,		DATA7E1 },
	{ 0x16,	V22bis_2400_Bell_ASYNC,		HYP_SBR_4800,	8,	PROTO_VISA,		DATA7E1 },
	{ 0x17,	V22bis_2400_CCITT_ASYNC,	HYP_SBR_4800,	8,	PROTO_VISA,		DATA7E1 },
	{ 0x22,	Bell212A_1200_Bell_ASYNC,	HYP_SBR_4800,	30,	PROTO_FDR,		DATA7E1 },
	{ 0x41,	V21_300_CCITT_ASYNC,		HYP_SBR_4800,	8,	PROTO_VISA,			DATA7E1 },
	{ 0x42,	V22_1200_CCITT_ASYNC,		HYP_SBR_4800,	8,	PROTO_VISA,			DATA7E1 },
	{ 0x45,	Bell212A_1200_Bell_ASYNC,	HYP_SBR_4800,	4,	PROTO_TRANSPARENT,	DATA8N1 },
	{ 0x52,	V22bis_2400_Bell_ASYNC,		HYP_SBR_4800,	4,	PROTO_TRANSPARENT,	DATA8N1 },
	{ 0x58,	Bell212A_1200_Bell_ASYNC,	HYP_SBR_4800,	4,	PROTO_VISA, DATA7E1  }, // NOVA settle
	{ 0x59,	Bell212A_1200_Bell_ASYNC,	HYP_SBR_4800,	4,	PROTO_VISA,	DATA7E1  }, // NOVA Debit/Auth
	{ 0x72,	V29fast_9600_BellCCITT_SDLC_FBV22bis,	HYP_SBR_38400,	4,	PROTO_SDLC,	DATA8N1 },
	{ 0x73,	V29fast_9600_BellCCITT_SDLC_FBMode0,	HYP_SBR_38400,	4,	PROTO_SDLC,	DATA8N1 },
	{ 0x90,	V90_56K_CCITT,				HYP_SBR_4800,	4,	PROTO_TRANSPARENT,	DATA8N1 },
	{ 0x91,	V90_56K_CCITT,				HYP_SBR_4800,	4,	PROTO_SDLC,			DATA8N1 },
};



//-----------------------------------------------------------------------------
//!
//!      Constructor. Creates communication module.
//!
//! \param
//!      deviceId        Unique ID to identify this device.
//!
//! \return
//!
//! \note
//!
TransportFactory::TransportFactory( int TransportId ):
	HypCMLTransport( TransportId ),
	// Protocol
	m_pProtocol( NULL ),
	// Transport below protocol
	m_pTransport( NULL ),
	// Sub transport
	m_pSubTransport( NULL ),
	// Protocol ID
	m_UseProtocol( PROTO_TRANSPARENT ),
	// Transport ID
	m_UseTransport( LINE_NOTCONFIGURED ),
#ifdef PLATFORM_M4100
    // GPRS pointer
    m_pGPRS( NULL ),
#endif
	// Modem pointer
	m_pModem( NULL )

{
	
}

//-----------------------------------------------------------------------------
//!
//!      Destroys the communication module.
//!
//! \return
//!      None.
//!
//! \note
//!
TransportFactory::~TransportFactory()
{
	// Kill protocol and transport if they still exist
	DeleteTransportObjects();
}

//-----------------------------------------------------------------------------
//!
//!      Mode selection.
//!
//! \param
//!      comType         Communication line type.
//! \param
//!      mode            Hypercom legacy modem mode number.
//!
//! \return
//!      true if request successful, false otherwise.
//!
//! \note
//!      Fails if SetMode was not previously called.
//!
HypCTransport * TransportFactory::DoCreateTransport( void )
{
	const TransportFactory::mode  *pModeInfo;

	if( !m_bInitialized )
	{
		return 0;
	}
	
	// convert HypETransport type to line type used by HypCModemMode
	switch( m_TransportType )
	{
		 // Perform Dial Up Connection
		case LINE_DIALUP:
			
			// was SetMode() done by individual parmameters?
			if( !m_bSetByMode ) 
			{
                CreateTransportObjects( m_TransportType, m_Protocol,
										0, "", "" );
			}
			// find the protocol for this mode
			else if( (pModeInfo = GetModeInfo( m_Mode )) )
			{
				// set the protocol
				m_Protocol = pModeInfo->protocol;
				HypSSerialParameters SerialInit;

				// set the serial port values
				SerialInit.ErrorCharFlag = 0;
				SerialInit.FlowCtrl = HYP_HARDWARE_FC;
				SerialInit.BaudRate = static_cast<HypESerialBaudRate>( pModeInfo->BaudRate );
				SerialInit.ReadIntervalTimeout = pModeInfo->InterCharTimeout;
                SerialInit.ErrorChar = 0;

				switch( pModeInfo->dataMode )
				{
					case DATA8N1:
						SerialInit.StopBits = HYP_STOP_1;
						SerialInit.DataBits = 8;
						SerialInit.Parity = HYP_PARITY_NONE;
						break;
						
					case DATA7E1:
						SerialInit.StopBits = HYP_STOP_1;
						SerialInit.DataBits = 7;
						SerialInit.Parity = HYP_PARITY_EVEN;
						break;
				}


				CreateTransportObjects( m_TransportType, m_Protocol,
										&SerialInit, "", "" );
			}
			else
			{
				return 0;
			}
			break;
		

		case LINE_TCPIP:
			// was SetMode() done by individual parmameters?
			if( !m_bSetByMode ) 
			{
				// yes , so we have a valid m_Protocol value
				CreateTransportObjects( m_TransportType, m_Protocol,
							0, "", "" );
			}
			else
			{
				// we did not get a protocol!			
				return 0;
			}
			break;

        case LINE_HLAN_HIGH:
            if( !m_bSetByMode ) 
            {
                CreateTransportObjects( m_TransportType, m_Protocol,
                                        0, "", "" );
            }
            break;

		case LINE_VOICE:
		case LINE_ANSWER:
        default:
			return 0;		
			break;

	}

	return m_pTopLevelTransport;

}


//-----------------------------------------------------------------------------
//!
//!      Create the tranaport objects. Set m_pCurrentTrasnport to 
//!      the top layer transport object.
//!      
//! \param
//!      transportType   transport type identifier, typically type 
//!                      HypETransport
//! \param
//!      mode            mode identifier
//! \param
//!      pSerialInit     pointer to strucutre containing desired serial 
//!                      parameters
//! \param
//!      connect         modem connect string if applicable to 
//!                      transport type
//! \param
//!      disconnect      modem disconnect string if applicable to
//!                      transport type 
//!
//! \return
//!      true if request successful, false otherwise.
//!
//! \note
//!
bool TransportFactory:: CreateTransportObjects( 
	                    int transportType,
						int protocol,
						const HypSSerialParameters *pSerialInit,
						const char */*connect*/,
						const char */*disconnect*/ )
{
	// Kill protocol and transport if they exist
	DeleteTransportObjects();

	// Copy all parameters
	m_UseTransport = transportType;
	m_UseProtocol = protocol;

	// Determine device ID for sub transport
	int DeviceID;
	if( m_UseProtocol == PROTO_HYPERCOM_TCPIP || m_UseProtocol == PROTO_TRANSPARENT )
	{
		// use caller's ID for top layer transport
		DeviceID = m_TransportID;
	}
	else
	{

		DeviceID = 0;
	}

	switch( m_UseTransport )
	{
		case LINE_DIALUP:
			if( pSerialInit != NULL )
			{
				// Create modem class
				HypCModemAAE *pAAEModem = new HypCModemAAE( DeviceID );

				// Set Serial port parameters for modem comm
				pAAEModem->SetSerialPortParams ( pSerialInit );
				
				// HypEModemProtocols
				int pmode = GetModemAPIProtocol( m_Mode );

				if( ( pmode == -1 ) || !pAAEModem->SetModeProtocol( pmode ) )
				{
					delete pAAEModem;
					pAAEModem = 0;
					return false;
				}

                
				pAAEModem->SetDestination( m_AddressSet );

				// save pointer to modem 
				m_pModem = pAAEModem;
				// set mode to the transport
				m_pTransport = pAAEModem;
// TODO! this call of function must be removed with the next HFC release
#ifdef PLATFORM_M4100
				pAAEModem->SetMdmPortNumber( HYP_SP_DOCK_MODEM );
#endif
			}
			else
			{
				return false;
			}
			break;

        case LINE_HLAN_HIGH:

            if( m_AddressSet.AddressCount() > 0 )
            {
                char* tailptr;
                long nHexCUAddr = strtol ( ((m_AddressSet.GetFirstAddress())->address).c_str(), &tailptr, 16 );

                if ( (*tailptr != '\0') )
                    nHexCUAddr = 0;

                if ( (nHexCUAddr > 0) && (nHexCUAddr < 255) )
                {
                    HypCHLANAdapter *pHLANAdapter = new HypCHLANAdapter( DeviceID, nHexCUAddr );
                    m_pTransport = pHLANAdapter;
                }
                else
                    m_pTransport = NULL;
            }
            else
                m_pTransport = NULL;

            break;

        case LINE_TCPIP:            
#ifdef PLATFORM_M4100
            if( m_pGPRS == NULL && IsGPRS() )
            {
              	HypCEvent event(20);
                HypInfoParam dsc;
                dsc.Title = m_pMultiLang->GetPrompt( Prompts::CONNECT );
           		dsc.Message = m_pMultiLang->GetPrompt( Prompts::CONNECT_GPRS );
                DBGPRINTF ( VLVL_NORMAL, CLASS_HYPERWARE, "%s - Title %s Message %s\n", __FUNCTION__, dsc.Title.c_str(), dsc.Message.c_str() );
                m_pInterface->InfoBox()->SetTextColor( clBlack ); 
                m_pInterface->InfoBox()->SetMsgY( WIN_H/2 - 23 );
                m_pInterface->InfoBox()->SetMsgH( 80 );
                // show initial host state message
                m_pInterface->InfoBox()->Show( event, dsc);
                
                m_pGPRS = new HypCGPRS;
                if( m_pGPRS != NULL )
                {
                    DBGPRINTF ( VLVL_NORMAL, CLASS_HYPERWARE, "%s - GPRS Connecting\n", __FUNCTION__ );
                    if( m_pGPRS->Connect( ) )
                    {
                        DBGPRINTF ( VLVL_NORMAL, CLASS_HYPERWARE, "%s - GPRS Add Routing\n", __FUNCTION__ );
                        //  add default route
                        if( !m_pGPRS->AddRoute( "0.0.0.0", DEFAULT_ROUTE, (unsigned char*) "0.0.0.0" ) )
                        {
                            // invalid mode
                            delete m_pGPRS;
                            m_pTransport = NULL;
                            m_pGPRS = NULL;
                        }
                    }
                }
                if( m_pGPRS == NULL )
                {
                    m_pInterface->InfoBox()->UpdateText( m_pMultiLang->GetPrompt( Prompts::CONNECT_FAILED ) );
                    b_UseGPRS = false;
                    m_pInterface->InfoBox()->Cancel();
                    break;
                }
                m_pInterface->InfoBox()->Cancel();
            }
#endif
			// use ethernet port
			{
				HypCNetClient *pNetClient = new HypCNetClient( DeviceID, !b_UseGPRS );

				if( PROTO_HYPERCOM_TCPIP == protocol  )
				{
					// prefix length bytes on send, strip on receive data
					pNetClient->ProcessPacketLength( true );
				}
				
				//pNetClient->SetDestination( "10.250.35.70", 5555 );
				pNetClient->SetDestination( m_AddressSet );

				// assume this will be top level, 
				// unless overwritten in InitProtocol
				m_pTransport = pNetClient;
				
		
			}
			break;

		default:
			return false;
			break;
	}
	
	if ( !CreateProtocol( m_pTransport ) )
	{
		return false;
	}

	m_pTopLevelTransport = m_pProtocol;

	return true;
}



//-----------------------------------------------------------------------------
//!
//!      Creates and initializes the protocol layer.
//!      Set m_pProtocol to the protocol creates or to the 
//!      given transport object if the protocol is transparent
//!      or not needed.
//!
//! \param
//!      pTransport      pointer to protocol transport sub-layer 
//!
//! \return
//!      true if initialization succesfully, false otherwise
//!
//! \note
//!
bool TransportFactory::CreateProtocol( HypCTransport *pTransport )
{
	// set device ID to user's transport id
	int DeviceID = m_TransportID;

	switch( m_UseProtocol )
	{
        case PROTO_HLAN:

            if( m_AddressSet.AddressCount() > 0 )
            {
                char* tailptr;
                long nHexCUAddr = strtol ( ((m_AddressSet.GetFirstAddress())->address).c_str(), &tailptr, 16 );

                if ( (*tailptr != '\0') )
                    nHexCUAddr = 0;

                if ( (nHexCUAddr > 0) && (nHexCUAddr < 255) )
                {
                    HypCHLAN *pHLAN = new HypCHLAN(nHexCUAddr, *pTransport, DeviceID);
                    m_pProtocol = pHLAN;
                }
                else
                    m_pProtocol = NULL;
            }
            else
                m_pProtocol = NULL;

            break;

		case PROTO_HYPERCOM_TCPIP:	
		case PROTO_TRANSPARENT:
			// bypass protocol layer
			m_pProtocol = pTransport;
			break;

		case PROTO_SDLC:
			m_pProtocol = new HypCSDLC( 0x30, *pTransport, DeviceID );
			break;

		
		case PROTO_VISA_OVER_IP:
		case PROTO_VISA:
			m_pProtocol = new HypCNova( *pTransport, DeviceID );
			
			// this handled at serial port level, so set false
			( static_cast<HypCNova *> ( m_pProtocol ) )->Set7E1Mode ( false );
			( static_cast<HypCNova *> ( m_pProtocol ) )->SetTranMode ( HypCNova::AUTO_DETECT );			 			

			if ( PROTO_VISA_OVER_IP == m_UseProtocol )
			{
				// Do not wait for ENQ and disable ACK/NAK processing
                ( static_cast<HypCNova *> ( m_pProtocol ) )->SetWaitFirstENQ( false );
				( static_cast<HypCNova *> ( m_pProtocol ) )->SetWaitENQ( false );
				( static_cast<HypCNova *> ( m_pProtocol ) )->SetAckNakProcessing( false );
			}

			if ( ( 0x41 == m_Mode ) || ( 0x42 == m_Mode ) )
			{
                ( static_cast<HypCNova *> ( m_pProtocol ) )->SetWaitFirstENQ( true );
				( static_cast<HypCNova *> ( m_pProtocol ) )->SetWaitENQ( false );
				( static_cast<HypCNova *> ( m_pProtocol ) )->SetAckNakProcessing( false );
				( static_cast<HypCNova *> ( m_pProtocol ) )->SetTranMode ( HypCNova::MULTI_TRAN );
			}

			// NOVA protocol for settle
			if( 0x58 == m_Mode  )
			{
				( static_cast<HypCNova *> ( m_pProtocol ) )->SetWaitFirstENQ( true );
				( static_cast<HypCNova *> ( m_pProtocol ) )->SetWaitENQ( true );
				// force multi-tran , do not auto detect for NOVA host
				( static_cast<HypCNova *> ( m_pProtocol ) )->SetTranMode ( HypCNova::MULTI_TRAN );
			}

			// NOVA for DEBIT/AUTH
			if( 0x59 == m_Mode  )
			{
				( static_cast<HypCNova *> ( m_pProtocol ) )->SetWaitFirstENQ( true );
				( static_cast<HypCNova *> ( m_pProtocol ) )->SetWaitENQ( true );
				// set the special debit mode for NOVA host
				( static_cast<HypCNova *> ( m_pProtocol ) )->SetNOVADebitMode( true );
			}
			


			break;


		case PROTO_TELCK:
			return false;	// not supported
//			m_pProtocol = new HypCTelck( *pTransport, DeviceID );
			break;

		case PROTO_FDR:	
			return false;	// not supported
//			m_pProtocol = new HypCFDR( *pTransport, DeviceID );
			break;								

		default:
			return false;
	}
	return true;
}


//-----------------------------------------------------------------------------
//!
//!      Deletes the current transport objects
//!
//! \return
//!      void
//!
//! \note
//!
void TransportFactory::DoDeleteTransportObjects()
{
	// delete protocol and transport objects if they exist
	if( m_pProtocol )
	{
		delete m_pProtocol;
		// if protocol was set to transport object
		if( m_pProtocol == m_pTransport )
		{
			m_pTransport = 0;
		}
		m_pProtocol = 0;
	}

	if( m_pTransport )
	{
		// clear this pointer in case it equals m_pTransport
		m_pModem = 0; 
		delete m_pTransport;
        m_pTransport = 0;
		
	}

	if( m_pSubTransport )
	{
		delete m_pSubTransport;
		m_pSubTransport = 0;
	}
#ifdef PLATFORM_M4100
    if( m_pGPRS )
    {
        delete m_pGPRS;
        m_pGPRS = NULL;
        DBGPRINTF ( VLVL_NORMAL, CLASS_HYPERWARE, "%s - GPRS Destroed\n", __FUNCTION__ );
    }
#endif
}



//-----------------------------------------------------------------------------
//!
//!      Validate the transport type and mode 
//!
//! \return
//!      Return true if mode parameters acceptable
//!
//! \note
//!
bool TransportFactory::ValidateInitByMode( HypETransport /*transportType*/, 
                              int mode )
{
	return ( -1 != GetModemAPIProtocol( mode ) );
}


//-----------------------------------------------------------------------------
//!
//!      Validate the transport type. protocol, and parameters
//!
//! \param
//!      transportType   transport type identifier, typically type 
//!                      HypETransport
//! \param
//!      mode            mode identifier
//! \param
//!      pSerialInit     pointer to strucutre containing desired serial 
//!                      parameters
//! \param
//!      connect         modem connect string if applicable to 
//!                      transport type
//! \param
//!      disconnect      modem disconnect string if applicable to
//!                      transport type 
//! \return
//!      Return true if mode parameters acceptable
//!
//! \note
//!
bool TransportFactory::ValidateInitByProtocol( HypETransport /*transportType*/,
		               HypEProtocol /*protocol*/,
			           const HypSSerialParameters * /*pSerialInit*/,
			           const char * /*connect*/,
			           const char * /*disconnect*/ )
{

	return true;
}


//-----------------------------------------------------------------------------
//!
//!      Retreive the modem protocol needed fot the Modem API based on
//!      the legacy modem mode number
//!
//! \param
//!      mode            Legacy modem mode number
//!
//! \return
//!      Returns Modem API protocol number if found , else -1
//!
//! \note
//!
int TransportFactory::GetModemAPIProtocol( int mode )
{

	for( unsigned int i=0;
		 i < sizeof(mode_table)/sizeof( TransportFactory::mode);i++ )
	{
		if ( mode_table[i].legacyMode == mode )
		{
			return mode_table[i].ModemAPIMode;
		}
	}
	
	return -1;
}
//-----------------------------------------------------------------------------
//!
//!      Retreive the modem mode info for given legacy mode
//!
//! \param
//!      mode            Legacy modem mode number
//!
//! \return
//!      Returns pointer to the mode structure , else 0
//!
//! \note
//!
const TransportFactory::mode *
       TransportFactory::GetModeInfo( int mode )
{
	for( unsigned int i = 0;
		 i < sizeof(mode_table)/sizeof( TransportFactory::mode);
		 i++ )
	{
		if ( mode_table[i].legacyMode == mode )
			return &mode_table[i];
	}
	
	return 0;
}

//-----------------------------------------------------------------------------
//!
//!      Returns the current modem transport layer if
//!      available
//!
//! \return
//!      Pointer to the HypCModem object or NULL
//!
//! \note
//!
HypCModem* TransportFactory::DoGetModem( )
{
	return m_pModem;
}

//-----------------------------------------------------------------------------
//!
//!      Returns the current lower transport layer if
//!      available
//!
//! \return
//!      Pointer to the HypCTransport object
//!
//! \note
//!      Usually it will return pointer to HypCNetClient or HypCModem. This
//!      method might be used get pointer to HypCNetClient and set it to use
//!      HypCSSLSocket instead of regular socket.
//!
HypCTransport* TransportFactory::SubTransport( )
{
	return m_pTransport;
}

//-----------------------------------------------------------------------------
//!
//!      Returns GPRS flag
//!
//! \return
//!      bool true      if GPRS flag is set
//!           false     if not 
//!
//! \note
//!
bool TransportFactory::IsGPRS( )
{
    b_UseGPRS = false;
#ifdef PLATFORM_M4100
    if( m_Connect == "GPRS" ) //gprs )
    {
        b_UseGPRS = true;
    }
#endif
    return b_UseGPRS;
}

//-----------------------------------------------------------------------------
//!
//!      Set User Inteface and Multilang pointers
//!
//! \param
//!      pInterface - pointer to User Interface
//! \param 
//!     pMultiLang - pointer to Multilang
//! \return
//!      none
//!
//! \note
//!
void TransportFactory::SetInterface( HypCUserInterface *pInterface,  HypCMultiLang* pMultiLang )
{
    DBGPRINTF ( VLVL_NORMAL, CLASS_HYPERWARE, "%s - Set interface\n", __FUNCTION__ );
    m_pInterface = pInterface;
    m_pMultiLang = pMultiLang;
}
