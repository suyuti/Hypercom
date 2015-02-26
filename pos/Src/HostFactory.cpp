//=============================================================================
// Company:
//      Hypercom Inc
//
// Product:
//      Hyperware Base Applicaiton
//      (c) Copyright 2006
//
// File Name:
//      HostFactory.cpp
//
// File Contents:
//      Implementation of HostFactory Class
//
//=============================================================================
#include <compiler.h>
#include "VisaHost.hpp"
#include "DemoHost.hpp"
#include "HypercomHost.hpp"
#include "AmexHost.hpp"
#include "HostFactory.hpp"


//-----------------------------------------------------------------------------
//!
//!      Creates a host object based on the host name.
//!
//! \param
//!      sHostName       Name of the host object to be created
//!
//! \return
//!      pointer to the newly created HypCost object
//!
//! \note
//!
HypCHost *HostFactory::DoCreateHost( const char *sHostName )
{
	HString HostName = sHostName;
	
	if( HostName == "DEMOHOST" )
	{
		return new DemoHost();
	}
	
	if( HostName == "HYPERCOM" )
	{
		return new HypercomHost();
	}
	
	if( HostName == "AMEX" )
	{
		return new AmexHost();
	}

	if( HostName == "VISAII" )
	{
		return new VisaHost();
	}

	return 0;
}


//-----------------------------------------------------------------------------
//!
//!      Check if host module name is valid
//!
//! \param
//!      sHostName       Name of the host object to test if valid
//!
//! \return
//!      true if the host name is found and host can be created
//!      false if host name is not valid
//!
//! \note
//!
bool HostFactory::DoIsValid( const char *sHostName )
{
	HString HostName = sHostName;

	if( ( HostName == "DEMOHOST" ) ||
		( HostName == "HYPERCOM" ) ||
		( HostName == "AMEX" )     ||
		( HostName == "VISAII" ) )
	{
		return true;
	}

	return false;

}

