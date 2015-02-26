//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hyperware Base Application
//      (c) Copyright 2006
//
// File Name:
//        HostFactory.hpp
//
// File Description:
//        Declaration of HostFactory class
//
//=============================================================================
#if !defined( _HOSTFACTORY_HPP )
#define _HOSTFACTORY_HPP

#include <HypCHostFactory.hpp>

//=============================================================================
// Public defines and typedefs
//=============================================================================

//=============================================================================
// Forward definitions
//=============================================================================

//=============================================================================
//!
//! \brief
//!      Creates object of type HypCHost.
//!
//!      Factory class to create classes of type HypCHost.
//!
//! \sa
//!      HypCHostFactory
//!
//=============================================================================
class HostFactory : public HypCHostFactory
{
	public:
		//! Constructor
		HostFactory( ) {};

		//! Destructor
		virtual ~HostFactory() {};
	
		
	protected:

		//! Creates a new host object
		HypCHost *DoCreateHost( const char *sHostName );

		//! Check if host module name is valid
        bool DoIsValid( const char *sHostName );			
		
};
// HostFactory

#endif //#if !defined( _HOSTFACTORY_HPP )


