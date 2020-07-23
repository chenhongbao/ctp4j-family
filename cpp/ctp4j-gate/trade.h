#pragma once

#ifndef __TRADE__
#define __TRADE__

#include "args.h"
#include "service.h"
#include "trade_spi.h"

#define ctp_req(type, c_str, fname)                     \
{                                                       \
    type req;                                           \
    set_field(req, c_str);                              \
    auto r = _api->fname(&req, add_and_get());          \
    if (r != 0)                                         \
        throw ::ctp_error(r);                           \
}

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
            client.send_body(body, FRAME_HEARTBEAT);
        }
        else if (body.type == MESSAGE_REQ_AUTHENTICATE) {
            ctp_req(CThostFtdcReqAuthenticateField, body.object.c_str(), ReqAuthenticate);
        }
        else if (body.type == MESSAGE_REQ_LOGIN) {
            ctp_req(CThostFtdcReqUserLoginField, body.object.c_str(), ReqUserLogin);
        }
        else if (body.type == MESSAGE_REQ_LOGOUT) {
            ctp_req(CThostFtdcUserLogoutField, body.object.c_str(), ReqUserLogout);
        }
        else if (body.type == MESSAGE_REQ_SETTLEMENT) {
            ctp_req(CThostFtdcSettlementInfoConfirmField, body.object.c_str(), ReqSettlementInfoConfirm);
        }
        else if (body.type == MESSAGE_REQ_ORDER_INSERT) {
            ctp_req(CThostFtdcInputOrderField, body.object.c_str(), ReqOrderInsert);
        }
        else if (body.type == MESSAGE_REQ_ORDER_ACTION) {
            ctp_req(CThostFtdcInputOrderActionField, body.object.c_str(), ReqOrderAction);
        }
        else if (body.type == MESSAGE_QRY_ACCOUNT) {
            ctp_req(CThostFtdcQryTradingAccountField, body.object.c_str(), ReqQryTradingAccount);
        }
        else if (body.type == MESSAGE_QRY_POSI_DETAIL) {
            ctp_req(CThostFtdcQryInvestorPositionDetailField, body.object.c_str(), ReqQryInvestorPositionDetail);
        }
        else if (body.type == MESSAGE_QRY_INSTRUMENT) {
            ctp_req(CThostFtdcQryInstrumentField, body.object.c_str(), ReqQryInstrument);
        }
        else if (body.type == MESSAGE_QRY_COMMISSION) {
            ctp_req(CThostFtdcQryInstrumentCommissionRateField, body.object.c_str(), ReqQryInstrumentCommissionRate);
        }
        else if (body.type == MESSAGE_QRY_MARGIN) {
            ctp_req(CThostFtdcQryInstrumentMarginRateField, body.object.c_str(), ReqQryInstrumentMarginRate);
        }
        else
            throw ::message_type_error(body.type);
    }

    virtual void on_open(::client& client) {
        _spi = new trade_spi(client);
        _init_flow_dirs();
        _init_api();
    }

    virtual void on_close() {
        _release_api();
        delete _spi;
        _spi = nullptr;
    }

protected:
    void _init_api() {
        _api = CThostFtdcTraderApi::CreateFtdcTraderApi(_flow_dir.c_str());
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

    void _init_flow_dirs() {
        auto path = _args.get_flow() + "/.trade";
        if (!create_directory(path.c_str()))
            _flow_dir = "";
        else
            _flow_dir = path;
    }

    std::string             _flow_dir;

    ::CThostFtdcTraderApi*  _api;
    ::trade_spi*            _spi;
    ::args&                 _args;
    ::frame_encoder         _frame_encoder;
};

#endif
