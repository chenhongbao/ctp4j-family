#pragma once

#ifndef __TRADE__
#define __TRADE__

#include "args.h"
#include "service.h"
#include "trade_spi.h"

class trade_service : public service {
public:
    trade_service(::args& args) : _spi(nullptr), _api(nullptr), _args(args) {
        _init_flow_dirs();
    }

    virtual ~trade_service() {}

#define trade_ctp_req(type, c_str, fname, id, m)        \
{                                                       \
    type req{ 0 };                                      \
    set_field(req, c_str);                              \
    auto nid = add_and_get();                           \
    m.put(nid, id);                                     \
    auto r = _api->fname(&req, nid);                    \
    if (r != 0)                                         \
        throw ::ctp_error(r);                           \
}

    virtual void on_body(::client& client, ::body& body) {
        ::frame rsp_frame;
        if (body.type == IOP_MESSAGE_HEARTBEAT) {
            // Send back the heartbeat with a new response ID.
            body.response_id = get_uuid();
            client.send_body(body, IOP_FRAME_HEARTBEAT);
        }
        else if (body.type == IOP_MESSAGE_REQ_AUTHENTICATE) {
            trade_ctp_req(
                CThostFtdcReqAuthenticateField,
                body.object.c_str(),
                ReqAuthenticate,
                body.request_id,
                _id);
        }
        else if (body.type == IOP_MESSAGE_REQ_LOGIN) {
            trade_ctp_req(
                CThostFtdcReqUserLoginField,
                body.object.c_str(),
                ReqUserLogin,
                body.request_id,
                _id);
        }
        else if (body.type == IOP_MESSAGE_REQ_LOGOUT) {
            trade_ctp_req(CThostFtdcUserLogoutField,
                body.object.c_str(),
                ReqUserLogout,
                body.request_id,
                _id);
        }
        else if (body.type == IOP_MESSAGE_REQ_SETTLEMENT) {
            trade_ctp_req(
                CThostFtdcSettlementInfoConfirmField,
                body.object.c_str(),
                ReqSettlementInfoConfirm,
                body.request_id,
                _id);
        }
        else if (body.type == IOP_MESSAGE_REQ_ORDER_INSERT) {
            /*
            trade_ctp_req(
                CThostFtdcInputOrderField,
                body.object.c_str(),
                ReqOrderInsert,
                body.request_id,
                _id);
                */
            CThostFtdcInputOrderField req;
            set_field(req, body.object.c_str());
            auto nid = add_and_get();
            _id.put(nid, body.request_id);
            auto r = _api->ReqOrderInsert(&req, nid);
            if (r != 0)
                throw ::ctp_error(r);
        }
        else if (body.type == IOP_MESSAGE_REQ_ORDER_ACTION) {
            trade_ctp_req(
                CThostFtdcInputOrderActionField,
                body.object.c_str(),
                ReqOrderAction,
                body.request_id,
                _id);
        }
        else if (body.type == IOP_MESSAGE_QRY_ACCOUNT) {
            trade_ctp_req(
                CThostFtdcQryTradingAccountField,
                body.object.c_str(),
                ReqQryTradingAccount,
                body.request_id,
                _id);
        }
        else if (body.type == IOP_MESSAGE_QRY_POSI_DETAIL) {
            trade_ctp_req(
                CThostFtdcQryInvestorPositionDetailField,
                body.object.c_str(),
                ReqQryInvestorPositionDetail,
                body.request_id,
                _id);
        }
        else if (body.type == IOP_MESSAGE_QRY_INSTRUMENT) {
            trade_ctp_req(
                CThostFtdcQryInstrumentField,
                body.object.c_str(),
                ReqQryInstrument,
                body.request_id,
                _id);      
        }
        else if (body.type == IOP_MESSAGE_QRY_COMMISSION) {
            trade_ctp_req(
                CThostFtdcQryInstrumentCommissionRateField,
                body.object.c_str(),
                ReqQryInstrumentCommissionRate,
                body.request_id,
                _id);
        }
        else if (body.type == IOP_MESSAGE_QRY_MARGIN) {
            trade_ctp_req(
                CThostFtdcQryInstrumentMarginRateField,
                body.object.c_str(),
                ReqQryInstrumentMarginRate,
                body.request_id,
                _id);
        }
        else
            throw ::message_type_error(body.type);
    }

    virtual void on_open(::client& client) {
        _spi = new trade_spi(client, _id);
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
        auto path = _get_flow();
        if (!create_directory(path.c_str()))
            _flow_dir = "";
        else
            _flow_dir = path;
    }

    std::string _get_flow() {
        auto path = _args.get_flow();
        if (path.length() == 0)
            path = ".trader\\";
        else if (path.back() == '/' || path.back() == '\\')
            path += ".trade" + path.back();
        else
            path += "\\.trade\\";
        return path;
    }

    std::string             _flow_dir;

    ::CThostFtdcTraderApi* _api;
    ::trade_spi* _spi;
    ::args& _args;
    ::frame_encoder         _frame_encoder;
    ::id_keeper             _id;
};

#endif
