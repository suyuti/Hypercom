//=============================================================================
//                         Hypercom Inc
// Product:
//      Hyperware Base Application
//      (c) Copyright 2006
//
// File Name:
//      HyperwareConfig.hpp
//
// File Description:
//      Declaration of the Class HyperwareConfig
//
//=============================================================================
#if !defined(_HYPERWAREAPPCONFIG_HPP_)
#define _HYPERWAREAPPCONFIG_HPP_

#include <compiler.h>
#include <HypCPOSConfig.hpp>
#include "MemFile.hpp"

//=============================================================================
// Public defines and typedefs
//=============================================================================

//! VISAII record common tags
struct VisaIITag
{
	static const char* TABLE;

	//! acquirer ID
	static const char* ACQUIRER_ID;

	//! acquirer bank number
	 static const char* ACQUIRER_BIN;

	 //! merchant number
	 static const char* MERCH_NUMBER;

	 //! store number
	 static const char* STORE_NUM;

	 //! terminal number
	 static const char* TERM_NUM;

	 //! merchant currency
	 static const char* MERCH_CURRENCY;

	 //! merchant country
	 static const char* MERCH_COUNTRY;

	 //! merchant city
	 static const char* MERCH_CITY;

	 //! time zone difference
	 static const char* TIME_ZONE_DIFF;

	 //! merchant category
	 static const char* MERCH_CAT;

	 //! merchant name
	 static const char* MERCH_NAME;

	 //! merchant city and state
	 static const char* MERCH_CITY_STATE;

	 //! agent's bank number
	 static const char* AGENT_BIN;

	 //! agent's chain number
	 static const char* AGENT_CHAIN_NUM;

	 //! merchant's location - first character
	 static const char* FIRST_CHAR_LOCATION;

	 //! merchant's location
	 static const char* MERCH_LOCATION;

	 //! terminal's serial number
	 static const char* TERMINAL_SERIAL_NUM;

	 enum VisaIIOptionBits
	 {
		 //! Default
		 _DEFAULT
	 };

};

//! Acquirer record common tags
struct AcquirerTag
{
	//! Tag for parameters reserved for future use
	static const char* ACQUIRER_TABLE;

	//! Tag for parameters reserved for future use
	static const char* ID;

	//! HypCString: Acquirer name
	static const char* NAME;

	//! HypCString: Acquirer NII
	static const char* NII;

	//! HypCString: Acquirer primary phone number
	static const char* PRI_PHONE;

	//! HypCWord: Acquirer primary dial attempts
	static const char* PRI_DIAL_ATTEMPTS;

	//! HypCWord: Acquirer primary connect timeout
	static const char* PRI_TIMEOUT;

	//! HypCString: Acquirer secondary phone number
	static const char* SEC_PHONE;

	//! HypCWord: Acquirer secondary dial attempts
	static const char* SEC_DIAL_ATTEMPTS;

	//! HypCWord: Acquirer secondary connect timeout
	static const char* SEC_TIMEOUT;

	//! HypCString: Acquirer terminal id
	static const char* TERMINAL_ID;

	//! HypCString: Acquirer acceptor id
	static const char* ACCEPTOR_ID;

	//! HypCString: Acquirer batch number
	static const char* BATCH_CURRENT;

	//! HypCString: Acquirer next batch number
	static const char* BATCH_NEXT;

	//! HypCOption: Acquirer options
	static const char* ACQUIRER_OPT1;

	//! HypCOption: Acquirer options
	static const char* ACQUIRER_OPT2;

	//! HypCOption: Acquirer options
	static const char* ACQUIRER_OPT3;

	//! HypCOption: Acquirer options
	static const char* ACQUIRER_OPT4;

	//! HypCQWord: Acquirer PIN key
	static const char* PIN_KEY;

	//! HypCQWord: Master key index
	static const char* MASTER_KEY_IDX;

	//! HypCQWord: Acquirer IP address
	static const char* ACQ_URL;

	//! HypCQWord: Acquirer IP port
	static const char* ACQ_PORT;

	//! HypCQWord: Acquirer IP address
	static const char* ACQ_SETTL_URL;

	//! HypCQWord: Acquirer IP port
	static const char* ACQ_SETTL_PORT;

