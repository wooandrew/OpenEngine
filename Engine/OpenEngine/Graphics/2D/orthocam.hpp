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

#ifndef OPEN_ENGINE_2D_ORTHOCAM_CHPP
#define OPEN_ENGINE_2D_ORTHOCAM_CHPP

#include <string>
#include <vector>

#include <GLM/glm.hpp>
#include <ASWU/utilities.hpp>

#include <OpenEngine/Input/keymap.hpp>

namespace OpenEngine {

	class OrthoCam {

		/// OpenEngine -> Basic Orthographic Camera Class \\\

	public:

		OrthoCam() = default;
		OrthoCam(float left, float right, float bottom, float top, float speed = 0);

		void Lock(bool lock = false);
		void Lock(std::vector<MovementMacros> directions, std::vector<bool> lock);

		void SetSpeed(float speed);

		void SetProjection(float left, float right, float bottom, float top);

		void SetZoom(float zoom, utilities::Dimensions2D<int> windowSize);

		float GetRotation() const;
		void SetRotation(float rotation);

		const glm::vec3& GetPosition() const;
		void SetPosition(const glm::vec3& position);

		const glm::mat4& GetProjectionMatrix() const;
		const glm::mat4& GetViewMatrix() const;
		const glm::mat4& GetViewProjectionMatrix() const;

		virtual void UpdateCamera(float dt);

	private:

		void RecalculateMatrix();

		bool lock;

		bool LockUp;
		bool LockDown;
		bool LockLeft;
		bool LockRight;

		float speed;

		glm::mat4 ProjectionMatrix;
		glm::mat4 ViewMatrix;
		glm::mat4 ViewProjectionMatrix;

		float zoom;
		float rotation;
		glm::vec3 position;
	};
}

#endif // !OPEN_ENGINE_2D_ORTHOCAM_CHPP
