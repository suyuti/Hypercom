//=============================================================================
//                         Hypercom Inc
//             Hypercom POS Foundation Classes HPOSFC
//                      (c) Copyright 2006
//=============================================================================
//
//  DocumentManager.cpp
//
//  Implementation of the Class DocumentManager
//
//=============================================================================
#include <compiler.h>
#include <HypCDocument.hpp>
#include <HypCInt16.hpp>
#include <HypCString.hpp>
#include "YemekSepetiConfig.hpp"
#include "DocumentManager.hpp"
#include "YemekSepetiTags.h"

// Initialize the array of documents requested by HypCDocumentManager
HypCDocument* HypCDocumentManager::m_Documents[DocumentManager::TOTAL_DOCS];

// Initialize the singleton instance of the DocumentManager
DocumentManager* DocumentManager::_Instance = NULL;

//-----------------------------------------------------------------------------
//!
//!      Returns an instance to the singleton instance of the document manager
//!
//! \return
//!      A pointer to the DocumentManager object for the application
//!
//! \note
//!
DocumentManager* DocumentManager::GetDocManager()
{
	if ( NULL == _Instance )
	{
		_Instance = new DocumentManager();
	}
	return _Instance;
}

//-----------------------------------------------------------------------------
//!
//!      Builds the doc manager using a reference to the application object.
//!
//! \return
//!      Nothing
//!
//! \note
//!
DocumentManager::DocumentManager() :
	HypCDocumentManager()
{
}


//-----------------------------------------------------------------------------
//!
//!      Creates the documents used by the Hyperware application.
//!
//! \return
//!      true if document creation was successful, false otherwise
//!
//! \note
//!
bool DocumentManager::DoCreateDocuments()
{
	// Create the configuration data object
	HyperwareConfig *pConfig = new HyperwareConfig;
	if ( NULL == pConfig )
	{
		return false;
	}

	// The TM database file
	pConfig->SetStorage("C:\\application.CFG");
	pConfig->SetDBDesc("C:\\config.FMT");
	// Set the delta file for storing data differences
	// bewteen TM database data and app changes of the data
	pConfig->SetDelta("D:\\delta.CFG");
	pConfig->SetControlFile("D:\\control.CFG");


	if ( pConfig->Init() )
	{
		// check system data, and if it does not exist then initialize
		// move this into HyperwareConfig, also need better way to do it
		HYP_CFG_HANDLE systable =  
			pConfig->GetTable( SystemDataTag::SYSTEM_TABLE );
	
		// get current invoice number
		HString str =  pConfig->GetParam( systable,
							  SystemDataTag::INVOICE_NUMBER );
		
		if( str.empty() )
		{
			pConfig->SetParam( systable, 
					  SystemDataTag::INVOICE_NUMBER, HypCString("000001"));
		}	
		
		// get system trace
		str =  pConfig->GetParam( systable,
							  SystemDataTag::SYSTEM_TRACE );
		
		if( str.empty() )
		{
			// system trace number, start with 0
			pConfig->SetParam ( systable,
							  SystemDataTag::SYSTEM_TRACE, HypCInt16(0) );
		}
	
	}
	// We need the pointer to the POS config document, so it can be deleted
	// in the destructor
	m_Documents[POS_CONFIG_DOC] = pConfig;
	return true;
};


//-----------------------------------------------------------------------------
//! DocumentManager::GetPOSConfig
//! 		Provides access to the generic POS configuration object
//!
//! \return
//!      Returns a pointer to the POS configuration document
//!
//! \note
//! 
HypCPOSConfig* DocumentManager::GetPOSConfig()
{
	return static_cast<HypCPOSConfig*>(m_Documents[POS_CONFIG_DOC]);
}


//-----------------------------------------------------------------------------
//! DocumentManager::~DocumentManager
//!      Virtual destructor
//!
//! \return
//!      void
//!
//! \note
//!
DocumentManager::~DocumentManager()
{
	Close();
	delete m_Documents[POS_CONFIG_DOC];
}

