#include "TransSiparisler.hpp"
#include "StepFactory.hpp"

CTransSiparisler::CTransSiparisler() :
BasicTransaction()
{
}
void CTransSiparisler::DoAssignSteps()
{
    SetTitle("Alinan Siparisler");
    AddStep(StepNameTag::STEP_SIPARIS_LISTE_GOSTER);
    //AddStep(StepNameTag::STEP_ANKET_SEC);
    //AddStep(StepNameTag::STEP_SORULAR);
    //AddStep(STEP_ANKET_SONUC);
}

