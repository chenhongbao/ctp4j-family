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
    if (id.load() == INT_MAX)
        id.store(1);
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

std::string get_file_name(const char* full) {
    if (full == nullptr || strlen(full) == 0)
        return "";
    std::string buf(full);
    auto pos = buf.find_last_of('\\');
    if (pos == std::string::npos)
        pos = buf.find_last_of('/');
    if (pos == std::string::npos)
        return buf;
    else
        return buf.substr(pos + 1);
}

#include <fstream>

#define print(m) v_print(m, __FILE__, __FUNCTION__ , __LINE__)

#define print_code(m, code)                                                                         \
{                                                                                                   \
    std::string msg = std::string(m) + std::string("(") + std::to_string(code) + std::string(")");  \
    print(msg.c_str());                                                                             \
}

void v_print(const char* msg, const char* src, const char* function, const int line, const char* file = "cout.log") {
    try {
        std::ofstream ofs(file, std::ios::app | std::ios::out);
        ofs << "[" << get_time_str() << "][" << get_file_name(src) << "][" << function << "][" << line << "] " << msg << std::endl;
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

#define WIN32_LEAN_AND_MEAN
#include "Windows.h"

std::string convert_gb2312_utf8(const char* gb2312)
{
    int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
    // The last character is null-ternimating, skip it.
    std::wstring wstr(len - 1, 0);
    LPWSTR wptr = const_cast<wchar_t*>(wstr.c_str());
    MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wptr, len);
    len = WideCharToMultiByte(CP_UTF8, 0, wptr, -1, NULL, 0, NULL, NULL);
    // The last character is null-ternimating, skip it.
    std::string str(len - 1, 0);
    LPSTR ptr = const_cast<char*>(str.c_str());
    WideCharToMultiByte(CP_UTF8, 0, wptr, -1, ptr, len, NULL, NULL);
    return str;
}

#undef min
#undef max

#endif