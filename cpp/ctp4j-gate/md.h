#pragma once

#ifndef __MD__
#define __MD__

#include "server.h"

class md_server : public server {
public:
    md_server(::args& args) : server(args) {
    }

    virtual ~md_server() {}

    virtual void on_body(::body& body) {

    }

    virtual void on_start() {

    }

    virtual void on_close() {

    }
};

#endif