	//! HypCWord: Acquirer secondary connect timeout
	static const char* ACQ_PRIM_SETTL_DIAL;

	//! HypCWord: Acquirer secondary connect timeout
	static const char* ACQ_SEC_SETTL_DIAL;

	//! HypCWord: Acquirer secondary dial attempts
	static const char* ACQ_SEC_SETTL_DIAL_ATTEMPTS;

	//! HypCWord: Acquirer secondary dial attempts
	static const char* ACQ_SEC_SETTL_CONN_TIME;

	//! HypCWord: Acquirer secondary dial attempts
	static const char* ACQ_PRIM_SETTL_CONN_TIME;

	//! HypCWord: Acquirer secondary dial attempts
	static const char* ACQ_PRIM_SETTL_DIAL_ATTEMPTS;

	//! HypCWord: Acquirer secondary dial attempts
	static const char* ACQ_MODEM_MODE;

	//! HypCWord: Acquirer secondary dial attempts
	static const char* ACQ_MODEM_MODE_SETTL;

	//! HypCString: Acquirer name
	static const char* PROGRAM_NAME;

	//! HypCString: Settlement protocol
	static const char* SETTLEMENT_PROTOCOL;

    //! HypCString: Acquirer HLAN CU Address
    static const char* ACQ_HLAN_ADDRESS;
};



//! Issuer record common tags
struct IssuerTag
{
	//! Tag for parameters reserved for future use
	static const char* ISSUER_TABLE;
       
	//! Tag for parameters reserved for future use
	static const char* ID;
   
	//! HypCString: Issuer card name
	static const char* NAME;
	
	//! HypCCurrency: Issuer floor limit
	static const char* FLOOR_LIMIT;
	
	//! HypCString: Issuer default account id
	static const char* DEFAULT_ACCOUNT_ID;
	
	//! HypCOption: Issuer options
	static const char* ISSUER_OPT1;
	
	//! HypCOption: Issuer options
	static const char* ISSUER_OPT2;

	//! HypCOption: Issuer options
	static const char* ISSUER_OPT3;

	//! HypCOption: Issuer options
	static const char* ISSUER_OPT4;

	//! HypCOption: Issuer options
	static const char* ISSUER_OPT5;

	//! HypCOption: Issuer options
	static const char* ISSUER_OPT6;
};



//! Card record common tags
struct CardTag 
{
	//! Tag for parameters reserved for future use
	static const char* CARD_TABLE;
    
	//! Tag for parameters reserved for future use
	static const char* CARDRESERVED;
    
	//! Acquirer ID
	static const char* ACQUIRER_ID;
		 
	//! Issuer ID
	static const char* ISSUER_ID;

	//! First ten digits (0000000000 - 9999999999)
	static const char* PAN_RANGE_HIGH;
		 
	//! First ten digits (0000000000 - 9999999999)
	static const char* PAN_RANGE_LOW;

    enum CardOptionBits 
	{
         //! Default
        _DEFAULT = 64
    };

};



//! Terminal configuration tags
struct TermConfigTag
{
	//! Tag for parameters reserved for future use
    static const char* TERMINAL_TABLE;
	
	//! HypCWord: Printer baud rate
	static const char* TCPRBAUD;
	
	//! HypCString: Telephone dial options
	static const char* TCDOPT;
	
	//! HypCString: Merchant password
	static const char* TCPWD;
	
	//! HypCString: Merchant name 1
	static const char* TCNAM1;
	
	//! HypCString: Merchant name 2
	static const char* TCNAM2;
	
	//! HypCString: Merchant name 3
	static const char* TCNAM3;
	
	//! HypCString: Currency leading symbol
	static const char* TCLEADC;
		
	//! HypCString: Local terminal options
	static const char* TCLOCOP;
	
	//! HypCString: Pinpad type
	static const char* TCPINPAD;
		
	//! HypCString: Maintenance password
	static const char* TCMPWD;
	
	//! HypCOptions: General terminal configuration options
	static const char* TERMINAL_OPT1;

	//! Added for backward compatibility only. Should be removed! UBriedis
	static const char* TERM_CONFIG_OPTIONS;
	
	//! HypCOptions: General terminal configuration options
	static const char* PAUSE_PRINTING_2_REC;
	
	//! HypCOptions: General terminal configuration options
	static const char* TERMINAL_OPT5;

