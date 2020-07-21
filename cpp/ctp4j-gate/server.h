#pragma once

#ifndef __SERVER__
#define __SERVER__

#include "args.h"
#include "service.h"
#include "ws_client.h"

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
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
                throw std::runtime_error("winsock error(" + std::to_string(WSAGetLastError()));
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
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = AI_PASSIVE;

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
            _call_catch(_service.on_open());
            do {
                r = recv(client, buffer, default_buff_size, 0);
                if (r > 0) {
                    _call_catch(_decode_call(buffer, r));
                }
                else {
                    // Socket is closed or error.
                    _client._set_socket(0);
                    closesocket(client);
                }
            } while (r > 0);
            _call_catch(_service.on_close());
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

    inline void _call_body() {
        ::body body;
        body_decoder::decode(_decoder.back(), body);
        _call_catch(_service.on_body(body));
        _decoder.pop_back();
    }

    SOCKET _listen_socket;
    ::args& _args;
    ::service& _service;
    ::ws_client _client;
    ::frame_decoder _decoder;
};

#endif
