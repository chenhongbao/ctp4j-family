/*
Don't use #pragma once directive because this file will be included twice to define and
undef and macros.
*/
#ifndef __RJMACRO__
#define __RJMACRO__
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"

#include <string>
#include <stdexcept>

using namespace rapidjson;

#define str(member)             #member
#define ref(object, member)     object.##member

#define set_Ty(member, checker, getter)                                                 \
{                                                                                       \
    auto iter = __doc__.FindMember(str(member));                                        \
    if (iter != __doc__.MemberEnd() && !iter->value.IsNull()                            \
        && iter->value.##checker()) {                                                   \
        ref(__field__, member) = iter->value.##getter();                                \
    }                                                                                   \
}

#define set_string(member)                                                              \
{                                                                                       \
    auto iter = __doc__.FindMember(str(member));                                        \
    if (iter != __doc__.MemberEnd() && !iter->value.IsNull()                            \
        && iter->value.IsString()) {                                                    \
        strcpy_s(ref(__field__, member), iter->value.GetString());                      \
    }                                                                                   \
}

#define set_flag(member)                                                                \
{                                                                                       \
    auto iter = __doc__.FindMember(str(member));                                        \
    if (iter != __doc__.MemberEnd() && !iter->value.IsNull() && iter->value.IsInt()) {  \
        auto i = iter->value.GetInt();                                                  \
        if (CHAR_MIN <= i && i <= UCHAR_MAX)                                            \
            ref(__field__, member) = (char)(iter->value.GetInt());                      \
        else                                                                            \
            throw std::runtime_error("flag value overflow");                            \
    }                                                                                   \
}

#define set_int(member)     set_Ty(member, IsInt, GetInt)

#define set_double(member)  set_Ty(member, IsDouble, GetDouble)

#define parse_or_throw()                                                                \
Document __doc__;                                                                       \
__doc__.Parse(__json__);                                                                \
{                                                                                       \
    if (__doc__.HasParseError())                                                        \
        throw std::runtime_error(                                                       \
            "json parser error " + std::to_string((int)__doc__.GetParseError()));       \
}


#define document()                                  \
    StringBuffer __s__;                             \
    Writer<StringBuffer> __writer__(__s__);         \
    __writer__.StartObject();

#define get_string(member)                          \
{                                                   \
    __writer__.Key(#member);                        \
    __writer__.String(__field__.##member);          \
}

#define get_int(member)                             \
{                                                   \
    __writer__.Key(#member);                        \
    __writer__.Int(__field__.##member);             \
}

#define get_null(member)                            \
{                                                   \
    __writer__.Key(#member);                        \
    __writer__.Null();                              \
}

#define get_flag(member)                            \
{                                                   \
    __writer__.Key(#member);                        \
    __writer__.Int((int)__field__.##member);        \
}

#define get_double(member)                          \
{                                                   \
    __writer__.Key(#member);                        \
    __writer__.Double(__field__.##member);          \
}

#define write_document()                            \
{                                                   \
    __writer__.EndObject();                         \
    __json__.assign(__s__.GetString());             \
}

#define setter_def(type) void set_field(type& __field__, const char* const __json__ = "{}")

#define getter_def(type) void get_field(type& __field__, std::string& __json__)

#else
#undef __RJMACRO__

#undef str
#undef ref
#undef set_Ty
#undef set_string
#undef set_double
#undef set_int
#undef set_flag
#undef parse_or_throw
#undef document
#undef get_string
#undef get_double
#undef get_int
#undef get_null
#undef get_flag
#undef write_document

#endif
