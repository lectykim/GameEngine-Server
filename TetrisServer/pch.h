#pragma once

#define WIN32_LEAN_AND_MEAN

#include <mutex>
#include <atomic>
#include <memory>
using BYTE = unsigned char;
#include "CoreMacro.h"
#include "CoreTLS.h"
#include "CoreGlobal.h"
#include <array>
#include <vector>
#include <queue>
#include <set>

#include <cstdlib>
#include <ctime>

#include <windows.h>
#include <iostream>
using namespace std;

#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>
#pragma comment(lib,"ws2_32.lib")

#include "Lock.h"
#include "Session.h"
#include "ThreadManager.h"
#include "Service.h"
#include "JobQueue.h"
#include "SendBuffer.h"
#include "RecvBuffer.h"

template<typename T>
inline shared_ptr<T> make_array(int size)
{
	return std::shared_ptr<T>(new T[size], [](T* p) {delete[] p; });
}

template<class... Ts> struct overloaded : Ts... {using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;


#include <variant>
using PacketVariant = variant<uint8_t, uint16_t, uint64_t, string, uint16_t*, uint64_t*>;

#include "Serializer.h"
#include "DeSerializer.h"