#pragma once

#ifndef __PARSER__
#define __PARSER__

#include "facade.h"

#include <vector>
#include <string>
#include <stdexcept>

typedef std::string		frame_body;

struct frame {
	frame_type type;
	frame_length length;
	frame_body body;
	
	frame() : type(0), length(-1) {}
};

class frame_parser
	: public std::vector<frame> {
public:
	enum class parser_state : unsigned char
	{
		wait_type, wait_length, wait_body
	};

	frame_parser() : _index(0), _state(parser_state::wait_type) {}
	virtual ~frame_parser() {}

	bool parse(const char* bytes, const int count) {
		_store(bytes, count);
		_parse_buffer();
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

	void _parse_buffer() {
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
#endif
