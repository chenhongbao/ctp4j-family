#pragma once

#ifndef __PARSER__
#define __PARSER__

#include "facade.h"

#include <vector>
#include <string>
#include <stdexcept>

typedef int32_t			frame_type;
typedef int32_t			frame_length;
typedef std::string		frame_body;

#define FRAME_HEARTBEAT		0x10000000
#define FRAME_REQUEST		0x10000001
#define FRAME_RESPONSE		0x10000002
#define FRAME_LOGIN			0x10000003

struct frame {
	frame_type type;
	frame_length length;
	frame_body body;

	frame() : type(0), length(-1) {}
};

class frame_decoder
	: public std::vector<frame> {
public:
	enum class parser_state : unsigned char
	{
		wait_type, wait_length, wait_body
	};

	frame_decoder() : _index(0), _state(parser_state::wait_type) {}
	virtual ~frame_decoder() {}

	bool decode(const char* bytes, const int count) {
		_store(bytes, count);
		_decode_buffer();
		return size() > 0;
	}

protected:
	void _store(const char* bytes, const int count) {
		for (int i = 0; i < count; ++i)
			_buffer.push_back(bytes[i]);
	}

	void _compact(int next_index) {
		int index = 0;
		if (next_index < _buffer.size())
			for (; next_index < _buffer.size(); ++index, ++next_index)
				_buffer[index] = _buffer[next_index];
		_buffer.resize(index);
		_index = 0;
	}

	void _decode_buffer() {
		bool res = true;
		while (res) {
			switch (_state)
			{
			case parser_state::wait_type:
				if (res = _set_type())
					_state = parser_state::wait_length;
				break;
			case parser_state::wait_length:
				if (res = _set_length())
					_state = parser_state::wait_body;
				break;
			case parser_state::wait_body:
				if (res = _set_body()) {
					_save_decoding();
					_state = parser_state::wait_type;
				}
				break;
			default:
				break;
			}
		}
		_compact(_index);
	}

	int32_t _decode_int32() {
		char b[4]{ 0 };
		int* p = (int*)b;
		b[0] = _buffer[_index++];
		b[1] = _buffer[_index++];
		b[2] = _buffer[_index++];
		b[3] = _buffer[_index++];
		return c_ntoh(*p);
	}

	bool _set_type() {
		if (_buffer.size() < 4)
			return false;
		_decoding.type = _decode_int32();
		return true;
	}

	bool _set_length() {
		if (_buffer.size() < 4)
			return false;
		_decoding.length = _decode_int32();
		return true;
	}

	bool _set_body() {
		if (_decoding.length <= 0)
			throw std::length_error("frame body length underflow");
		if (_index < _buffer.size()) {
			if (_buffer.size() - _index < _decoding.length - _decoding.body.length()) {
				while (_index < _buffer.size())
					_decoding.body.push_back(_buffer[_index++]);
				return false;
			}
			else {
				while (_decoding.body.length() < _decoding.length)
					_decoding.body.push_back(_buffer[_index++]);
				return true;
			}
		}
		if (_decoding.body.length() < _decoding.length)
			return false;
		else
			return true;
	}

	void _save_decoding() {
		push_back(_decoding);
		new(&_decoding) frame();
	}

	std::vector<char> _buffer;
	int _index;
	parser_state _state;
	frame _decoding;
};

class frame_encoder {
public:
	frame_encoder() {}
	virtual ~frame_encoder() {}

	void encode(frame& frame, std::string& bytes) {
		if (frame.length <= 0)
			throw std::length_error("frame body length underflow");
		_append(frame.type, bytes);
		_append(frame.length, bytes);
		_append(frame.body, bytes);
	}

protected:
	static inline void _append(int32_t value, std::string& bytes) {
		value = c_hton(value);
		bytes.append((char*)(&value), sizeof(int32_t));
	}

	static inline void _append(std::string& content, std::string& bytes) {
		bytes.append(content);
	}
};
#endif
