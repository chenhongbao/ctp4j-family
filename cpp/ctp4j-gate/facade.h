#pragma once

#ifndef __FACADE__
#define __FACADE__

#include <stdint.h>

#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>

int32_t c_hton(int32_t host32) {
	return (int32_t)htonl((u_long)host32);
}

int32_t c_ntoh(int32_t host32) {
	return (int32_t)ntohl((u_long)host32);
}

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

#include "Objbase.h"

std::string get_uuid() {
    char buffer[64] = { 0 };
    GUID guid;
    if (CoCreateGuid(&guid) != S_OK)
        return "";
    sprintf_s(buffer, sizeof(buffer),
        "%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
        guid.Data1,
        guid.Data2,
        guid.Data3,
        guid.Data4[0], guid.Data4[1], guid.Data4[2],guid.Data4[3], guid.Data4[4], guid.Data4[5],guid.Data4[6], guid.Data4[7]);
    return buffer;
}

#include "io.h"
#include "direct.h"

bool create_directory(const char* path) {
    if (_access(path, 0) != 0 && _mkdir(path) != 0)
        return false;
    else
        return true;
}

#undef min
#undef max

#endif