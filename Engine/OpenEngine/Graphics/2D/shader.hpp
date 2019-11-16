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

#ifndef OPEN_ENGINE_2D_SHADER_CHPP
#define OPEN_ENGINE_2D_SHADER_CHPP

#include <string>
#include <unordered_map>

#include <GLM/glm.hpp>

namespace OpenEngine {

	class Shader {

		/// OpenEngine -> Shader class \\\

	public:

		Shader() = default;
		Shader(const std::string& shaderPath);

		void Bind() const;
		void Unbind() const;

		void SetInt(const std::string& name, int value);
		void SetFloat3(const std::string& name, const glm::vec3& value);
		void SetFloat4(const std::string& name, const glm::vec4& value);
		void SetMat4(const std::string& name, const glm::mat4& value);

		std::string GetName() const;

		void init(const std::string& shaderPath);
		// void Create(const std::string& name, const std::string& vertexSource, const std::string fragmentSource);

		void UploadUniformInt(const std::string& name, int value);

		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:

		unsigned int RendererID;
		std::string name;
	};

	class ShaderLibrary {

	public:

		void Add(const std::string& name, const Shader& shader);
		void Add(const Shader& shader);

		Shader Load(const std::string& shaderPath);
		Shader Load(const std::string& name, const std::string& shaderPath);

		Shader Get(const std::string& name);

		bool Exists(const std::string& name) const;

	private:

		std::unordered_map<std::string, Shader> Shaders;
	};
}

#endif // !OPEN_ENGINE_2D_SHADER_CHPP
