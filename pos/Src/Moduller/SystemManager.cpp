#define _INCLUDE_NUCLEUS_NET_
#include <hycddl.h>
#include "SystemManager.h"

bool CSystemManager::EthernetUp()
{
    return true;
	//return (NU_Device_Up(DN_ETHERNET) == OS_TRUE);
}
