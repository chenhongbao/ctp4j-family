#pragma once

#ifndef __MESSAGE__
#define __MESSAGE__

#include "rjparser.h"
#include "frame.h"

typedef std::string		body_encoded;
typedef std::string		message_id;
typedef std::string		message_type;
typedef int				message_count;

#define _str(m) #m

#define MESSAGE_HEARTBEAT				_str(HEARTBEAT)
#define MESSAGE_SUB_MD					_str(SUB_MD)
#define MESSAGE_RSP_SUB_MD				_str(RSP_SUB_MD)
#define MESSAGE_UNSUB_MD				_str(UNSUB_MD)
#define MESSAGE_RSP_UNSUB_MD			_str(RSP_UNSUB_MD)
#define MESSAGE_FLOW_DEPTH				_str(FLOW_DEPTH)
#define MESSAGE_FLOW_CANDLE				_str(FLOW_CANDLE)
#define MESSAGE_REQ_AUTHENTICATE		_str(REQ_AUTHENTICATE)
#define MESSAGE_RSP_REQ_AUTHENTICATE	_str(RSP_REQ_AUTHENTICATE)
#define MESSAGE_REQ_LOGIN				_str(REQ_LOGIN)
#define MESSAGE_RSP_REQ_LOGIN			_str(RSP_REQ_LOGIN)
#define MESSAGE_REQ_LOGOUT				_str(REQ_LOGOUT)
#define MESSAGE_RSP_REQ_LOGOUT			_str(RSP_REQ_LOGOUT)
#define MESSAGE_REQ_SETTLEMENT			_str(REQ_SETTLEMENT)
#define MESSAGE_RSP_REQ_SETTLEMENT		_str(RSP_REQ_SETTLEMENT)
#define MESSAGE_REQ_ORDER_INSERT		_str(REQ_ORDER_INSERT)
#define MESSAGE_RSP_REQ_ORDER_INSERT	_str(RSP_REQ_ORDER_INSERT)
#define MESSAGE_REQ_ORDER_ACTION		_str(REQ_ORDER_ACTION)
#define MESSAGE_RSP_REQ_ORDER_ACTION	_str(RSP_REQ_ORDER_ACTION)
#define MESSAGE_QRY_ACCOUNT				_str(QRY_ACCOUNT)
#define MESSAGE_RSP_QRY_ACCOUNT			_str(RSP_QRY_ACCOUNT)
#define MESSAGE_QRY_ORDER				_str(QRY_ORDER)
#define MESSAGE_RSP_QRY_ORDER			_str(RSP_QRY_ORDER)
#define MESSAGE_QRY_POSITION			_str(QRY_POSITION)
#define MESSAGE_RSP_QRY_POSITION		_str(RSP_QRY_POSITION)
#define MESSAGE_QRY_POSI_DETAIL			_str(QRY_POSI_DETAIL)
#define MESSAGE_RSP_QRY_POSI_DETAIL		_str(RSP_QRY_POSI_DETAIL)
#define MESSAGE_QRY_INSTRUMENT			_str(QRY_INSTRUMENT)
#define MESSAGE_RSP_QRY_INSTRUMENT		_str(RSP_QRY_INSTRUMENT)
#define MESSAGE_QRY_COMMISSION			_str(QRY_COMMISSION)
#define MESSAGE_RSP_QRY_COMMISSION		_str(RSP_QRY_COMMISSION)
#define MESSAGE_QRY_MARGIN				_str(QRY_MARGIN)
#define MESSAGE_RSP_QRY_MARGIN			_str(RSP_QRY_MARGIN)
#define MESSAGE_RTN_ORDER				_str(RTN_ORDER)
#define MESSAGE_RTN_TRADE				_str(RTN_TRADE)
#define MESSAGE_RTN_ORDER_ACTION		_str(RTN_ORDER_ACTION)
#define MESSAGE_RTN_ORDER_INSERT		_str(RTN_ORDER_INSERT)
#define MESSAGE_RSP_ORDER_ACTION		_str(RSP_ORDER_ACTION)
#define MESSAGE_RSP_ORDER_INSERT		_str(RSP_ORDER_INSERT)

struct body {
	message_type type;
	message_id request_id, response_id;
	message_count current_count, total_count;
	body_encoded object, rsp_info;

	body() : current_count(0), total_count(0) {}
};

void decode(frame& frame, body& body) {
	Document doc;
	if (doc.Parse(frame.body.c_str()).HasParseError())
		throw std::runtime_error("parser error");
	_decode_string("Type", doc, body.type);
	_decode_string("RequestID", doc, body.request_id);
	_decode_string("ResponseID", doc, body.response_id);
	_decode_string("Body", doc, body.object);
	_decode_string("RspInfo", doc, body.rsp_info);
	_decode_int("CurrentCount", doc, body.current_count);
	_decode_int("TotalCount", doc, body.total_count);
}

void _decode_string(
	const char* member,
	Document& doc,
	std::string& dest) {
	if (doc.HasMember(member) && doc[member].IsString())
		dest.assign(doc[member].GetString());
}


void _decode_int(
	const char* member,
	Document& doc,
	int& dest) {
	if (doc.HasMember(member) && doc[member].IsInt())
		dest = doc[member].GetInt();
}

template<typename Ty>
struct message {
	message_type type;
	message_id request_id, response_id;
	message_count current_count, total_count;
	Ty object;
	CThostFtdcRspInfoField rsp_info;

	message() : current_count(0), total_count(0), rsp_info{ 0 } {}
};

template<typename Ty>
void decode(body& body, message<Ty>& message) {
	// Decode body to message.
	set_field(message.rsp_info, body.rsp_info.c_str());
	set_field(message.object, body.rsp_info.c_str());
	message.type = body.type;
	message.current_count = body.current_count;
	message.total_count = body.total_count;
	message.request_id = body.request_id;
	message.response_id = body.response_id;
}

#endif