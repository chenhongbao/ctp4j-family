#pragma once

#ifndef __IOP_MESSAGE__
#define __IOP_MESSAGE__

#include "frame.h"
#include "rjparser.h"

typedef std::string body_encoded;
typedef std::string message_id;
typedef std::string message_type;
typedef int         message_count;

#define _str(m) #m

#define IOP_MESSAGE_HEARTBEAT               _str(HEARTBEAT)
#define IOP_MESSAGE_SUB_MD                  _str(SUB_MD)
#define IOP_MESSAGE_RSP_SUB_MD              _str(RSP_SUB_MD)
#define IOP_MESSAGE_UNSUB_MD                _str(UNSUB_MD)
#define IOP_MESSAGE_RSP_UNSUB_MD            _str(RSP_UNSUB_MD)
#define IOP_MESSAGE_FLOW_DEPTH              _str(FLOW_DEPTH)
#define IOP_MESSAGE_FLOW_CANDLE             _str(FLOW_CANDLE)
#define IOP_MESSAGE_REQ_AUTHENTICATE        _str(REQ_AUTHENTICATE)
#define IOP_MESSAGE_RSP_REQ_AUTHENTICATE    _str(RSP_REQ_AUTHENTICATE)
#define IOP_MESSAGE_REQ_LOGIN               _str(REQ_LOGIN)
#define IOP_MESSAGE_RSP_REQ_LOGIN           _str(RSP_REQ_LOGIN)
#define IOP_MESSAGE_REQ_LOGOUT              _str(REQ_LOGOUT)
#define IOP_MESSAGE_RSP_REQ_LOGOUT          _str(RSP_REQ_LOGOUT)
#define IOP_MESSAGE_REQ_SETTLEMENT          _str(REQ_SETTLEMENT)
#define IOP_MESSAGE_RSP_REQ_SETTLEMENT      _str(RSP_REQ_SETTLEMENT)
#define IOP_MESSAGE_REQ_ORDER_INSERT        _str(REQ_ORDER_INSERT)
#define IOP_MESSAGE_RSP_REQ_ORDER_INSERT    _str(RSP_REQ_ORDER_INSERT)
#define IOP_MESSAGE_REQ_ORDER_ACTION        _str(REQ_ORDER_ACTION)
#define IOP_MESSAGE_RSP_REQ_ORDER_ACTION    _str(RSP_REQ_ORDER_ACTION)
#define IOP_MESSAGE_QRY_ACCOUNT             _str(QRY_ACCOUNT)
#define IOP_MESSAGE_RSP_QRY_ACCOUNT         _str(RSP_QRY_ACCOUNT)
#define IOP_MESSAGE_QRY_ORDER               _str(QRY_ORDER)
#define IOP_MESSAGE_RSP_QRY_ORDER           _str(RSP_QRY_ORDER)
#define IOP_MESSAGE_QRY_POSITION            _str(QRY_POSITION)
#define IOP_MESSAGE_RSP_QRY_POSITION        _str(RSP_QRY_POSITION)
#define IOP_MESSAGE_QRY_POSI_DETAIL         _str(QRY_POSI_DETAIL)
#define IOP_MESSAGE_RSP_QRY_POSI_DETAIL     _str(RSP_QRY_POSI_DETAIL)
#define IOP_MESSAGE_QRY_INSTRUMENT          _str(QRY_INSTRUMENT)
#define IOP_MESSAGE_RSP_QRY_INSTRUMENT      _str(RSP_QRY_INSTRUMENT)
#define IOP_MESSAGE_QRY_COMMISSION          _str(QRY_COMMISSION)
#define IOP_MESSAGE_RSP_QRY_COMMISSION      _str(RSP_QRY_COMMISSION)
#define IOP_MESSAGE_QRY_MARGIN              _str(QRY_MARGIN)
#define IOP_MESSAGE_RSP_QRY_MARGIN          _str(RSP_QRY_MARGIN)
#define IOP_MESSAGE_RTN_ORDER               _str(RTN_ORDER)
#define IOP_MESSAGE_RTN_TRADE               _str(RTN_TRADE)
#define IOP_MESSAGE_RTN_ORDER_ACTION        _str(RTN_ORDER_ACTION)
#define IOP_MESSAGE_RTN_ORDER_INSERT        _str(RTN_ORDER_INSERT)
#define IOP_MESSAGE_RSP_ORDER_ACTION        _str(RSP_ORDER_ACTION)
#define IOP_MESSAGE_RSP_ORDER_INSERT        _str(RSP_ORDER_INSERT)
#define IOP_MESSAGE_RSP_ERROR               _str(RSP_ERROR)
#define IOP_MESSAGE_RSP_CONNECT             _str(RSP_CONNECT)
#define IOP_MESSAGE_RSP_DISCONNECT          _str(RSP_DISCONNECT)

