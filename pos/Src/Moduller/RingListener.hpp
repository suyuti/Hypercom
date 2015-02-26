#ifndef _RING_LISTENER_HPP_
#define _RING_LISTENER_HPP_
#include <HypCSerialPort.hpp> 

void RingListenerThreadProc(UNSIGNED, VOID*);
HypCSerialPort* SerialPortForModule(void);

#endif
