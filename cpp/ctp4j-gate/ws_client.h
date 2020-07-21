#pragma once
#ifndef __NN_CLIENT__
#define __NN_CLIENT__

#include "client.h"
#include "message.h"

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

    virtual size_t send_body(::body& body, __int32 frame_type) {
        std::unique_lock<std::mutex> lock(_send_mutex);
        _json.clear();
        ::body_encoder::encode(body, _encoding, frame_type);
        ::frame_encoder::encode(_encoding, _json);
        return _send(_json.c_str(), _json.length());
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
    size_t _send(const char* src, const size_t length) {
        if (!is_valid())
            return SOCKET_ERROR;
        std::unique_lock<std::mutex> lock(_send_mutex);
        size_t sent = 0;
        while (sent < length) {
            int r = 0;
            if ((r = send(_socket, src + sent, (int)(length - sent), 0)) < 0) {
                _set_socket(0);
                throw ws_error(WSAGetLastError());
            }
            sent += r;
        }
        return sent;
    }

    void _set_socket(SOCKET sock) {
        std::unique_lock<std::mutex> lock(_send_mutex);
        _socket = sock;
    }

private:
    SOCKET      _socket;
    std::mutex  _send_mutex;
    ::frame     _encoding;
    std::string _json;
};

#endif
