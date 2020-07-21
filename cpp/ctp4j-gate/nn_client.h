#pragma once
#ifndef __NN_CLIENT__
#define __NN_CLIENT__

#include "client.h"
#include "nanomsg/nn.h"
#include "nanomsg/tcp.h"

class nn_client : public client {
public:
    nn_client() : _nn_sock(-1) {}

    virtual ~nn_client() {}

    virtual int send(const char* src, const int length) {
        if (is_valid())
            return nn_send(_nn_sock, src, length, 0);
        else
            return -1;
    }

    bool is_valid() {
        return _nn_sock > 0;
    }

    friend class server;

protected:
    void _set_nn_socket(int sock) {
        _nn_sock = sock;
    }

private:
    int _nn_sock;
};

#endif
