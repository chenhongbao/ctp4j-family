#pragma once
#ifndef __NN_CLIENT__
#define __NN_CLIENT__

#include "client.h"

#include <winsock2.h>

#include <stdexcept>
#include <string>
#include <mutex>

class ws_error : public std::runtime_error {
public:
    ws_error(int error) : std::runtime_error("winsock error(" + std::to_string(error) + ")") {
    }

    virtual ~ws_error() {}
};

class ws_client : public client {
public:
    ws_client() : _socket(0) {}

    virtual ~ws_client() {}

    virtual int c_send(const char* src, const int length) {
        std::unique_lock<std::mutex> lock(_send_mutex);
        int sent = 0;
        while (sent < length) {
            int r = 0;
            if ((r = send(_socket, src + sent, length - sent, 0)) == SOCKET_ERROR)
                throw ws_error(WSAGetLastError());
            sent += r;
        }
        return sent;
    }

    bool is_valid() {
        std::unique_lock<std::mutex> lock(_send_mutex);
        return _socket != 0;
    }

    void close() {
        std::unique_lock<std::mutex> lock(_send_mutex);
        if (is_valid()) {
            closesocket(_socket);
            _socket = 0;
        }
    }

    friend class server;

protected:
    void _set_socket(SOCKET sock) {
        std::unique_lock<std::mutex> lock(_send_mutex);
        _socket = sock;
    }

private:
    SOCKET _socket;
    std::mutex _send_mutex;
};

#endif
