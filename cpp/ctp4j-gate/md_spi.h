#pragma once

#ifndef __MD_SPI__
#define __MD_SPI__

#include "client.h"
#include "message.h"
#include "id_keeper.h"

#include "ThostFtdcMdApi.h"

template<typename Ty>
void _to_md_body(::body& body, const char* type, Ty* object, CThostFtdcRspInfoField* rsp, message_id& id, int count, int total, ::id_keeper& m) {
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

#define md_rsp(msg_type, object_ptr, rsp_ptr, nid, is_last, keeper)                                                     \
    static int count = 0, total = 0;                                                                                    \
    ::body body;                                                                                                        \
    ::message_id id;                                                                                                    \
    try {                                                                                                               \
        id = _keeper.get_id(nid);                                                                                       \
        ++count;                                                                                                        \
        if (is_last)                                                                                                    \
            total = count;                                                                                              \
        _to_md_body(body, msg_type, object_ptr, rsp_ptr, id, count, total, keeper);                                     \
        _send(body);                                                                                                    \
    }                                                                                                                   \
    catch (std::exception& e) {                                                                                         \
        print(e.what());                                                                                                \
    }                                                                                                                   \
    if (is_last)                                                                                                        \
        count = total = 0;

class md_spi : public CThostFtdcMdSpi {
public:
    md_spi(::client& client, ::id_keeper& keeper) : _client(client), _keeper(keeper) {
        _keeper.put(0, "00000000-0000-0000-0000-000000000000");
    }

    virtual ~md_spi() {}

    virtual void OnFrontConnected() {
        CThostFtdcConnectField conn;
        CThostFtdcRspInfoField rsp_info{ 0 };
        md_rsp(IOP_MESSAGE_RSP_CONNECT, &conn, &rsp_info, 0, true, _keeper);
    }

    virtual void OnFrontDisconnected(int nReason) {
        CThostFtdcDisconnect disconn;
        CThostFtdcRspInfoField rsp_info{ 0 };
        disconn.Reason = nReason;
        md_rsp(IOP_MESSAGE_RSP_DISCONNECT, &disconn, &rsp_info, 0, true, _keeper);
    }

    virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField* pRspAuthenticateField, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        md_rsp(IOP_MESSAGE_RSP_REQ_AUTHENTICATE, pRspAuthenticateField, pRspInfo, nRequestID, bIsLast, _keeper);
    }

    virtual void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        md_rsp(IOP_MESSAGE_RSP_REQ_LOGIN, pRspUserLogin, pRspInfo, nRequestID, bIsLast, _keeper);
    }

    virtual void OnRspUserLogout(CThostFtdcUserLogoutField* pUserLogout, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        md_rsp(IOP_MESSAGE_RSP_REQ_LOGOUT, pUserLogout, pRspInfo, nRequestID, bIsLast, _keeper);
    }

    virtual void OnRspError(CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        md_rsp(IOP_MESSAGE_RSP_ERROR, pRspInfo, pRspInfo, nRequestID, bIsLast, _keeper);
    }

    virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        md_rsp(IOP_MESSAGE_RSP_SUB_MD, pSpecificInstrument, pRspInfo, nRequestID, bIsLast, _keeper);
    }

    virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        md_rsp(IOP_MESSAGE_RSP_UNSUB_MD, pSpecificInstrument, pRspInfo, nRequestID, bIsLast, _keeper);
    }

    virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData) {
        CThostFtdcRspInfoField rsp_info{ 0 };
        md_rsp(IOP_MESSAGE_FLOW_DEPTH, pDepthMarketData, &rsp_info, 0, true, _keeper);
    }

private:
    int _send(::body& body) {
        return (int)_client.send_body(body, IOP_FRAME_RESPONSE);
    }

    ::client&       _client;
    ::id_keeper&    _keeper;
};

#endif