//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hyperware Base Application
//      (c) Copyright 2006
//
// File Name:
//      HyperwareConfig.cpp
//
// File Contents:
//      Implementation of the Class HypCHyperwareConfig.
//      This is the POS configuration document. Provides access to POS tables 
//      as defined by the document parsed at initalization time.
//
//=============================================================================
#include <compiler.h>
#include <HycDDL.h>
#include <HypCInt8.hpp>
#include <HypCInt16.hpp>
#include <HypCInt32.hpp>
#include <HypCInt64.hpp>
#include <HypCDateTime.hpp>
#include <HypCString.hpp>
#include <HypCOptions.hpp>
#include "YemekSepetiTags.h"
#include <BCDUtil.h>
#include <HString.hpp>
#include "YemekSepetiConfig.hpp"
#include <HypTrace.h>

// Uncomment the lines below to switch off logging in debug mode

//#if defined(DBGPRINTF)
//#undef DBGPRINTF
//#define DBGPRINTF(...)
//#endif


#define USE_MEM_FILE

#define _DELTA_ (!m_CfgDelta.empty() )
#define _CTRL_  (!m_CfgCtrl.empty() )
#define _DESC_  (!m_CfgDesc.empty() )
#define _ADDITIONAL_FILES_ ( _DELTA_ && _CTRL_ && _DESC_ )
#define _INITIALIZED_ ( m_Initialized && _ADDITIONAL_FILES_ )


//=============================================================================
// VISAII record common tags
//=============================================================================

// Table name
const char* VisaIITag::TABLE = "Visa II";
// acquirer ID
const char* VisaIITag::ACQUIRER_ID = "VISAII_ACQUIRER_ID";
// acquirer bank number
const char* VisaIITag::ACQUIRER_BIN = "VISAII_ACQUIRER_BIN";
// merchant number
const char* VisaIITag::MERCH_NUMBER = "VISAII_MERCH_NUMBER";
// store number
const char* VisaIITag::STORE_NUM = "VISAII_STORE_NUM";
// terminal number
const char* VisaIITag::TERM_NUM = "VISAII_TERM_NUM";
// merchant currency
const char* VisaIITag::MERCH_CURRENCY = "VISAII_MERCH_CURRENCY";
// merchant country
const char* VisaIITag::MERCH_COUNTRY = "VISAII_MERCH_COUNTRY";
// merchant city
const char* VisaIITag::MERCH_CITY = "VISAII_MERCH_CITY";
// time zone difference
const char* VisaIITag::TIME_ZONE_DIFF = "VISAII_TIME_ZONE_DIFF";
// merchant category
const char* VisaIITag::MERCH_CAT = "VISAII_MERCH_CAT";
// merchant name
const char* VisaIITag::MERCH_NAME = "VISAII_MERCH_NAME";
// merchant city and state
const char* VisaIITag::MERCH_CITY_STATE = "VISAII_MERCH_CITY_STATE";
// agent's bank number
const char* VisaIITag::AGENT_BIN = "VISAII_AGENT_BIN";
// agent's chain number
const char* VisaIITag::AGENT_CHAIN_NUM = "VISAII_AGENT_CHAIN_NUM";
// merchant's location - first character
const char* VisaIITag::FIRST_CHAR_LOCATION = "VISAII_FIRST_CHAR_LOCATION";
// merchant's location
const char* VisaIITag::MERCH_LOCATION = "VISAII_MERCH_LOCATION";
// terminal's serial number
const char* VisaIITag::TERMINAL_SERIAL_NUM = "VISAII_TERMINAL_SERIAL_NUM";

//=============================================================================
// Acquirer record common tags
//=============================================================================
	
// The acquirers table name
const char* AcquirerTag::ACQUIRER_TABLE	= "ACQUIRER";
	
// Acquirer ID
const char* AcquirerTag::ID 				= "ACQUIRER_ID";
		
// HypCString: Acquirer name
const char* AcquirerTag::NAME = "_ACQUIRER ## NAME_";
	
// HypCString: Acquirer NII
const char* AcquirerTag::NII = "ACQUIRER_NII";
	
// HypCString: Acquirer primary phone number
const char* AcquirerTag::PRI_PHONE            = "ACQUIRER_PRIM_TRANS_TEL_NUM";
		
// HypCWord: Acquirer primary dial attempts
const char* AcquirerTag::PRI_DIAL_ATTEMPTS    = "ACQUIRER_PRIM_TRANS_DIAL_ATTEMPTS";
	
// HypCWord: Acquirer primary connect timeout
const char* AcquirerTag::PRI_TIMEOUT          = "ACQUIRER_PRIM_TRANS_CONN_TIME";
	
// HypCString: Acquirer secondary phone number
const char* AcquirerTag::SEC_PHONE            = "ACQUIRER_SEC_TRANS_TEL_NUM";
		
// HypCWord: Acquirer secondary dial attempts
const char* AcquirerTag::SEC_DIAL_ATTEMPTS    = "ACQUIRER_SEC_TRANS_DIAL_ATTEMPTS";
	
// HypCWord: Acquirer secondary connect timeout
const char* AcquirerTag::SEC_TIMEOUT          = "ACQUIRER_SEC_TRANS_CONN_TIME";
	
// HypCString: Acquirer terminal id
const char* AcquirerTag::TERMINAL_ID   		= "ACQUIRER_TERM_ID";
	
// HypCString: Acquirer acceptor id
const char* AcquirerTag::ACCEPTOR_ID          = "ACQUIRER_ID_CODE";
	
// HypCString: Acquirer batch number
const char* AcquirerTag::BATCH_CURRENT        = "ACQUIRER_CURR_BATCH_NUM";
	
// HypCString: Acquirer next batch number
const char* AcquirerTag::BATCH_NEXT           = "ACQUIRER_NEXT_BATCH_NUM";
	
// HypCOption: Acquirer options
const char* AcquirerTag::ACQUIRER_OPT1        = "ACQUIRER_OPT1";
	
// HypCOption: Acquirer options
const char* AcquirerTag::ACQUIRER_OPT2        = "ACQUIRER_OPT2";
	
// HypCOption: Acquirer options
const char* AcquirerTag::ACQUIRER_OPT3        = "ACQUIRER_OPT3";
	
// HypCOption: Acquirer options
const char* AcquirerTag::ACQUIRER_OPT4        = "ACQUIRER_OPT4";
	
// HypCQWord: Acquirer PIN key
const char* AcquirerTag::PIN_KEY              = "ACQUIRER_PIN_KEY";
	
// HypCQWord: Master key index
const char* AcquirerTag::MASTER_KEY_IDX		 = "ACQUIRER_MASTER_KEY_IDX_PIN";
	
// HypCQWord: Acquirer IP address
const char* AcquirerTag::ACQ_URL              = "ACQUIRER_IP_URL";
	
// HypCQWord: Acquirer IP port
const char* AcquirerTag::ACQ_PORT             = "ACQUIRER_IP_PORT";
		
// HypCQWord: Acquirer IP address
const char* AcquirerTag::ACQ_SETTL_URL        = "ACQUIRER_IP_SETTL_URL";
	
// HypCQWord: Acquirer IP port
const char* AcquirerTag::ACQ_SETTL_PORT       = "ACQUIRER_IP_SETTL_PORT";
	
// HypCWord: Acquirer secondary connect timeout
const char* AcquirerTag::ACQ_PRIM_SETTL_DIAL  = "ACQUIRER_PRIM_SETTL_TEL_NUM";
	
// HypCWord: Acquirer secondary connect timeout
const char* AcquirerTag::ACQ_SEC_SETTL_DIAL  = "ACQUIRER_SEC_SETTL_TEL_NUM";
	
// HypCWord: Acquirer secondary dial attempts
const char* AcquirerTag::ACQ_SEC_SETTL_DIAL_ATTEMPTS = "ACQUIRER_SEC_SETTL_DIAL_ATTEMPTS";
	
// HypCWord: Acquirer secondary dial attempts
const char* AcquirerTag::ACQ_SEC_SETTL_CONN_TIME = "ACQUIRER_SEC_SETTL_CONN_TIME";
	
// HypCWord: Acquirer secondary dial attempts
const char* AcquirerTag::ACQ_PRIM_SETTL_CONN_TIME = "ACQUIRER_PRIM_SETTL_CONN_TIME";
	
// HypCWord: Acquirer secondary dial attempts
const char* AcquirerTag::ACQ_PRIM_SETTL_DIAL_ATTEMPTS = "ACQUIRER_PRIM_SETTL_DIAL_ATTEMPTS";
	
// HypCWord: Acquirer secondary dial attempts
const char* AcquirerTag::ACQ_MODEM_MODE		= "ACQUIRER_MODEM_MODE";
	
// HypCWord: Acquirer secondary dial attempts
const char* AcquirerTag::ACQ_MODEM_MODE_SETTL = "ACQUIRER_MODEM_MODE_SETTL";

// HypCString: Acquirer program name
const char* AcquirerTag::PROGRAM_NAME = "ACQUIRER_PROGRAM_NAME";

// HypCString: Settlement protocol
const char* AcquirerTag::SETTLEMENT_PROTOCOL = "ACQUIRER_SETTL_PROTOCOL";

// HypCString: CU Address for HLAN protocol
const char* AcquirerTag::ACQ_HLAN_ADDRESS = "ACQUIRER_HLAN_ADDRESS";

//=============================================================================
// Issuer record common tags
//=============================================================================
	
// Tag for parameters reserved for future use
const char* IssuerTag::ISSUER_TABLE 	= "ISSUER";
		
// Tag for parameters reserved for future use
const char* IssuerTag::ID 				= "ISSUER_ID";
	