	//! HypCOptions: General terminal configuration options
	static const char* TERMINAL_OPT6;
};

//! Security provider configuration tags
struct SecProvTag
{
	//! Tag for parameters reserved for future use
    static const char* SECPROV_TABLE;

    //! Security provider from SECPROV table
	static const char* SECURITY_PROVIDER;
};

struct Soru {
    static const char* SORU_TABLE_NAME;
    static const char* SORUID;
    static const char* SORUADI;
    static const char* SORU;
    static const char* CEVAPGENEL;
    static const char* CEVAP1;
    static const char* CEVAP2;
    static const char* CEVAP3;
    static const char* CEVAP4;
};


#define S_TRAPPEXP			3
#define S_TRATC				2
#define S_TRAC				8
#define S_TRISAPDAT			(1+32)
#define S_TRAIP				2
#define S_TRAUC				2
#define S_TRRAND			4
#define S_TRAPPVER			2
#define S_TRTAIDVER			2
#define S_TRTVR				5
#define S_TRISAC			(5+5+5)
#define S_TRAID				16
#define S_TREMVRSPC			2
#define S_TRISSSCRIPTRES	48
#define S_TRTSI				2
#define	S_TRCVMRESULTS		3

#define TAIDMAX		10
#define ICCMAX		8

//Application Capabilities
//first byte
#define APP_CAP1_CARDHOLDER_CONF 0x80    // Enable Transaction Log
#define APP_CAP1_MULTI_LANG      0x40    // Disable Exception file flag
#define APP_CAP1_PED_PRESENT     0x20    // Disable merch force online capability
#define APP_CAP1_PIN_BYPASS      0x10    // Disable merch force accept after fail capability
#define APP_CAP1_AMT_PIN_SAME    0x08    // Enable Transaction Log
//second byte
#define APP_CAP2_TXN_LOG         0x80    // Enable Transaction Log
#define APP_CAP2_EXC_FILE_TEST   0x40    // Disable Exception file flag
#define APP_CAP2_MERCH_SUSP      0x20    // Disable merch force online capability
#define APP_CAP2_EMV_FORCED      0x10    // Disable merch force accept after fail capability
//third byte
#define APP_CAP3_EMV_ADVICES     0x80    // Enable Transaction Log
#define APP_CAP3_ISS_REFER       0x40    // Disable Exception file flag
#define APP_CAP3_CARD_REFER      0x20    // Disable merch force online capability

//#include "./EMV/emv_common.h"
#include "HypCEMV.hpp"

struct ICC_Tag
{
	// table tag
	static const char* ICC_TABLE;
	static const char* ICC_TABLE_ID;
	static const char* ICC_TABLE_LENGTH;
	static const char* ICC_TABLE_NUMBER;
	static const char* ICC_ISS;
	static const char* ICC_TARG_PER_CENT;
	static const char* ICC_MAX_PER_CENT;
	static const char* ICC_TRESH;
	static const char* ICC_TAC_DEN;
	static const char* ICC_TAC_ONL;
	static const char* ICC_TAC_DEF;
};

struct TAIDTAB_Tag
{
	// table tag
	static const char* TAIDTAB_TABLE;
    static const char* TABLE_ID;
    static const char* TABLEID;
    static const char* ADTID;
    static const char* AID_LEN;
    static const char* ICCAID;
    static const char* TAIDTAB_OPT_1;
	static const char* TAIDVER1;
	static const char* TAIDVER2;
	static const char* TAIDVER3;
};

struct KEYDATA_Tag
{
	// table tag
	static const char* KEYDATA_TABLE;
};

struct REVKEY_Tag
{
	// table tag
	static const char* REVKEY_TABLE;
};

struct CA_KEYS_Tag
{
	// table tag
	static const char* CA_KEYS_TABLE;
};

struct ADDTAGS_Tag
{
	// table tag
	static const char* ADDTAGS_TABLE;
};

struct KEYEXPIRE_Tag
{
	// table tag
	static const char* KEYEXPIRE_TABLE;
};

struct EMVTerminalTag
{
	// table tag
	static const char* EMV_TABLE;

	// terminal type
	static const char* TERM_TYPE;
	
	// local currency code
	static const char* CUR_CODE;
	
	// country code
	static const char* COUNTRY_CODE;
	
