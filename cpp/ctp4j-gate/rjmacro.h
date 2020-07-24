/*
Don't use #pragma once directive because this file will be included twice to define and
undef and macros.
*/
#ifndef __RJMACRO__
#define __RJMACRO__
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"

#include "except.h"

#include <string>

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

#define set_flag(member, attribute)                                                     \
{                                                                                       \
    auto iter = __doc__.FindMember(str(attribute));                                     \
    if (iter != __doc__.MemberEnd() && !iter->value.IsNull() && iter->value.IsInt()) {  \
        auto i = iter->value.GetInt();                                                  \
        if (CHAR_MIN <= i && i <= UCHAR_MAX)                                            \
            ref(__field__, member) = (char)(iter->value.GetInt());                      \
        else                                                                            \
            throw ::flag_error(i);                                                      \
    }                                                                                   \
}

#define set_int(member)     set_Ty(member, IsInt, GetInt)

#define set_double(member)  set_Ty(member, IsDouble, GetDouble)

#define set_array(array_m, count_m)                                                     \
{                                                                                       \
    auto iter = __doc__.FindMember(str(array_m));                                       \
    if (iter != __doc__.MemberEnd() && !iter->value.IsNull() && iter->value.IsArray()   \
        && iter->value.Size() > 0) {                                                    \
        __field__.##count_m = (int)iter->value.Size();                                  \
        __field__.##array_m = new char* [__field__.##count_m];                          \
        for (int i = 0; i < __field__.Count; ++i) {                                     \
            __field__.##array_m[i] = new TThostFtdcInstrumentIDType{ 0 };               \
            strcpy_s(__field__.##array_m[i], sizeof(TThostFtdcInstrumentIDType),        \
                iter->value[i].GetString());                                            \
        }                                                                               \
    }                                                                                   \
}

#define parse_or_throw()                                                                \
Document __doc__;                                                                       \
__doc__.Parse(__json__);                                                                \
{                                                                                       \
    if (__doc__.HasParseError())                                                        \
        throw ::json_error(__doc__.GetParseError());                                    \
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
