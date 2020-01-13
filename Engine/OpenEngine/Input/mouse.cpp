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

#include "mouse.hpp"

namespace OpenEngine {

	double Mouse::x = 0;
	double Mouse::y = 0;

	bool Mouse::Buttons[GLFW_MOUSE_BUTTON_LAST] = { 0 };
	bool Mouse::ButtonsDown[GLFW_MOUSE_BUTTON_LAST] = { 0 };
	bool Mouse::ButtonsUp[GLFW_MOUSE_BUTTON_LAST] = { 0 };

	std::pair<int, int> Mouse::origin = std::make_pair(500, 309);

	void Mouse::init(std::pair<int, int> _origin) {
		origin = _origin;
	}

	void Mouse::MousePositionCallback(GLFWwindow* window, double _x, double _y) {

		int width;
		int height;

		glfwGetFramebufferSize(window, &width, &height);

		x = _x;
		y = height - _y;
	}

	void Mouse::MouseButtonCallback(GLFWwindow* window, int button, int action, int modifiers) {

		if (button < 0)
			return;

		if ((action != GLFW_RELEASE) && (!Buttons[button])) {
			ButtonsDown[button] = true;
			ButtonsUp[button] = false;
		}

		if ((action == GLFW_RELEASE) && (Buttons[button])) {
			ButtonsDown[button] = false;
			ButtonsUp[button] = true;
		}

		Buttons[button] = action != GLFW_RELEASE;
	}

	double Mouse::GetMouseX() {
		return x - origin.first;
	}
	double Mouse::GetMouseY() {
		return y - origin.second;
	}

	void Mouse::SetOrigin(std::pair<int, int> _origin) {
		origin = _origin;
	}

	bool Mouse::ButtonDown(int button) {

		bool buttonsDown = ButtonsDown[button];
		ButtonsDown[button] = false;

		return buttonsDown;
	}

	bool Mouse::ButtonUp(int button) {

		bool buttonUp = ButtonsUp[button];
		ButtonsUp[button] = false;

		return buttonUp;
	}

	bool Mouse::ButtonIsPressed(int button) {
		return Buttons[button];
	}
}
