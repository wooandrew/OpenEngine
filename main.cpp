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

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include <OpenEngine/engine.hpp>

#include <OpenEngine/Physics/collision.hpp>
#include <OpenEngine/Physics/rigidbody.hpp>

#include <OpenEngine/Audio/audio.hpp>

#include <OpenEngine/Input/keyboard.hpp>
#include <OpenEngine/Input/mouse.hpp>
#include <OpenEngine/Input/input_macros.hpp>

#include <OpenEngine/UI/button.hpp>

#include <OpenEngine/Graphics/graphics.hpp>
#include <OpenEngine/Graphics/2D/renderer.hpp>
#include <OpenEngine/Graphics/2D/splashscreen.hpp>
#include <OpenEngine/Graphics/2D/sprite.hpp>
#include <OpenEngine/Graphics/2D/spritesheet.hpp>
#include <OpenEngine/Graphics/2D/texture.hpp>

#include <ASWL/utilities.hpp>

#define DEBUG

int TestNamespaceUtilities() {

	util::Logger("Hello World", true);

	std::string error = "xxxxx";
	std::string passArgs[] = { "Hello ", "World, @ [", "Andrew", "]." };
	util::Logger(error, std::string("ss"), passArgs[0], passArgs[1], passArgs[2], passArgs[3]);
	util::Logger('\n', false);
	util::Logger(error.c_str(), "ss");

	std::vector<std::string> rt = util::split("\nHello World! 22223,232,1212", ',');

	for (std::string r : rt)
		std::cout << r << " ";

	std::cout << '\n' << util::GetDateTime() << " -> " << util::GetDateTime("ctd") << std::endl;

	util::DeltaTime dt1;

	for (int x = 0; x < 10; x++) {
		std::cout << x << " " << dt1.GetDeltaTime() << std::endl;
		dt1.UpdateDeltaTime();
	}

	std::cout << std::endl;

	double tFPS = 0;
	util::DeltaTime dt2;

	int x = 0;
	dt2.UpdateDeltaTime(true);
	for (x = 0; x < 10000000; x++) {
		util::FramesPerSecond::UpdateFPS();
		std::cout << "";
		tFPS += util::FramesPerSecond::GetFPS();
	}
	dt2.UpdateDeltaTime();

	std::cout << x << " -- "  << dt2.GetDeltaTime() << " ----- " << tFPS/10000000 << std::endl;

	std::ifstream fileExists("file.txt");

	if (!fileExists) {
		std::ofstream file("log.OElog");
		file << "CREATED -> " << util::GetDateTime("ctd");
	}

	std::fstream file("file.txt", std::ios::out | std::ios::app);

	util::RedirectIOStream(std::ref(file), 1);
	util::Logger("RedirectIOStream test -> cerr", true);
	util::RedirectIOStream(std::ref(file), 6);
	util::Logger("UndirectIOStream test -> cerr", true);
	util::RedirectIOStream(std::ref(file), 1, true);
	util::RedirectIOStream(std::ref(file), 6);

	return 0;
}

