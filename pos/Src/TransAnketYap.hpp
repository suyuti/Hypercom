#ifndef _TRANS_ANKET_YAP_HPP_
#define _TRANS_ANKET_YAP_HPP_

#include "BasicTransaction.hpp"

class CTransAnketYap : public BasicTransaction 
{
public:
    CTransAnketYap();
protected:
    virtual void DoAssignSteps();
};

#endif
