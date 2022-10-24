/**************************************************************************
Singleton used to create, store and distribute FreeType character maps used to display text.
**************************************************************************/

#pragma once
#include <ft2build.h>
#include "freetype/freetype.h"

namespace HARIKEN {

	struct Character {
		GLuint TextureID;  // ID handle of the glyph texture
		glm::ivec2 Size;       // Size of glyph
		glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
		GLuint Advance;    // Offset to advance to next glyph
	};

	class FontHandler
	{
	public:

		static FontHandler* GetInstance();
		static void resetInstance();

		FontHandler(const FontHandler&) = delete;
		FontHandler(FontHandler&&) = delete;
		FontHandler& operator = (const FontHandler&) = delete;
		FontHandler& operator = (FontHandler&&) = delete;

		std::map<char16_t, Character>* getCharacterMap(const std::string& fontName_, int fontSize_, const char* text_);
		std::map<char16_t, Character>* getCharacterMap(const std::string& fontName_, int fontSize_, const char16_t* text_);

	private:

		FontHandler();
		~FontHandler();

		static std::unique_ptr<FontHandler> fontInstance;
		friend std::default_delete<FontHandler>;

		std::map<std::string, std::map<char16_t, Character>*>characterMap;

	};

}