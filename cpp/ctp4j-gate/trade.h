#pragma once

#ifndef __TRADE__
#define __TRADE__

#include "server.h"

class trade_server : public server {
public:
    trade_server(::args& args) : server(args) {
    }

    virtual ~trade_server() {}

    virtual void on_body(::body& body) {

    }

    virtual void on_start() {

    }

    virtual void on_close() {

    }
};

#endif