	// terminal capabilities
	static const char* TERM_CAP;
	
	// additional terminal capabilities
	static const char* TERM_ADD_CAP;

	// application capabilities
	static const char* APP_CAPABILITIES;

	// transaction type
	static const char* TXNTYPE;
};

//! Some system wide data items
struct SystemDataTag
{
	//! System trace audit number
	static const char* SYSTEM_TABLE;

	//! System trace audit number
	static const char* SYSTEM_TRACE;

	//! Terminal invoice number
	static const char* INVOICE_NUMBER;

	//! will need other items - later
	//! dialing options ,etc - based on TERMREC struct in systruc.inc from SPOS/CPOS

};
        
//! ****ADDING NEW OPTION FOR HYPERWAREAPP, PLEASE ADD IT'S 
//! DESCRIPTION IN config.FMT FILE**** - ( IT SHOULD BE CHANGED
//! IN FUTURE VERSIONS )
//! TERM_CONFIG_OPTIONS option bits
enum
{
	TC1_REST,       // Restaurant processing
	TC1_CASHIER,    // Cashier entry on
	TC1_RECON,      // 0-enter, 1-confirm
	TC5_HSMENU,     // Do host select using menu where applic
	TC5_NOHSPRM,    // No host select prompt during settlemnt
	TC6_PINBYPASSPIN, // ALLOW PIN BYPASS (from pinpad)
	TC6_ICCEARLYAMT,  // EARLY AMOUNT ENTRY FOR ICC TXNS
	TC6_NOSECOND,   // Supress second receipt
    TCL_USE_RFID,     // Use internal RFID
    //! Ignore host time
	ACQ_IGNORE_HOST_TIME,
	//! use GPRS connection
	ACQ_USE_GPRS,
	//! Send batch no in 01x0 & 02x0 messages
	ACQ_SEND_BAT_NO,
	TCP_SMCARD,   // SMART CARD ENABLED
	//! Is expiry date entry required
	ISS_EXPIRATION_DATE_ALLOWED,
    //! Is roc number required (invoice number)
	ISS_ROC_NUMBER_REQUIRED,
    //! Capture card range
	ISS_CAPTURE_CARD_RANGE,
    //! Generate 6 digit auth for floor limit
	ISS_GENERATE_6_DIGIT_AUTH,
	//! This is a debit issuer
	ISS_DEBIT_ISSUER,
	//! Authorize if over floor limit
	ISS_AUTH_OVER_LIMIT,
	//! Allow address verification
	ISS_ADDRESS_VERIFICATION_ALLOWED,
    //! Cardholder mail address required
	ISS_MAIL_ADDRESS_REQUIRED,
	//! Cardholder zipcode required
	ISS_AVS_ZIPCODE_REQUIRED,
	//! Enable level ii cmrc./purch. card amount
	ISS_LEVEL2_AMOUNT_ENABLED,
	//! Enable level ii cmrc./purch. card p.o. number
	ISS_LEVEL2_PO_ENABLED,
};	


