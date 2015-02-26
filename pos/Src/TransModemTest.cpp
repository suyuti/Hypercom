#include "TransModemTest.hpp"
#include "StepFactory.hpp"

CTransModemTest::CTransModemTest() :
BasicTransaction()
{
}
void CTransModemTest::DoAssignSteps()
{
    SetTitle("Modem Test");
    AddStep(StepNameTag::STEP_MODEM_TEST);
}

