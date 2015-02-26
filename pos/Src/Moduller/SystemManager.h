#ifndef _SYSTEM_MANAGER_HPP_
#define _SYSTEM_MANAGER_HPP_

#define DN_ETHERNET "Ethernet 0"

class CSystemManager
{
public:
    CSystemManager() {};
    virtual ~CSystemManager() {};
	static bool EthernetUp();
protected:
private:
};
#endif
