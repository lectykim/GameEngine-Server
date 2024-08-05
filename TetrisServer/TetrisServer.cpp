

#include <iostream>
#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib,"ws2_32")

#define PORT 33333
#define MAX_PACKET_SIZE 4096

/* 127.0.0.1 localhost << 스프링할때도 배웠잖아요
    외부에서 내부로 접속하려면 포트포워딩이란걸 해야되고
    저희의 IP 주소를 향해 패킷 요청을 보내고
    그걸 이제 라우터가 받아서
    저희 서비스에 연결을 시키는 과정이 있을텐데
    localhost는 이제 내 서버를 내가 연결할때 그럴때 사용 합니다
    그래서 스프링을 동작시키고 스프링에 접속할때 localhost를 쓴 거에요
    C++ 서버도 똑같음
    저희가 저희가 만든 서버를 테스트하기 위해서는 127.0.0.1:33333<< 으로 접속하면 됨 !
    근데 브라우저로 접속하는 게 아니라
    클라이언트로 왜냐면 웹이 아니기때문에

    what is htons
    33333 << 이 숫자를 이제
    소켓을 담당하는 코드가 알아볼 수 있는 형태로 바꿔주는 함수입니다
    little endian big endian 이런게있는데
    좆문대 -y-대학교에서는 그런거 안알려줌

    근데 저흰 알아야됨 왜? 겜 서버니까 ㅋ


*/

int main()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET sock;
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN sockaddr = {};
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(PORT);
    // 모든 ip 주소에서 요청을 수락하겠다 라는 의미
    sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(sock, (SOCKADDR*)&sockaddr, sizeof(sockaddr));
    listen(sock, SOMAXCONN);

    SOCKADDR_IN clientAddr = {};
    int clientSize = sizeof(clientAddr);
    SOCKET client = accept(sock, (SOCKADDR*)&clientAddr, &clientSize);
    while (true) {
        

        char buf[MAX_PACKET_SIZE] = {};
        recv(client, buf, MAX_PACKET_SIZE, 0);
        printf("Recv msg : %s\n", buf);

        
        send(client, buf, strlen(buf), 0);
    }
    
    

    


    WSACleanup();
    return 0;

}
