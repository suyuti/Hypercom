//=============================================================================
//                         Hypercom Inc
//             Hypercom POS Foundation Classes HPOSFC
//                      (c) Copyright 2006
//=============================================================================
#if !defined(_DOCUMENTMANAGER_HPP_)
#define _DOCUMENTMANAGER_HPP_

//=============================================================================
//
//  DocumentManager.hpp
//
//  Implementation of the Class DocumentManager
//
//=============================================================================

#include <HypCDocumentManager.hpp>

//=============================================================================
// Public defines and typedefs
//=============================================================================

//=============================================================================
// Forward definitions
//=============================================================================
class HyperwareConfig;
class HypCPOSConfig;

//=============================================================================
//!
//!
//! \brief
//!     Keeps application documents and data.
//!
//!     This class keeps track of all the business objects for the application.
//!		A HPOSFC application will use a document manager (or derived) object as
//!		the holder of all application documents. Transactions, configuration
//!		settings, even system information will be accessed using the document
//!		manager.
//!		There should only be one publicly accesible Document manager object for
//!		the entire application, so this is a singleton class.
//!
//! \sa
//!      HypCDocument
//!
//=============================================================================
class DocumentManager : public HypCDocumentManager
{
//=============================================================================
// Member functions
//=============================================================================
public:
	enum
	{
		POS_CONFIG_DOC,
		TOTAL_DOCS
	};

	static DocumentManager* GetDocManager();

	//! Virtual so an user can create an specialized document manager
	virtual ~DocumentManager();

	//! Returns a pointer to the POS configuration document
	HypCPOSConfig* GetPOSConfig();

protected:

	//! Mandated function. This is where actual documents are created
	bool DoCreateDocuments();

private:
	//! This is the default constructor. 
	DocumentManager();

	//! User defined - how many documents are there in the specific application
	virtual size_t GetNumDocs()
	{
		return TOTAL_DOCS;
	}

//=============================================================================
// Member variables
//=============================================================================
private:
	static DocumentManager* _Instance;

};
// DocumentManager

#endif // !defined(_DOCMANAGER_HPP_)

