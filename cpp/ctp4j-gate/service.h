#pragma once

#ifndef __SERVICE__
#define __SERVICE__

struct body;

class service {
public:
    virtual void on_open() = 0;
    virtual void on_body(::body& body) = 0;
    virtual void on_close() = 0;
};

#endif
