#ifndef _CTransSiparisler_HPP_
#define _CTransSiparisler_HPP_

#include "BasicTransaction.hpp"

class CTransSiparisler : public BasicTransaction 
{
public:
    CTransSiparisler();
protected:
    virtual void DoAssignSteps();
};

#endif
