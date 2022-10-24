/**********************************************************************************************
Header to store conversion methods. Currently only used to convert normal strings/integers into Unicode 16 strings.
**********************************************************************************************/

#pragma once

#include<string>
#include<locale>
#include<codecvt>

using namespace std;

class conversions {

public:

	static std::u16string to_u16string(int const& i);

	static std::u16string to_u16string(string const& utf8string);

};