// HypCString: Issuer card name
const char* IssuerTag::NAME  			= "ISSUER_NAME";
	
// HypCCurrency: Issuer floor limit
const char* IssuerTag::FLOOR_LIMIT		= "ISSUER_FLOOR_LIMIT";
	
// HypCString: Issuer default account id
const char* IssuerTag::DEFAULT_ACCOUNT_ID = "ISSUER_DEF_ACCT";
	
// HypCOption: Issuer options
const char* IssuerTag::ISSUER_OPT1		= "ISSUER_OPT1";
	
// HypCOption: Issuer options
const char* IssuerTag::ISSUER_OPT2		= "ISSUER_OPT2";
	
// HypCOption: Issuer options
const char* IssuerTag::ISSUER_OPT3		= "ISSUER_OPT3";
	
// HypCOption: Issuer options
const char* IssuerTag::ISSUER_OPT4		= "ISSUER_OPT4";
	
// HypCOption: Issuer options
const char* IssuerTag::ISSUER_OPT5		= "ISSUER_OPT5";
	
// HypCOption: Issuer options
const char* IssuerTag::ISSUER_OPT6		= "ISSUER_OPT6";

//=============================================================================
// Card record common tags
//=============================================================================

// Tag for parameters reserved for future use
const char* CardTag::CARD_TABLE		= "CARD";

// Tag for parameters reserved for future use
const char* CardTag::CARDRESERVED	= "CARD RESERVED";

// Acquirer ID
const char* CardTag::ACQUIRER_ID	= "CARD_ACQUIRER_TABLE_ID";
 
// Issuer ID
const char* CardTag::ISSUER_ID		= "CARD_ISSUER_TABLE_ID";

// First ten digits (0000000000 - 9999999999)
const char* CardTag::PAN_RANGE_HIGH	= "CARD_PAN_HIGH";
 
// First ten digits (0000000000 - 9999999999)
const char* CardTag::PAN_RANGE_LOW	= "CARD_PAN_LOW";

//=============================================================================
// Terminal configuration tags
//=============================================================================

// Tag for parameters reserved for future use
const char* TermConfigTag::TERMINAL_TABLE	= "TERMINAL";

// HypCString: Telephone dial options
const char* TermConfigTag::TCDOPT      	= "TERMINAL_TEL_DIAL_OPT";

// HypCString: Merchant password
const char* TermConfigTag::TCPWD       	= "TERMINAL_PASSWD";

// HypCString: Merchant name 1
const char* TermConfigTag::TCNAM1      	= "TERMINAL_DEF_MERCH_NAME";

// HypCString: Merchant name 2
const char* TermConfigTag::TCNAM2      	= "TERMINAL_RECEIPT_2";

// HypCString: Merchant name 3
const char* TermConfigTag::TCNAM3      	= "TERMINAL_RECEIPT_3";

// HypCString: Currency leading symbol
const char* TermConfigTag::TCLEADC     	= "TERMINAL_CURRENCY_SYMBOL";

// HypCString: Local terminal options
const char* TermConfigTag::TCLOCOP  		= "TERMINAL_LOCAL_OPT";

// HypCString: Pinpad type
const char* TermConfigTag::TCPINPAD		= "TERMINAL_PIN_PAD_TYPE";

// HypCString: Maintenance password
const char* TermConfigTag::TCMPWD			= "TERMINAL_MAINTENANCE_PASSWD";

// HypCOptions: General terminal configuration options
const char* TermConfigTag::TERMINAL_OPT1        = "TERMINAL_OPT1";

// Added for backward compatibility only. Should be removed! UBriedis
const char* TermConfigTag::TERM_CONFIG_OPTIONS  = "TERMINAL_OPT1";

// HypCOptions: General terminal configuration options
const char* TermConfigTag::TERMINAL_OPT5        = "TERMINAL_OPT5";

// HypCOptions: General terminal configuration options
const char* TermConfigTag::TERMINAL_OPT6        = "TERMINAL_OPT6";

// HypCOptions: General terminal configuration options
const char* TermConfigTag::PAUSE_PRINTING_2_REC = "PAUSE_PRINTING_2_REC";

//=============================================================================
// Security provider configuration tags
//=============================================================================

//! Tag for parameters reserved for future use
const char* SecProvTag::SECPROV_TABLE = "SECPROV";

//! Security provider from SECPROV table
const char* SecProvTag::SECURITY_PROVIDER = "SECURITY_PROVIDER";

//=============================================================================
// Some system wide data items
//=============================================================================

// System trace audit number
const char* SystemDataTag::SYSTEM_TABLE	=	"SYSTEM_PARAMETERS";
// System trace audit number
const char* SystemDataTag::SYSTEM_TRACE	=	"SYS_TRACE_NUMBER";
// Terminal invoice number
const char* SystemDataTag::INVOICE_NUMBER	=	"SYS_INVOICE_NUMBER";



const char* Soru::SORU_TABLE_NAME = "SORU";
const char* Soru::SORUID = "";

//=============================================================================
// ICC tags
//=============================================================================

// table name
const char* ICC_Tag::ICC_TABLE = "ICC";
const char* ICC_Tag::ICC_TABLE_ID = "TABLE_ID";
const char* ICC_Tag::ICC_TABLE_LENGTH = "TABLE_LENGTH";
const char* ICC_Tag::ICC_TABLE_NUMBER = "TBLNMBR";
const char* ICC_Tag::ICC_ISS = "ICCISS";
const char* ICC_Tag::ICC_TARG_PER_CENT = "ICCTARGPCT";
const char* ICC_Tag::ICC_MAX_PER_CENT = "ICCMAXPCT";
const char* ICC_Tag::ICC_TRESH = "ICCTHRESH";
const char* ICC_Tag::ICC_TAC_DEN = "ICCTACDEN";
const char* ICC_Tag::ICC_TAC_ONL = "ICCTACONL";
const char* ICC_Tag::ICC_TAC_DEF = "ICCTACDEF";

//=============================================================================
// TAIDTAB tags
//=============================================================================

// table name
const char* TAIDTAB_Tag::TAIDTAB_TABLE = "TAIDTAB";
const char* TAIDTAB_Tag::TABLE_ID = "TABLE_ID";
const char* TAIDTAB_Tag::TABLEID = "TABLEID";
const char* TAIDTAB_Tag::ADTID = "ADTID";
const char* TAIDTAB_Tag::AID_LEN = "AID_LEN";
const char* TAIDTAB_Tag::ICCAID = "ICCAID";
const char* TAIDTAB_Tag::TAIDTAB_OPT_1 = "TAIDTAB_OPT_1";
const char* TAIDTAB_Tag::TAIDVER1 = "TAIDVER1";
const char* TAIDTAB_Tag::TAIDVER2 = "TAIDVER2";
const char* TAIDTAB_Tag::TAIDVER3 = "TAIDVER3";


//=============================================================================
// KEYDATA tags
//=============================================================================

// table name
const char* KEYDATA_Tag::KEYDATA_TABLE = "KEYDATA";

//=============================================================================
// REVKEY tags
//=============================================================================

// table name
const char* REVKEY_Tag::REVKEY_TABLE = "REVKEY";

//=============================================================================
// CA_KEYS tags
//=============================================================================

// table name
const char* CA_KEYS_Tag::CA_KEYS_TABLE = "CA_KEYS";

//=============================================================================
// ADDTAGS tags
//=============================================================================

// table name
const char* ADDTAGS_Tag::ADDTAGS_TABLE = "ADDTAGS";

//=============================================================================
// KEYEXPIRE tags
//=============================================================================

// table name
const char* KEYEXPIRE_Tag::KEYEXPIRE_TABLE = "KEYEXPIRE";

//=============================================================================
// EMV_terminal tags
//=============================================================================
	
// local table name
const char* EMVTerminalTag::EMV_TABLE 	 = "EMV_Terminal";

// terminal type
const char* EMVTerminalTag::TERM_TYPE 	 = "TERMTYPE";

// local currency code
const char* EMVTerminalTag::CUR_CODE	 = "CURRCODE";

// country code
const char* EMVTerminalTag::COUNTRY_CODE = "CTRYCODE";

// terminal capabilities
const char* EMVTerminalTag::TERM_CAP 	 = "TCAP";

// additional terminal capabilities
const char* EMVTerminalTag::TERM_ADD_CAP = "ADDTCAP";

// application capabilities
const char* EMVTerminalTag::APP_CAPABILITIES = "APPCAP";

// transactio ntype
const char* EMVTerminalTag::TXNTYPE		 = "TXNTYPE";

