#pragma once

#ifndef __MD__
#define __MD__

#include "args.h"
#include "service.h"
#include "message.h"

class md_service : public service {
public:
    md_service(::args& args) {
    }

    virtual ~md_service() {}

    virtual void on_body(::body& body) {

    }

    virtual void on_open(::client& client) {

    }

    virtual void on_close() {

    }
};

#endif