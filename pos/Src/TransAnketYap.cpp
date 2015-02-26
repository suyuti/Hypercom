#include "TransAnketYap.hpp"
#include "StepFactory.hpp"

CTransAnketYap::CTransAnketYap() :
BasicTransaction()
{
}
void CTransAnketYap::DoAssignSteps()
{
    SetTitle("Anket Yap");
    AddStep(StepNameTag::STEP_ANKET_BASLAT);
    AddStep(StepNameTag::STEP_ANKET_SEC);
    AddStep(StepNameTag::STEP_SORULAR);
    //AddStep(STEP_ANKET_SONUC);
}

