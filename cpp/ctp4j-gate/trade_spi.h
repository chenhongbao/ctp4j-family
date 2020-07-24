#pragma once

#ifndef __TRADE_SPI__
#define __TRADE_SPI__

#include "client.h"
#include "message.h"
#include "id_keeper.h"
#include "spi_common.h"

#include "ThostFtdcTraderApi.h"

class trade_spi : public CThostFtdcTraderSpi {
public:
    trade_spi(::client& client, ::id_keeper& keeper) : _client(client), _keeper(keeper) {
        _keeper.put(0, "0");
    }

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

    virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField* pRspAuthenticateField, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        spi_rsp(IOP_MESSAGE_RSP_REQ_AUTHENTICATE, pRspAuthenticateField, pRspInfo, nRequestID, bIsLast, _keeper, _client);
    }

    virtual void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        spi_rsp(IOP_MESSAGE_RSP_REQ_LOGIN, pRspUserLogin, pRspInfo, nRequestID, bIsLast, _keeper, _client);
    }

    virtual void OnRspUserLogout(CThostFtdcUserLogoutField* pUserLogout, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        spi_rsp(IOP_MESSAGE_RSP_REQ_LOGOUT, pUserLogout, pRspInfo, nRequestID, bIsLast, _keeper, _client);
    }

    virtual void OnRspOrderInsert(CThostFtdcInputOrderField* pInputOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        spi_rsp(IOP_MESSAGE_RSP_ORDER_INSERT, pInputOrder, pRspInfo, nRequestID, bIsLast, _keeper, _client);
    }

    virtual void OnRspOrderAction(CThostFtdcInputOrderActionField* pInputOrderAction, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        spi_rsp(IOP_MESSAGE_RSP_ORDER_ACTION, pInputOrderAction, pRspInfo, nRequestID, bIsLast, _keeper, _client);
    }

    virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField* pSettlementInfoConfirm, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        spi_rsp(IOP_MESSAGE_RSP_REQ_SETTLEMENT, pSettlementInfoConfirm, pRspInfo, nRequestID, bIsLast, _keeper, _client);
    }

    virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField* pTradingAccount, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        spi_rsp(IOP_MESSAGE_RSP_QRY_ACCOUNT, pTradingAccount, pRspInfo, nRequestID, bIsLast, _keeper, _client);
    }

    virtual void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField* pInstrumentMarginRate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        spi_rsp(IOP_MESSAGE_RSP_QRY_MARGIN, pInstrumentMarginRate, pRspInfo, nRequestID, bIsLast, _keeper, _client);
    }

    virtual void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField* pInstrumentCommissionRate, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        spi_rsp(IOP_MESSAGE_RSP_QRY_COMMISSION, pInstrumentCommissionRate, pRspInfo, nRequestID, bIsLast, _keeper, _client);
    }

    virtual void OnRspQryInstrument(CThostFtdcInstrumentField* pInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        gb2312_utf8_inplace(pInstrument);
        spi_rsp(IOP_MESSAGE_RSP_QRY_INSTRUMENT, pInstrument, pRspInfo, nRequestID, bIsLast, _keeper, _client);
    }

    virtual void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField* pInvestorPositionDetail, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        spi_rsp(IOP_MESSAGE_RSP_QRY_POSI_DETAIL, pInvestorPositionDetail, pRspInfo, nRequestID, bIsLast, _keeper, _client);
    }

    virtual void OnRspError(CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {
        spi_rsp(IOP_MESSAGE_RSP_ERROR, pRspInfo, pRspInfo, nRequestID, bIsLast, _keeper, _client);
    }

    virtual void OnRtnOrder(CThostFtdcOrderField* pOrder) {
        CThostFtdcRspInfoField rsp_info{ 0 };
        gb2312_utf8_inplace(pOrder);
        spi_rsp(IOP_MESSAGE_RTN_ORDER, pOrder, &rsp_info, 0, true, _keeper, _client);
    }

    virtual void OnRtnTrade(CThostFtdcTradeField* pTrade) {
        CThostFtdcRspInfoField rsp_info{ 0 };
        spi_rsp(IOP_MESSAGE_RTN_TRADE, pTrade, &rsp_info, 0, true, _keeper, _client);
    }

    virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField* pInputOrder, CThostFtdcRspInfoField* pRspInfo) {
        spi_rsp(IOP_MESSAGE_RTN_ORDER_INSERT, pInputOrder, pRspInfo, 0, true, _keeper, _client);
    }

    virtual void OnErrRtnOrderAction(CThostFtdcOrderActionField* pOrderAction, CThostFtdcRspInfoField* pRspInfo) {
        spi_rsp(IOP_MESSAGE_RTN_ORDER_ACTION, pOrderAction, pRspInfo, 0, true, _keeper, _client);
    }

private:
    ::client& _client;
    ::id_keeper& _keeper;
};

#endif
