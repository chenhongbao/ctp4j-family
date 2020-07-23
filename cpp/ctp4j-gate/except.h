#pragma once

#ifndef __EXCEPT__
#define __EXCEPT__

#include <stdexcept>
#include <string>

class ctp_error : public std::runtime_error {
public:
	ctp_error(int error) : std::runtime_error("ctp error(" + std::to_string(error) + ")") {
	}

	virtual ~ctp_error() {}
};

class ws_error : public std::runtime_error {
public:
    ws_error(int error) : std::runtime_error("winsock error(" + std::to_string(error) + ")") {
    }

    virtual ~ws_error() {}
};

class message_type_error : public std::runtime_error {
public:
    message_type_error(const std::string msg) : std::runtime_error("bad message type(" + msg + ")") {
    }

    virtual ~message_type_error() {}
};

class json_error : public std::runtime_error {
public:
    json_error(const int code) : std::runtime_error("json error(" + std::to_string(code) + ")") {
    }

    virtual ~json_error() {}
};

class flag_error : public std::runtime_error {
public:
    flag_error(const int flag) : std::runtime_error("bad flag value(" + std::to_string(flag) + ")") {
    }

    virtual ~flag_error() {}
};

class frame_length_error : public std::runtime_error {
public:
    frame_length_error(const int length) : std::runtime_error("frame length(" + std::to_string(length) + ")") {
    }

    virtual ~frame_length_error() {}
};

#endif