const HyperwareConfig::CFG_OPT_MAPPING 
      HyperwareConfig::m_OptionsMapping[] = {
        {
            TC1_REST,       // Restaurant processing
            "TC1_REST"
        },
        {
            TC1_CASHIER,    // Cashier entry on
            "TC1_CASHIER"
        },
        {
            TC1_RECON,      // 0-enter, 1-confirm
            "TC1_RECON"
        },
        {
            TC5_HSMENU,     // Do host select using menu where applic
            "TC5_HSMENU"
        },
        {
            TC5_NOHSPRM,    // No host select prompt during settlemnt
            "TC5_NOHSPRM"
        },
        {
            TC6_PINBYPASSPIN,     // ALLOW PIN BYPASS (from pinpad)
            "TC6_PINBYPASSPIN"
        },
        {
			TC6_ICCEARLYAMT,    // EARLY AMOUNT ENTRY FOR ICC TXNS
			"TC6_ICCEARLYAMT"
		},
        {
            TC6_NOSECOND,   // Supress second receipt
            "TC6_NOSECOND"
        },
        {
            TCL_USE_RFID,     // NO REPORT PASSWORD
            "TCL_USE_RFID"
        },
        {
            // Ignore host time
            ACQ_IGNORE_HOST_TIME,
            "ACQ_IGNORE_HOST_TIME"
        },
        {
            // use GPRS connection
            ACQ_USE_GPRS,
            "ACQ_USE_GPRS"
        },
        {
            // Send batch no in 01x0 & 02x0 messages
            ACQ_SEND_BAT_NO,
            "ACQ_SEND_BAT_NO"
        },
        {
            TCP_SMCARD,   // SMART CARD ENABLED
            "TCP_SMCARD"
        },
        {
            // Is expiry date entry required
            ISS_EXPIRATION_DATE_ALLOWED,
            "ISS_EXPIRATION_DATE_ALLOWED"
        },
        {
            // Is roc number required (invoice number)
            ISS_ROC_NUMBER_REQUIRED,
            "ISS_ROC_NUMBER_REQUIRED"
        },
        {
            // Capture card range
            ISS_CAPTURE_CARD_RANGE,
            "ISS_CAPTURE_CARD_RANGE"
        },
        {
            // Generate 6 digit auth for floor limit
            ISS_GENERATE_6_DIGIT_AUTH,
            "ISS_GENERATE_6_DIGIT_AUTH"
        },
        {
            // This is a debit issuer
            ISS_DEBIT_ISSUER,
            "ISS_DEBIT_ISSUER"
        },
        {
            // Authorize if over floor limit
            ISS_AUTH_OVER_LIMIT,
            "ISS_AUTH_OVER_LIMIT"
        },
        {
            // Allow address verification
            ISS_ADDRESS_VERIFICATION_ALLOWED,
            "ISS_ADDRESS_VERIFICATION_ALLOWED"
        },
        {
            // Cardholder mail address required
            ISS_MAIL_ADDRESS_REQUIRED,
            "ISS_MAIL_ADDRESS_REQUIRED"
        },
        {
            // Cardholder zipcode required
            ISS_AVS_ZIPCODE_REQUIRED,
            "ISS_AVS_ZIPCODE_REQUIRED"
        },
        {
            // Enable level ii cmrc./purch. card amount
            ISS_LEVEL2_AMOUNT_ENABLED,
            "ISS_LEVEL2_AMOUNT_ENABLED"
        },
        {
            // Enable level ii cmrc./purch. card p.o. number
            ISS_LEVEL2_PO_ENABLED,
            "ISS_LEVEL2_PO_ENABLED"
        },
///////////////////////////////////////////////////////////////////////////////
////////// TABLE TERMINATOR ENTRY /////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
		{
			-1,
			""
		}
};

//-----------------------------------------------------------------------------
//!
//!      Look up for the particular option code in the option mapping table
//!
//! \param
//!      name   - option name
//!
//! \return
//!      int      option code as defined in HypTransactionTags.h
//!
//! \note
//!		
int HyperwareConfig::GetOptionCode( const HString& name )
{
	int i = 0;
	if ( !name.empty() )
	{
        while ( -1 != m_OptionsMapping[ i ].OptionCode )
		{
			if ( name == m_OptionsMapping[ i ].OptionName )
			{
				return m_OptionsMapping[ i ].OptionCode;
			}
			i++;
		}
	}
	return NOT_FOUND;
}

//-----------------------------------------------------------------------------
//!
//!      Look up for the particular option name in the option mapping table
//!
//! \param
//!      code   - option code
//!
//! \return
//!      HString      option name
//!
//! \note
//!		
HString HyperwareConfig::GetOptionName( int code )
{
	int i = 0;
	while ( -1 != m_OptionsMapping[ i ].OptionCode )
	{
		if ( code == m_OptionsMapping[ i ].OptionCode )
		{
			return m_OptionsMapping[ i ].OptionName;
		}
		i++;
	}
	return "NOT DEFINED";
}

//-----------------------------------------------------------------------------
//!
//!      Initializes tables index
//!
//! \return
//!      void
//!
//! \note
//!		
void HyperwareConfig::InitTables()
{
	int UnionCount = 0;
	int UnionID = -1;
	unsigned int PrevParamLength = 0;

	for (int i = 0; i < CFG_TABLES_COUNT; i++)
    {
		m_Tables[ i ].rows = 0;
    }

	// Set parameters offsets
	for (int i = 0; i < CFG_PARAMETERS_COUNT; i++) 
	{
		UnionCount = ( 0 == m_Parameters[ i ].offset ) ? 0 :
						( UnionID == m_Parameters[ i ].offset ) ? UnionCount + 1 : 
						( UnionID = m_Parameters[ i ].offset ) ? 1 : 1;

        if ( ( i > 0 ) && 
			 ( m_Parameters[ i ].table == m_Parameters[ i - 1 ].table ) )
        {
			if ( 2 > UnionCount )
			{
			    m_Parameters[ i ].offset = m_Parameters[ i - 1 ].offset + PrevParamLength;
			}
			else
			{
				m_Parameters[ i ].offset = m_Parameters[ i - 1 ].offset;
			}
        }
        else
        {
			m_Parameters[ i ].offset = 0;
			if ( 0 < UnionCount )
			{
				UnionCount = 1;
			}
        }
		if ( 2 > UnionCount )
		{
			PrevParamLength = m_Parameters[ i ].length;
		}
		else
		{
			if ( PrevParamLength < m_Parameters[ i ].length )
			{
				PrevParamLength = m_Parameters[ i ].length;
			}
		}
	}
}

//-----------------------------------------------------------------------------
//!
//!      Constructor
//!
//! \return
//!      void
//!
//! \note
//!		
HyperwareConfig::HyperwareConfig():
    m_Parameters ( NULL ),
    m_Options ( NULL ),
    m_Tables ( NULL ),
    m_Delta ( NULL ),
    CFG_SYS_PARAMS ( 0 ),
    CFG_TABLES_COUNT ( 0 ),
    CFG_PARAMETERS_COUNT ( 0 ),
    CFG_OPTIONS_COUNT ( 0 ),
    m_Initialized( false )
{
}

//-----------------------------------------------------------------------------
//!
//!      Destructor
//!
//! \return
//!      void
//!
//! \note
//!
HyperwareConfig::~HyperwareConfig()
{
	HYP_CFG_ROW_DESCRIPTOR* current = 0;
	HYP_CFG_ROW_DESCRIPTOR* tmp = 0;

    if ( m_Tables )
    {
    	for ( int i = 0; i < CFG_TABLES_COUNT ; i++)
        {
    		current = m_Tables[ i ].rows ;
    		while ( 0 != current )
            {
    			tmp = current -> next;
    			delete current;
    			current = tmp;
    		}
    	}
    	delete [] m_Tables;
    }

	delete [] m_Parameters;
	delete [] m_Options;

	ClearDelta( false );
}

//-----------------------------------------------------------------------------
//!
//!      Auxiliary routine for reading bytes from open file
//!
//! \param
//!      file	Handle to the file (should be open)
//! \param
//!      n       Number of bytes to read
//! \param
//!      buf     Buffer for the bytes
//!
//! \return
//!      bool
//!
//! \note
//!      
bool HyperwareConfig::ReadBytes( HypCFile * file, int n, uint8_t* buf )
{
	bool bRetVal = true;
	for( int i = 0; i < n; i++ ) 
    {
        if ((uint8_t)EOF == ( buf[i] = file->Getc( ) ))
        {
			bRetVal = false;
			break;
        }
	}
	return bRetVal;
}

//-----------------------------------------------------------------------------
//!
//!      Auxiliary routine to initialize System Parameters table
//!      (virtual table, which doesn't exist in the main CFG file; 
//!       additional system parameters are stored there by application)
//!
//! \param
//!      offset	Table "offset"; must be behind the end of the main CFG file
//!
//! \return
//!      bool	true - if init successful, false otherwise
//!
//! \note
//!
bool HyperwareConfig::InitSysParams( int offset )
{
	bool bRetVal = false;

	for ( int i = 0; i < CFG_TABLES_COUNT; i++ )
	{
		if ( m_Tables[ i ].Name == SystemDataTag::SYSTEM_TABLE )
		{
			CFG_SYS_PARAMS = i;
			break;
		}
	}

	if ( CFG_SYS_PARAMS < CFG_TABLES_COUNT ) 
    {
		m_Tables[ CFG_SYS_PARAMS ].offset = offset;
		m_Tables[ CFG_SYS_PARAMS ].data_length = 0;

		// calculate the length of data for the table:
        for ( int i = 0; i < CFG_PARAMETERS_COUNT; i++ ) 
        {
            if ( m_Parameters[ i ].table == m_Tables[ CFG_SYS_PARAMS ].ID ) 
            {
				m_Tables[ CFG_SYS_PARAMS ].data_length += 
					m_Parameters[ i ].length;				
            }
        }

		if ( 0 < m_Tables[ CFG_SYS_PARAMS ].data_length ) 
        {
			m_Tables[ CFG_SYS_PARAMS ].rows = new HYP_CFG_ROW_DESCRIPTOR;
			if ( m_Tables[ CFG_SYS_PARAMS ].rows ) 
            {
				m_Tables[ CFG_SYS_PARAMS ].rows_count = 1;
				m_Tables[ CFG_SYS_PARAMS ].rows -> ID = 0;
				m_Tables[ CFG_SYS_PARAMS ].rows -> DBID = 1;
				m_Tables[ CFG_SYS_PARAMS ].rows -> length = 
					m_Tables[ CFG_SYS_PARAMS ].data_length;
				m_Tables[ CFG_SYS_PARAMS ].rows -> next = 0;
				m_Tables[ CFG_SYS_PARAMS ].rows -> prev = 0;
				m_Tables[ CFG_SYS_PARAMS ].rows -> offset = 
					m_Tables[ CFG_SYS_PARAMS ].offset;
				m_Tables[ CFG_SYS_PARAMS ].rows -> table = 
					&m_Tables[ CFG_SYS_PARAMS ];

				bRetVal = true;
			} 
            else 
            {
				m_Tables[ CFG_SYS_PARAMS ].rows_count = 0;
				m_Tables[ CFG_SYS_PARAMS ].rows = NULL;
				m_Tables[ CFG_SYS_PARAMS ].data_length = 0;
				// return false;
			}
		} 
        else 
        {
			m_Tables[ CFG_SYS_PARAMS ].rows_count = 0;
			m_Tables[ CFG_SYS_PARAMS ].rows = NULL;
			bRetVal = true;
		}
	}
	return bRetVal;
}

