/***********************************************************************************
Singleton in charge of handling anything related to the game window and starting the rendering chain.
***********************************************************************************/

#pragma once
#include "Scene.h"
#include <Windows.h>
#include <glm.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_syswm.h>
#include <assert.h>
#include <glm.hpp>
#include<memory>

namespace HARIKEN {

	class WindowSys
	{
	public:

		WindowSys(const WindowSys&) = delete;
		WindowSys(WindowSys&&) = delete;
		WindowSys& operator = (const WindowSys&) = delete;
		WindowSys& operator = (WindowSys&&) = delete;

		static WindowSys* GetInstance();

		bool init();
		void update(float deltaTime);
		void render();
		bool shutdown();

		glm::vec2 getWinSize();

		const float* positionScale;
		const float* windowScale;

		const HWND getHWND();
		const HDC getHDC();

		HGLRC getPrimaryContext();
		HGLRC newThreadContext();

	protected:

		SDL_Window * window = NULL;

		SDL_GLContext glContext;

		HGLRC primaryContext;

		glm::vec2 size;

		bool KMS;

	private:

		WindowSys();
		~WindowSys();

		static std::unique_ptr<WindowSys>instance;
		friend std::default_delete<WindowSys>;

		float posScale;
		float winScale; 
		SceneManager* sceneManager;

		SDL_SysWMinfo windowInfo;

	};

}