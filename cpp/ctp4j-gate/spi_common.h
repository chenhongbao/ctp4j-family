#pragma once

#ifndef __SPI_COMMON__
#define __SPI_COMMON__

#include "facade.h"
#include "ThostFtdcUserApiStruct.h"

void gb2312_utf8_inplace(CThostFtdcInstrumentField* instrument) {
    if (instrument == nullptr)
        return;
    auto utf8 = convert_gb2312_utf8(instrument->InstrumentName);
    strncpy_s(instrument->InstrumentName, sizeof(instrument->InstrumentName), utf8.c_str(), _TRUNCATE);
}

void gb2312_utf8_inplace(CThostFtdcRspInfoField* rsp_info) {
    if (rsp_info == nullptr)
        return;
    auto utf8 = convert_gb2312_utf8(rsp_info->ErrorMsg);
    strncpy_s(rsp_info->ErrorMsg, sizeof(rsp_info->ErrorMsg), utf8.c_str(), _TRUNCATE);
}

void gb2312_utf8_inplace(CThostFtdcOrderField* rtn) {
    if (rtn == nullptr)
        return;
    auto utf8 = convert_gb2312_utf8(rtn->StatusMsg);
    strncpy_s(rtn->StatusMsg, sizeof(rtn->StatusMsg), utf8.c_str(), _TRUNCATE);
}

template<typename Ty>
void _to_body(::body& body, const char* type, Ty* object, CThostFtdcRspInfoField* rsp, message_id& id, int count, int total, ::id_keeper& m) {
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

template<typename Ty>
void spi_rsp(const char* msg_type, Ty* object_ptr, CThostFtdcRspInfoField* rsp_ptr, int nid, bool is_last, ::id_keeper& keeper, ::client& client) {
    if (object_ptr == nullptr) {
        auto str = std::string(msg_type) + ", ctp rsp null";
        print(str.c_str());
        return;
    }
    static int count = 0, total = 0;
    ::body body;
    ::message_id id;
    CThostFtdcRspInfoField tmp_rsp{ 0 };
    try {
        id = keeper.get_id(nid);
        ++count;
        if (is_last)
            total = count;
        if (rsp_ptr != nullptr) {
            gb2312_utf8_inplace(rsp_ptr);
            _to_body(body, msg_type, object_ptr, rsp_ptr, id, count, total, keeper);
        }
        else
            _to_body(body, msg_type, object_ptr, &tmp_rsp, id, count, total, keeper);
        client.send_body(body, IOP_FRAME_RESPONSE);
    }
    catch (std::exception& e) {
        print(e.what());
    }
    if (is_last)
        count = total = 0;
}

#endif
