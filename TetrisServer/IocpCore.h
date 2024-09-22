#pragma once
class IocpObject : public enable_shared_from_this<IocpObject>
{
public:
	virtual HANDLE GetHandle() abstract;
	virtual void Dispatch(class IocpEvent* iocpEvent, int numOfBytes = 0) abstract;
};


class IocpCore
{
public:
	IocpCore();
	~IocpCore();

	HANDLE GetHandle()const  { return _iocpHandle; }

	bool Register(shared_ptr<IocpObject> iocpObject);
	bool Dispatch(uint32_t timeoutMs = INFINITE);

private:
	HANDLE _iocpHandle;
};