//-----------------------------------------------------------------------------
//!
//!      Initializes the object of the class. 
//!      Performs some precalculations of tables/rows offsets, feels 
//!      cache tables used in further calculations.
//!
//! \return
//!      void
//!
//! \note
//!    
bool HyperwareConfig::Init()
{
	uint8_t c  = 0;
	uint8_t c1 = 0;
	uint8_t c2 = 0;
	int x = 0;
	uint16_t data_length = 0;
	HYP_CFG_ROW_DESCRIPTOR* current;
	HYP_CFG_ROW_DESCRIPTOR* tmp;
	HYP_CFG_DELTA_ITEM_DESCRIPTOR* currentD;
	HYP_CFG_DELTA_ITEM_DESCRIPTOR* tmpD;
	int desc = NOT_FOUND;
	int delta_offset;
	HypCFile file;
	uint32_t internal_descriptor;
	uint8_t buff[ sizeof(uint32_t) ];

	HString name;
	name.reserve( 20 );	// To avoid re-allocs later on

	// Initialize index for configuration file (m_Tables)
#if defined( USE_MEM_FILE )
	if ( file.Open( GetStorage() ) ) 
	{
		
		// setup the memory file
		memFile.Load( file );
		file.Close();

	}
	else
	{
		m_ErrCode = -1; // couldn't open "application.cfg"
		return false;
	}
#endif

	if ( HypCPOSConfig::Init() && InvokeParser() && InitControl() && _ADDITIONAL_FILES_ ) 
    {
		// Initialize index for configuration file (m_Tables)
		if ( file.Open( GetStorage() ) ) 
        {
		
		   // Read the first byte of cfg file table section 
		   // (length of the table name)
		   while ( (uint8_t)EOF != ( c = file.Getc(  ) ) ) 
           {
              c = CvtBin( c ); 
			  // Read table name
			  name.clear();
			  x = c;
              for ( int i = 0; i < x; i++ )
              {
                  if ( (uint8_t)EOF != ( c = file.Getc(  ) ) ) 
                  {
                      name += c;
                  }
				  else 
                  {
                      file.Close();
                      return false; // Cannot read table name
                  }
              }
			  name.ToUpper();
			  // Read table data length (max = 9999)
			  if ( ( (uint8_t)EOF != ( c = file.Getc(  ) ) ) && 
                  ( (uint8_t)EOF != ( c2 = file.Getc(  ) ) ) ) 
              {
				  data_length = CvtBin( c ) * 100 + CvtBin( c2 );
                  if( !data_length )  
                  {
                      // this is extended format supporting tables longer 9999 bytes, see ISS01580
                      if( !ReadBytes( &file, 4, buff ) )
                      {
                          file.Close();
                          return false; 
                      }
                      // length is big endian binary 4 byte integer
                      data_length = ( buff[0] << 24 ) + ( buff[1] << 16 ) + ( buff[2] << 8 ) + buff[3];
                      if( data_length < 9999 )
                      {
                          file.Close();
                          return false; 
                      }
                  }

				  if ( (uint8_t)EOF != ( c = file.Getc(  ) ) ) 
                  {
                      if ( CFG_TABLES_COUNT <= c ) 
                      {
                          file.Close();
                          return false; // Wrong table ID
                      }
					  m_Tables[ c ].data_length = data_length;
					  m_Tables[ c ].Name = name;
					  m_Tables[ c ].offset = 
						  ( HYP_CFG_HANDLE )(file.Tell(  ) - 1); 
					  // Offset of the first parameter of the first row
					  // Calculate table entries offsets and store its 
					  // to the rows* double linked list
					  x = 0;
					  current = 0;
					  while ( true ) 
                      {
						  if ( (HYP_CFG_HANDLE)file.Tell(  ) == 
							  m_Tables[ c ].offset + 
							  m_Tables[ c ].data_length ) 
                          {
                              break; 
                          }

                          if (x > 0) 
                          {
							  if ( (uint8_t)EOF == file.Getc (  ) )
                              {   
                                  file.Close();  // Read table name
								  return false;  // Data truncated
                              }                  // Read row length
                          }

						  if ( ( (uint8_t)EOF != ( c1 = file.Getc(  ) ) ) && 
                               ( (uint8_t)EOF != ( c2 = file.Getc(  ) ) ) ) 
                          {
								tmp = new HYP_CFG_ROW_DESCRIPTOR;
								tmp -> ID = x;
								if ( name == "REVKEY" ) 
								// this table doesn't have key field
								{
									tmp -> DBID = 255; // fake value
									file.Getc();
								}
								else
								{
									tmp -> DBID = file.Getc();
									if ( 1 == c ) // TERMINAL TABLE
									{
										tmp -> DBID = 1;
									}
									if ( (uint8_t)EOF == tmp -> DBID )
									{
										file.Close();
										return false;
									}
								}
								tmp -> length = CvtBin( c1 ) * 100 + CvtBin( c2 ) + 3;
								tmp -> next = 0;
								tmp -> prev = 0;
								tmp -> table = ( struct HYP_CFG_TABLE_DESCRIPTOR* )&m_Tables[ c ];
								tmp -> offset = file.Tell(  ) - 4;
								x++;
								if (0 == current) 
                                {
									m_Tables[ c ].rows = tmp;
									current = m_Tables[ c ].rows;
								} 
                                else 
                                {
									current -> next = tmp;
									tmp = current;
									current = current -> next;
									current -> prev = tmp;
								}
  								// Skip row data
								if ( file.Tell(  ) + ( current -> length - 4 ) != file.Seek( current -> length - 4, HypCFile::currentSeekPosition ) ) 
                                {
                                    file.Close();
                                    return false; // Table data was truncated
                                }
						  } 
                      }
						
					  m_Tables[ c ].rows_count = x;
                  } 
                  else 
                  {
                      file.Close();
                      return false; // Cannot read table ID
                  }
			  } 
              else 
              {
                  file.Close();
                  return false; // Cannot read datalength
              }
		   } 
		   // Initialize additional parameters table
		   InitSysParams( file.FileSize() );
		   file.Close();
        } 
        else 
        {
		   file.Close();
		   m_ErrCode = -1; // couldn't open "application.cfg"
		   return false; // HypCFile.Open failed
		}
		// Initialize index for delta file (m_Delta)
		currentD = 0;
		delta_offset = 0;
		if ( file.Open( GetDelta() ) ) 
        {
			while ( ReadBytes( &file, sizeof(internal_descriptor), buff ) ) 
            {
				tmpD = new HYP_CFG_DELTA_ITEM_DESCRIPTOR;
				tmpD -> internal_descriptor = 0;
                for ( uint16_t i = 0; i < sizeof(internal_descriptor); i++ ) 
                {
					tmpD -> internal_descriptor |= ((HYP_CFG_HANDLE)buff[i]) <<
						(((sizeof(internal_descriptor) - i) << 3) - 8);
                }
				desc = (int)GetIdFromParamInternalDesc( tmpD -> 
					internal_descriptor );
				desc = CvtBin(( desc >> 8 ) & 0xff ) * 100 + 
						CvtBin( desc & 0xff );
				if ( NOT_FOUND == desc ) 
                {   // Delta file is corrupted
					ClearDelta(  );
					break;
				} 
                else 
                {
					// Adds delta item descriptor to the list
					tmpD -> delta_offset = delta_offset;
					tmpD -> next = 0;
					tmpD -> prev = 0;
					if ( 0 == currentD ) 
                    {
						m_Delta = tmpD;
						currentD = tmpD;
					} 
                    else 
                    {
						currentD -> next = tmpD;
						tmpD = currentD;
						currentD = currentD -> next;
						currentD -> prev = tmpD;
					}
					// Skip parameter data
					delta_offset = file.Seek( m_Parameters[ desc ].length, HypCFile::currentSeekPosition );
				}
			}
			file.Close();
		} 
        else 
        {
			file.Close();
		}
		m_Initialized = true;
	} // superclass Init successful if filename m_CfgStorage is defined
	else
	{
		m_Initialized = false;
	}
	return m_Initialized;
}
		
//-----------------------------------------------------------------------------
//!
//!      Gets handle to the configuration table by table name 
//!
//! \param
//!      tableName           Name of the configuration DB table
//!
//! \return
//!      HYP_CFG_HANDLE        Handle to the table. In this realization it is
//!                          an offset of the table from the start of CFG file.
//!
//! \note
//!
HYP_CFG_HANDLE HyperwareConfig::GetTable(const HString& tableName) 
{
	if ( _INITIALIZED_ )
    {
		HString name ( tableName );
		name.ToUpper();

        for (int i = 0; i < CFG_TABLES_COUNT; i++) 
        {
			if ( ( m_Tables[ i ].offset > -1 ) &&
				 ( m_Tables[ i ].data_length > 0 ) && 
				 ( name == m_Tables[ i ].Name ) ) 
            { 
				return m_Tables[ i ].offset;
            }
        }
	}
	return NOT_FOUND;
}

