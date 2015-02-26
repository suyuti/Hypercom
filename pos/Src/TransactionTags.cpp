//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hypercom Foundation Classes
//      (c) Copyright 2006
//
// File Name:
//      TransactionTags.cpp
//
// File Contents:
//      Initialization of tags used by Hyperware
//
//=============================================================================
#if defined(__GNUC__)  // GNU compiler
#pragma implementation
#endif

#include <HypCISO8583_Transaction.hpp>
#include "TransactionTags.h"

//=============================================================================
//  Transaction record common tags
//=============================================================================

const char* TransactionTag::SECILEN_ANKET       = "SECILENANKET";
const char* TransactionTag::ISIM                = "ISIM";

const char* TransactionTag::KEY 				= "TR KEY";
	
// HypCString: Transaction type name 
const char* TransactionTag::TYPE_NAME			= "TR NAME";

// HypCCurrency: Base transaction amount
const char* TransactionTag::BASE_AMOUNT			= ISO8583_BASE_AMOUNT;  

// HypCCurrency: Total transaction amount
const char* TransactionTag::TOTAL_AMOUNT		= "TR TOTAL AMT";  

// HypCCurrency: Total tip amount or any additional amounts
const char* TransactionTag::TIP_AMOUNT          = ISO8583_ADDITIONAL_AMOUNTS;

// HypCString: NII for transaction 
const char* TransactionTag::NII      			= ISO8583_NII;

// HypCString: Terminal ID for transaction
const char* TransactionTag::TERMINAL_ID         = ISO8583_TERMINAL_ID;

// HypCString: Processing Code 
const char* TransactionTag::PROCESSING_CODE     = ISO8583_PROCESSING_CODE;

// HypCString: Systems Trace Audit Number
const char* TransactionTag::STAN                = ISO8583_STAN;

// HypCPAN: PAN
const char* TransactionTag::PAN                 = IS08583_PAN;

// HypCString: Track 1 data
const char* TransactionTag::TRACK1            = ISO8583_TRACK1;

// HypCString: Track 2 data
const char* TransactionTag::TRACK2            = ISO8583_TRACK2;

// HypCString: Card Holder Name
const char* TransactionTag::HOLDER_NAME       = "TR CHOLDER NAME";

// HypCString: Account Id
const char* TransactionTag::ACCOUNT_ID        = "TR ACCT ID";

// HypCString: Issuer name
const char* TransactionTag::ISSUER_NAME       = "TR ISSUER NAME";

// HypCString: Acquirer name
const char* TransactionTag::ACQUIRER_NAME     = "TR ACQUIRER NAME";

// HypCDateTime: Expiration date
const char* TransactionTag::EXPIRATION_DATE   = ISO8583_EXPIRATION_DATE;

// HypCDateTime: Application expiration date
const char* TransactionTag::APP_EXPIRATION_DATE = "APP_EXPIRATION_DATE";

// HypCDateTime: Time&Date of transaction
const char* TransactionTag::DATE_TIME         = ISO8583_DATE_TIME;

// HypCString: POS Entry mode
const char* TransactionTag::POS_ENTRY_MODE    = ISO8583_POS_ENTRY_MODE;

// HypCString: POS Condition Code
const char* TransactionTag::POS_CONDITION_CODE = ISO8583_POS_CONDITION_CODE;

// HypCString: Retrieval reference number
const char* TransactionTag::RETRIEVAL_REF_NUM = ISO8583_RETRIEVAL_REF_NUM;

// HypCString: Auth ID Response ( appoval code )
const char* TransactionTag::AUTH_ID			  = ISO8583_AUTH_ID;

// HypCString: Card Acceptor Id ( acquirer id )
const char* TransactionTag::CARD_ACCEPTOR_ID  = ISO8583_CARD_ACCEPTOR_ID;

// HypCString: Card Acceptor Name( acquirer name )
const char* TransactionTag::CARD_ACCEPTOR_NAME = ISO8583_CARD_ACCEPTOR_NAME;

// HypCDateTime: last settlement attempt 
const char* TransactionTag::LAST_SETL_ATT		= "LAST_SETL_ATT";

// HypCDateTime: last settlement successful attempt 
const char* TransactionTag::LAST_SETL_SUCC	= "LAST_SETL_SUCC";

// HypCInt64: number of reversals
const char* TransactionTag::REV_COUNT			= "REV_COUNT";

// HypCInt64: number of adjusts
const char* TransactionTag::ADJ_COUNT			= "ADJ_COUNT";

