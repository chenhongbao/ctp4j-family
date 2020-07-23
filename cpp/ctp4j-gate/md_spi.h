#pragma once

#ifndef __MD_SPI__
#define __MD_SPI__

#include "client.h"
#include "message.h"

#include "ThostFtdcMdApi.h"

class md_spi : public CThostFtdcMdSpi {
public:
	md_spi(::client& client) : _client(client) {
	}

	virtual ~md_spi() {}

	virtual void OnFrontConnected() {};

	virtual void OnFrontDisconnected(int nReason) {};

	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {};

	virtual void OnRspUserLogout(CThostFtdcUserLogoutField* pUserLogout, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {};

	virtual void OnRspError(CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {};

	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {};

	virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField* pSpecificInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) {};

	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData) {};

private:
	::client& _client;
};

#endif