//-----------------------------------------------------------------------------
//!
//!      Gets handle to the configuration table by table ID 
//!
//! \param
//!      tableID           ID of the configuration DB table
//!
//! \return
//!      HYP_CFG_HANDLE        Handle to the table. In this realization it is
//!                          an offset of the table from the start of CFG file.
//!
//! \note
//!
HYP_CFG_HANDLE HyperwareConfig::GetTable(const HYP_CFG_ID tableID) 
{
	if ( _INITIALIZED_ ) 
    {
		if ( ( tableID < CFG_TABLES_COUNT ) && 
			 ( tableID > -1 ) && 
			 ( m_Tables[ tableID ].offset > -1 ) &&
			 ( m_Tables[ tableID ].data_length > 0 ) )
        {
			return m_Tables[ tableID ].offset;
        }
	}
	return NOT_FOUND;
}

//-----------------------------------------------------------------------------
//!
//!      Gets handle to the row by row number
//!      There are predefined row numbers LAST, NEXT, PREV, FIRST, 
//!      NO_DATA_FOUND.
//!
//! \param
//!      table            HANDLE to the table which contains requested row  
//! \param
//!      rowID           ID of the configuration DB table
//!
//! \return
//!      HYP_CFG_HANDLE        Handle to the row. In this realization it is
//!                            an offset of the table row from 
//!                            the start of CFG file.
//!
//! \note
//!
HYP_CFG_HANDLE HyperwareConfig::GetTableRow( HYP_CFG_HANDLE table, 
											 HYP_CFG_ID rowID) 
{
	static HYP_CFG_ROW_DESCRIPTOR* currentRow = 0;
    static int currentTable = 0;
    
	if ( _INITIALIZED_ ) 
    {
		// Find table 
		if ( !(0 <= currentTable && currentTable < CFG_TABLES_COUNT 
			&& m_Tables[ currentTable ].offset == table) ) 
        {
			for ( int i = 0; i < CFG_TABLES_COUNT; i++ ) 
            {
				if ( table == m_Tables[ i ].offset && 
					0 < m_Tables[ i ].data_length ) 
                {
					currentTable = i;
					break;
				}
			}

		    if ( !( table == m_Tables[ currentTable ].offset && 
				    0 < m_Tables[ currentTable ].data_length ) ) 
            {
				return NOT_FOUND;
            }
		}
	    
		// Find requested row
		switch( rowID ) 
        {
			case FIRST:
				currentRow = ( 0 != m_Tables[ currentTable ].rows) ? 
							   m_Tables[ currentTable ].rows : 0 ;
				break;
			case LAST:
				currentRow = m_Tables[ currentTable ].rows;
                if (0 != currentRow) 
                {
					while ( 0 != currentRow -> next )
                    {
						currentRow = currentRow -> next;
                    }
                }
				break;
			case NEXT:
				if ( 0 != currentRow && 0 != currentRow -> next )
                {
					currentRow = currentRow -> next;
                }
				else
                {
					currentRow = 0;
                }
				break;
			case PREV:
				if ( 0 != currentRow && 0 != currentRow -> prev )
                {
					currentRow = currentRow -> prev;
                }
				else
                {
                    currentRow = 0;
                }
				break;
			default:
				currentRow = m_Tables[ currentTable ].rows;
				if ( m_Tables[ currentTable ].rows_count > rowID 
					&& 0 <= rowID )
                {
					for ( int i = 0; i < rowID; i++ )
                    {
						currentRow = currentRow -> next;
                    }
                }
				break;
		}
		return ( 0 == currentRow) ? NOT_FOUND : currentRow -> offset;
	} else return NOT_FOUND;
}

//-----------------------------------------------------------------------------
//!
//!      Looks for the particular row using parameter value as a key
//!
//! \param
//!      table         HANDLE to the table which contains requested row 
//! \param
//!      searchParam   Parameter used as a key for the search
//! \param
//!      searchValue   Value for searchParam
//!
//! \return
//!      HYP_CFG_HANDLE     Handle to the row. In this realization it is
//!                         an offset of the table row from the start of 
//!                         CFG file.
//!
//! \note
//!        which contains searchParam which equals to the searchValue. 
//!        To find next row which contains searchParam which equals to 
//!        the searchValue, call this method one more time.
//!
HYP_CFG_HANDLE HyperwareConfig::FindTableRow( HYP_CFG_HANDLE table, 
											  const char * searchParam, 
											  const HypCData& searchValue )
{
	HString param;
	HYP_CFG_HANDLE handle = GetTableRow( table, FIRST );
	const HString strSearchVal = searchValue.AsString().Trim();

	while ( (HYP_CFG_HANDLE)NOT_FOUND != handle ) 
    {
        param = this->GetParam( handle, searchParam ).Trim();
	
		if ( !param.empty() && 
			 ( param == strSearchVal ) )
		{
			return handle;
		}
		handle = this -> GetTableRow( table, NEXT );
	}

	return NOT_FOUND;
}

//-----------------------------------------------------------------------------
//!
//!      Auxiliary method which encapsulates all work needed to check
//!      if provided BCD date is valid. Date should be passed in BCD form
//!      in format YYMMDDHHMMSS or YYMMDD.
//!
//! \param
//!      bcd          date
//! \param
//!      n		     Length of the date
//!
//! \return
//!      bool         true - if date is valid, false - otherwise
//!
//! \note
//!
bool HyperwareConfig::CheckBCDDate(uint8_t* bcd, int n)
{
	switch ( n ) 
    {
		case 3:
			if ( bcd[0] <= 0x99 && 
			     bcd[1] >= 0x01 && bcd[1] <= 0x12 && 
			     bcd[2] >= 0x01 && bcd[2] <= 0x31 )
            {
				 return true;
            }
			else
            {
				return false;
            }
		case 6:
			if ( bcd[0] <= 0x99 && 
			     bcd[1] >= 0x01 && bcd[1] <= 0x12 && 
			     bcd[2] >= 0x01 && bcd[2] <= 0x31 && 
			     bcd[3] <= 0x24 && 
			     bcd[4] <= 0x60 && 
			     bcd[5] <= 0x60)
            {
				 return true;
            }
			else
            {
				return false;
            }
		default:
			return false;
	}
}

//-----------------------------------------------------------------------------
//!
//!      Auxiliary method which encapsulates all work needed to read the 
//!      parameter from file. File pointer should point to the start of 
//!      the parameter.
//!
//! \param
//!      file          File handle (should be open)
//! \param
//!      length		  Length of parameter value
//! \param
//!      type          Type of the parameter
//!
//! \return
//!      HString       string data in form as required for assigned HypCData object
//!
//! \note
//!
HString HyperwareConfig::GetParamFromFile( HypCFile * file, 
										   uint32_t length, 
										   const HypC11NType type,
										   const HypC11NType appType) 
{
	uint8_t buff [ length + 1 ];
	HString ascii;

	if ( file -> IsOpen( ) ) 
    {
		unsigned int bytes_read = 0;
		file -> Read( buff, length, bytes_read );
		if ( bytes_read != length ) 
        {
			return ascii;						// Data was truncated 
												// or invalid length
		}										// was specified
	} 
    else	
    {
		return ascii;					
	}
									

	switch ( type )
	{
	case CFG_BCD_BYTE:
	{
		char a[] = "  ";
	
		ascii.clear();

		for (uint32_t i = 0; i < length; i++) 
		{
			BufAsc(a, &buff[ i ]);
			ascii += a ;
		}

		// return all these as strings
		switch ( appType ) 
		{
		case CFG_APP_INT32:
			{
				HypCInt32 result( ascii );
				ascii = result.AsString();
				break;
			}
		case CFG_APP_INT64:
			{
				HypCInt64 result ( ascii );
				ascii = result.AsString();
				break;
			}
		default:
			{
				// simply return ascii as it is already. 
				break;
			}
		}
	}
	break;

	case CFG_ALPHA_BYTE:
		{
            buff[ length ] = '\0';
			ascii = HString ( reinterpret_cast<const char*>(&buff[0]) ).Trim();
			break;
		}

	case CFG_BITSET_BYTE:
		{
            HypCInt8 result ( buff[0] );
			ascii = result.AsString();
			break;
		}

	case CFG_DTBCD_BYTE:

		if ( CheckBCDDate( buff, length) ) 
		{
			switch ( length ) 
			{
			case 3: // Convert time from BCD
				{
                    buff[0] = CvtBin( buff[0] );
					buff[1] = CvtBin( buff[1] );
					buff[2] = CvtBin( buff[2] );
					HypCDateTime dt ( buff[0], buff[1], buff[2] );		
					ascii = dt.AsString();
					break;
				}
			case 6:
				{
                    buff[0] = CvtBin( buff[0] );
					buff[1] = CvtBin( buff[1] );
					buff[2] = CvtBin( buff[2] );
					buff[3] = CvtBin( buff[3] );
					buff[4] = CvtBin( buff[4] );
					buff[5] = CvtBin( buff[5] );
					HypCDateTime dt ( buff[0], buff[1], buff[2] );
					dt.TimeFromBCD( buff + 3 );
					ascii = dt.AsString(); 
					break;
				}
			default:
				{
                    ascii.clear(); // Wrong date format
					break;
				}
			}
		} 
		else 
		{
			ascii.clear();
		}
		break;

	default:
	    ascii.clear();	// Wrong data type defined in 
		break;     		// parameters definition tables
	}

	return ascii;
}

