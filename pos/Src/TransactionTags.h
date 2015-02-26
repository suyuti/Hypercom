//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hyperware Base Application
//      (c) Copyright 2006
//
// File Name:
//      TransactionTags.h
//
// File Contents:
//      String tags and options stored in the transaxction record used 
//      by Hyperware
//
//=============================================================================
#if !defined( _TRANSACTIONTAGS_H_ )
#define _TRANSACTIONTAGS_H_

//=============================================================================
// Public defines and typedefs
//=============================================================================

//! Contains pointers to text labels of transaction data
struct TransactionTag
{
    //HypCString
    static const char* SECILEN_ANKET;
    // HypCString 
    static const char* ISIM;

	//! HypCString: Transaction key ( identifier )
	static const char* KEY;

	//! HypCString: Transaction type name 
	static const char* TYPE_NAME;

	//! HypCCurrency: Base transaction amount
	static const char* BASE_AMOUNT;

	//! HypCCurrency: Total transaction amount
	static const char* TOTAL_AMOUNT;

	//! HypCCurrency: Total tip amount or any additional amounts
	static const char* TIP_AMOUNT;

	//! HypCString: NII for transaction 
	static const char* NII;

	//! HypCString: Terminal ID for transaction
	static const char* TERMINAL_ID;

	//! HypCString: Processing Code 
	static const char* PROCESSING_CODE;

	//! HypCString: Systems Trace Audit Number
	static const char* STAN;

	//! HypCPAN: PAN
	static const char* PAN;

	//! HypCString: Track 1 data
	static const char* TRACK1;

	//! HypCString: Track 2 data
	static const char* TRACK2;

	//! HypCString: Track 3 data
	static const char* TRACK3;

	//! HypCString: Card Holder Name
	static const char* HOLDER_NAME;

	//! HypCString: Account Id
	static const char* ACCOUNT_ID;

	//! HypCString: Issuer name
	static const char* ISSUER_NAME;

	//! HypCString: Acquirer name
	static const char* ACQUIRER_NAME;

	//! HypCDateTime: Expiration date
	static const char* EXPIRATION_DATE;

	//! HypCDateTime: Application expiration date
	static const char* APP_EXPIRATION_DATE;

	//! HypCDateTime: Time&Date of transaction
	static const char* DATE_TIME;

	//! HypCString: POS Entry mode
	static const char* POS_ENTRY_MODE;

	//! HypCString: POS Condition Code
	static const char* POS_CONDITION_CODE;

	//! HypCString: Retrieval reference number
	static const char* RETRIEVAL_REF_NUM;

	//! HypCString: Auth ID Response ( appoval code )
	static const char* AUTH_ID;

	//! HypCString: Card Acceptor Id ( acquirer id )
	static const char* CARD_ACCEPTOR_ID;

	//! HypCString: Card Acceptor Name( acquirer name )
	static const char* CARD_ACCEPTOR_NAME;

	//! HypCString: Invoice number
	static const char* INVOICE;

	//! HypCString: Invoice number
	static const char* TRACE_NUMBER;

	//! HypCString: Response code        
	static const char* ISO_RESPONSE_CODE;

	//! HypCString: Response text        
	static const char* RESPONSE_TEXT;

	//! HypCString: Additional response data        
	static const char* ADDITIONAL_RESPONSE_DATA;

	//! HypCString: Additional private data        
	static const char* ADDITIONAL_PRIVATE_DATA;

	//! HypCBlob: Pin block ( 8 bytes )
	static const char* PIN_BLOCK;

	//! HypCOptions: Transaction status flags
	static const char* STATUS_FLAGS;

	// HypCString: service code
	static const char* SERVICE_CODE;

	// HypCString: program name
	static const char* PROGRAM_NAME;

	// HypCString: PAN sequence number
	static const char* PAN_SEQ_NUM;

	// HypCString: Application usage control
	static const char* APP_USAGE_CTRL;

	// HypCString: AIP
	static const char* AIP;

	// HypCString: AID
	static const char* AID;

	// HypCString: Application version
	static const char* APP_VERSION;

	// HypCString: Issuer action codes
	static const char* ISS_ACTION;

	// HypCString: Unpredictable number
	static const char* RAND;

	// HypCString: Merchant online flag
	static const char* MERCH_ONLINE;

	// HypCString: Terminal action code by default
	static const char* TACDEF;

	// transaction status information
	static const char* TRTSI;

	// cryptogram information data
	static const char* TRCRYPTINFO;

	// cryptogram information data
	static const char* TRATC;

	// application cryptogram
	static const char* TRAC;

	// issuer application data
	static const char* TRISAPDAT;

	// terminal verification results
	static const char* TRTVR;

	// CVM results
	static const char* TRCVMRESULTS;

	// Terminal Application Version Number
	static const char* TRTAIDVER;


	static const char* TAIDVER1;
	static const char* TAIDVER2;
	static const char* TAIDVER3;

	// Response Code
	static const char* TRRSPC;

	// Application capabilities
	static const char* APP_CAPABILITIES;

	// Currency code
	static const char* CUR_CODE;

	// Country code
	static const char* COUNTRY_CODE;

