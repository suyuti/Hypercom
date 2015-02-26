#ifndef _STEP_ANKET_SEC_HPP_
#define _STEP_ANKET_SEC_HPP_
#include <HypCTransactionStep.hpp>

class CStepAnketSec : public HypCTransactionStep 
{
public:
    CStepAnketSec() : HypCTransactionStep() {};
protected:
    virtual bool doExecute();
};

#endif
