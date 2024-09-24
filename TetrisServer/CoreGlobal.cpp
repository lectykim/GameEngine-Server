#include "pch.h"
#include "CoreGlobal.h"
#include "ThreadManager.h"
#include "GlobalQueue.h"
#include "SocketUtils.h"
#include "JobTimer.h"
#include "SendBuffer.h"

ThreadManager* GThreadManager = nullptr;
GlobalQueue* GGlobalQueue = nullptr;
JobTimer* GJobTimer = nullptr;
SendBufferManager* GSendBufferManager = nullptr;

class CoreGlobal
{
public:
	CoreGlobal()
	{
		GThreadManager = new ThreadManager();
		GGlobalQueue = new GlobalQueue();
		GJobTimer = new JobTimer();
		GSendBufferManager = new SendBufferManager();
		SocketUtils::Init();
	}
	~CoreGlobal()
	{
		delete GThreadManager;
		delete GGlobalQueue;
		delete GJobTimer;
		delete GSendBufferManager;
		SocketUtils::Clear();
	}
}GCoreGlobal;