	// Terminal capabilities
	static const char* TERM_CAP;

	// Selected EMV application
	static const char* ICCAID;

	// Issuer script buffer
	static const char* ISS_SCRIPT_BUF;

	//! Transaction STATUS_FLAGS option bits
	enum
	{
		//! Host settled
		HOST_SETTLED,	
		//! Tip entered
		TIP_ENTERED,
		//! Need to send advice to host
		SEND_ADVICE,
		//! This is a reversal
		REVERSAL,
		//! Transaction voided
		VOIDED,
		//! Transaction adjusted
		ADJUSTED,
		//! Training mode transaction
		TRAINING_MODE,
		//! AVS failed and transaction not captured
		AVS_FAILED,
		//! Debit transaction selected
		DEBIT_KEY_PRESSED,
		//! EBT transaction selected
		EBT_KEY_PRESSED,
		//! 1;
		EBTFOOD,
		//! Credit or EBT has been selected. Use this flag
		CREDIT_EBT_SELECTED,
		//! Electronic receipt sent to sig cap host						
		ERC_SENT,

		//! determines whether to print just a copy of the transaction 
		SF_REPRINT,
		//! determines whether is needed to save transaction in a journal
		STORE_NEEDED
	};	

	//! HypCBlob: Message Auth Code ( 8 bytes )
	static const char* MESSAGE_AUTH_CODE;

	//! HypCString: Security Control Info
	static const char* SECURITY_CONTROL_INFO;

	//! HypCString: Private Field Bit 60
	static const char* PRIVATE_FIELD_BIT60;

	//! HypCString: Private Field Bit 61
	static const char* PRIVATE_FIELD_BIT61;

	//! HypCString: Private Field Bit 62
	static const char* PRIVATE_FIELD_BIT62;

	//! HypCString: Private Field Bit 63
	static const char* PRIVATE_FIELD_BIT63;

	//! HypCOptions: Transaction attributes
	static const char* TRANSACTION_ATTRIBUTES;

	//! Private field Bit60 fields

	//! HypCString, Batch number, an 6
	static const char* BATCH_NUMBER;

	//! HypCString, Original message type, an 4
	static const char* ORIGINAL_MSG_TYPE;

	//! HypCString, Original STAN, an 6
	static const char* ORIGINAL_STAN;

	//! HypCString, Original amount, an 12
	static const char* ORIGINAL_AMOUNT;

	//! Private field Bit63 fields

	//! HypCString: (10), Cashier number, ans 4
	static const char* CASHIER;

	//! HypCString: (10), Till number, ans 4
	static const char* TILLNO;

	//! HypCString: (15), Level II comercial card indicator, an 1
	static const char* LVL2_INDICATOR;

	//! HypCString: (16), Card verification value II indicator, an 1
	static const char* CVV2_INDICATOR;

	//! HypCString: (16), Card verification value II request response code, an 1
	//! Indicates response required from host
	static const char* CVV2_RESPONSE_CODE;

	//! HypCString: (16), Card verification value II data, an 4
	static const char* CVV2_DATA;

	//! HypCString: (16), Card verification value II result code, an 1
	static const char* CVV2_RESULT_CODE;

	//! HypCString: (20), Payment services 2000 indicator, ans 1
	//! Generated by acquirer
	static const char* PS2000_INDICATOR;

	//! HypCString: (20), Transaction ID, ans 15
	//! Genereated by VISA 
	static const char* TRANSACTION_IDENTIFIER;

	//! HypCString: (20), Validation code, ans 4
	//! Genereated by VISA 
	static const char* VALIDATION_CODE;

	//! HypCString: (20), VISA II Response code, ans 2
	static const char* VISA2_RESPONSE_CODE;

	//! HypCString: (20), VISA II Pos Entry Mode, ans 2
	static const char* VISA2_POS_ENTRY;

	//! HypCCurrency: (21), Authorised amount, an 12
	static const char* AUTHORISED_AMOUNT;

	//! HypCString: (22), Alternate host response, an 40
	static const char* ALT_HOST_RESPONSE;

	//! HypCString: (29), Additional host print data, ans ..x
	static const char* HOST_PRINT_DATA;

	//! HypCString: (31), Host Reference data, ans ..50
	static const char* HOST_REF_DATA;

	//! HypCString: (33), Key serial number for DUK/PT encryption, ans 20
	static const char* KEY_SN;

	//! HypCString: (35), Additional prompt data
	static const char* ADDITIONAL_PROMPT;

	//! HypCCurrency: (39), Tax Amount #1, ans 12
	static const char* TAX_AMOUNT1;

	//! HypCCurrency: (40), Tax Amount #2, ans 12
	static const char* TAX_AMOUNT2;

	//! HypCCurrency: (41), CashBack Amount, ans 12
	static const char* CASHBACK_AMOUNT;

	//! HypCCurrency: (44), Surcharge Amount, ans 12
	static const char* SURCHARGE_AMOUNT;

	//! HypCString: (47), EBT specific, Clerk ID, ans 10
	static const char* EBT_CLERK_ID;

