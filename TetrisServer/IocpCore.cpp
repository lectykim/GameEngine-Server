#include "pch.h"
#include "IocpCore.h"
#include "IocpEvent.h"
IocpCore::IocpCore() 
{
	_iocpHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
}
IocpCore::~IocpCore()
{
	::CloseHandle(_iocpHandle);
}

bool IocpCore::Register(shared_ptr<IocpObject> iocpObject)
{
	return ::CreateIoCompletionPort(iocpObject->GetHandle(), _iocpHandle, 0, 0);
}

bool IocpCore::Dispatch(uint32_t timeoutMs)
{
	DWORD numOfBytes = 0;
	ULONG_PTR key = 0;
	IocpEvent* iocpEvent = nullptr;

	if (::GetQueuedCompletionStatus(_iocpHandle, OUT & numOfBytes, OUT & key, OUT reinterpret_cast<LPOVERLAPPED*>(&iocpEvent), timeoutMs))
	{
		shared_ptr<IocpObject> iocpObject = iocpEvent->owner;
		iocpObject->Dispatch(iocpEvent, numOfBytes);
	}
	else
	{
		int errCode = ::WSAGetLastError();
		switch (errCode)
		{
		case WAIT_TIMEOUT:
			return false;
		/*case ERROR_NETNAME_DELETED:
		{
			shared_ptr<IocpObject> iocpObject = iocpEvent->owner;
			iocpEvent->eventType = EventType::Disconnect;
			iocpObject->Dispatch(iocpEvent, numOfBytes);
			break;
		}*/
		default:
			cout << errCode << endl;
			shared_ptr<IocpObject> iocpObject = iocpEvent->owner;
			iocpObject->Dispatch(iocpEvent, numOfBytes);
			break;
		}
	}


	return true;
}