namespace HyperwareC11N {

//====================================================================
//
// Configuration data types
//
//====================================================================
#ifdef READONLY
#undef READONLY
#endif
#ifdef HIDDEN
#undef HIDDEN
#endif
#ifdef PWDPROTECTED
#undef PWDPROTECTED
#endif
#ifdef LABEL
#undef LABEL
#endif
#ifdef KEY
#undef KEY
#endif

enum {
	 PWDPROTECTED = 1,
	 READONLY     = 2,
	 HIDDEN       = 4,
	 LABEL        = 8,
	 KEY          = 16	 
	};

enum HypC11NType {
	 CFG_BCD_BYTE,
	 CFG_ALPHA_BYTE,
	 CFG_BITSET_BYTE,
	 CFG_DTBCD_BYTE,   // Date/Time in BCD
     CFG_VARALPHA,     // Variable length alpha HString
     CFG_APP_INT32,    // These types should
     CFG_APP_STRING,   // be returned to application
     CFG_APP_INT64,    //
     CFG_UNDEFINED     //
	};

typedef struct HYP_CFG_PARAMETER_DESCRIPTOR {

	HYP_CFG_PARAMETER_DESCRIPTOR()
	{
		table = 0;
		type = CFG_BCD_BYTE;
		appType = CFG_BCD_BYTE;
		offset = 0;
		length = 0;
		flags = 0;
		link = 0;
	}

	int table;
	HString paramName;
	HypC11NType type;    // Config DB type
	HypC11NType appType; // Application's type
	HYP_CFG_HANDLE offset;
	uint32_t length;
	int flags;
	int link;
} HYP_CFG_PARAMETER_DESCRIPTOR;

typedef struct HYP_CFG_OPTION_DESCRIPTOR {

	HYP_CFG_OPTION_DESCRIPTOR()
	{
		optionID = 0;
		paramID = 0;
		mask = 0;
		flags = 0;
	}

	//! Options might be stored in different parameters
	int optionID; // Since option tags are stored 
				   //! in enumerations it is int...
    int paramID; 
	uint8_t mask;
	int flags;
} HYP_CFG_OPTION_DESCRIPTOR;

struct HYP_CFG_TABLE_DESCRIPTOR; // Forward definition

typedef struct HYP_CFG_ROW_DESCRIPTOR {
	HYP_CFG_ID ID;
	uint32_t DBID;
	int length;
    HYP_CFG_HANDLE offset;
	struct HYP_CFG_ROW_DESCRIPTOR* next;   
	struct HYP_CFG_ROW_DESCRIPTOR* prev;   
	struct HYP_CFG_TABLE_DESCRIPTOR* table;
} HYP_CFG_ROW_DESCRIPTOR;

typedef struct HYP_CFG_TABLE_DESCRIPTOR {

	HYP_CFG_TABLE_DESCRIPTOR()
	{
		ID = 0;
		data_length = 0;
		offset = 0;
		rows = 0;
		rows_count = 0;
		flags = 0;
	}

    HString Name;
	HYP_CFG_ID ID;
	int data_length;
    HYP_CFG_HANDLE offset;
	HYP_CFG_ROW_DESCRIPTOR* rows;  // Table entries offsets 
	int rows_count;
	int flags;
} HYP_CFG_TABLE_DESCRIPTOR;

};

//=============================================================================
// Forward definitions
//=============================================================================

using namespace HyperwareC11N;

class MetaInformation {
public:
	HYP_CFG_PARAMETER_DESCRIPTOR * Parameters;
	HYP_CFG_OPTION_DESCRIPTOR * Options;
	HYP_CFG_TABLE_DESCRIPTOR * Tables;
	int ParametersCount;
	int OptionsCount;
	int TablesCount;
};

//=============================================================================
//!
//! \brief
//!      Read TM database and keeps configuration parameters for application.
//!
//!      POS configuration tables are stored in this document. Initial data
//!      comes from the TermMaster configuration file; out of the parsing process
//!      we get the tables that define POS behavior
//!
//! \sa
//!      HypCDocument, HypCDocumentManager, HypCPOSConfig
//!
//=============================================================================
class HyperwareConfig : public HypCPOSConfig
{
//=============================================================================
// Typedefs
//=============================================================================
    private:
		enum DescType {  // Types for GetCfgDescriptor function
			TABLE,
			ROW,
			PARAM
		};

		typedef struct HYP_CFG_DELTA_ITEM_DESCRIPTOR {
			HYP_CFG_HANDLE internal_descriptor;
			HYP_CFG_HANDLE delta_offset;
			struct HYP_CFG_DELTA_ITEM_DESCRIPTOR* next;
			struct HYP_CFG_DELTA_ITEM_DESCRIPTOR* prev;
		} HYP_CFG_DELTA_ITEM_DESCRIPTOR;

		typedef struct CFG_OPT_MAPPING
		{
			int OptionCode;
			char * OptionName;
		} CFG_OPT_MAPPING;

//=============================================================================
// Member functions
//=============================================================================
	public:

		HyperwareConfig();

		virtual ~HyperwareConfig();

		//! Initializes the object of the class
		virtual bool Init();
		
        //! Gets handle to the configuration table by table name 
		virtual HYP_CFG_HANDLE GetTable(const HString& tableName);

        //! Gets handle to the configuration table by table ID 
		virtual HYP_CFG_HANDLE GetTable(const HYP_CFG_ID tableID);

