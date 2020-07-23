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

template<typename Ty>
void release_md(Ty& v) {
    if (v.Count > 0)
        for (int i = 0; i < v.Count; ++i)
            if (v.InstrumentID[i] != nullptr)
                delete v.InstrumentID[i];
    delete v.InstrumentID;
}
#endif