//-----------------------------------------------------------------------------
//!
//!      Auxiliary method which writes configuration parameter to the file.
//!      File pointer should point to the start of the parameter.
//!
//! \param
//!      file          File handle (should be open)
//! \param
//!      length		  Length of parameter value
//! \param
//!      value         Parameter value, should be packed 
//!                    in the object of the class derived from HypCData
//! \param
//!      type          Type of the field in the configuration file
//!
//! \return
//!      bool          true if parameter was written successfully, false - otherwise.
//!
//! \note
//!
bool HyperwareConfig::WriteParamToFile( HypCFile * file, 
										const uint32_t length, 
										const HypCData* value, 
										const HypC11NType type )
{
	if ( 0 != value ) 
    {
		size_t i, x;
		uint32_t bytes_written;
		uint64_t q;
		uint8_t buff[ length + 1 ];

		HString ascii = value -> AsString();

		switch (type) 
        {
			case CFG_BCD_BYTE:	
                if ( ascii.length() % 2 ) 
                {
					//ascii = HString("0") + ascii;
					ascii.insert( 0, 1, '0' );
                }
				if ( length >= static_cast<uint32_t>( ascii.length() / 2 ) ) 
                {
					x = length - (ascii.length() >> 1);
					AscHex( buff + x, ascii.c_str(), (uint8_t)(length - x));
                    for ( i = 0; i < x; i++ ) 
                    {
						buff[i] = 0;
                    }
				} 
                else 
                {
					return false;
				}
				break;
			case CFG_ALPHA_BYTE:
                for ( i = 0; i < static_cast<size_t>( ascii.length() ); i++ ) 
                {
					buff[ i ] = ascii[ i ];
                }
				for ( ; i < length; i++  )
                {
					buff[ i ] = ' ';
                }
				break;
			case CFG_BITSET_BYTE:
				q = value -> AsWord(); // due options are set as Int8
				for (uint32_t j = 0; j < length; j++) 
                {
					buff[ j ] = (uint8_t)(q >> (j << 3));
				}
				break;
			case CFG_DTBCD_BYTE:
				switch ( length ) 
                {
				case 6:
					((HypCDateTime *)value) -> DateToBCD( buff, HypCDateTime::yymmdd );
					((HypCDateTime *)value) -> TimeToBCD( buff + 3 );
					break;
				case 3:
					((HypCDateTime *)value) -> DateToBCD( buff, HypCDateTime::yymmdd );
					break;
				default:
					return false; // Wrong length
				}
				break;
			default: 
				return false; // Wrong data type defined in 
				break;        // parameters definition tables
		}

		if ( file -> Write( buff, (unsigned int)length, (unsigned int&)
                     bytes_written ) && bytes_written == length ) 
        {
			return true;
		}
		return false;
	} 
	return false;
}

//-----------------------------------------------------------------------------
//!
//!      Gets configuration parameter by parameter name.
//!
//! \param
//!      row           Handle to the row of the configuration DB table
//! \param
//!      paramName     Name of the parameter
//!
//! \return
//!      HString       Parameter value, "" if not found
//!
//! \note
//!		Delta file format:
//!			<param_offset><param_value>
//!          ------------  -----------
//!           sizeof(int)   m_Parameters[ param ].length
//!   
//!      Where: param_offset - offset of the parameter in main CFG file,
//!             if param_offset > CFG file length => parameter was set by application
//!             param_value - parameter's value
//!
//!      Variable length parameters (type CFG_VARALPHA) are not supported yet
//!
HString HyperwareConfig::GetParam( const HYP_CFG_HANDLE row, 
								   const char * paramName ) 
{
	int paramDesc = -1;
	HYP_CFG_DELTA_ITEM_DESCRIPTOR* currentD = 0;
	HString strRetVal;

	if ( _INITIALIZED_ ) 
    {
		// Get the table descriptor for this row.
		const uint32_t tmpTableDescriptor = GetDescriptor( row, TABLE );

		// Find parameter description
	    for (int i = 0; i < CFG_PARAMETERS_COUNT; i++ ) 
        {
			if ( ( tmpTableDescriptor == static_cast<uint32_t>(m_Parameters[ i ].table) ) &&
				 ( m_Parameters[ i ].paramName == paramName ) )
            {
				paramDesc = i;
				break;
			}
  	    }
        if ( -1 == paramDesc ) 
        {
			// strRetVal is empty at this point.
			DBGPRINTF ( VLVL_NORMAL, CLASS_HYPERWARE, "%s - Unable to find %s\n", __FUNCTION__, paramName );
			return strRetVal; // Cannot find description - unknown parameter
        }

		HypCFile file ( GetDelta() );
		if ( file.IsOpen() )
		{
            // Check delta ( local settings has priority! )
			currentD = m_Delta;
			while ( 0 != currentD )
			{
				if ( GetParamOffsetFromParamInternalDesc( currentD->internal_descriptor ) 
					 == row + m_Parameters[ paramDesc ].offset )
				{
					const int nSeekTo = currentD->delta_offset + sizeof(uint32_t);
					if ( nSeekTo == static_cast<int>( file.Seek( nSeekTo, HypCFile::beginSeekPosition )) )
					{
						// It can return anything, because if GetParamFromFile
						// returns NULL, then it means that an error occured not
						// in the data, but in parameters definitions
						strRetVal = GetParamFromFile( &file, 
													 m_Parameters[ paramDesc ].length, 
													 m_Parameters[ paramDesc ].type,
													 m_Parameters[ paramDesc ].appType);

						return strRetVal;
					}
				}
				currentD = currentD->next;
			}
		} else	// Delta file was corrupted or non-existent.
		{
			file.Close();
			ClearDelta();
		}
		file.Close();

		// Did not find the parameter on the delta file. Clear result and
		// look for it on the regular configuration file.
		strRetVal.clear();
		// Get parameter ( if not found in delta or delta was corrupted )
#if defined( USE_MEM_FILE )
		if ( memFile.Open() )
#else
		if ( file.Open( GetStorage() ) )
#endif
		{
			const int nSeekTo = row + m_Parameters[ paramDesc ].offset;
#if defined( USE_MEM_FILE )
			if ( nSeekTo == static_cast<int>( memFile.Seek( nSeekTo, HypCFile::beginSeekPosition ) ) )
			{
				strRetVal = GetParamFromFile( &memFile, 
											  m_Parameters[ paramDesc ].length,
											  m_Parameters[ paramDesc ].type, 
											  m_Parameters[ paramDesc ].appType );
			}

#else
			if ( nSeekTo == static_cast<int>(file.Seek( nSeekTo, HypCFile::beginSeekPosition )) )
			{
				strRetVal = GetParamFromFile( &file, 
											  m_Parameters[ paramDesc ].length,
											  m_Parameters[ paramDesc ].type, 
											  m_Parameters[ paramDesc ].appType );
			}

#endif

		}
    }
	return strRetVal;
}


bool HyperwareConfig::GetRawRow( const HYP_CFG_HANDLE row, void* buff ) 
{
	//int paramDesc = -1;
	HYP_CFG_DELTA_ITEM_DESCRIPTOR* currentD = 0;
	HString strRetVal;

	if ( _INITIALIZED_ ) 
    {

#if defined( USE_MEM_FILE )
		if ( memFile.Open() )
#else
		if ( file.Open( GetStorage() ) )
#endif
		{
			unsigned int bytes_read = 0;
			const int nSeekTo = row + 1;
			uint16_t rowsz;
		
#if defined( USE_MEM_FILE )
			if ( nSeekTo == static_cast<int>( memFile.Seek( nSeekTo, HypCFile::beginSeekPosition ) ) )
			{
				memFile.Read( &rowsz, 2, bytes_read );
				rowsz = CvtBinW( ( rowsz >> 8 ) | ( rowsz << 8 ) );
				memFile.Read( buff, rowsz, bytes_read );
			}

#else
			if ( nSeekTo == static_cast<int>(file.Seek( nSeekTo, HypCFile::beginSeekPosition )) )
			{
				file.Read( &rowsz, 2, bytes_read );
				rowsz = CvtBinW( ( rowsz >> 8 ) | ( rowsz << 8 ) );
				file.Read( buff, rowsz, bytes_read );
			}
#endif

		}
    }
	return true;
}

//-----------------------------------------------------------------------------
//!
//!      Checks if a particular configuration option is set or not
//!
//! \param
//!      row           Handle to the row of the configuration DB table
//! \param
//!      optionName    Name of the option
//!
//! \return
//!      bool          true - if option is set, false - otherwise
//!
//! \note
//!	Optimization notes: This function should use a HypCOptions object
//!	to read the needed boolean value.
//!  In order to implement this, the initialization step must create and
//!  populate the HypCOptions object we need here.
//!
bool HyperwareConfig::IsOptionSet( const HYP_CFG_HANDLE row, int optionBit )
{
	bool res = false;

	if ( _INITIALIZED_ ) 
    {
		const uint32_t tmpTableDescriptor = GetDescriptor( row, TABLE);
		// Find option descriptor
        for ( int i = 0; i < CFG_OPTIONS_COUNT; i++ )
        {
			uint32_t cur_table = static_cast<uint32_t>( m_Parameters[ m_Options[ i ].paramID ].table );
			if ( ( m_Options[ i ].optionID == optionBit ) &&
				 ( tmpTableDescriptor == cur_table ) )
			{
				// Get parameter
				HString str = GetParam( row,
										m_Parameters[ m_Options[ i ].paramID ].paramName.c_str() );
				if ( !str.empty() ) 
                {
					HypCInt8 options ( str );
                    uint8_t t = options;
					if( t & m_Options[ i ].mask )
					{
						res = true;
					}
				}
				break; // Cannot get parameter for some reason
			}
        }
    }
    return res;
}

