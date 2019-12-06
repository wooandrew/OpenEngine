// OpenEngine (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

/* OpenEngine is a game engine built on
 * OpenGL using related dependencies.
 *
 * This project is built on CMake using the MSVC C++ Compiler
 * This is to attempt Linux cross-compadibility, however, the
 * project itself was built on and is optimized for Windows.
 *
 * License: Modified MIT & Public Domain
 * Note: Modifications made to the MIT License are marked by ">".
 *
 * This software is dual-licensed to the public domain and under the following
 * license:
 *
 * Start License
 *
 * Copyright 2019 Andrew Woo
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * Restrictions:
 >  The Software may not be sold unless significant, mechanics changing modifications are made by the seller, or unless the buyer
 >  understands an unmodified version of the Software is available elsewhere free of charge, and agrees to buy the Software given
 >  this knowledge.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * End License
**/

#pragma once

#ifndef OPEN_ENGINE_2D_RENDERER_CHPP
#define OPEN_ENGINE_2D_RENDERER_CHPP

#include <vector>

//#include <GLFW/src/glfw3.h>
#include <GLM/glm.hpp>

#include <OpenEngine/UI/button.hpp>

#include <OpenEngine/Graphics/2D/orthocam.hpp>
#include <OpenEngine/Graphics/2D/shader.hpp>
#include <OpenEngine/Graphics/2D/splashscreen.hpp>
#include <OpenEngine/Graphics/2D/sprite.hpp>
#include <OpenEngine/Graphics/2D/texture.hpp>
#include <OpenEngine/Graphics/2D/vertexarray.hpp>

namespace OpenEngine {

	class Render2D {

		/// OpenEngine -> 2D Renderer \\\

	public:

		static void init();
		static void shutdown();

		static void StartScene(const OrthoCam& camera);
		static void EndScene();

		static void RenderSplashScreens(GLFWwindow* window, const glm::vec2& position, const std::vector<std::shared_ptr<SplashScreen>>& SplashScreens);

		static void Fade(GLFWwindow* window, const glm::vec2& position, const std::shared_ptr<Texture>& texture, float fadetime = 10);
		static void Fade(GLFWwindow* window, const glm::vec3& position, const std::shared_ptr<Texture>& texture, float fadetime = 10);
		static void Fade(GLFWwindow* window, const glm::vec2& position, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, float fadetime = 10);
		static void Fade(GLFWwindow* window, const glm::vec3& position, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, float fadetime = 10);

		static void RenderSprite(const std::shared_ptr<Sprite>& sprite);

		static void RenderButton(const std::shared_ptr<Button>& button);

		static void RenderTexture(const glm::vec2& position, const std::shared_ptr<Texture>& texture);
		static void RenderTexture(const glm::vec3& position, const std::shared_ptr<Texture>& texture);
		static void RenderTexture(const glm::vec2& position, const glm::vec2& scale, const std::shared_ptr<Texture>& texture);
		static void RenderTexture(const glm::vec3& position, const glm::vec2& scale, const std::shared_ptr<Texture>& texture);

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	};
}

#endif // !OPEN_ENGINE_2D_RENDERER_CHPP
