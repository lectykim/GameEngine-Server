#pragma once
#ifdef _DEBUG
#pragma comment(lib,"..\\TetrisServer\\x64\\Debug\\TetrisServer.lib")
#else
#pragma comment(lib,"TetrisServer\\x64\Release\\TetrisServer.lib")
#endif

#include <unordered_map>
#include <array>

#include <variant>



#include "../TetrisServer/pch.h"

using PacketVariant = variant<uint8_t, uint16_t, double, string, uint16_t*, double*>;