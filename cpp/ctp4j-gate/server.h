#pragma once

#ifndef __SERVER__
#define __SERVER__

#include "args.h"
#include "message.h"
#include "nn_client.h"

#define _call_catch(function)           \
{                                       \
    try {                               \
        function;                       \
    }                                   \
    catch (std::exception& e) {         \
        print(e.what());                \
    }                                   \
    catch (...) {                       \
        print("unknown exception");     \
    }                                   \
}

class server {
public:
    server(::args& args) : _args(args) {}
    virtual ~server() {}

    void run() {
        int eid = -1, r = -1;
        char* buf = NULL;
        _call_catch(on_start());
        auto bind_addr = _get_bind_addr();
        auto socket = nn_socket(AF_SP, NN_TCP);
        if ((eid = nn_bind(socket, bind_addr.c_str())) < 0)
            throw std::runtime_error(nn_strerror(errno));
        // Set the client's socket.
        _client._set_nn_socket(socket);
        while ((r = nn_recv(socket, buf, NN_MSG, 0)) > 0) {
            _call_catch(_decode_call(buf, r));
            nn_freemsg(buf);
        }
        nn_shutdown(socket, eid);
        _call_catch(on_close());
    }

    virtual void on_start() = 0;
    virtual void on_body(::body& body) = 0;
    virtual void on_close() = 0;

protected:
    std::string _get_bind_addr() {
        return "tcp://" + _args.get_host() + ":" + std::to_string(_args.get_port());
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
        _call_catch(on_body(body));
        _decoder.pop_back();
    }

    ::args& _args;
    ::nn_client _client;
    ::frame_decoder _decoder;
};

#endif
