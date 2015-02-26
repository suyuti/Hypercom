#ifndef _TRANSMODEMTEST_HPP_
#define _TRANSMODEMTEST_HPP_
#include "BasicTransaction.hpp"

class CTransModemTest : public BasicTransaction 
{
public:
    CTransModemTest();
protected:
    virtual void DoAssignSteps();

};
#endif
