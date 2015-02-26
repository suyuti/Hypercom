#ifndef _STEPMODEMTEST_HPP_
#define _STEPMODEMTEST_HPP_

#include <HypCTransactionStep.hpp>
#include <HypCSerialPort.hpp> 

class CStepModemTest : public HypCTransactionStep 
{
public:
    CStepModemTest() : HypCTransactionStep() {};
    bool SendATCommand( const char *reqString, const char *respString, unsigned int timeout , char *result );
    static HypCSerialPort *SerialPortForModule(void);
    void DoCommunication();

protected:
    virtual bool doExecute();
};
#endif
