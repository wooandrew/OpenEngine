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

#include "orthocam.hpp"

#include <GLM/gtc/matrix_transform.hpp>

#include <OpenEngine/Input/keyboard.hpp>
#include <OpenEngine/Input/mouse.hpp>

namespace OpenEngine {

	OrthoCam::OrthoCam(float left, float right, float bottom, float top, float speed)
		: ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), ViewMatrix(1.0f), speed(speed) {

		zoom = 1.f;

		lock = false;

		LockUp = false;
		LockDown = false;
		LockLeft = false;
		LockRight = false;

		position = glm::vec3();
		rotation = 0;

		ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
	}

	void OrthoCam::Lock(bool lock) {
		this->lock = lock;
	}

	void OrthoCam::Lock(std::vector<MovementMacros> directions, std::vector<bool> lock) {

		if (directions.size() != lock.size()) {
			utilities::Logger<std::string, std::string>("OC_01", "Error: directions size does not match lock size -> [", std::to_string(directions.size()), " ,", std::to_string(lock.size()), "].");
			return;
		}

		for (int x = 0; x < directions.size(); x++) {

			if (directions[x] == MovementMacros::UP)
				LockUp = lock[x];
			else if (directions[x] == MovementMacros::DOWN)
				LockDown = lock[x];
			else if (directions[x] == MovementMacros::LEFT)
				LockLeft = lock[x];
			else if (directions[x] == MovementMacros::RIGHT)
				LockRight = lock[x];
		}
	}

	void OrthoCam::SetSpeed(float speed) {
		this->speed = speed;
	}

	void OrthoCam::SetProjection(float left, float right, float bottom, float top) {

		ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
	}

	void OrthoCam::SetZoom(float zoom, utilities::Dimensions2D<int> windowSize) {
		
		if (zoom > 0.0f) {
		
			this->zoom = zoom;

			float width = static_cast<float>(windowSize.width) / 2.f;
			float height = static_cast<float>(windowSize.height) / 2.f;

			SetProjection(-width * zoom, width * zoom, -height * zoom, height * zoom);
		}
	}

	float OrthoCam::GetRotation() const {
		return rotation;
	}
	void OrthoCam::SetRotation(float rotation) {
		this->rotation = rotation;
	}

	const glm::vec3& OrthoCam::GetPosition() const {
		return position;
	}
	void OrthoCam::SetPosition(const glm::vec3& position) {
		this->position = position;
		RecalculateMatrix();
	}

	const glm::mat4& OrthoCam::GetProjectionMatrix() const {
		return ProjectionMatrix;
	}
	const glm::mat4& OrthoCam::GetViewMatrix() const {
		return ViewMatrix;
	}
	const glm::mat4& OrthoCam::GetViewProjectionMatrix() const {
		return ViewProjectionMatrix;
	}

	void OrthoCam::RecalculateMatrix() {

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), glm::vec3(0, 0, 1));

		ViewMatrix = glm::inverse(transform);
		ViewProjectionMatrix = ProjectionMatrix * ViewMatrix;
	}

	void OrthoCam::UpdateCamera(float dt) {

		if (!lock) {

			if (Keyboard::KeyIsPressed(KeyMap::KM_Up) && !LockUp) {
				position.x += -sin(glm::radians(rotation)) * speed * dt;
				position.y += cos(glm::radians(rotation)) * speed * dt;
			}
			else if (Keyboard::KeyIsPressed(KeyMap::KM_Down) && !LockDown) {
				position.x -= -sin(glm::radians(rotation)) * speed * dt;
				position.y -= cos(glm::radians(rotation)) * speed * dt;
			}

			if (Keyboard::KeyIsPressed(KeyMap::KM_Left) && !LockLeft) {
				position.x -= cos(glm::radians(rotation)) * speed * dt;
				position.y -= sin(glm::radians(rotation)) * speed * dt;
			}
			else if (Keyboard::KeyIsPressed(KeyMap::KM_Right) && !LockRight) {
				position.x += cos(glm::radians(rotation)) * speed * dt;
				position.y += sin(glm::radians(rotation)) * speed * dt;
			}

			RecalculateMatrix();
		}
	}
}
