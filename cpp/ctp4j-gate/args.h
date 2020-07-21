#pragma once

#ifndef __ARGS__
#define __ARGS__

#include <string>
#include <vector>

enum class app_mode : char {
    trade, md, unknown
};

class args {
public:
    args(int argc, char** argv)
        : _use_udp(false), _multicast(false), _mode(app_mode::unknown) {
        _parse(argc, argv);
    }

    virtual ~args() {}

    bool use_udp() {
        return _use_udp;
    }

    bool is_multicast() {
        return _multicast;
    }

    bool is_help() {
        return _help;
    }

    app_mode get_mode() {
        return _mode;
    }

    const std::string& get_flow() {
        return _flow;
    }

    const std::string& get_host() {
        return _host;
    }

    const std::string& get_port() {
        return _port;
    }

    const std::vector<std::string>& get_fronts() {
        return _fronts;
    }

protected:
    void _parse(int argc, char** argv) {
        // UDP and multicast.
        _use_udp = _check_arg("--udp", argc, argv);
        _multicast = _check_arg("--multicast", argc, argv);
        // help.
        _help = _check_arg("--help", argc, argv);
        // mode.
        if (_check_arg("--trade", argc, argv))
            _mode = app_mode::trade;
        else if (_check_arg("--md", argc, argv))
            _mode = app_mode::md;
        // host and port.
        const char* p;
        p = _get_arg("--host", argc, argv);
        if (p == nullptr)
            _host = "localhost";
        else
            _host = p;
        p = _get_arg("--port", argc, argv);
        if (p == nullptr)
            _port = "9036";
        else
            _port = p;
        // flow.
        p = _get_arg("--flow", argc, argv);
        if (p == nullptr)
            _flow = ".";
        else
            _flow = p;
        // front addresses.
        p = _get_arg("--front", argc, argv);
        if (p != nullptr)
            _parse_front(p);
    }

    const char* _get_arg(const char* prefix, int argc, char** argv) {
        int i = 0;
        for (i = 0; i < argc; ++i)
            if (strcmp(argv[i], prefix) == 0)
                break;
        if (i < argc - 1) {
            return argv[i + 1];
        }
        else
            return nullptr;
    }

    bool _check_arg(const char* prefix, int argc, char** argv) {
        for (int i = 0; i < argc; ++i)
            if (strcmp(argv[i], prefix) == 0)
                return true;
        return false;
    }

    void _parse_front(const char* fronts) {
        char* token         = NULL;
        char* next_token    = NULL;
        int size            = (int)strlen(fronts) + 1;
        if (size < 2)
            return;
        char* buffer = new char[size] { 0 };
        strcpy_s(buffer, size, fronts);
        token = strtok_s(buffer, ",", &next_token);
        while (token) {
            _fronts.push_back(token);
            token = strtok_s(NULL, ",", &next_token);
        }
    }

    bool                        _use_udp, _multicast, _help;
    app_mode                    _mode;
    std::string                 _flow, _host, _port;
    std::vector<std::string>    _fronts;
};

#endif