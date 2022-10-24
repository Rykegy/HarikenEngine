#include "stdafx.h"
#include "NiftyConversions.h"

std::u16string conversions::to_u16string(int const& i) //Integer to unicode-friendly string
{

	string utf8string = to_string(i);

	return to_u16string(utf8string);

}

std::u16string conversions::to_u16string(string const& utf8string) //String to unicode-friendly string
{

	wstring_convert<std::codecvt_utf8_utf16<int16_t>, int16_t> convert;

	auto p = reinterpret_cast<const char*>(utf8string.data());
	auto q = convert.from_bytes(p);

	return u16string(q.begin(), q.end());

}