//-----------------------------------------------------------------------------
//!
//!      Sets configuration parameter value
//!
//! \param
//!      row           Handle to the row of the configuration DB table
//! \param
//!      paramName     Name of the parameter
//! \param
//!      value         New value of the parameter
//!
//! \return
//!      None
//!
//! \note
//!
void HyperwareConfig::SetParam( const HYP_CFG_HANDLE row, const char * paramName, const HypCData& value ) 
{
	int paramDesc = -1;
	HYP_CFG_DELTA_ITEM_DESCRIPTOR* currentD = NULL;
	HYP_CFG_DELTA_ITEM_DESCRIPTOR* tmpD = NULL;
	HypCFile file;
	uint32_t internal_descriptor = 0;
	uint8_t buff_len[ sizeof(uint32_t) ];
	int delta_offset = 0;
	uint32_t table = 0, id = 0;
	HYP_CFG_ROW_DESCRIPTOR * row_desc = NULL;

	if ( _INITIALIZED_ && 0 != &value ) 
    {
	   for (int i = 0; i < CFG_PARAMETERS_COUNT; i++ ) 
       {
			if( GetDescriptor(row,TABLE) == static_cast<uint32_t>(m_Parameters[ i ].table) &&
				m_Parameters[ i ].paramName == paramName ) 
            {
				paramDesc = i;
				break;
			}
  	    }
       if ( -1 == paramDesc ) 
       {
           return; // Cannot find parameter description
       }

		// Check delta
		currentD = m_Delta;
		while ( 0 != currentD ) 
        {
			if ( GetParamOffsetFromParamInternalDesc( currentD -> internal_descriptor ) 
				== row + m_Parameters[ paramDesc ].offset ) 
            {
				// Process existing parameter in delta
				if ( CFG_VARALPHA != m_Parameters[ paramDesc ].type ) 
				{ 
					if ( file.Open( GetDelta() , F_OPEN_EXISTING, F_WRITE ) ) 
                    {
						const int nSeekPos = currentD->delta_offset + sizeof(HYP_CFG_HANDLE);
						if ( nSeekPos == static_cast<int>( file.Seek( nSeekPos, // 4 = offset field
													HypCFile::beginSeekPosition) ) ) 
                        {
						     WriteParamToFile( &file, 
											   m_Parameters[ paramDesc ].length, 
											   &value, 
											   m_Parameters[ paramDesc ].type );
						     file.Close();
						     return;
						} 
                        else 
                        {
						     ClearDelta();
                        }
						file.Close();
					}
                    else
                    {
						file.Close();
                    }
				} 
                else 
                {
                    return; // Variable length strings cannot be changed locally 
                }
			} 
			currentD = currentD -> next;
		}

		// If parameter not found in delta...
		// ...write it to the end of delta file...

#if defined(__GNUC__) || defined(__ARMCC_VERSION)
#define	MODE F_WRITE | F_READ     
		int size = HypCFile::FileSize( GetDelta() );
        int FLAG = 0;
		if ( 0 < size )
        {
			FLAG = F_OPEN_EXISTING | F_SHARE_READ;
        }
		else
        {
			FLAG = F_CREATE | F_SHARE_READ;
        }
#else
#define	MODE F_WRITE       // This hack is needed,
#define	FLAG F_OPEN_ALWAYS // because flags of HypCFile_Win32 and 
#endif                     // flags of HypCFile_Win32 aren't compatible

		if ( file.Open( GetDelta(), FLAG, MODE ) ) 
        {
			 file.Seek( 0, HypCFile::endSeekPosition);
			 delta_offset = file.Tell( );

			 table = GetDescriptor( row + m_Parameters[ paramDesc ].offset, TABLE );

			 row_desc = (HYP_CFG_ROW_DESCRIPTOR *)GetDescriptor( row + m_Parameters[ paramDesc ].offset, ROW );

			 id = GetDescriptor( row + m_Parameters[ paramDesc ].offset, PARAM );

			 table = BinBcdB( (uint8_t)( table & 0xff) );

			 id = ( BinBcdB( (uint8_t)( id / 100 ) ) << 8 ) | 
					BinBcdB( (uint8_t)( id % 100 ) );

			 internal_descriptor = CreateParamInternalDesc( table,
															row_desc -> DBID, 
															id );
			 for ( size_t i = 0; i < sizeof(internal_descriptor); i++ )
             {
				 buff_len[ i ] = (uint8_t)(internal_descriptor >> (((sizeof(internal_descriptor) - i) << 3) - 8) & 0xff);
             }

			 unsigned int bytes_written = 0;

			 file.Write( &buff_len, sizeof(uint32_t), bytes_written );
             if ( sizeof(uint32_t) == bytes_written ) 
             {
				WriteParamToFile( &file, 
								  m_Parameters[ paramDesc ].length, 
								  &value, 
								  m_Parameters[ paramDesc ].type );
             }
			 file.Close();
  		     
			 // ...and create a descriptor for m_Delta list.
			 tmpD = new HYP_CFG_DELTA_ITEM_DESCRIPTOR;
			 tmpD->delta_offset = delta_offset;
			 tmpD->next = 0;
			 tmpD->prev = 0;
			 tmpD->internal_descriptor = internal_descriptor;
			 currentD = m_Delta;
			 if ( 0 == currentD )
             {
				 m_Delta = tmpD;
             }
			 else 
             {
                 while ( 0 != currentD -> next ) 
                 {
					currentD = currentD -> next;
                 }
				 tmpD -> prev = currentD;
				 currentD -> next = tmpD;
			 }
		}
	}
}

#undef MODE
#undef FLAG

//-----------------------------------------------------------------------------
//!
//!      Sets configuration option
//!
//! \param
//!      row           Handle to the row of the configuration DB table
//! \param
//!      optionName    Name of the option
//! \param
//!      option        New value of the option
//!
//! \return
//!      None
//!
//! \note
//!
void HyperwareConfig::SetOption(const HYP_CFG_HANDLE row, int optionBit, bool option) 
{
	if ( _INITIALIZED_ ) 
    {
		// Find option descriptor
        for ( int i = 0; i < CFG_OPTIONS_COUNT; i++ ) 
		{
			if ( m_Options[ i ].optionID == optionBit &&
				 GetDescriptor( row, TABLE) == 
				 static_cast<uint32_t>(m_Parameters[ m_Options[ i ].paramID ].table ) )
			{
				// Get parameter
				HString str = GetParam(row, m_Parameters[ m_Options[ i ].paramID ].paramName.c_str() );
				if ( !str.empty() ) 
				{
					HypCInt8 tmp(str);
					uint8_t options = tmp;

					if ( ! ( options & m_Options[ i ].mask ) )
					{
						if ( option ) 
						{
							options |= m_Options[ i ].mask;
							tmp = options;
							SetParam( row, m_Parameters[ m_Options[ i ].paramID ].paramName.c_str(), tmp );
						}
					}
					else
					{
						if ( ! option ) 
						{
							options &= (~m_Options[ i ].mask);
							tmp = options;
							SetParam( row, m_Parameters[ m_Options[ i ].paramID ].paramName.c_str(), tmp );
						}
					}
					break;
				}
				else
				{
					break;
				}
			} 
		}
	}
}

//-----------------------------------------------------------------------------
//!
//!     Returns position of parameter descriptor in global descriptor table
//!
//! \param
//!      globalOffset	offset from the beginning of the file
//! \param
//!      type            type of requested CFG entity ( TABLE, ROW, PARAM )
//!
//! \return
//!      int		position of parameter descriptor in m_Parameters table,
//!				or NOT_FOUND
//!
//! \note
//!
uint32_t HyperwareConfig::GetDescriptor( HYP_CFG_HANDLE globalOffset, DescType type ) 
{
	HYP_CFG_ROW_DESCRIPTOR* current = NULL;
	int localOffset = 0;

	for (int i = 0; i < CFG_TABLES_COUNT; i++) 
    {
		if ( ( m_Tables[ i ].data_length + m_Tables[ i ].offset > globalOffset ) &&
			 ( m_Tables[ i ].offset <= globalOffset ) && 
			 ( NULL != m_Tables[ i ].rows ) ) // Found non-empty table
		{
			if ( TABLE == type ) 
            {
                return i;
            }
			 // Find row
			current = m_Tables[ i ].rows;
            while ( 0 != current ) 
            {
				if ( ( current->offset <= globalOffset ) &&
					 ( current->length + current->offset > globalOffset ) ) // Row found
				{
                    if ( ROW == type ) 
                    {
                        return reinterpret_cast<uint32_t>(current);
                    }
					localOffset = globalOffset - current -> offset;
					for ( int j = 0; j < CFG_PARAMETERS_COUNT; j++ )
                    {
						if ( m_Parameters[ j ].table == m_Tables[ i ].ID &&
							 m_Parameters[ j ].offset == localOffset )
                        {
							 return j; // Return parameter
                        }
                    }
				}
				current = current -> next;
            }
		}
	}
	return NOT_FOUND;
}

//-----------------------------------------------------------------------------
//!
//!      Clears delta file and related data
//!
//! \return
//!      None
//!
//! \note
//!
void HyperwareConfig::ClearDelta( bool deleteFile ) 
{
	HYP_CFG_DELTA_ITEM_DESCRIPTOR* currentD = 0;
	HYP_CFG_DELTA_ITEM_DESCRIPTOR* tmpD = 0;

	if ( deleteFile ) 
    {
        HypCFile::Delete( GetDelta() );
    }
    
	currentD = m_Delta;

	while ( 0 != currentD ) 
    {
		tmpD = currentD;
		currentD = currentD -> next;
		delete tmpD;
	}

	m_Delta = 0;
}

