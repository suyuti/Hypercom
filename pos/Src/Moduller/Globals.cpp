#include "Globals.h"

NU_QUEUE* CGlobal::g_pQueuePOSServerYSClient = NULL;

void CGlobal::CreateQueue()
{
	STATUS  status;
	BYTE* QueueStack = new BYTE[QueueStackSize];
	if (QueueStack)
	{
		status = Hyc_AllocControlBlock( CB_NU_QUEUE, (void **)&g_pQueuePOSServerYSClient);
		status = NU_Create_Queue(g_pQueuePOSServerYSClient, "qPSYS", QueueStack, QueueStackSize, NU_FIXED_SIZE, sizeof(int), NU_FIFO);
		if (status != NU_SUCCESS)
		{
			delete[] QueueStack;
			return;
		}
	}
}