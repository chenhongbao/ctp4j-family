#pragma once

#ifndef __TRADE_SPI__
#define __TRADE_SPI__

#include "client.h"
#include "message.h"
#include "id_keeper.h"

#include "ThostFtdcTraderApi.h"

template<typename Ty>
void _to_trade_body(::body& body, const char* type, Ty* object, CThostFtdcRspInfoField* rsp, message_id& id, int count, int total, ::id_keeper& m) {
    try {
        body.request_id = id;
        body.response_id = get_uuid();
        body.current_count = count;
        body.total_count = total;
        body.type = type;
        get_field(*object, body.object);
        get_field(*rsp, body.rsp_info);
    }
    catch (std::exception& e) {
        print(e.what());
    }
}

#define trader_rsp(msg_type, object_ptr, rsp_ptr, nid, is_last, keeper)                                                 \
    if (object_ptr == nullptr) {                                                                                        \
        auto str = std::string(msg_type) + ", ctp rsp null";                                                            \
        print(str.c_str());                                                                                             \
        return;                                                                                                         \
    }                                                                                                                   \
    static int count = 0, total = 0;                                                                                    \
    ::body body;                                                                                                        \
    ::message_id id;                                                                                                    \
    CThostFtdcRspInfoField tmp_rsp{ 0 };                                                                                \
    try {                                                                                                               \
        id = _keeper.get_id(nid);                                                                                       \
        ++count;                                                                                                        \
        if (is_last)                                                                                                    \
            total = count;                                                                                              \
        if (rsp_ptr != nullptr)                                                                                         \
            _to_trade_body(body, msg_type, object_ptr, rsp_ptr, id, count, total, keeper);                              \
        else                                                                                                            \
            _to_trade_body(body, msg_type, object_ptr, &tmp_rsp, id, count, total, keeper);                             \
        _send(body);                                                                                                    \
    }                                                                                                                   \
    catch (std::exception& e) {                                                                                         \
        print(e.what());                                                                                                \
    }                                                                                                                   \
    if (is_last)                                                                                                        \
        count = total = 0;


class trade_spi : public CThostFtdcTraderSpi {
public:
    trade_spi(::client& client, ::id_keeper& keeper) : _client(client), _keeper(keeper) {
        _keeper.put(0, "0");
    }

    virtual void OnFrontConnected() {
        CThostFtdcConnectField conn;
        CThostFtdcRspInfoField rsp_info{ 0 };
        trader_rsp(IOP_MESSAGE_RSP_CONNECT, &conn, &rsp_info, 0, true, _keeper);
    }

    virtual void OnFrontDisconnected(int nReason) {
        CThostFtdcDisconnect disconn;
        CThostFtdcRspInfoField rsp_info{ 0 };
        disconn.Reason = nReason;
        trader_rsp(IOP_MESSAGE_RSP_DISCONNECT, &disconn, &rsp_info, 0, true, _keeper);
    }

    virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField* pRspAuthenticateField, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        trader_rsp(IOP_MESSAGE_RSP_REQ_AUTHENTICATE, pRspAuthenticateField, pRspInfo, nRequestID, bIsLast, _keeper);
    }

    virtual void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        trader_rsp(IOP_MESSAGE_RSP_REQ_LOGIN, pRspUserLogin, pRspInfo, nRequestID, bIsLast, _keeper);
    }

    virtual void OnRspUserLogout(CThostFtdcUserLogoutField* pUserLogout, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        trader_rsp(IOP_MESSAGE_RSP_REQ_LOGOUT, pUserLogout, pRspInfo, nRequestID, bIsLast, _keeper);
    }

    virtual void OnRspOrderInsert(CThostFtdcInputOrderField* pInputOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        trader_rsp(IOP_MESSAGE_RSP_ORDER_INSERT, pInputOrder, pRspInfo, nRequestID, bIsLast, _keeper);
    }

    virtual void OnRspOrderAction(CThostFtdcInputOrderActionField* pInputOrderAction, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        trader_rsp(IOP_MESSAGE_RSP_ORDER_ACTION, pInputOrderAction, pRspInfo, nRequestID, bIsLast, _keeper);
    }

    virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField* pSettlementInfoConfirm, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        trader_rsp(IOP_MESSAGE_RSP_REQ_SETTLEMENT, pSettlementInfoConfirm, pRspInfo, nRequestID, bIsLast, _keeper);
    }

    virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField* pTradingAccount, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        trader_rsp(IOP_MESSAGE_RSP_QRY_ACCOUNT, pTradingAccount, pRspInfo, nRequestID, bIsLast, _keeper);
    }

    virtual void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField* pInstrumentMarginRate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        trader_rsp(IOP_MESSAGE_RSP_QRY_MARGIN, pInstrumentMarginRate, pRspInfo, nRequestID, bIsLast, _keeper);
    }

    virtual void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField* pInstrumentCommissionRate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        trader_rsp(IOP_MESSAGE_RSP_QRY_COMMISSION, pInstrumentCommissionRate, pRspInfo, nRequestID, bIsLast, _keeper);
    }

    virtual void OnRspQryInstrument(CThostFtdcInstrumentField* pInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        trader_rsp(IOP_MESSAGE_RSP_QRY_INSTRUMENT, pInstrument, pRspInfo, nRequestID, bIsLast, _keeper);
    }

    virtual void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField* pInvestorPositionDetail, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        trader_rsp(IOP_MESSAGE_RSP_QRY_POSI_DETAIL, pInvestorPositionDetail, pRspInfo, nRequestID, bIsLast, _keeper);
    }

    virtual void OnRspError(CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        trader_rsp(IOP_MESSAGE_RSP_ERROR, pRspInfo, pRspInfo, nRequestID, bIsLast, _keeper);
    }

    virtual void OnRtnOrder(CThostFtdcOrderField* pOrder) {
        CThostFtdcRspInfoField rsp_info{ 0 };
        trader_rsp(IOP_MESSAGE_RTN_ORDER, pOrder, &rsp_info, 0, true, _keeper);
    }

    virtual void OnRtnTrade(CThostFtdcTradeField* pTrade) {
        CThostFtdcRspInfoField rsp_info{ 0 };
        trader_rsp(IOP_MESSAGE_RTN_TRADE, pTrade, &rsp_info, 0, true, _keeper);
    }

    virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField* pInputOrder, CThostFtdcRspInfoField* pRspInfo) {
        trader_rsp(IOP_MESSAGE_RTN_ORDER_INSERT, pInputOrder, pRspInfo, 0, true, _keeper);
    }

    virtual void OnErrRtnOrderAction(CThostFtdcOrderActionField* pOrderAction, CThostFtdcRspInfoField* pRspInfo) {
        trader_rsp(IOP_MESSAGE_RTN_ORDER_ACTION, pOrderAction, pRspInfo, 0, true, _keeper);
    }

private:
    int _send(::body& body) {
        return (int)_client.send_body(body, IOP_FRAME_RESPONSE);
    }

    ::client& _client;
    ::id_keeper& _keeper;
};

#endif
