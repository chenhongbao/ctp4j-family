#pragma once

#ifndef __TRADE__
#define __TRADE__

#include "args.h"
#include "service.h"
#include "trade_spi.h"

using namespace std::placeholders;

class trade_service : public service {
public:
    trade_service(::args& args) : _spi(nullptr), _api(nullptr), _args(args) {
        _init_flow_dirs();
    }

    virtual ~trade_service() {}

    virtual void on_body(::client& client, ::body& body) {
        auto rsp_cb = std::bind(&CThostFtdcTraderSpi::OnRspError, _spi, _1, _2, _3);
        ::frame rsp_frame;
        if (body.type == IOP_MESSAGE_HEARTBEAT) {
            // Send back the heartbeat with a new response ID.
            body.response_id = get_uuid();
            client.send_body(body, IOP_FRAME_HEARTBEAT);
        }
        else if (body.type == IOP_MESSAGE_REQ_AUTHENTICATE) {
            ctp_req<CThostFtdcReqAuthenticateField, CThostFtdcRspInfoField>(
                body.object.c_str(),
                std::bind(&CThostFtdcTraderApi::ReqAuthenticate, _api, _1, _2), 
                rsp_cb,
                body.request_id,
                _id);
        }
        else if (body.type == IOP_MESSAGE_REQ_LOGIN) {
            ctp_req<CThostFtdcReqUserLoginField, CThostFtdcRspInfoField>(
                body.object.c_str(),
                std::bind(&CThostFtdcTraderApi::ReqUserLogin, _api, _1, _2),
                rsp_cb,
                body.request_id,
                _id);
        }
        else if (body.type == IOP_MESSAGE_REQ_LOGOUT) {
            ctp_req<CThostFtdcUserLogoutField, CThostFtdcRspInfoField>(
                body.object.c_str(),
                std::bind(&CThostFtdcTraderApi::ReqUserLogout, _api, _1, _2),
                rsp_cb,
                body.request_id,
                _id);
        }
        else if (body.type == IOP_MESSAGE_REQ_SETTLEMENT) {
            ctp_req<CThostFtdcSettlementInfoConfirmField, CThostFtdcRspInfoField>(
                body.object.c_str(),
                std::bind(&CThostFtdcTraderApi::ReqSettlementInfoConfirm, _api, _1, _2),
                rsp_cb,
                body.request_id,
                _id);
        }
        else if (body.type == IOP_MESSAGE_REQ_ORDER_INSERT) {
            ctp_order_req<CThostFtdcInputOrderField, CThostFtdcRspInfoField>(
                body.object.c_str(),
                std::bind(&CThostFtdcTraderApi::ReqOrderInsert, _api, _1, _2),
                std::bind(&CThostFtdcTraderSpi::OnRspOrderInsert, _spi, _1, _2, _3, _4),
                body.request_id,
                _id);
        }
        else if (body.type == IOP_MESSAGE_REQ_ORDER_ACTION) {
            ctp_order_req<CThostFtdcInputOrderActionField, CThostFtdcRspInfoField>(
                body.object.c_str(),
                std::bind(&CThostFtdcTraderApi::ReqOrderAction, _api, _1, _2),
                std::bind(&CThostFtdcTraderSpi::OnRspOrderAction, _spi, _1, _2, _3, _4),
                body.request_id,
                _id);
        }
        else if (body.type == IOP_MESSAGE_QRY_ACCOUNT) {
            ctp_req<CThostFtdcQryTradingAccountField, CThostFtdcRspInfoField>(
                body.object.c_str(),
                std::bind(&CThostFtdcTraderApi::ReqQryTradingAccount, _api, _1, _2),
                rsp_cb,
                body.request_id,
                _id);
        }
        else if (body.type == IOP_MESSAGE_QRY_POSI_DETAIL) {
            ctp_req<CThostFtdcQryInvestorPositionDetailField, CThostFtdcRspInfoField>(
                body.object.c_str(),
                std::bind(&CThostFtdcTraderApi::ReqQryInvestorPositionDetail, _api, _1, _2),
                rsp_cb,
                body.request_id,
                _id);
        }
        else if (body.type == IOP_MESSAGE_QRY_INSTRUMENT) {
            ctp_req<CThostFtdcQryInstrumentField, CThostFtdcRspInfoField>(
                body.object.c_str(),
                std::bind(&CThostFtdcTraderApi::ReqQryInstrument, _api, _1, _2),
                rsp_cb,
                body.request_id,
                _id);
        }
        else if (body.type == IOP_MESSAGE_QRY_COMMISSION) {
            ctp_req<CThostFtdcQryInstrumentCommissionRateField, CThostFtdcRspInfoField>(
                body.object.c_str(),
                std::bind(&CThostFtdcTraderApi::ReqQryInstrumentCommissionRate, _api, _1, _2),
                rsp_cb,
                body.request_id,
                _id);
        }
        else if (body.type == IOP_MESSAGE_QRY_MARGIN) {
            ctp_req<CThostFtdcQryInstrumentMarginRateField, CThostFtdcRspInfoField>(
                body.object.c_str(),
                std::bind(&CThostFtdcTraderApi::ReqQryInstrumentMarginRate, _api, _1, _2),
                rsp_cb,
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
