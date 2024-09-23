#include "pch.h"
#include "Service.h"
#include "Session.h"
#include "Listener.h"

Service::Service(ServiceType type, NetworkConnector address, shared_ptr<IocpCore> core, SessionFactory factory, int maxSessionCount)
	:_type(type),_netAddress(address),_iocpCore(core),_sessionFactory(factory),_maxSessionCount(maxSessionCount)
{
}

Service::~Service()
{
}

void Service::CloseService()
{
	WRITE_LOCK;
	for (const auto& session : _sessions)
	{
		session->Disconnect(L"Exit Call");
	}
	_sessions.clear();
	_sessionCount = 0;
}

void Service::Broadcast(shared_ptr<BYTE*> buffer)
{
	WRITE_LOCK;
	for (const auto& session : _sessions)
	{
		session->Send(buffer);
	}
}

shared_ptr<Session> Service::CreateSession()
{
	shared_ptr<Session> session = _sessionFactory();
	session->SetService(shared_from_this());
	if (_iocpCore->Register(session) == false)
		return nullptr;
	return session;
}

void Service::AddSession(shared_ptr<Session> session)
{
	WRITE_LOCK;
	_sessionCount++;
	_sessions.insert(session);
}

void Service::ReleaseSession(shared_ptr<Session> session)
{
	WRITE_LOCK;
	_sessions.erase(session);;
	_sessionCount--;
}

ClientService::ClientService(NetworkConnector targetAddress, shared_ptr<IocpCore> core, SessionFactory factory, int maxSessionCount)
	:Service(ServiceType::Client,targetAddress,core,factory,maxSessionCount)
{

}

bool ClientService::Start()
{
	if (CanStart() == false)
		return false;

	const int sessionCount = GetMaxSessionCount();
	for (int i = 0; i < sessionCount; i++)
	{
		shared_ptr<Session> session = CreateSession();
		if (session->Connect() == false)
			return false;
	}
	return true;
}

ServerService::ServerService(NetworkConnector targetAddress, shared_ptr<IocpCore> core, SessionFactory factory, int maxSessionCount):
	Service(ServiceType::Server,targetAddress,core,factory,maxSessionCount)
{

}


bool ServerService::Start()
{
	if (CanStart() == false)
		return false;

	_listener = make_shared<Listener>();
	if (_listener == nullptr)
		return false;
	shared_ptr<ServerService> service = static_pointer_cast<ServerService>(shared_from_this());
	if (_listener->StartAccept(service) == false)
		return false;

	return true;
}

void ServerService::CloseService()
{
	Service::CloseService();
}
