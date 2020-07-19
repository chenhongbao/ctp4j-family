#pragma once

#ifndef __STRUCTS__
#define __STRUCTS__

#include "ThostFtdcUserApiDataType.h"

typedef int TThostFtdcInstrumentCountType;
typedef int TThostFtdcDisconnectReasonType;
typedef char** TThostFtdcInstrumentIDArrayType;

struct CThostFtdcConnectField
{
};

struct CThostFtdcDisconnect
{
	TThostFtdcDisconnectReasonType Reason;
};

struct CThostFtdcSubMarketDataField
{
	TThostFtdcInstrumentIDArrayType InstrumentID;
	TThostFtdcInstrumentCountType Count;
};

struct CThostFtdcUnsubMarketDataField
{
	TThostFtdcInstrumentIDArrayType InstrumentID;
	TThostFtdcInstrumentCountType Count;
};
#endif