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

#include "engine.hpp"

#include <OpenEngine/Input/keyboard.hpp>
#include <OpenEngine/Input/mouse.hpp>

namespace OpenEngine {

	utilities::Dimensions2D<int> Engine::WindowDimensions = utilities::make_2d_dimension<int>(1000, 618);

	Engine::Engine(std::string windowTitle, int windowWidth, int windowHeight) {
		WindowTitle = windowTitle;
		WindowDimensions = utilities::make_2d_dimension<int>(windowWidth, windowHeight);
	}

	int Engine::init() {

		// Initialize GLFW
		if (!glfwInit()) {
			utilities::Logger("E0001", "Fatal Error: Failed to initialize GLFW -> !glfwInit().");
			return -1;
		}

		// Create OpenGL Window
		window = glfwCreateWindow(WindowDimensions.width, WindowDimensions.height, WindowTitle.c_str(), NULL, NULL);
		if (!window) {

			utilities::Logger("E0002", "Fatal Error: Failed to create window -> !glfwCreateWindow() ");
			glfwTerminate();

			return -2;
		}

		// Create Window Context
		glfwMakeContextCurrent(window);

		// Initialize GLAD
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			utilities::Logger("E0003", "Fatal Error: Failed to initialize GLAD -> !gladLoadGLLoader().");
			return -3;
		}

		int width;
		int height;

		glfwGetFramebufferSize(window, &width, &height);
		glfwSwapInterval(1);

		// Window Setup
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		int xPos = (mode->width - WindowDimensions.width) / 2;
		int yPos = (mode->height - WindowDimensions.height) / 2;
		glfwSetWindowPos(window, xPos, yPos);

		// Input Callback
		glfwSetKeyCallback(window, Keyboard::KeyCallback);

		glfwSetCursorPosCallback(window, Mouse::MousePositionCallback);
		glfwSetMouseButtonCallback(window, Mouse::MouseButtonCallback);

		glfwSetWindowSizeLimits(window, WindowDimensions.width, WindowDimensions.height, WindowDimensions.width, WindowDimensions.height);

		return 0;
	}

	void Engine::BeginRender() const { // Deprecated
		glad_glClearColor(1.0f, 1.0f, 1.0f, 1);
		glad_glClear(GL_COLOR_BUFFER_BIT);
	}

	void Engine::Update() const {
		glfwPollEvents();
	}

	void Engine::EndRender() const { // Deprecated
		glfwSwapBuffers(window);
	}

	GLFWwindow* Engine::GetWindow() {
		return window;
	}
}
