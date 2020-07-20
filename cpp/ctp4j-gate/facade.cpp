#include "facade.h"

#if defined(__linux__)
#include <arpa/inet.h>
int32_t c_hton(int32_t host32) {
	return (int32_t)htonl((uint32_t)host32);
}

int32_t c_ntoh(int32_t host32) {
	return (int32_t)ntohl((uint32_t)host32);
}
#else
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#pragma comment (lib, "Ws2_32.lib")

int32_t c_hton(int32_t host32) {
	return (int32_t)htonl((u_long)host32);
}

int32_t c_ntoh(int32_t host32) {
	return (int32_t)ntohl((u_long)host32);
}
#endif
