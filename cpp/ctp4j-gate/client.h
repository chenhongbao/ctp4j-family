#pragma once

#ifndef __CLIENT__
#define __CLIENT__

class client {
public:
    virtual int c_send(const char* src, const int length) = 0;
    virtual ~client() {}
};

#endif
