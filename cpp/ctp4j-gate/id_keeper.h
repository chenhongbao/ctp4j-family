#pragma once

#ifndef __ID_KEEPER__
#define __ID_KEEPER__

#include "except.h"

#include <map>
#include <mutex>

class id_keeper {
public:
    id_keeper() {
    }

    virtual ~id_keeper() {}

    void put(int n_id, const std::string& id) {
        std::unique_lock<std::mutex> lock(_mutex);
        _id.emplace(n_id, id);
    }

    const std::string& get_id(int n_id) {
        auto iter = _id.find(n_id);
        if (iter == _id.end())
            throw ::nid_not_found(n_id);
        else
            return iter->second;
    }

private:
    std::mutex                  _mutex;
    std::map<int, std::string>  _id;
};

#endif