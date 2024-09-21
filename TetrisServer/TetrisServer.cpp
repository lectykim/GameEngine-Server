#include "pch.h"
#include "ThreadManager.h"
#include "Service.h"
#include "Session.h"
#include "GameSession.h"
enum
{
    WORKER_TICK = 64
};

void DoWorkerJob(shared_ptr<ServerService>& service)
{
    while (true)
    {
        LEndTickCount = ::GetTickCount64();

        service->GetIocpCore()->Dispatch(10);

        ThreadManager::DistributeReservedJobs();

        ThreadManager::DoGlobalQueueWork();
    }
    
}

int main()
{
    //템플릿은 컴파일 타임에 타입이 지정된다.
    //그러나 make_shared를 이중으로 쓰는 경우에는
    //전처리기가 '모호한 타입'으로 판단해버려서 빌드가 불가능하다
    //그럴 때에는 캐스팅을 통해 타입을 명시해줌으로서 상황 타파가 가능하다.

    
    shared_ptr<ServerService> service = make_shared<ServerService>(
        NetworkConnector(L"127.0.0.1", 7777),
        make_shared<IocpCore>(),
        static_cast<SessionFactory>(make_shared<GameSession>),
        10000);

    service->Start();

    for (int i = 0; i < 17; i++)
    {
        GThreadManager->Launch([&service]()
            {
                DoWorkerJob(service);
            });
    }

    DoWorkerJob(service);

    GThreadManager->Join();
    
    return 0;

}