	//! HypCString: (47), EBT specific, Supervisor ID, ans 10
	static const char* EBT_SUPERVISOR_ID;

	//! HypCString: (47), EBT specific, Voucher number, ans 15
	static const char* EBT_VOUCHER_NUMBER;

	//! HypCString: (47), EBT specific, Generation number, ans 6
	static const char* EBT_GENERATION_NUMBER;

	//! HypCCurrency: (53), Miscellaneous amount, an 12
	static const char* MISC_AMOUNT;

	//! HypCString: (54), Address verification zip code, an 9
	static const char* AVS_ZIP;

	//! HypCString: (54), Address verification address, an 20
	static const char* AVS_ADDRESS;

	//! HypCString: (55), Address verification response code, an 3
	static const char* AVS_RESPONSE;

	//! HypCString: (73), Level II comercial card data
	//! Optional amount ID, an 1
	static const char* LVL2_OPT_AMOUNT_ID;

	//! HypCCurrency: (73), LVL2, Optional amount, an 12
	static const char* LVL2_OPT_AMOUNT;

	//! HypCString: (73), LVL2, Purchase order number, an 17
	static const char* LVL2_PO_NUMBER;

	//! HypCString: Authorization Characteristics Indicator
	static const char* ACI;

	//! HypCString: Authorization source code
	static const char* AUTH_SRC;

	//! HypCDateTime: last settlement attempt 
	static const char* LAST_SETL_ATT;

	//! HypCDateTime: last settlement successful attempt 
	static const char* LAST_SETL_SUCC;

	//! HypCInt64: number of reversals
	static const char* REV_COUNT;

	//! HypCInt64: number of adjusts
	static const char* ADJ_COUNT;

	//! HypCInt64: number of offlines
	static const char* ADV_COUNT;

	//! HypCString: Settle flag
	static const char* SETTLE_TYPE;

	//! HypCString: Settlement type: CLBATCH
	static const char* SETTLE_CLBATCH;

	//! HypCString: Settlement type: CLBATCHA
	static const char* SETTLE_CLBATCHA;

	//! HypCString: Settlement type: CLTERM
	static const char* SETTLE_CLTERM;

	//! HypCString: Settlement type: RUPLOAD
	static const char* SETTLE_RUPLOAD;

	//! HypCString: Settlement type: CLBATCHE
	static const char* SETTLE_CLBATCHE;

	//! Transaction attributes
	enum
	{
			//! No tip amounts	
			NOTIP,         
			//! No account required in proc code
			NOACCT,
			//! No receipt required
			NORECEIPT,
			//! No capture required			
			NOCAPTURE,
			//! No system time update
			NOTIME,
			//! Credit-type transaction
			CREDIT,
			//! Send all advices prior
			PREADV,
			//! Send a single advice after
			POSTADV,
			//! Settle type transaction			
			SETTLE,
			//! No reversal prior
			NOPREREV,
			//! Transaction is offline entered
			OFFLINE,
			//! Floor limts allowed
			FLOOR,
			//! No input for next event
			NOINPUT,
			//! Show transaction complete after trans
			COMPLETE,
			//! Referral allowed
			REFER,
			//! Reprint allowed (if receipt disallowed)
			REPRINT,
			//! Set batch pending for this tran
			BATPEND,
			//! No issuer name in tranbuf
			NOISNAME,
			//! Use chk service acquirer/issuer
			CHK_IS_AQ,
			//! Check batpend
			CHK_PEND,
			//! Show transaction accepted after trans
			ACCEPTED,
			//! Ignore init required flag
			NO_INIT,
			//! Reversal required for this trans
			REV,
			//! Use terminal parameters for dialing
			TERMPARAM,
			//! Check to reset pinpad
			PINRES,
			//! Check expiry date
			CHKEXPD,
			//! Do not clear hidden batch
			NOCLRBAT,
			//! Do not upload (320) at settle
			NOUPLOAD,
			//! Ebt card transaction
			EBTCARD,
			//! Debit card transaction
			DEBCARD,
			//! No response display on pinpad
			NOPINDSP,
			//! A refund transaction
			REFUND_TYPE,
        #ifdef MAKE_EMV
			//! EMV transaction
			EMV_TYPE
        #endif
		};


	static const char* JOURNAL_NAME;

	//! HypCInt64: number of sales
	static const char* SALES_COUNT;

	//! HypCInt64: number of debit sales
	static const char* SALES_DEB_COUNT;

	//! HypCInt64: sales amount
	static const char* SALES_AMOUNT;
	
	//! HypCInt64: debit sales amount
	static const char* SALES_DEB_AMOUNT;
	
	//! HypCInt64: number of sales
	static const char* REFUNDS_COUNT;
	
	//! HypCInt64: number of debit sales
	static const char* REFUNDS_DEB_COUNT;
	
	//! HypCInt64: sales amount
	static const char* REFUNDS_AMOUNT;
	
	//! HypCInt64: debit sales amount
	static const char* REFUNDS_DEB_AMOUNT;

	//! to signal that only one journal is present in the system
	static const char* ONE_JOURNAL;
};

#endif // #if !defined( _TRANSACTIONTAGS_H_ )


