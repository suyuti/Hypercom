#include "RingListener.hpp"
#include <HypCSerialTransport.hpp>
#include <HypCModemAAE.hpp>
#include <HypCTimer.hpp> 
#include <HypCTransport.hpp> 
#include <HypCBuffer.hpp> 
#include <HypCSerialPort.hpp> 
#include "..\TransactionUtility.hpp"
#include "yemeksepeticlient.hpp"
#include "IPUpdater.h"

#define TIMER_EVENT (10)
#define BUFFER_LEN (12)

void RingListenerThreadProc(UNSIGNED x, VOID* y)
{
    HyperwareMain *pApp = (HyperwareMain*)y;
    HypCEvent*      event;
    HypCEventInfo   eventInfo;
    HypCTimer*      timer;
    HypCBuffer*     buffer;
    int req,status,t;
    HypCBuffer*     opt;
    bool bRecieveResp = false;
    req = 0;
    event=new HypCEvent();

    char bf[BUFFER_LEN + 1] = "";
    HypCSerialPort *com2 = SerialPortForModule();
    if (com2->Connect()) {
        com2->Write("ATZ\r",4); // modemi initialize et
        while (true)
        {
            req = 0;
            status = 0;
            memset(bf, 0, BUFFER_LEN);
            com2->ReadReq(bf, BUFFER_LEN, *event);
            if (event->Wait(eventInfo)) {
                req = eventInfo.GetRequestID();
                status = eventInfo.GetStatus();
                if ( req == HypCTransport::READ_REQUEST)
                {
                    // gelen RING mi ona bakýlacak
                    com2->Write("ATH1\r",5); // telefonu aç
                    event->Wait(eventInfo, 500);
                    com2->Write("ATH0\r",5); // yüzüne kapat!... çat DIIIIIIIIIII, Alov alov alov
                    //event->Wait(eventInfo, 1000);
                    com2->CancelRequests();
                    //event->Wait(eventInfo, 1000);
                    com2->Write("ATZ\r",4); // modemi initialize et
                    //event->Wait(eventInfo, 1000);
                    com2->CancelRequests();
                    //event->Wait(eventInfo, 1000);

					CIPUpdater ipUpdater("172.16.0.215", "19");
					ipUpdater.Update();

                    CYemekSepetiClient cli("172.16.0.215");
                    cli.SetApp(pApp);
                    string resp = cli.GetSiparis(5);
                    HypCEvent* event = pApp->GetListenEvent();
                    event->Send(9999);
                }
            }
        }
        com2->Disconnect();
    }
    delete com2;
}


HypCSerialPort* SerialPortForModule(void)
{
    HypCSerialTransport *p;
    p = new HypCSerialPort(19, HYP_SP_MODEM);
    HypSSerialParameters param;
    param.ErrorCharFlag = 0;
	param.FlowCtrl = HYP_HARDWARE_FC;
    //param.BaudRate = HYP_SBR_115200;
    param.BaudRate = HYP_SBR_9600;
//	param->ReadIntervalTimeout = pModeInfo->InterCharTimeout;
    param.ErrorChar = 0;
	param.StopBits = HYP_STOP_1;
	param.DataBits = 8;
	param.Parity = HYP_PARITY_NONE;

    p->Init(param);
	return (HypCSerialPort*)p;
}