int main() {

	//TestNamespaceUtilities();

	utilities::SilenceWarnings();

	// Initialize Engine
	OpenEngine::Engine engine;

	int engineInitReturnValue = engine.init();
	if (engineInitReturnValue != 0)
		return engineInitReturnValue;
	else
		util::Logger("  E  ", "Engine initializaiton success. All systems go!");

	// Initialize OpenEngine
	OpenEngine::Audio::init();
	OpenEngine::Graphics::init();
	OpenEngine::Render2D::init();
	OpenEngine::Mouse::init();

	// Initialize Primary Camera
	OpenEngine::OrthoCam PrimaryOrthoCam(static_cast<float>(-OpenEngine::Engine::WindowDimensions.width / 2.f), static_cast<float>(OpenEngine::Engine::WindowDimensions.width / 2.f), 
		static_cast<float>(-OpenEngine::Engine::WindowDimensions.height / 2.f), static_cast<float>(OpenEngine::Engine::WindowDimensions.height / 2.f), 500.f);

	// Button Cam
	OpenEngine::OrthoCam ButtonCam(static_cast<float>(-OpenEngine::Engine::WindowDimensions.width / 2.f), static_cast<float>(OpenEngine::Engine::WindowDimensions.width / 2.f),
		static_cast<float>(-OpenEngine::Engine::WindowDimensions.height / 2.f), static_cast<float>(OpenEngine::Engine::WindowDimensions.height / 2.f), 500.f);

	// Initialize Delta Time
	utilities::DeltaTime dt;

	bool run = true;

	auto splashLogo1 = OpenEngine::SplashScreen(R"(C:\Users\Andrew\Pictures\logo1819.png)", 10.f, 0.75f);
	auto splashLogo2 = OpenEngine::SplashScreen(R"(C:\Users\Andrew\Documents\Projects\OpenEngine\Assets\Logo\oelogo.png)", 10.f, 0.75f);
	auto splashLogo3 = OpenEngine::SplashScreen(R"(C:\Users\Andrew\Documents\Projects\OpenEngine\Assets\Splash\splash.png)", 10.f);
	auto splash_logo1819 = std::make_shared<OpenEngine::SplashScreen>(splashLogo1);
	auto splash_logoh19 = std::make_shared<OpenEngine::SplashScreen>(splashLogo2);
	auto splash_logo = std::make_shared<OpenEngine::SplashScreen>(splashLogo3);

	OpenEngine::Sprite sprite(R"(C:\Users\Andrew\Pictures\aw.png)", { 0, 0 }, { 0.2f, 0.2f }, 10.f);
	auto spritePtr = std::make_shared<OpenEngine::Sprite>(sprite);

	OpenEngine::UI::Button button(R"(C:\Users\Andrew\Documents\Projects\OpenEngine\Assets\test.png)", { -405, -275, 0.1 });
	auto buttonPtr = std::make_shared<OpenEngine::UI::Button>(button);

	OpenEngine::SpriteSheet spritesheet(R"(C:\Users\Andrew\Documents\Projects\OpenEngine\Assets\ss.png)", 4, 4, 10.f, 500.f, { 0, 0 }, 1.f);
	auto ssptr = std::make_shared<OpenEngine::SpriteSheet>(spritesheet);

	OpenEngine::Graphics::BeginRender();
	OpenEngine::Render2D::StartScene(PrimaryOrthoCam);

	OpenEngine::Render2D::RenderSplashScreens(engine.GetWindow(), { 0, 0 }, { splash_logo1819, splash_logoh19, splash_logo });

	OpenEngine::Render2D::EndScene();
	OpenEngine::Graphics::EndRender(engine.GetWindow());

	PrimaryOrthoCam.Lock(true);
	
	float zoom = 1.f;

	OpenEngine::Physics::Rigidbody rb(spritePtr->GetPosition(), { spritePtr->GetTexture()->GetDimensions().width, spritePtr->GetTexture()->GetDimensions().height, 0 }, spritePtr->GetScale());

	glm::vec3 rbPos = glm::vec3();
	glm::vec3 rbSize = glm::vec3(50.f);
	float rbRot = 0.0f;
	OpenEngine::Physics::Rigidbody r1(rbPos, rbSize);

	OpenEngine::Graphics::SetClearColor({ 1, 1, 1, 1 });
	while (!glfwWindowShouldClose(engine.GetWindow()) && run) {

		// *** GAME LOGIC *** //
		if (OpenEngine::Keyboard::KeyIsPressed(OpenEngine::OEKeyboardKeys::OE_KEY_K)) {
			zoom += 0.5f * static_cast<float>(dt.GetDeltaTime());
			PrimaryOrthoCam.SetZoom(zoom, OpenEngine::Engine::WindowDimensions);
		}
		else if (OpenEngine::Keyboard::KeyIsPressed(OpenEngine::OEKeyboardKeys::OE_KEY_L)) {
			zoom -= 0.5f * static_cast<float>(dt.GetDeltaTime());
			PrimaryOrthoCam.SetZoom(zoom, OpenEngine::Engine::WindowDimensions);
		}

		static int counter = 0;

		if (button.IsPressed())
			std::cout << "Wowzers! " << counter++ << std::endl;

		// *** GAME LOGIC *** //

		// *** UPDATE *** //
		dt.UpdateDeltaTime();
		engine.Update();

		PrimaryOrthoCam.UpdateCamera(static_cast<float>(dt.GetDeltaTime()));

		spritePtr->Update(static_cast<float>(dt.GetDeltaTime()));
		ssptr->UpdateSprite(static_cast<float>(dt.GetDeltaTime()));

		rb.Update(spritePtr->GetPosition(), spritePtr->GetRotation());
		r1.Update(rbPos, rbRot);
		// *** UPDATE *** //

		// *** RENDER LOGIC *** //
		OpenEngine::Graphics::BeginRender();

		OpenEngine::Render2D::StartScene(PrimaryOrthoCam);
		OpenEngine::Render2D::DrawQuad(rb.LowerLeftVertex, { 5, 5 }, { 2, 0, 0, 1 });
		OpenEngine::Render2D::DrawQuad(rb.UpperLeftVertex, { 5, 5 }, { 2, 0, 0, 1 });
		OpenEngine::Render2D::DrawQuad(rb.LowerRightVertex, { 5, 5 }, { 2, 0, 0, 1 });
		OpenEngine::Render2D::DrawQuad(rb.UpperRightVertex, { 5, 5 }, { 2, 0, 0, 1 });
		OpenEngine::Render2D::RenderSprite(spritePtr);

		if (OpenEngine::Physics::Collision::SeparatingAxisTheorem(rb, r1))
			OpenEngine::Render2D::DrawQuad(rbPos, rbSize, { 0, 255, 0, 1.f });
		else
			OpenEngine::Render2D::DrawQuad(rbPos, rbSize, { 0, 0, 0, 1.f });
		OpenEngine::Render2D::RenderSpriteSheet(ssptr);
		OpenEngine::Render2D::EndScene();

		OpenEngine::Render2D::StartScene(ButtonCam);
		OpenEngine::Render2D::RenderButton(buttonPtr);
		OpenEngine::Render2D::EndScene();

		OpenEngine::Graphics::EndRender(engine.GetWindow());
		// *** RENDER LOGIC *** //
	}

	OpenEngine::Graphics::shutdown();
	OpenEngine::Render2D::shutdown();
	OpenEngine::Audio::shutdown();

	glfwTerminate();

	return 0;
}
