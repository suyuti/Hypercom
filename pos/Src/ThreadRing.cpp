#include "ThreadRing.hpp"

CThreadModemRing::CThreadModemRing()
:
HypCThread("ModemRing", 4096)
{
    
}

void CThreadModemRing::Start()
{
    this->Execute();
    this->Suspend();
}

void CThreadModemRing::Execute()
{
    int i = 0;
    while (true)
    {
        i++;
        NU_Relinquish();
    }
}