		//! Gets handle to the row by row number
		//! There are predefined row numbers LAST, NEXT, PREV, FIRST, NO_DATA_FOUND.
		virtual HYP_CFG_HANDLE GetTableRow(HYP_CFG_HANDLE table, HYP_CFG_ID rowID);

		//! Looks for the particular row using parameter value as a key
		virtual HYP_CFG_HANDLE FindTableRow(HYP_CFG_HANDLE table, const char * searchParam, const HypCData& searchValue);

		//! Gets configuration parameter's value
		virtual HString GetParam(const HYP_CFG_HANDLE row, const char * paramName);

                // Gets entire row
		virtual bool GetRawRow( const HYP_CFG_HANDLE row, void* buff );

		//! Checks an option
		virtual bool IsOptionSet(const HYP_CFG_HANDLE row, int optionBit);

		//! Sets configuration parameter's value
		virtual void SetParam(const HYP_CFG_HANDLE row, const char * paramName, const HypCData& value);

		//! Sets an option
		virtual void SetOption(const HYP_CFG_HANDLE row, int optionBit, bool option);

		//! Sets the name of the delta file
		inline void SetDelta(const char *deltaFileName);

		//! Returns the name of the delta file
		inline const char *GetDelta() const;

		//! Sets the name of database descriptor file
		inline void SetDBDesc(const char *descFileName);

		//! Returns the name of database descriptor file
		inline const char *GetDBDesc() const;

		//! Sets the name of database checksum file
		inline void SetControlFile(const char *ctrlFileName);

		//! Returns the name of databse checksum file
		inline const char *GetControlFile() const;

		//! Returns pointers to the configuration metadata
		inline MetaInformation GetMetaInformation();

		//! Returns error code
		inline int GetErrCode();

		//! Returns option code by option's name
		static int GetOptionCode( const HString& name );

		//! Returns option name by option's code
		static HString GetOptionName( int code );


	protected:
	

	private:
		//! Avoid copying this object by mistake:
		//! declare as private, do not provide implementation
		HyperwareConfig ( const HyperwareConfig& rhs );
		HyperwareConfig& operator=( const HyperwareConfig& rhs );

		//! Returns position of parameter descriptor in global descriptor table
		uint32_t GetDescriptor( HYP_CFG_HANDLE globalOffset, DescType type ); 

		//! Clears delta file and related data
		void ClearDelta( bool deleteFile = true );

		//! Gets parameter from the file
		HString GetParamFromFile(HypCFile * file, const uint32_t length, const HypC11NType type, const HypC11NType appType);

		//! Writes parameter to the file
		bool WriteParamToFile(HypCFile * file, const uint32_t length, const HypCData* value, const HypC11NType type);

		//! Auxiliary routine for reading bytes from opened file
		bool ReadBytes( HypCFile* file, int n, uint8_t* buf);

		//! Auxiliary routine for checking if BCD date is valid
		bool CheckBCDDate(uint8_t* bcd, int n);

		//! Auxiliary routine to initialize System Parameters table
		bool InitSysParams(int offset);

		//! Auxiliary routine to check the CFG checksum (Adler-32)
		bool InitControl();

        //! Auxiliary routine to calculate the checksum (RFC-1950)
		unsigned long UpdateAdler32( unsigned long adler,
									 unsigned char *buf, 
									 int len);

		//! Auxiliary routine to calculate the descriptor of 
		//! a parameter in delta.CFG
		static uint32_t CreateParamInternalDesc( uint32_t table, 
												 uint32_t row,
												 uint32_t id );

		//! Auxiliary routine to get the table id from parameter's internal 
		//! descriptor
		static uint32_t GetTblFromParamInternalDesc( uint32_t desc );

		//! Auxiliary routine to get the row id from parameter's internal 
		//! descriptor
		static uint32_t GetRowFromParamInternalDesc( uint32_t desc );

		//! Auxiliary routine to get the parameter id from parameter's internal 
		//! descriptor
		static uint32_t GetIdFromParamInternalDesc( uint32_t desc );

		//! Auxiliary routine to get the parameter offset in the main CFG filre
		//! using from parameter's internal descriptor
		HYP_CFG_HANDLE GetParamOffsetFromParamInternalDesc( uint32_t desc );

		//! Invokes descriptor file parser
		bool InvokeParser();

		//! Initializes tables index
		void InitTables();


//=============================================================================
// Member variables
//==========================================
	private:
        //! Name of the delta file
        HString m_CfgDelta;

