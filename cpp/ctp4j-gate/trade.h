#pragma once

#ifndef __TRADE__
#define __TRADE__

#include "args.h"
#include "service.h"
#include "trade_spi.h"

class trade_service : public service {
public:
    trade_service(::args& args) : _spi(nullptr), _api(nullptr), _args(args) {
    }

    virtual ~trade_service() {}

    virtual void on_body(::client& client, ::body& body) {
        ::frame rsp_frame;
        if (body.type == MESSAGE_HEARTBEAT) {
            // Send back the heartbeat with a new response ID.
            body.response_id = get_uuid();
            int s = client.send_body(body, FRAME_HEARTBEAT);
        }
        else if (body.type == MESSAGE_SUB_MD) {

        }
        else if (body.type == MESSAGE_UNSUB_MD) {

        }
        else if (body.type == MESSAGE_REQ_AUTHENTICATE) {

        }
        else if (body.type == MESSAGE_REQ_LOGIN) {

        }
        else if (body.type == MESSAGE_REQ_LOGOUT) {

        }
        else if (body.type == MESSAGE_REQ_SETTLEMENT) {

        }
        else if (body.type == MESSAGE_REQ_ORDER_INSERT) {

        }
        else if (body.type == MESSAGE_REQ_ORDER_ACTION) {

        }
        else if (body.type == MESSAGE_QRY_ACCOUNT) {

        }
        else if (body.type == MESSAGE_QRY_ORDER) {

        }
        else if (body.type == MESSAGE_QRY_POSI_DETAIL) {

        }
        else if (body.type == MESSAGE_QRY_INSTRUMENT) {

        }
        else if (body.type == MESSAGE_QRY_COMMISSION) {

        }
        else if (body.type == MESSAGE_QRY_MARGIN) {

        }
        else {

        }
    }

    virtual void on_open(::client& client) {
        _spi = new trade_spi(client);
        _init_api();
    }

    virtual void on_close() {
        _release_api();
        delete _spi;
        _spi = nullptr;
    }

protected:
    void _init_api() {
        _api = CThostFtdcTraderApi::CreateFtdcTraderApi(_get_flow().c_str());
        _api->RegisterSpi(_spi);
        _api->SubscribePrivateTopic(THOST_TERT_RESUME);
        _api->SubscribePublicTopic(THOST_TERT_RESUME);
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

    std::string _get_flow() {
        auto path = _args.get_flow() + "/.trade";
        if (!create_directory(path.c_str()))
            return "";
        else
            return path;
    }

    int _send_body() {

    }

    ::CThostFtdcTraderApi*  _api;
    ::trade_spi*            _spi;
    ::args&                 _args;
    ::frame_encoder         _frame_encoder;
};

#endif