//-----------------------------------------------------------------------------
//!
//!      Invokes configuration file's parser. Uses the following global 
//!      variables:
//!          yyin     input for parser
//!          FirstRun 1 or 0; parser is designed to work in two-run mode, i.e.
//!                   during the first run it counts the elements and validates 
//!                   grammar, but on second run it reads elements into 
//!                   corresponding arrays
//!
//! \return
//!      true if the parsing process succeeded, false otherwise.
//!
//! \note
//!
bool HyperwareConfig::InvokeParser() 
{
	extern HYP_CFG_OPTION_DESCRIPTOR * CfgOptions;
	extern HYP_CFG_PARAMETER_DESCRIPTOR * CfgParameters;
	extern HYP_CFG_TABLE_DESCRIPTOR * CfgTables;
	extern int CFG_TBL_COUNT_OUT;
	extern int CFG_OPT_COUNT_OUT;
	extern int CFG_PAR_COUNT_OUT;
	extern int FirstRun;
	extern HypCFile * yyin;
	extern int yyparse(); // Returns:
						  //   0 - YYACCEPT - success
						  //   1 - YYABORT  - failure

	HypCFile cfgDesc;
	yyin = &cfgDesc;
	int result = 1;	// failure

	if( yyin->Open( GetDBDesc(), F_READ ) )
	{
		FirstRun = 1;
		result = yyparse();
		yyin -> Close();

		if ( !result ) 
		{
			FirstRun = 0;
			yyin -> Open( GetDBDesc(), F_READ );
			result = yyparse();
			if ( !result )
			{
				m_Parameters = CfgParameters;
				m_Options = CfgOptions;
				m_Tables = CfgTables;
				CFG_OPTIONS_COUNT = CFG_OPT_COUNT_OUT;
				CFG_PARAMETERS_COUNT = CFG_PAR_COUNT_OUT;
				CFG_TABLES_COUNT = CFG_TBL_COUNT_OUT;
				InitTables();
			}
		}
	}
	else
	{
		m_ErrCode = -2; // couldn't open "config.fmt" file
		return false;
	}
	yyin -> Close();	
	return ( result != 0) ? false : true;
}

#undef _INITIALIZED_
#undef _DELTA_
#undef _CTRL_
#undef _ADDITIONAL_FILES_


//-----------------------------------------------------------------------------
//!
//!     Auxiliary routine to check the checksum of format descriptor file
//!
//! \return
//!      bool - true if success, false otherwise
//!
//! \note
//!
#define BUF_LEN 1024

bool HyperwareConfig::InitControl() 
{
	unsigned long DescAdler32 = 1L;
	unsigned long OldDescAdler32 = 0L;
	unsigned int bytes;
	HypCFile file;
	bool read;
	uint8_t buffer[ BUF_LEN ];
	int c;

	// Calculate the checksum of description file
	if ( file.Open( GetDBDesc() ) )
	{
		for (;;)
		{
		   read = file.Read(buffer, BUF_LEN, bytes);
           DescAdler32 = UpdateAdler32(DescAdler32, buffer, bytes);
		   if ( !read || bytes != BUF_LEN )
		   {
			  break;
		   }
        }		
		file.Close();
	}
	else
	{
		m_ErrCode = -2; // couldn't open "config.fmt" file
		return false;
	}

	if ( file.Open( GetControlFile() ) )
	{

		// Read descriptor checksum
		for ( uint16_t i = 0; i < sizeof( unsigned long ); i++ )
		{
			if ( EOF == (c = file.Getc()) )
			{
				file.Close();
				return false;
			}
			OldDescAdler32 |= ((unsigned long)c) << (((sizeof( unsigned long ) - i) << 3) - 8);
		}

		file.Close();
	}
	
    if ( DescAdler32 != OldDescAdler32 )
	{
		HypCFile::Delete( GetDelta() );

#if defined(__GNUC__) || defined(__ARMCC_VERSION)
#define	MODE F_WRITE | F_READ     
		int size = HypCFile::FileSize( GetControlFile() );
		int FLAG = 0;
		if ( 0 < size )
		{
			FLAG = F_OPEN_EXISTING | F_SHARE_READ;
		}
		else
		{
			FLAG = F_CREATE | F_SHARE_READ;
		}
#else
#define	MODE F_WRITE       // This hack is needed,
#define	FLAG F_OPEN_ALWAYS // because flags of HypCFile_Win32 and 
#endif                     // flags of HypCFile_Win32 aren't compatible
		if ( file.Open( GetControlFile(), FLAG, MODE ) )
		{
			uint16_t i;

			for ( i = 0; i < sizeof( unsigned long ); i++ )
			{
				buffer[ i ] = ( uint8_t )(DescAdler32 >> (((sizeof( unsigned long ) - i) << 3) - 8));
			}

			file.Write( buffer, sizeof(unsigned long), bytes);

			if ( sizeof(unsigned long) != bytes )
			{
				file.Close();
				return false;
			}

			file.Close();
		}
	}
	return true;
}

#undef BUF_LEN

//-----------------------------------------------------------------------------
//!
//!     Update a running Adler-32 checksum with the bytes buf[0..len-1]
//!     and return the updated checksum. The Adler-32 checksum should be
//!     initialized to 1.
//!
//! \param
//!      adler - initialization value
//! \param
//!      buf   - buffer to compute checksum for
//! \param
//!      len   - buffer's length
//!
//! \return
//!      unsigned long  adler checksum of the buffer
//!
//! \note
//!      See RFC-1950
//!
#define BASE 65521 /* largest prime smaller than 65536 */

unsigned long HyperwareConfig::UpdateAdler32( unsigned long adler,
											  unsigned char *buf, 
											  int len )
{
	unsigned long s1 = adler & 0xffff;
    unsigned long s2 = ( adler >> 16 ) & 0xffff;
    int n;

    for (n = 0; n < len; n++) 
	{
       s1 = ( s1 + buf[n] ) % BASE;
       s2 = ( s2 + s1 )     % BASE;
    }

    return ( s2 << 16 ) + s1;
}

#undef BASE

//-----------------------------------------------------------------------------
//!
//!      Auxiliary routine to calculate the descriptor of 
//!      a parameter in delta.CFG
//!
//! \param
//!      table - 1 byte BCD - table ID
//! \param
//!      row   - 1 byte BCD - row ID (FF in case of terminal table, i.e. if 
//!              table == '01'
//! \param
//!      id    - 2 bytes BCD parameter's ID in m_Parameters. In the future 
//!              releases it can be replaced with parameter's name or name's 
//!              hash
//!
//! \return
//!      uint32_t  internal parameter's ID for delta.CFG
//!
//! \note
//!
uint32_t HyperwareConfig::CreateParamInternalDesc( uint32_t table, 
												   uint32_t row,
												   uint32_t id )
{
	uint32_t nRetVal = ( ( table << 24 ) | ( ( row & 0xff ) << 16 ) | ( id & 0xffff ) );
	return nRetVal;
}

//-----------------------------------------------------------------------------
//!
//!      Auxiliary routine to get the table id from parameter's internal 
//!      descriptor
//!
//! \param
//!      desc - 4 byte BCD - internal parameter's descriptor
//!
//! \return
//!      uint32_t  1 byte BCD - table ID
//!
//! \note
//!
uint32_t HyperwareConfig::GetTblFromParamInternalDesc( uint32_t desc )
{
	uint32_t nRetVal = ( desc >> 24 );
	return nRetVal;
}

//-----------------------------------------------------------------------------
//!
//!      Auxiliary routine to get the row id from parameter's internal 
//!      descriptor
//!
//! \param
//!      desc - 4 byte BCD - internal parameter's descriptor
//!
//! \return
//!      uint32_t  1 byte BCD - row ID ('FF' in case of terminal table '01')
//!
//! \note
//!
uint32_t HyperwareConfig::GetRowFromParamInternalDesc( uint32_t desc )
{
	uint32_t nRetVal = ( ( desc >> 16 ) & 0xff );
	return nRetVal;
}

//-----------------------------------------------------------------------------
//!
//!      Auxiliary routine to get the parameter id from parameter's internal 
//!      descriptor
//!
//! \param
//!      desc - 4 byte BCD - internal parameter's descriptor
//!
//! \return
//!      uint32_t  2 byte BCD - parameter ID
//!
//! \note
//!
uint32_t HyperwareConfig::GetIdFromParamInternalDesc( uint32_t desc )
{
	uint32_t nRetVal = ( desc & 0xffff );
	return nRetVal;
}

//-----------------------------------------------------------------------------
//!
//!      Auxiliary routine to get the parameter offset in the main CFG file
//!      using from parameter's internal descriptor
//!
//! \param
//!      desc - 4 byte BCD - internal parameter's descriptor
//!
//! \return
//!      HYP_CFG_HANDLE  offset of the parameter in the main CFG file
//!
//! \note
//!
HYP_CFG_HANDLE HyperwareConfig::GetParamOffsetFromParamInternalDesc( uint32_t desc ) 
{
	uint8_t table = GetTblFromParamInternalDesc( desc );
	uint8_t row   = GetRowFromParamInternalDesc( desc );
	uint32_t param = GetIdFromParamInternalDesc( desc );
	HYP_CFG_ROW_DESCRIPTOR * current = 0;

	table = CvtBin( table );
	param = CvtBin( ( param >> 8 ) & 0xff ) * 100 + CvtBin( param & 0xff );

	if ( CFG_TABLES_COUNT > table )
	{
		current = m_Tables[ table ].rows;

		while ( 0 != current )
		{
			if ( row == current->DBID )
			{
				return current->offset + m_Parameters[ param ].offset;
			}
			current = current -> next;
		}
	}
	return NOT_FOUND;
}

