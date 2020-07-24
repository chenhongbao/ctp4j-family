#pragma once

#ifndef __MD_SPI__
#define __MD_SPI__

#include "client.h"
#include "message.h"
#include "id_keeper.h"
#include "spi_common.h"

#include "ThostFtdcMdApi.h"

class md_spi : public CThostFtdcMdSpi {
public:
    md_spi(::client& client, ::id_keeper& keeper) : _client(client), _keeper(keeper) {
        _keeper.put(0, "0");
    }

    virtual ~md_spi() {}

    virtual void OnFrontConnected() {
        CThostFtdcConnectField conn;
        CThostFtdcRspInfoField rsp_info{ 0 };
        spi_rsp(IOP_MESSAGE_RSP_CONNECT, &conn, &rsp_info, 0, true, _keeper, _client);
    }

    virtual void OnFrontDisconnected(int nReason) {
        CThostFtdcDisconnect disconn;
        CThostFtdcRspInfoField rsp_info{ 0 };
        disconn.Reason = nReason;
        spi_rsp(IOP_MESSAGE_RSP_DISCONNECT, &disconn, &rsp_info, 0, true, _keeper, _client);
    }

    virtual void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        spi_rsp(IOP_MESSAGE_RSP_REQ_LOGIN, pRspUserLogin, pRspInfo, nRequestID, bIsLast, _keeper, _client);
    }

    virtual void OnRspUserLogout(CThostFtdcUserLogoutField* pUserLogout, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        spi_rsp(IOP_MESSAGE_RSP_REQ_LOGOUT, pUserLogout, pRspInfo, nRequestID, bIsLast, _keeper, _client);
    }

    virtual void OnRspError(CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        spi_rsp(IOP_MESSAGE_RSP_ERROR, pRspInfo, pRspInfo, nRequestID, bIsLast, _keeper, _client);
    }

    virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        spi_rsp(IOP_MESSAGE_RSP_SUB_MD, pSpecificInstrument, pRspInfo, nRequestID, bIsLast, _keeper, _client);
    }

    virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        spi_rsp(IOP_MESSAGE_RSP_UNSUB_MD, pSpecificInstrument, pRspInfo, nRequestID, bIsLast, _keeper, _client);
    }

    virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData) {
        CThostFtdcRspInfoField rsp_info{ 0 };
        spi_rsp(IOP_MESSAGE_FLOW_DEPTH, pDepthMarketData, &rsp_info, 0, true, _keeper, _client);
    }

private:
    ::client&       _client;
    ::id_keeper&    _keeper;
};

#endif