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

#include <atomic>

int add_and_get(int i = 1) {
    static std::atomic<int> id(1);
    return id.fetch_add(i);
}

#include <iomanip>
#include <ctime>
#include <sstream>

std::string get_time_str(const char* format = "%Y-%m-%d %H:%M:%S") {
    std::stringstream ss;
    ::time_t t_c = ::time(nullptr);
    ::tm t_m;
    ::localtime_s(&t_m, &t_c);
    ss << std::put_time(&t_m, format);
    return ss.str();
}

#include <fstream>

void print(const char* msg, const char* file = "cout.log") {
    try {
        std::ofstream ofs(file, std::ios::app | std::ios::out);
        ofs << get_time_str() << " " << msg << std::endl;
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