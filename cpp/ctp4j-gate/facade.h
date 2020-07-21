#pragma once

#ifndef __FACADE__
#define __FACADE__

#include <stdint.h>

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

int32_t c_hton(int32_t host32) {
	return (int32_t)htonl((u_long)host32);
}

int32_t c_ntoh(int32_t host32) {
	return (int32_t)ntohl((u_long)host32);
}
#endif

#include <fstream>

void print(const char* msg = "") {
	try {
		std::ofstream ofs("cout.log", std::ios::app | std::ios::out);
		ofs << msg << std::endl;
		ofs.flush();
	}
	catch (std::exception& e) {
		printf("%s\n", e.what());
	}
}

#endif