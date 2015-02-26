#ifndef _GLOBALS_HPP_
#define _GLOBALS_HPP_
#include <HypCApplication.hpp>
#include <HypCFont.hpp>
#include <HypCGrafixWindow.hpp>
#include <HypCSmartCardDeviceAAE.hpp>
#include <HypCSecurityProvider.hpp>
#include <HypCImage.hpp>
#include <HypCEvent.hpp>
class CGlobal
{
public:
	// Listen eden class ile YemekSepetiClient aras?ndaki kuyu
	// Accept() oldu?unda kuyuya atar, Ring oldu?unda kuyuya atar
	// YemeksepetiClient kuyudan çeker
	static NU_QUEUE* g_pQueuePOSServerYSClient;
	enum {
		QueueStackSize = 100
	};
	static void CreateQueue();
protected:
private:
};

#endif