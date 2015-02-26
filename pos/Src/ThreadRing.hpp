#ifndef _THREADRING_HPP_
#define _THREADRING_HPP_

#include <HypCThread.hpp>

class CThreadModemRing : public HypCThread 
{
public:
    CThreadModemRing();
    virtual ~CThreadModemRing() {};
    void Start();
protected:
private:
    virtual void Execute();
};
#endif
