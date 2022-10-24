/**************
Title screen text.
**************/

#pragma once
#include "UIObject.h"
#include "TextTest.h"

namespace MEIUN {

	class DescText : public HARIKEN::UIObject
	{
	public:

		void onCreate();
		void update();

	private:

		Language lang;

	};

}