#ifndef _STEP_SORU_SOR_HPP_
#define _STEP_SORU_SOR_HPP_
#include <HypCTransactionStep.hpp>
class CStepSoruSor : public HypCTransactionStep 
{
public:
    CStepSoruSor() : HypCTransactionStep() {};
protected:
    virtual bool doExecute();
};
#endif
