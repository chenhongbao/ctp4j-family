#pragma once

#ifndef __TRADE__
#define __TRADE__

#include "args.h"
#include "service.h"
#include "message.h"

class trade_service : public service {
public:
    trade_service(::args& args) {
    }

    virtual ~trade_service() {}

    virtual void on_body(::body& body) {

    }

    virtual void on_open(::client& client) {

    }

    virtual void on_close() {

    }
};

#endif
