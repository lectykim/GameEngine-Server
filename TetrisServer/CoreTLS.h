#pragma once

extern thread_local uint32_t LThreadId;
extern thread_local uint64_t LEndTickCount;

extern thread_local class JobQueue* LCurrentJobQueue;