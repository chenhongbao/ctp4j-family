#pragma once

#ifndef __CLIENT__
#define __CLIENT__

struct body;

class client {
public:
    virtual size_t send_body(::body& body, __int32 frame_type) = 0;
    virtual ~client() {}
};

#endif
