#define _INCLUDE_NUCLEUS_NET_
#include "StepModemTest.hpp"
#include <HypCSerialTransport.hpp>
#include <HypCModemAAE.hpp>
#include <HypCTimer.hpp> 
#include <HypCTransport.hpp> 
#include <HypCBuffer.hpp> 
#include <HypCSerialPort.hpp> 
#include "TransactionUtility.hpp"
#include "ThreadRing.hpp"
#include ".\Comm\POSComm.hpp"
#include <HypCPrinter.hpp>
#include <HypCTransaction.hpp>


//#define TIMER_EVENT (USERDEFINED_REQUEST+1)
#define TIMER_EVENT (10)
#define BUFFER_LEN (12)

void task_0(UNSIGNED argc, VOID* argv);
void task_1(UNSIGNED argc, VOID* argv);
void task_2(UNSIGNED argc, VOID* argv);

void task_0(UNSIGNED argc, VOID* argv)
{
    int i = 0;
    while (true)
    {
        i++;
    }
}
#define STACK_SIZE	(16 * 1024)


void Network()
{
    INT soc;
    int status;
    struct addr_struct servaddr;
    char buff[] = "Selam";
    int sent;

    servaddr.family = NU_FAMILY_IP;
    servaddr.port = 1234;
    servaddr.id.is_ip_addrs[0] = 172;
    servaddr.id.is_ip_addrs[1] = 16;
    servaddr.id.is_ip_addrs[2] = 0;
    servaddr.id.is_ip_addrs[3] = 215;
    servaddr.name = "server";

    soc = NU_Socket(NU_FAMILY_IP, NU_TYPE_STREAM, 0);
    status = NU_Connect(soc, &servaddr, 0);
    if (status != NU_INVALID_SOCKET)
    {
        sent = NU_Send(soc, buff, strlen(buff), 0);
        NU_Close_Socket(soc);
    }
    //soc = NU_Socket(NU_FAMILY_IP, NU_TYPE_STREAM, 0);

}


bool CStepModemTest::doExecute()
{
    char res[100] = "";
    CPosComm comm;
    string ip("172.16.0.215");
    comm.Initialize(ip, 1500);
    comm.Listen();
    //DoCommunication();
    //SendATCommand( "ATD3589", "ATD3589", 30000, res);
    return false;
}

bool CStepModemTest::SendATCommand( const char *reqString, const char *respString, unsigned int timeout , char *result)
{
    HypCEvent*      event;
    HypCEventInfo   eventInfo;
	HypCTimer*      timer;
	HypCBuffer *buffer;
	int req,status,t;
	HypCBuffer *opt;
	bool bRecieveResp = false;
        req = 0;
    event=new HypCEvent();



    char bf[BUFFER_LEN + 1] = "";
	// Create configuration for serial line to module
	HypCSerialPort *com2 = SerialPortForModule();
	if (com2->Connect()) {
        com2->Write("ATZ\r",4); // modemi initialize et
        while (true)
        {
            //com2->Disconnect();
            //com2->Connect();
            req = 0;
            status = 0;
            //com2->Write("ATZ\r",4);

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
                    //Network();
                    DoCommunication();
                }
            }
        }
        com2->Disconnect();
    }
    delete com2;
    return false;

	return bRecieveResp;
}

HypCSerialPort *CStepModemTest::SerialPortForModule(void)
{
    HypCSerialTransport *p;
    //HypCSerialPort *com2=new HypCSerialPort(19, HYP_SP_MODEM);
    //p = new HypCSerialPort(19, HYP_SP_RS232);
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

void CStepModemTest::DoCommunication()
{
    CPosComm comm;
    string ip("172.16.0.215");
    comm.Initialize(ip, 1500);
    comm.TumSiparisSorgula();

    HypCPrinter *prn = Transaction().GetPrinter();
    if (prn != NULL)
    {
        HypCEvent FinishedPrinting;
        HypCEventInfo   eventInfo;
        prn->Print(FinishedPrinting, "Siparis");
        FinishedPrinting.Wait ( eventInfo );
    }
}


