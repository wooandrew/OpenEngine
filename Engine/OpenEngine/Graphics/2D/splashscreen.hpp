// OpenEngine (c) Andrew Woo, 2019-2020
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
 * Copyright 2019-2020 Andrew Woo
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

#ifndef OPEN_ENGINE_SPLASH_SCREEN_CHPP
#define OPEN_ENGINE_SPLASH_SCREEN_CHPP

#include <string>
#include <vector>

#include <OpenEngine/Graphics/2D/texture.hpp>

#include <GLFW/src/glfw3.h>
#include <GLM/glm.hpp>

namespace OpenEngine {

	class SplashScreen {
		
		/// OpenEngine -> Splashscreen Class \\\

	public:

		SplashScreen(const std::string& TexturePath, const float fadetime, const glm::vec3& scale = glm::vec3(1.f));
        SplashScreen(const std::string& TexturePath, const float fadetime, const float scale);

		const float GetFadeTime() const;
		void SetFadeTime(float fadetime);

		const glm::vec3& GetScale() const;
		void SetScale(const glm::vec3& scale);

        const std::shared_ptr<Texture>& GetTexture() const;

	private:

        std::shared_ptr<Texture> texture;

		float FadeTime;
		glm::vec3 scale;
	};
}

#endif // !OPEN_ENGINE_SPLASH_SCREEN_CHPP
