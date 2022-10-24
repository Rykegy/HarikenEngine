#include "stdafx.h"
#include "FontHandler.h"
#include "NiftyConversions.h"

using namespace HARIKEN;

std::unique_ptr<FontHandler> FontHandler::fontInstance = nullptr;

std::map<char16_t, Character>* HARIKEN::FontHandler::getCharacterMap(const std::string& fontName_, int fontSize_, const char* text_)
{

	return getCharacterMap(fontName_, fontSize_, conversions::to_u16string(std::string(text_)).c_str());

}

std::map<char16_t, Character>* HARIKEN::FontHandler::getCharacterMap(const std::string & fontName_, int fontSize_, const char16_t* text_)
{

	FT_Library ft;

	if (FT_Init_FreeType(&ft))
		std::cout << "!!ERROR!!" << std::endl << "Could not init FreeType Library" << std::endl;

	//Return a character texture map for a given font face at a particular size.
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	std::string fontFileName = "ASSET/TTC/" + fontName_;

	FT_Face face;

	if (FT_New_Face(ft, fontFileName.c_str(), 0, &face)) {

		//std::cout << "!!ERROR!!" << std::endl << "FREETYPE: Failed to load font" << std::endl;

		return NULL;

	}

	FT_Set_Pixel_Sizes(face, 0, fontSize_);
	//If character map doesn't exist for either that font or size, create a new map.
	if (characterMap.find(fontFileName + std::to_string(fontSize_)) == characterMap.end())
		characterMap[fontFileName + std::to_string(fontSize_)] = new std::map<char16_t, Character>();

	std::map<char16_t, Character>* temp = characterMap[fontFileName + std::to_string(fontSize_)];

	FT_GlyphSlot slot = face->glyph;

	const char16_t *ch;

	for (ch = text_; *ch; ch++) {

		if (temp->find(*ch) != temp->end())
			continue;

		FT_Load_Glyph(face, FT_Get_Char_Index(face, *ch), FT_LOAD_RENDER);
		const FT_Bitmap& bitmap = face->glyph->bitmap;

		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			bitmap.width,
			bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			bitmap.buffer
		);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			static_cast<GLuint>(face->glyph->advance.x)
		};
		temp->insert(std::pair<char16_t, Character>(*ch, character));
		glBindTexture(GL_TEXTURE_2D, 0);

	}

	/* Legacy character loader
	//Check if the texture for all the characters in the string exists. If it doesn't, create one and add it to the map. This way the map is only as large as it needs to be.
	const char *ch;

	for (ch = text_; *ch; ch++)
	{
		
		if (temp->find(*ch) != temp->end())
			continue;

		// Load character glyph 
		if (FT_Load_Char(Fonts[fontName_], *ch, FT_LOAD_RENDER))
		{
			std::cout << "!!ERROR!!" << std::endl << "Failed to load Glyph at " << ch << std::endl;
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			Fonts[fontName_]->glyph->bitmap.width,
			Fonts[fontName_]->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			Fonts[fontName_]->glyph->bitmap.buffer
		);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = {
			texture,
			glm::ivec2(Fonts[fontName_]->glyph->bitmap.width, Fonts[fontName_]->glyph->bitmap.rows),
			glm::ivec2(Fonts[fontName_]->glyph->bitmap_left, Fonts[fontName_]->glyph->bitmap_top),
			static_cast<GLuint>(Fonts[fontName_]->glyph->advance.x)
		};
		temp->insert(std::pair<GLchar, Character>(*ch, character));
		glBindTexture(GL_TEXTURE_2D, 0);

	}

	*/

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	FT_Done_FreeType(ft);

	return temp;

}

FontHandler::FontHandler()
{

}


FontHandler::~FontHandler()
{


}

FontHandler * HARIKEN::FontHandler::GetInstance()
{

	if (fontInstance.get() == nullptr)
		fontInstance.reset(new FontHandler);

	return fontInstance.get();

}

void HARIKEN::FontHandler::resetInstance()
{

	fontInstance.reset(new FontHandler);

}