// HypCInt64: number of offlines
const char* TransactionTag::ADV_COUNT			= "OFF_COUNT";

// HypCString: Invoice number
const char* TransactionTag::INVOICE			= "TR INVOICE";

// HypCString: Invoice number
const char* TransactionTag::TRACE_NUMBER		= "TR TRACE NUMBER";

// HypCString: Response code        
const char* TransactionTag::ISO_RESPONSE_CODE	= ISO8583_ISO_RESPONSE_CODE;

// HypCString: Response text        
const char* TransactionTag::RESPONSE_TEXT		= "TR RESP TEXT";

// HypCString: Additional response data     
const char* TransactionTag::ADDITIONAL_RESPONSE_DATA = ISO8583_ADDITIONAL_RESPONSE_DATA; 

// HypCString: Additional private data      
const char* TransactionTag::ADDITIONAL_PRIVATE_DATA  = ISO8583_ADDITIONAL_PRIVATE_DATA;

// HypCBlob: Pin block ( 8 bytes )
const char* TransactionTag::PIN_BLOCK         = ISO8583_PIN_BLOCK;

// HypCOptions: Transaction status flags
const char* TransactionTag::STATUS_FLAGS      = "TR STATUS";

// HypCString: service code
const char* TransactionTag::SERVICE_CODE	  = "SERVICE CODE";

// HypCString: program name
const char* TransactionTag::PROGRAM_NAME	  = "PROGRAM_NAME";

// HypCString: PAN sequence number
const char* TransactionTag::PAN_SEQ_NUM		  = "PAN_SEQ_NUM";

// HypCString: Application usage control
const char* TransactionTag::APP_USAGE_CTRL 	  = "APP_USAGE_CTRL";

// HypCString: AIP
const char* TransactionTag::AIP				  = "AIP";

// HypCString: AID
const char* TransactionTag::AID				  = "AID";

// HypCString: Application version
const char* TransactionTag::APP_VERSION		  = "APP_VERSION";

// HypCString: Issuer action codes
const char* TransactionTag::ISS_ACTION		  = "ISS_ACTION";

// HypCString: Unpredictable number
const char* TransactionTag::RAND			  = "RAND";

// HypCString: Merchant online flag
const char* TransactionTag::MERCH_ONLINE					  = "MERCH_ONLINE";

// HypCString: Terminal action code by default
const char* TransactionTag::TACDEF							  = "TACDEF";

// transaction status information
const char* TransactionTag::TRTSI							  = "TRTSI";

// cryptogram information data
const char* TransactionTag::TRCRYPTINFO						  = "TRCRYPTINFO";

// cryptogram information data
const char* TransactionTag::TRATC							  = "TRATC";

// application cryptogram
const char* TransactionTag::TRAC							  = "TRAC";

// issuer application data
const char* TransactionTag::TRISAPDAT						  = "TRISAPDAT";

// terminal verification results
const char* TransactionTag::TRTVR							  = "TRTVR";

// CVM results
const char* TransactionTag::TRCVMRESULTS					  = "TRCVMRESULTS";

// Terminal Application Version Number
const char* TransactionTag::TRTAIDVER						  = "TRTAIDVER";

const char* TransactionTag::TAIDVER1						  = "TAIDVER1";
const char* TransactionTag::TAIDVER2						  = "TAIDVER2";
const char* TransactionTag::TAIDVER3						  = "TAIDVER3";

// Response Code
const char* TransactionTag::TRRSPC							  = "TRRSPC";

// Application capabilities
const char* TransactionTag::APP_CAPABILITIES    			  = "APP_CAP";

// Currency code
const char* TransactionTag::CUR_CODE						  = "CUR_CODE";

// Country code
const char* TransactionTag::COUNTRY_CODE					  = "COUNTRY_CODE";

// Terminal capabilities
const char* TransactionTag::TERM_CAP						  = "TERM_CAP";

// Selected EMV application
const char* TransactionTag::ICCAID							  = "ICCAID";

// Issuer script buffer
const char* TransactionTag::ISS_SCRIPT_BUF					  = "ISS_SCRIPT_BUF";

// HypCString: Authorization Characteristics Indicator
const char* TransactionTag::ACI				= "TR ACI";

// HypCString: Authorization source code
const char* TransactionTag::AUTH_SRC			= "TR AUTH SRC";

// HypCString: Settle flag
const char* TransactionTag::SETTLE_TYPE		= "SETTLE";

