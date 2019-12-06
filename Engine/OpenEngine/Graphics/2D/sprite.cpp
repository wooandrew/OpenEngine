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

#include "sprite.hpp"

#include <OpenEngine/Input/keyboard.hpp>
#include <OpenEngine/Input/mouse.hpp>

namespace OpenEngine {

	Sprite::Sprite(const unsigned int width, const unsigned int height, const glm::vec2& position, const float scale, float speed, float rotation) {
		
		texture = std::make_shared<Texture>(width, height);

		lock = false;

		LockUp = false;
		LockDown = false;
		LockLeft = false;
		LockRight = false;

		this->speed = speed;
		this->rotation = rotation;

		this->position = { position.x, position.y, 0.0f };
		this->scale = glm::vec3(scale);
	}
	Sprite::Sprite(const unsigned int width, const unsigned int height, const glm::vec2& position, const glm::vec2& scale, float speed, float rotation) {
	
		texture = std::make_shared<Texture>(width, height);

		lock = false;

		LockUp = false;
		LockDown = false;
		LockLeft = false;
		LockRight = false;

		this->speed = speed;
		this->rotation = rotation;

		this->position = { position.x, position.y, 0.0f };
		this->scale = { scale.x, scale.y, 1.0f };
	}
	Sprite::Sprite(const unsigned int width, const unsigned int height, const glm::vec3& position, const float scale, float speed, float rotation) {

		texture = std::make_shared<Texture>(width, height);

		lock = false;

		LockUp = false;
		LockDown = false;
		LockLeft = false;
		LockRight = false;

		this->speed = speed;
		this->rotation = rotation;

		this->position = { position.x, position.y, 0.0f };
		this->scale = glm::vec3(scale);
	}
	Sprite::Sprite(const unsigned int width, const unsigned int height, const glm::vec3& position, const glm::vec3& scale, float speed, float rotation) {

		texture = std::make_shared<Texture>(width, height);

		lock = false;

		LockUp = false;
		LockDown = false;
		LockLeft = false;
		LockRight = false;

		this->speed = speed;
		this->rotation = rotation;

		this->position = { position.x, position.y, position.z };
		this->scale = { scale.x, scale.y, scale.z };
	}
	Sprite::Sprite(const std::string& TexturePath, const glm::vec2& position, const float scale, float speed, float rotation) {
		
		texture = std::make_shared<Texture>(TexturePath);

		lock = false;

		LockUp = false;
		LockDown = false;
		LockLeft = false;
		LockRight = false;

		this->speed = speed;
		this->rotation = rotation;

		this->position = { position.x, position.y, 0.0f };
		this->scale = glm::vec3(scale);
	}
	Sprite::Sprite(const std::string& TexturePath, const glm::vec2& position, const glm::vec2& scale, float speed, float rotation) {

		texture = std::make_shared<Texture>(TexturePath);

		lock = false;

		LockUp = false;
		LockDown = false;
		LockLeft = false;
		LockRight = false;

		this->speed = speed;
		this->rotation = rotation;

		this->position = { position.x, position.y, 0.0f };
		this->scale = { scale.x, scale.y, 1.0f };
	}
	Sprite::Sprite(const std::string& TexturePath, const glm::vec3& position, const float scale, float speed, float rotation) {

		texture = std::make_shared<Texture>(TexturePath);

		lock = false;

		LockUp = false;
		LockDown = false;
		LockLeft = false;
		LockRight = false;

		this->speed = speed;
		this->rotation = rotation;

		this->position = position;
		this->scale = glm::vec3(scale);
	}
	Sprite::Sprite(const std::string& TexturePath, const glm::vec3& position, const glm::vec3& scale, float speed, float rotation) {

		texture = std::make_shared<Texture>(TexturePath);

		lock = false;

		LockUp = false;
		LockDown = false;
		LockLeft = false;
		LockRight = false;

		this->speed = speed;
		this->rotation = rotation;

		this->position = position;
		this->scale = scale;
	}

	void Sprite::Update(float dt) {

		if (!lock) {

			if (!(Keyboard::KeyIsPressed(KeyMap::KM_Up) && Keyboard::KeyIsPressed(KeyMap::KM_Down))) {

				if (Keyboard::KeyIsPressed(KeyMap::KM_Up) && !LockUp) {
					//position.x += -sin(glm::radians(rotation)) * speed * dt;
					position.y += /*cos(glm::radians(rotation)) */ speed * dt;
				}
				else if (Keyboard::KeyIsPressed(KeyMap::KM_Down) && !LockDown) {
					//position.x -= -sin(glm::radians(rotation)) * speed * dt;
					position.y -= /*cos(glm::radians(rotation)) */ speed * dt;
				}
			}

			if (!(Keyboard::KeyIsPressed(KeyMap::KM_Left) && Keyboard::KeyIsPressed(KeyMap::KM_Right))) {
			
				if (Keyboard::KeyIsPressed(KeyMap::KM_Left) && !LockLeft) {
					position.x -= /*cos(glm::radians(rotation)) */ speed * dt;
					//position.y -= sin(glm::radians(rotation)) * speed * dt;
				}
				else if (Keyboard::KeyIsPressed(KeyMap::KM_Right) && !LockRight) {
					position.x += /*cos(glm::radians(rotation)) */ speed * dt;
					//position.y += sin(glm::radians(rotation)) * speed * dt;
				}
			}

			if (Keyboard::KeyIsPressed(KeyMap::rLeft)) {
				rotation += 500.f * dt;
				rotation = std::fmodf(rotation, 360);
			}
			else if (Keyboard::KeyIsPressed(KeyMap::rRight)) {
				rotation -= 500.f * dt;
				rotation = std::fmodf(rotation, 360);
			}
		}
	}

	void Sprite::Lock(bool lock) {
		this->lock = lock;
	}
	void Sprite::Lock(std::vector<MovementMacros> directions, std::vector<bool> lock) {

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

	void Sprite::SetSpeed(float speed) {
		this->speed = speed;
	}

	void Sprite::SetRotation(float rotation) {
		this->rotation = rotation;
	}

	void Sprite::SetPosition(const float position) {
		SetPosition({ position, position, position });
	}
	void Sprite::SetPosition(const glm::vec2& position) {
		SetPosition({ position.x, position.y, 0.f });
	}
	void Sprite::SetPosition(const glm::vec3& position) {
		this->position = position;
	}

	void Sprite::SetScale(const float scale) {
		SetScale({ 1.f, 1.f, 1.f });
	}
	void Sprite::SetScale(const glm::vec2& scale) {
		SetScale({ scale.x, scale.y, 1.f });
	}
	void Sprite::SetScale(const glm::vec3& scale) {
		this->scale = scale;
	}

	const float Sprite::GetRotation() const {
		return rotation;
	}
	const glm::vec3& Sprite::GetScale() const {
		return scale;
	}
	const glm::vec3& Sprite::GetPosition() const {
		return position;
	}

	const std::shared_ptr<Texture>& Sprite::GetTexture() const {
		return texture;
	}
}
