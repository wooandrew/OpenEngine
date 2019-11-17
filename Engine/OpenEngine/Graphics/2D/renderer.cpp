// OpenEngine (c) Andrew Woo, 2019
// Email: seungminleader@gmail.com
// Website: https://wooandrew.github.io

/* OpenEngine is a game engine built on
 * OpenGL using related dependencies.
 *
 * This project is built on CMake using the MSVC C++ Comglm::pi<float>()ler
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
 * and/or sell coglm::pi<float>()es of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all coglm::pi<float>()es or substantial portions of the Software.
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

#include "renderer.hpp"

#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/constants.hpp>

#include <OpenEngine/Graphics/graphics.hpp>

namespace OpenEngine {

	struct Render2DStorage {

		Render2DStorage() = default;

		std::shared_ptr<VertexArray> QuadVertexArray;
		std::shared_ptr<Shader> TextureShader;
		std::shared_ptr<Texture> WhiteTexture;
	};

	static Render2DStorage* RenderData;

	void Render2D::init() {

		RenderData = new Render2DStorage();
		RenderData->QuadVertexArray = std::make_shared<VertexArray>();

		float squareVertices[5 * 4] = {

			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // Bottom Left
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Bottom Right
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // Top Right
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f  // Top Left 
		};

		std::shared_ptr<VertexBuffer> squareVB = std::make_shared<VertexBuffer>(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({ { ShaderDataType::Float3, "a_Position" }, { ShaderDataType::Float2, "a_TexCoord" } });
		RenderData->QuadVertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIB = std::make_shared<IndexBuffer>(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		RenderData->QuadVertexArray->SetIndexBuffer(squareIB);

		RenderData->WhiteTexture = std::make_shared<Texture>(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		RenderData->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		RenderData->TextureShader = std::make_shared<Shader>("Assets/Shaders/texture.glsl");
		RenderData->TextureShader->Bind();
		RenderData->TextureShader->SetInt("u_Texture", 0);
	}

	void Render2D::shutdown() {
		delete RenderData;
	}

	void Render2D::StartScene(const OrthoCam& camera) {
		RenderData->TextureShader->Bind();
		RenderData->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Render2D::EndScene() { }

	void Render2D::RenderSplashScreens(GLFWwindow* window, const glm::vec2& position, const std::vector<std::shared_ptr<SplashScreen>>& splashScreens) {

		for (auto splash : splashScreens) {

			utilities::DeltaTime fadetimer;

			float alpha = 0;
			float period = (2 * glm::pi<float>()) / splash->GetFadeTime();

			float timePassed = 0;

			while (timePassed < (splash->GetFadeTime() - (splash->GetFadeTime() / 4))) {

				glfwPollEvents();

				timePassed += static_cast<float>(fadetimer.GetDeltaTime());

				alpha = std::sin((timePassed * period) - (glm::pi<float>() / splash->GetFadeTime()));

				RenderData->TextureShader->SetFloat4("u_Color", { 1.f, 1.f, 1.f, alpha });
				splash->Bind();

				float tempWidth = static_cast<float>(splash->GetDimensions().width)* splash->GetScale().x;
				float tempHeight = static_cast<float>(splash->GetDimensions().height)* splash->GetScale().y;

				glm::mat4 transform = glm::translate(glm::mat4(1.0f), { position.x, position.y, -0.1f }) * glm::scale(glm::mat4(1.0f), { tempWidth, tempHeight, 1.0f });
				RenderData->TextureShader->SetMat4("u_Transform", transform);

				RenderData->QuadVertexArray->Bind();

				Graphics::BeginRender();
				Graphics::DrawIndexed(RenderData->QuadVertexArray);
				Graphics::EndRender(window);

				fadetimer.UpdateDeltaTime();
			}
		}
	}

	void Render2D::Fade(GLFWwindow* window, const glm::vec2& position, const std::shared_ptr<Texture>& texture, float fadetime) {
		Fade(window, { position.x, position.y, 0.0f }, texture, fadetime);
	}
	void Render2D::Fade(GLFWwindow* window, const glm::vec3& position, const std::shared_ptr<Texture>& texture, float fadetime) {

		utilities::DeltaTime fadetimer;

		float alpha = 0;
		float period = (2 * glm::pi<float>()) / fadetime;

		float timePassed = 0;

		while (timePassed < (fadetime - (fadetime / 4))) {

			timePassed += static_cast<float>(fadetimer.GetDeltaTime());

			alpha = std::sin((timePassed * period) - (glm::pi<float>() / fadetime));

			RenderData->TextureShader->SetFloat4("u_Color", { 1.f, 1.f, 1.f, alpha });
			texture->Bind();

			float tempWidth = static_cast<float>(texture->GetDimensions().width);
			float tempHeight = static_cast<float>(texture->GetDimensions().height);

			glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { tempWidth, tempHeight, 1.0f });
			RenderData->TextureShader->SetMat4("u_Transform", transform);

			RenderData->QuadVertexArray->Bind();

			Graphics::BeginRender();
			Graphics::DrawIndexed(RenderData->QuadVertexArray);
			Graphics::EndRender(window);

			fadetimer.UpdateDeltaTime();
		}
	}
	void Render2D::Fade(GLFWwindow* window, const glm::vec2& position, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, float fadetime) {
		Fade(window, { position.x, position.y, 0.0f }, scale, texture, fadetime);
	}
	void Render2D::Fade(GLFWwindow* window, const glm::vec3& position, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, float fadetime) {

		utilities::DeltaTime fadetimer;

		float alpha = 0;
		float period = (2 * glm::pi<float>()) / fadetime;

		float timePassed = 0;

		float tempWidth = static_cast<float>(texture->GetDimensions().width)* scale.x;
		float tempHeight = static_cast<float>(texture->GetDimensions().height)* scale.y;

		while (timePassed < (fadetime - (fadetime / 4))) {

			timePassed += static_cast<float>(fadetimer.GetDeltaTime());

			alpha = std::sin((timePassed * period) - (glm::pi<float>() / fadetime));

			RenderData->TextureShader->SetFloat4("u_Color", { 1.f, 1.f, 1.f, alpha });
			texture->Bind();

			glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { tempWidth, tempHeight, 1.0f });
			RenderData->TextureShader->SetMat4("u_Transform", transform);

			RenderData->QuadVertexArray->Bind();

			Graphics::BeginRender();
			Graphics::DrawIndexed(RenderData->QuadVertexArray);
			Graphics::EndRender(window);

			fadetimer.UpdateDeltaTime();
		}
	}

	void Render2D::RenderSprite(const std::shared_ptr<Sprite>& sprite) {

		RenderData->TextureShader->SetFloat4("u_Color", glm::vec4(1.0f));
		sprite->Bind();

		float scaleX = static_cast<float>(sprite->GetDimensions().width)* sprite->GetScale().x;
		float scaleY = static_cast<float>(sprite->GetDimensions().height)* sprite->GetScale().y;
		float scaleZ = 1.f * sprite->GetScale().z;

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), sprite->GetPosition());
		transform = glm::rotate(transform, glm::radians(sprite->GetRotation()), glm::vec3(0.f, 0.f, 1.f));
		transform = glm::scale(transform, { scaleX, scaleY, scaleZ });

		RenderData->TextureShader->SetMat4("u_Transform", transform);

		RenderData->QuadVertexArray->Bind();
		Graphics::DrawIndexed(RenderData->QuadVertexArray);
	}

	void Render2D::RenderButton(const std::shared_ptr<Button>& button) {

		RenderData->TextureShader->SetFloat4("u_Color", glm::vec4(1.0f));
		button->Bind();

		float tempWidth = static_cast<float>(button->GetDimensions().width)* button->GetScale().x;
		float tempHeight = static_cast<float>(button->GetDimensions().height) * button->GetScale().y;

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), button->GetPosition()) * glm::scale(glm::mat4(1.0f), { tempWidth, tempHeight, 1.0f });

		RenderData->TextureShader->SetMat4("u_Transform", transform);

		RenderData->QuadVertexArray->Bind();
		Graphics::DrawIndexed(RenderData->QuadVertexArray);
	}

	void Render2D::RenderTexture(const glm::vec2& position, const std::shared_ptr<Texture>& texture) {
		RenderTexture({ position.x, position.y, 0.0f }, texture);
	}
	void Render2D::RenderTexture(const glm::vec3& position, const std::shared_ptr<Texture>& texture) {

		RenderData->TextureShader->SetFloat4("u_Color", glm::vec4(1.0f));
		texture->Bind();

		float tempWidth = static_cast<float>(texture->GetDimensions().width);
		float tempHeight = static_cast<float>(texture->GetDimensions().height);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { tempWidth, tempHeight, 1.0f });
		RenderData->TextureShader->SetMat4("u_Transform", transform);

		RenderData->QuadVertexArray->Bind();
		Graphics::DrawIndexed(RenderData->QuadVertexArray);
	}
	void Render2D::RenderTexture(const glm::vec2& position, const glm::vec2& scale, const std::shared_ptr<Texture>& texture) {
		RenderTexture({ position.x, position.y, 0.0f }, scale, texture);
	}
	void Render2D::RenderTexture(const glm::vec3& position, const glm::vec2& scale, const std::shared_ptr<Texture>& texture) {

		RenderData->TextureShader->SetFloat4("u_Color", glm::vec4(1.0f));
		texture->Bind();

		float tempWidth = static_cast<float>(texture->GetDimensions().width)* scale.x;
		float tempHeight = static_cast<float>(texture->GetDimensions().height)* scale.y;

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { tempWidth, tempHeight, 1.0f });
		RenderData->TextureShader->SetMat4("u_Transform", transform);

		RenderData->QuadVertexArray->Bind();
		Graphics::DrawIndexed(RenderData->QuadVertexArray);
	}

	void Render2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}
	void Render2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {

		RenderData->TextureShader->SetFloat4("u_Color", color);
		RenderData->WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		RenderData->TextureShader->SetMat4("u_Transform", transform);
		RenderData->QuadVertexArray->Bind();

		Graphics::DrawIndexed(RenderData->QuadVertexArray);
	}
	void Render2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture) {
		DrawQuad({ position.x, position.y, 0.0f }, size, texture);
	}
	void Render2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture>& texture) {

		RenderData->TextureShader->SetFloat4("u_Color", glm::vec4(1.0f));
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		RenderData->TextureShader->SetMat4("u_Transform", transform);

		RenderData->QuadVertexArray->Bind();
		Graphics::DrawIndexed(RenderData->QuadVertexArray);
	}
}