        //! Name of the delta file
        HString m_CfgDesc;

        //! Name of the CFG checksum file
        HString m_CfgCtrl;

        //! Array of parameters descriptors
		HYP_CFG_PARAMETER_DESCRIPTOR * m_Parameters;

        //! Array of options descriptors
		HYP_CFG_OPTION_DESCRIPTOR * m_Options;

		//! Index (table/rows-level) of CFG file
		HYP_CFG_TABLE_DESCRIPTOR * m_Tables;

		//! Index of the delta file
		HYP_CFG_DELTA_ITEM_DESCRIPTOR * m_Delta;

		//! ID of the table which contains system's parameters
		int CFG_SYS_PARAMS;

		//! Number of tables
		int CFG_TABLES_COUNT;

		//! Number of tables
		int CFG_PARAMETERS_COUNT;

		//! Number of tables
		int CFG_OPTIONS_COUNT;

		//! Flag which indicates if object is properly initialized
        bool m_Initialized;

		//! Mapping table: HypTransactionTags option codes <-> 
		//!                config.FMT option names
		static const CFG_OPT_MAPPING m_OptionsMapping[];

		//! Memory file used to contain all TM data
		MemFile memFile;

		//! Error code for after initialization
		int m_ErrCode;

};
// HyperwareConfig

//-----------------------------------------------------------------------------
//!
//!      Set's delta file
//!
//! \param
//!      deltaFileName	delta file name
//!
//! \return
//!      void
//!
//! \note
//!		
inline void HyperwareConfig::SetDelta(const char *deltaFileName) 
{
	m_CfgDelta = deltaFileName;
}


//-----------------------------------------------------------------------------
//!
//!      Get's delta file name
//!
//! \return
//!      HString	Delta file name
//!
//! \note
//!		
inline const char *HyperwareConfig::GetDelta() const
{
	return m_CfgDelta.c_str();
}

//-----------------------------------------------------------------------------
//!
//!      Set's database descriptor file
//!
//! \param
//!      descFileName	descriptor file name
//!
//! \return
//!      void
//!
//! \note
//!		
inline void HyperwareConfig::SetDBDesc(const char *descFileName) 
{
	m_CfgDesc = descFileName;
}


//-----------------------------------------------------------------------------
//!
//!      Get's database descriptor file name
//!
//! \return
//!      HString	Descriptor file name
//!
//! \note
//!		
inline const char * HyperwareConfig::GetDBDesc() const
{
	return m_CfgDesc.c_str();
}

//-----------------------------------------------------------------------------
//!
//!      Sets the file were the application
//!      will store CFG control info: checksums, etc...
//!
//! \param
//!      ctrlFileName	control file name
//!
//! \return
//!      void
//!
//! \note
//!		
inline void HyperwareConfig::SetControlFile(const char *ctrlFileName) 
{
	m_CfgCtrl = ctrlFileName;
}


//-----------------------------------------------------------------------------
//!
//!      Gets database control file name
//!
//! \return
//!      HString	Control file name
//!
//! \note
//!		
inline const char *HyperwareConfig::GetControlFile() const
{
	return m_CfgCtrl.c_str();
}

//-----------------------------------------------------------------------------
//!
//!      Returns pointers to the configuration metadata
//!
//! \return
//!      MetaInformation  - collection of pointers
//!
//! \note
//!		
inline MetaInformation HyperwareConfig::GetMetaInformation()
{
	MetaInformation result;
	result.Options = m_Options;
	result.Parameters = m_Parameters;
	result.Tables = m_Tables;
	result.OptionsCount = CFG_OPTIONS_COUNT;
	result.ParametersCount = CFG_PARAMETERS_COUNT;
	result.TablesCount = CFG_TABLES_COUNT;
	return result;
}

//-----------------------------------------------------------------------------
//!
//!      Returns error code for problems during initialization
//!
//! \return
//!      int - code: 0  - no problems
//!					 -1 - "application.cfg" not found,
//!					 -2 - "config.fmt" not found,  
//!
//! \note
//!		
inline int HyperwareConfig::GetErrCode()
{
	return m_ErrCode;
}

#endif // !defined(_HYPERWAREAPPCONFIG_HPP_)

