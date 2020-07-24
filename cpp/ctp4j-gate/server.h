#pragma once

#ifndef __SERVER__
#define __SERVER__

#include "args.h"
#include "service.h"
#include "ws_client.h"

#include <ws2tcpip.h>

#define _call_catch(function)           \
{                                       \
    try {                               \
        function;                       \
    }                                   \
    catch (std::exception& e) {         \
        print(e.what());                \
    }                                   \
    catch (...) {                       \
        print("unknown error");         \
    }                                   \
}

#define default_buff_size (128 * 1024)

class server {
public:
    server(::args& args, ::service& service) : _args(args), _service(service), _listen_socket(INVALID_SOCKET) {}
    virtual ~server() {}

    void run() {
        _init_dirs();
        _ws();
        _listen(_args.get_host().c_str(), _args.get_port().c_str());
        _serve();
        _ws();
    }



protected:
    void _ws() {
        static bool up = false;
        WSADATA wsaData;
        if (!up) {
            if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
                throw ::ws_error(WSAGetLastError());
            up = true;
        }
        else {
            WSACleanup();
        }
    }

    void _listen(const char* host, const char* port) {
        struct addrinfo* result = NULL;
        struct addrinfo hints;

        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family     = AF_INET;
        hints.ai_socktype   = SOCK_STREAM;
        hints.ai_protocol   = IPPROTO_TCP;
        hints.ai_flags      = AI_PASSIVE;

        // Resolve the server address and port
        if (getaddrinfo(host, port, &hints, &result) != 0) {
            WSACleanup();
            throw ws_error(WSAGetLastError());
        }
        _listen_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
        if (_listen_socket == INVALID_SOCKET) {
            freeaddrinfo(result);
            WSACleanup();
            throw ws_error(WSAGetLastError());
        }
        if (bind(_listen_socket, result->ai_addr, (int)result->ai_addrlen) == SOCKET_ERROR) {
            freeaddrinfo(result);
            closesocket(_listen_socket);
            WSACleanup();
            throw ws_error(WSAGetLastError());
        }
        freeaddrinfo(result);
        // Listening.
        if (listen(_listen_socket, SOMAXCONN) == SOCKET_ERROR) {
            closesocket(_listen_socket);
            WSACleanup();
            throw ws_error(WSAGetLastError());
        }
    }

    SOCKET _accept() {
        SOCKET client_socket = INVALID_SOCKET;
        if ((client_socket = accept(_listen_socket, NULL, NULL)) == INVALID_SOCKET) {
            closesocket(_listen_socket);
            WSACleanup();
            throw ws_error(WSAGetLastError());
        }
        _client._set_socket(client_socket);
        return client_socket;
    }

    void _serve() {
        int r;
        SOCKET client;
        char* buffer = new char[default_buff_size];
        while ((client = _accept()) != INVALID_SOCKET) {
            _call_catch(_service.on_open(_client));
            do {
                r = recv(client, buffer, default_buff_size, 0);
                if (r > 0) {
                    _call_catch(_decode_call(buffer, r));
                }
                else {
                    // Socket is closed or error.
                    _call_catch(_service.on_close());
                    _client._set_socket(0);
                    closesocket(client);
                }
            } while (r > 0);
        }
        delete[] buffer;
        closesocket(_listen_socket);
    }

    void _decode_call(const char* buf, int r) {
        if (_decoder.decode(buf, r)) {
            while (_decoder.size() > 0) {
                _call_catch(_call_body());
            }
        }
    }

    void _write_req(const std::string& json) {
        auto file = get_time_str("%Y%m%d%H%M%S") + "_" + std::to_string(add_and_get()) + ".json";
        auto path = _flow_req_dir + "/" + file;
        try {
            std::ofstream osf(path, std::ios::out | std::ios::app);
            osf.write(json.c_str(), json.length());
            osf.flush();
        }
        catch (std::exception& e) {
            print(e.what());
        }
    }

    void _init_dirs() {
        auto path = _get_flow();
        if (!create_directory(path.c_str()))
            _flow_req_dir = "";
        else
            _flow_req_dir = path;
    }

    std::string _get_flow() {
        auto path = _args.get_flow();
        if (path.length() == 0)
            path = ".req\\";
        else if (path.back() == '/' || path.back() == '\\')
            path += ".req" + path.back();
        else
            path += "\\.req\\";
        return path;
    }

    inline void _call_body() {
        ::body body;
        ::frame& frame = _decoder.back();
        body_decoder::decode(frame, body);
        _call_catch(_service.on_body(_client, body));
        _write_req(frame.body);
        _decoder.pop_back();
    }

    SOCKET          _listen_socket;
    std::string     _flow_req_dir;

    ::args&         _args;
    ::service&      _service;
    ::ws_client     _client;
    ::frame_decoder _decoder;
};

#endif
