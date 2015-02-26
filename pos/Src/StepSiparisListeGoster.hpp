#ifndef _CStepSiparisListeGoster_HPP_
#define _CStepSiparisListeGoster_HPP_
#include <HypCTransactionStep.hpp>

class CStepSiparisListeGoster : public HypCTransactionStep 
{
public:
    CStepSiparisListeGoster() : HypCTransactionStep() {};
protected:
    virtual bool doExecute();
	virtual void FillListe();
	virtual void OnCmdTumunuSil();
	virtual void OnCmdYazdir();
	virtual void OnCmdSil();
};
#endif
