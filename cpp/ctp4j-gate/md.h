#pragma once

#ifndef __MD__
#define __MD__

#include "args.h"
#include "service.h"
#include "md_spi.h"

using namespace std::placeholders;

class md_service : public service {
public:
    md_service(::args& args) : _spi(nullptr), _api(nullptr), _args(args) {
        _init_flow_dirs();
    }

    virtual ~md_service() {}

    virtual void on_body(::client& client, ::body& body) {
        auto rsp_cb = std::bind(&CThostFtdcMdSpi::OnRspError, _spi, _1, _2, _3);
        ::frame rsp_frame;
        if (body.type == IOP_MESSAGE_HEARTBEAT) {
            // Send back the heartbeat with a new response ID.
            body.response_id = get_uuid();
            client.send_body(body, IOP_FRAME_HEARTBEAT);
        }
        else if (body.type == IOP_MESSAGE_REQ_LOGIN) {
            ctp_req<CThostFtdcReqUserLoginField>(
                body.object.c_str(),
                std::bind(&CThostFtdcMdApi::ReqUserLogin, _api, _1, _2),
                rsp_cb,
                body.request_id,
                _id);
        }
        else if (body.type == IOP_MESSAGE_REQ_LOGOUT) {
            ctp_req<CThostFtdcUserLogoutField>(
                body.object.c_str(),
                std::bind(&CThostFtdcMdApi::ReqUserLogout, _api, _1, _2),
                rsp_cb,
                body.request_id,
                _id);
        }
        else if (body.type == IOP_MESSAGE_SUB_MD) {
            CThostFtdcSubMarketDataField sub;
            set_field(sub, body.object.c_str());
            auto r = _api->SubscribeMarketData(sub.InstrumentID, sub.Count);
            release_md(sub);
            if (r != 0)
                throw ::ctp_error(r);
        }
        else if (body.type == IOP_MESSAGE_UNSUB_MD) {
            CThostFtdcUnsubMarketDataField unsub;
            set_field(unsub, body.object.c_str());
            auto r = _api->SubscribeMarketData(unsub.InstrumentID, unsub.Count);
            release_md(unsub);
            if (r != 0)
                throw ::ctp_error(r);
        }
        else
            throw ::message_type_error(body.type);
    }

    virtual void on_open(::client& client) {
        _spi = new md_spi(client, _id);
        _init_api();
    }

    virtual void on_close() {
        _release_api();
        delete _spi;
        _spi = nullptr;
    }

protected:
    void _init_api() {
        _api = CThostFtdcMdApi::CreateFtdcMdApi(_flow_dir.c_str(), _args.use_udp(), _args.is_multicast());
        _api->RegisterSpi(_spi);
        // Set front addresses.
        char addr[32]{ 0 };
        for (auto& a : _args.get_fronts()) {
            strcpy_s(addr, sizeof(addr), a.c_str());
            _api->RegisterFront(addr);
            memset(addr, 0, sizeof(addr));
        }
        _api->Init();
    }

    void _release_api() {
        _api->Release();
        _api = nullptr;
    }

    void _init_flow_dirs() {
        auto path = _get_flow();
        if (!create_directory(path.c_str()))
            _flow_dir = "";
        else
            _flow_dir = path;
    }

    std::string _get_flow() {
        auto path = _args.get_flow();
        if (path.length() == 0)
            path = ".md\\";
        else if (path.back() == '/' || path.back() == '\\')
            path += ".md" + path.back();
        else
            path += "\\.md\\";
        return path;
    }

    std::string             _flow_dir;

    ::CThostFtdcMdApi*      _api;
    ::md_spi*               _spi;
    ::args&                 _args;
    ::frame_encoder         _frame_encoder;
    ::id_keeper             _id;
};

#endif