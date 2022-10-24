#include "stdafx.h"
#include "UIObject.h"
#include "NiftyConversions.h"

using namespace HARIKEN;

UIObject::UIObject()
{

}


UIObject::~UIObject()
{

	for(auto m : model)
		delete m;

	for (std::map<AssetFile*, int>::iterator i = filesUsed.begin(); i != filesUsed.end(); i++)
		i->first->disassociate(this);

	filesUsed.clear();

	if (GameScene != nullptr) {

		for (size_t i = 0; i < GameScene->renderQueue.size(); i++)
			if (GameScene->UIRenderQueue[i] == this) {

				GameScene->UIRenderQueue.erase(GameScene->UIRenderQueue.begin() + i);
				break;

			}

	}

}

void HARIKEN::UIObject::init(Scene* gameScene)
{

	time = Time::GetInstance();
	InputSys = InputSys::GetInstance();
	Window = WindowSys::GetInstance();
	sceneManager = SceneManager::GetInstance();
	fontHandler = FontHandler::GetInstance();
	camera = Camera::GetInstance();
	assetHandler = AssetHandler::GetInstance();

	GameScene = gameScene;
	windowSize = Window->getWinSize();

	onCreate();

}

void HARIKEN::UIObject::afterUpdate()
{

	while (imagepos.size() != model.size()) {

		if (model.size() > imagepos.size())
			imagepos.push_back(glm::vec2());

		else if (model.size() < imagepos.size())
			imagepos.pop_back();

	}

	if (willRender) {

		if (GameScene->UIRenderQueue.empty())
			GameScene->UIRenderQueue.push_back(this);

		else {

			bool closest = true;

			for (size_t i = 0; i < GameScene->UIRenderQueue.size(); i++) {

				if (layer <= GameScene->UIRenderQueue[i]->layer) {
					GameScene->UIRenderQueue.insert(GameScene->UIRenderQueue.begin() + static_cast<int>(i), this);
					closest = false;
					break;
				}

			}

			if (closest)
				GameScene->UIRenderQueue.push_back(this);

		}

	}

}

void UIObject::render()
{

	for (size_t i = 0; i < model.size(); i++) {
		
		if (type == UIType::Image) {

			if (imagepos.empty())
				imagepos.push_back(glm::vec2());

			if (model[0]->getScale() != scale)
				model[0]->setScale(glm::vec3(scale));

			float windowScale = *Window->windowScale;
			float px = position.x * windowScale - windowSize.x / 2;
			float py = -position.y  * windowScale + windowSize.y / 2;

			imagepos[0].x = position.x - GameScene->cameraPos.x;
			imagepos[0].y = position.y - GameScene->cameraPos.y;

			switch (alignment.horizontal) {

			default:

				imagepos[0].x = std::round(imagepos[0].x - model[0]->getSize().x / 2);
				break;

			case Align::left:

				imagepos[0].x = std::round(imagepos[0].x);
				px += model[0]->getSize().x * scale.x / 2;
				break;

			case Align::right:

				imagepos[0].x = std::round(imagepos[0].x - model[0]->getSize().x);
				px -= model[0]->getSize().x * scale.x / 2;
				break;

			}

			switch (alignment.vertical) {

			default:

				imagepos[0].y += model[0]->getSize().y / 2;
				break;

			case Align::top:

				imagepos[0].y += model[0]->getSize().y;
				py -= model[0]->getSize().y * scale.y / 2;
				break;

			case Align::bottom:

				py += model[0]->getSize().y * scale.y / 2;
				break;

			}

			imagepos[0].y = std::round(windowSize.y - imagepos[0].y);

			model[0]->setPosition(glm::vec3(px, py, 0.0f));

			model[0]->render();

			break;

		}

		else if (type == UIType::Text) {

			if (imagepos.size() < i + 1)
				imagepos.push_back(glm::vec2());

			glm::vec3 offset = model[i]->getPosition();
			float w = model[i]->getSize().x;
			float h = model[i]->getSize().y;

			glm::vec2 alignmentOffset = getSize();
			float px = position.x;
			float py = -position.y;

			switch (alignment.horizontal) {

			case Align::center:
				px -= alignmentOffset.x / 2;
				break;

			default:
				break;

			case Align::right:
				px -= alignmentOffset.x;
				break;

			}

			switch (alignment.vertical) {

			case Align::center:
				break;

			default:
				py -= alignmentOffset.y / 2;
				break;

			case Align::top:
				py += alignmentOffset.y / 2;
				break;

			}

			imagepos[i].x = std::floor((px + offset.x) + windowSize.x / 2);
			imagepos[i].y = std::floor((py + offset.y) + windowSize.y / 2);

			model[i]->setPosition(offset + glm::vec3(px, py, 0.0f));
			model[i]->render();
			model[i]->setPosition(offset);

		}

	}

}

const glm::vec2 HARIKEN::UIObject::getPosition()
{
	return position;
}

void HARIKEN::UIObject::setPosition(float newX, float newY)
{

	position = glm::vec2(newX, newY);

}

void HARIKEN::UIObject::setPosition(glm::vec2 newPosition)
{

	position = newPosition;

}

glm::vec2 HARIKEN::UIObject::getSize()
{

	if (type == UIType::Text)
	{
		if (!model.empty()) {

			float largest = 0;

			for (auto m : model)
				if (m->getSize().y > largest)
					largest = m->getSize().y;

			return glm::vec2(model[model.size() - 1]->getPosition().x - model[0]->getPosition().x + model[0]->getSize().x / 2 + model[model.size() - 1]->getSize().x, largest);

		}

		return glm::vec2(0.0f);

	}

	else
		return glm::vec2(model[0]->getSize().x, model[0]->getSize().y);

}