// HypCString: Settlement type: CLBATCH
const char* TransactionTag::SETTLE_CLBATCH	= "CLBATCH";

// HypCString: Settlement type: CLBATCHA
const char* TransactionTag::SETTLE_CLBATCHA	= "CLBATCHA";

// HypCString: Settlement type: CLTERM
const char* TransactionTag::SETTLE_CLTERM		= "CLTERM";

// HypCString: Settlement type: RUPLOAD
const char* TransactionTag::SETTLE_RUPLOAD	= "RUPLOAD";

// HypCString: Settlement type: CLBATCHE
const char* TransactionTag::SETTLE_CLBATCHE	= "CLBATCHE";

// HypCBlob: Message Auth Code ( 8 bytes )
const char* TransactionTag::MESSAGE_AUTH_CODE = ISO8583_MESSAGE_AUTH_CODE;

// HypCString: Security Control Info
const char* TransactionTag::SECURITY_CONTROL_INFO = ISO8583_SECURITY_CONTROL_INFO;

// HypCString: Private Field Bit 60
const char* TransactionTag::PRIVATE_FIELD_BIT60 = ISO8583_PRIVATE_FIELD_BIT60;

// HypCString: Private Field Bit 61
const char* TransactionTag::PRIVATE_FIELD_BIT61 = ISO8583_PRIVATE_FIELD_BIT61;

// HypCString: Private Field Bit 62
const char* TransactionTag::PRIVATE_FIELD_BIT62 = ISO8583_PRIVATE_FIELD_BIT62;

// HypCString: Private Field Bit 63
const char* TransactionTag::PRIVATE_FIELD_BIT63 = ISO8583_PRIVATE_FIELD_BIT63;

// HypCOptions: Transaction attributes
const char* TransactionTag::TRANSACTION_ATTRIBUTES = "TR ATTRIBUTES";

// Private field Bit60 fields

// HypCString, Batch number, an 6
const char* TransactionTag::BATCH_NUMBER		= "TR BATCH NO";

// HypCString, Original message type, an 4
const char* TransactionTag::ORIGINAL_MSG_TYPE	= "TR ORIGINAL MSGTYPE";

// HypCString, Original STAN, an 6
const char* TransactionTag::ORIGINAL_STAN		= "TR ORIGINAL STAN";

// HypCString, Original amount, an 12
const char* TransactionTag::ORIGINAL_AMOUNT	= "TR ORIGINAL AMT";

// Private field Bit63 fields

// HypCString: (10), Cashier number, ans 4
const char* TransactionTag::CASHIER			= "TR CASHIER";

// HypCString: (10), Till number, ans 4
const char* TransactionTag::TILLNO			= "TR TILLNO";

// HypCString: (15), Level II comercial card indicator, an 1
const char* TransactionTag::LVL2_INDICATOR	= "TR LVL2 INDICATOR";

// HypCString: (16), Card verification value II indicator, an 1
const char* TransactionTag::CVV2_INDICATOR	= "TR CVV2 INDICATOR";

// HypCString: (16), Card verification value II request response code, an 1
// Indicates response required from host
const char* TransactionTag::CVV2_RESPONSE_CODE= "TR CVV2 RESPCODE";

// HypCString: (16), Card verification value II data, an 4
const char* TransactionTag::CVV2_DATA			= "TR CVV2 DATA";

// HypCString: (16), Card verification value II result code, an 1
const char* TransactionTag::CVV2_RESULT_CODE	= "TR CVV2 RESCODE";

// HypCString: (20), Payment services 2000 indicator, ans 1
// Generated by acquirer
const char* TransactionTag::PS2000_INDICATOR	= "TR PS2000 INDICATOR";

// HypCString: (20), Transaction ID, ans 15
// Generated by VISA 
const char* TransactionTag::TRANSACTION_IDENTIFIER= "TR IDENTIFIER";

// HypCString: (20), Validation code, ans 4
// Genereated by VISA 
const char* TransactionTag::VALIDATION_CODE	= "TR VALIDATION CODE";

// HypCString: (20), VISA II Response code, ans 2
const char* TransactionTag::VISA2_RESPONSE_CODE = "TR VISA2 RESPCODE";

// HypCString: (20), VISA II Pos Entry Mode, ans 2
const char* TransactionTag::VISA2_POS_ENTRY	= "TR VISA2 POS ENTRY";

// HypCCurrency: (21), Authorised amount, an 12
const char* TransactionTag::AUTHORISED_AMOUNT	= "TR AUTHORISED AMT";