struct body {
    message_type    type;
    message_id      request_id, response_id;
    message_count   current_count, total_count;
    body_encoded    object, rsp_info;

    body() : current_count(0), total_count(0) {}
};

class body_decoder {
public:
    static void decode(frame& frame, body& body) {
        Document doc;
        if (doc.Parse(frame.body.c_str()).HasParseError())
            throw ::json_error((int)doc.GetParseError());
        _decode_string(_str(Type),         doc, body.type);
        _decode_string(_str(RequestID),    doc, body.request_id);
        _decode_string(_str(ResponseID),   doc, body.response_id);
        _decode_string(_str(Body),         doc, body.object);
        _decode_string(_str(RspInfo),      doc, body.rsp_info);
        _decode_int(_str(CurrentCount), doc, body.current_count);
        _decode_int(_str(TotalCount),   doc, body.total_count);
    }

protected:
    static void _decode_string(const char* member, Document& doc,
        std::string& dest) {
        if (doc.HasMember(member) && doc[member].IsString())
            dest.assign(doc[member].GetString());
    }

    static void _decode_int(const char* member, Document& doc, int& dest) {
        if (doc.HasMember(member) && doc[member].IsInt())
            dest = doc[member].GetInt();
    }
};

class body_encoder {
public:
    static void encode(body& body, frame& frame, frame_type type) {
        StringBuffer sb;
        Writer<StringBuffer> wr(sb);
        wr.StartObject();
        _encode_string(wr,  _str(Type),         body.type);
        _encode_string(wr,  _str(RequestID),    body.request_id);
        _encode_string(wr,  _str(ResponseID),   body.response_id);
        _encode_string(wr,  _str(Body),         body.object);
        _encode_string(wr,  _str(RspInfo),      body.rsp_info);
        _encode_int(wr,  _str(CurrentCount), body.current_count);
        _encode_int(wr,  _str(TotalCount),   body.total_count);
        wr.EndObject();
        frame.type      = type;
        frame.length    = (frame_length)sb.GetSize();
        frame.body.assign(sb.GetString(), sb.GetSize());
    }

protected:
    static void _encode_string(Writer<StringBuffer>& wr, const char* member,
        std::string& str) {
        wr.Key(member);
        wr.String(str.c_str());
    }

    static void _encode_int(Writer<StringBuffer>& wr, const char* member,
        int value) {
        wr.Key(member);
        wr.Int(value);
    }
};

template <typename Ty>
struct message {
    message_type            type;
    message_id              request_id, response_id;
    message_count           current_count, total_count;
    Ty                      object;
    CThostFtdcRspInfoField  rsp_info;

    message() : current_count(0), total_count(0), rsp_info{ 0 } {}
};

template <typename Ty>
class message_encoder {
public:
    static void decode(body& body, message<Ty>& message) {
        // Decode body to message.
        set_field(message.rsp_info, body.rsp_info.c_str());
        set_field(message.object,   body.rsp_info.c_str());
        message.type            = body.type;
        message.current_count   = body.current_count;
        message.total_count     = body.total_count;
        message.request_id      = body.request_id;
        message.response_id     = body.response_id;
    }
};

template <typename Ty>
class message_decoder {
public:
    static void encode(message<Ty>& message, body& body) {
        get_field(message.object,   body.object);
        get_field(message.rsp_info, body.rsp_info);
        body.type           = message.type;
        body.current_count  = message.current_count;
        body.total_count    = message.total_count;
        body.request_id     = message.request_id;
        body.response_id    = message.response_id;
    }
};
#endif