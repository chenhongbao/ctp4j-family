#pragma once

#ifndef __FACADE__
#define __FACADE__

#include <stdint.h>

typedef int32_t			frame_type;
typedef int32_t			frame_length;

#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>

#pragma comment (lib, "Ws2_32.lib")

int32_t c_hton(int32_t host32);
int32_t c_ntoh(int32_t host32);

#endif