// HypCString: (22), Alternate host response, an 40
const char* TransactionTag::ALT_HOST_RESPONSE	= "TR ALT HOST RESP";

// HypCString: (29), Additional host print data, ans ..x
const char* TransactionTag::HOST_PRINT_DATA	= "TR ALT HOST RESP";

// HypCString: (31), Host Reference data, ans ..50
const char* TransactionTag::HOST_REF_DATA		= "TR HOST REFDATA";

// HypCString: (33), Key serial number for DUK/PT encryption, ans 20
const char* TransactionTag::KEY_SN			= "TR KEY SN";

// HypCString: (35), Additional prompt data
const char* TransactionTag::ADDITIONAL_PROMPT	= "TR ADD PROMPT";

// HypCCurrency: (39), Tax Amount #1, ans 12
const char* TransactionTag::TAX_AMOUNT1		= "TR TAX AMT1";

// HypCCurrency: (40), Tax Amount #2, ans 12
const char* TransactionTag::TAX_AMOUNT2		= "TR TAX AMT2";

// HypCCurrency: (41), CashBack Amount, ans 12
const char* TransactionTag::CASHBACK_AMOUNT	= "TR CASHBACK AMT";

// HypCCurrency: (44), Surcharge Amount, ans 12
const char* TransactionTag::SURCHARGE_AMOUNT	= "TR SURCHARGE AMT";

// HypCString: (47), EBT specific, Clerk ID, ans 10
const char* TransactionTag::EBT_CLERK_ID		= "TR EBT CLERKID";

// HypCString: (47), EBT specific, Supervisor ID, ans 10
const char* TransactionTag::EBT_SUPERVISOR_ID	= "TR EBT SUPERVISORID";

// HypCString: (47), EBT specific, Voucher number, ans 15
const char* TransactionTag::EBT_VOUCHER_NUMBER= "TR EBT VOUCHERNUM";

// HypCString: (47), EBT specific, Generation number, ans 6
const char* TransactionTag::EBT_GENERATION_NUMBER = "TR EBT GENERATIONNUM";

// HypCCurrency: (53), Miscellaneous amount, an 12
const char* TransactionTag::MISC_AMOUNT		= "TR MISC AMT";

// HypCString: (54), Address verification zip code, an 9
const char* TransactionTag::AVS_ZIP			= "TR AVS ZIP";

// HypCString: (54), Address verification address, an 20
const char* TransactionTag::AVS_ADDRESS		= "TR AVS ADDRESS";

// HypCString: (55), Address verification response code, an 3
const char* TransactionTag::AVS_RESPONSE		= "TR AVS RESPONSE";

// HypCString: (73), Level II comercial card data
// Optional amount ID, an 1
const char* TransactionTag::LVL2_OPT_AMOUNT_ID = "TR LVL2 OPTAMTID";

// HypCCurrency: (73), LVL2, Optional amount, an 12
const char* TransactionTag::LVL2_OPT_AMOUNT	= "TR LVL2 OPTAMT";

// HypCString: (73), LVL2, Purchase order number, an 17
const char* TransactionTag::LVL2_PO_NUMBER	= "TR LVL2 PONUM";

// HypCString: Journal Name
const char* TransactionTag::JOURNAL_NAME 	= "TR JOURNAL NAME";

// HypCInt64: number of sales
const char* TransactionTag::SALES_COUNT		= "SALESCOUNT";

// HypCInt64: number of debit sales
const char* TransactionTag::SALES_DEB_COUNT	= "SALESDEBCOUNT";

// HypCInt64: sales amount
const char* TransactionTag::SALES_AMOUNT		= "SALESAMOUNT";

// HypCInt64: debit sales amount
const char* TransactionTag::SALES_DEB_AMOUNT	= "SALESDEBAMOUNT";

// HypCInt64: number of sales
const char* TransactionTag::REFUNDS_COUNT		= "REFUNDSCOUNT";

// HypCInt64: number of debit sales
const char* TransactionTag::REFUNDS_DEB_COUNT	= "REFUNDSDEBCOUNT";

// HypCInt64: sales amount
const char* TransactionTag::REFUNDS_AMOUNT	= "REFUNDSAMOUNT";

// HypCInt64: debit sales amount
const char* TransactionTag::REFUNDS_DEB_AMOUNT  = "REFUNDSDEBAMOUNT";

// HypCString: to signal that only one journal is present in the system
const char* TransactionTag::ONE_JOURNAL			= "ONE_JOURNAL";