glm::vec2 HARIKEN::UIObject::getImagePosition()
{
	return imagepos[0];
}

glm::vec2 HARIKEN::UIObject::getImagePosition(int index)
{
	return imagepos[index];
}

void HARIKEN::UIObject::setScale(glm::vec3 scale_)
{

	scale = scale_;

}

glm::vec3 HARIKEN::UIObject::getScale()
{

	return scale;

}

void HARIKEN::UIObject::addTag(std::string tag_)
{

	tag.push_back(tag_);

}

bool HARIKEN::UIObject::hasTag(std::string tag_)
{

	for (auto t : tag)
		if (t == tag_)
			return true;

	return false;

}

void HARIKEN::UIObject::setImg(const Texture * image_)
{

	type = Image;

	image = image_;

	if (model.empty())
		model.push_back(new imageFrame(image->size.x, image->size.y, image->textureID));
	else {
		delete model[0];
		model[0] = new imageFrame(image->size.x, image->size.y, image->textureID);
	}

}

void HARIKEN::UIObject::setFont(std::string path)
{

	std::string pathName = "ASSET/TTC/" + path;

	fontName = path;

}

void HARIKEN::UIObject::setText(std::string text_, int size_, glm::vec3 color_)
{

	setText(conversions::to_u16string(text_), size_, color_);

}

void HARIKEN::UIObject::setText(std::u16string text_, int fontSize_, glm::vec3 color_)
{

	type = UIType::Text;
	request = setTextRequest(text_, fontSize_, color_);

}

AssetFile* HARIKEN::UIObject::getAssetFile(std::string name)
{

	AssetFile* file = assetHandler->getAssetFile(name);

	if (file != nullptr) {

		filesUsed[file] = 0;

		file->associate(this);

		return file;

	}

	return nullptr;

}

bool UIObject::onClick()
{

	if (type == UIType::Image && image != nullptr) {

		if (InputSys->inputs.Click.leftclickdown && (InputSys->inputs.Click.clickpos.x >= imagepos[0].x && InputSys->inputs.Click.clickpos.x <= imagepos[0].x + image->size.x && InputSys->inputs.Click.clickpos.y >= imagepos[0].y && InputSys->inputs.Click.clickpos.y <= imagepos[0].y + image->size.y))
			return true;

	}

	else if (type == UIType::Text) {

		if (InputSys->inputs.Click.leftclickdown) {

			float x1 = imagepos.front().x - model.front()->getSize().x / 2;
			float x2 = imagepos.back().x + model.back()->getSize().x / 2;
			float y1 = imagepos.front().y - model.front()->getSize().y / 2;
			float y2 = imagepos.front().y + model.front()->getSize().y / 2;

			for (size_t i = 0; i < model.size(); i++)
				if (imagepos[i].y + model[i]->getSize().y / 2 > y2)
					y2 = imagepos[i].y + model[i]->getSize().y / 2;

			if (InputSys->inputs.Click.clickpos.x >= x1 && InputSys->inputs.Click.clickpos.x <= x2 && InputSys->inputs.Click.clickpos.y >= y1 && InputSys->inputs.Click.clickpos.y <= y2)
				return true;

		}

	}

	return false;
}

bool UIObject::onMouseOver()
{

	int mPosX;
	int mPosY;

	SDL_GetMouseState(&mPosX, &mPosY);

	if (type == UIType::Image && image != nullptr) {

		if (mPosX >= imagepos[0].x && mPosX <= imagepos[0].x + image->size.x &&mPosY >= imagepos[0].y && mPosY <= imagepos[0].y + image->size.y)
			return true;

	}

	else if (type == UIType::Text) {

			float x1 = imagepos.front().x - model.front()->getSize().x / 2;
			float x2 = imagepos.back().x + model.back()->getSize().x / 2;
			float y1 = imagepos.front().y - model.front()->getSize().y / 2;
			float y2 = imagepos.front().y + model.front()->getSize().y / 2;

			for (size_t i = 0; i < model.size(); i++)
				if (imagepos[i].y + model[i]->getSize().y / 2 > y2)
					y2 = imagepos[i].y + model[i]->getSize().y / 2;

			if (InputSys->inputs.Click.clickpos.x >= x1 && InputSys->inputs.Click.clickpos.x <= x2 && InputSys->inputs.Click.clickpos.y >= y1 && InputSys->inputs.Click.clickpos.y <= y2)
				return true;
			
	}

	return false;
}

const Texture * HARIKEN::UIObject::getImage()
{
	return image;
}

void HARIKEN::UIObject::realSetText()
{

	request.requestMade = false;

	if (request.text == text && request.size == fontSize)
		return;

	for (auto m : model) {
		delete m;
	}
	model.clear();

	text = request.text;
	fontSize = request.size;

	characterMap = fontHandler->getCharacterMap(fontName, fontSize, text.c_str());

	float x = 0.0f;
	float y = 0.0f;

	for (std::u16string::const_iterator c = text.begin(); c != text.end(); c++)
	{

		Character ch = characterMap->at(*c);

		GLfloat xpos = x;
		GLfloat ypos = y;

		GLfloat w = ch.Size.x;
		GLfloat h = ch.Size.y;

		imageFrame* temp = new imageFrame(w, h, ch.TextureID, true);
		temp->setPosition(glm::vec3(xpos + ch.Size.x / 2 + ch.Bearing.x, ypos - ch.Size.y / 2 + (ch.Size.y - ch.Bearing.y), 0.0f));
		temp->getMeshProperties()->color = request.color;

		model.push_back(temp);
		imagepos.push_back(glm::vec2());

		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6); // Bitshift by 6 to get value in pixels (2^6 = 64)
	}

}
