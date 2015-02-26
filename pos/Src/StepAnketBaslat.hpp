#ifndef _STEP_ANKET_BASLAT_HPP_
#define _STEP_ANKET_BASLAT_HPP_

#include <HypCTransactionStep.hpp>

class CStepAnketBaslat : public HypCTransactionStep 
{
public:
    CStepAnketBaslat() : HypCTransactionStep() {};
protected:
    virtual bool doExecute();
};
#endif
