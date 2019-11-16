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

#include "shader.hpp"

#include <fstream>
#include <vector>
#include <array>

#include <GLAD/glad.h>
#include <GLM/gtc/type_ptr.hpp>
#include <ASWU/utilities.hpp>

namespace OpenEngine {

	// ***********************************************************
	// *** Shader ************************************************
	// ***********************************************************

	Shader::Shader(const std::string& shaderPath) {
		init(shaderPath);
	}

	void Shader::init(const std::string& shaderPath) {

		/*
		std::string source;

		std::ifstream input(shaderPath, std::ios::in | std::ios::binary);
		if (input) {

			input.seekg(0, std::ios::end);
			source.resize(input.tellg());

			input.seekg(0, std::ios::beg);
			input.read(&source[0], source.size());
			input.close();
		}
		else {
			utilities::Logger("S0001", "Error: Could not create shader from source [ERR].");
			return;
		}

		// --- PreProcess

		std::unordered_map<unsigned int, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = std::strlen(typeToken);
		size_t position = source.find(typeToken, 0);

		while (position != std::string::npos) {

			size_t eol = source.find_first_of("\r\n", position);

			if (eol == std::string::npos) {
				utilities::Logger("S0002", "Error: Shader syntax error.");
				return;
			}

			size_t begin = position + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);

			auto StringToShaderType = [type]() { if (type == "vertex") return GL_VERTEX_SHADER; if (type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER; };

			if (type != "vertex" || type != "fragment") {
				utilities::Logger(std::string("S0003"), std::string("Error: Invalid shader type ["), type, std::string("]."));
				//return;
			}

			size_t nextLinePosition = source.find_first_not_of("\r\n", eol);
			if (eol == std::string::npos) {
				utilities::Logger("S0004", "Error: Shader syntax error.");
				return;
			}

			position = source.find(typeToken, nextLinePosition);

			shaderSources[StringToShaderType()] = (position == std::string::npos) ? source.substr(nextLinePosition) : source.substr(nextLinePosition, position - nextLinePosition);
		}*/

		// --- Compile
		std::string vertexSrc = R"(
		#version 330 core

		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec2 a_TexCoord;

		uniform mat4 u_ViewProjection;
		uniform mat4 u_Transform;

		out vec2 v_TexCoord;

		void main()
		{
			v_TexCoord = a_TexCoord;
			gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
		}
	)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;

			uniform vec4 u_Color;
			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord * 1.0) * u_Color;
			}
		)";

		std::unordered_map<GLenum, std::string> shaderSources;
		shaderSources[GL_VERTEX_SHADER] = vertexSrc;
		shaderSources[GL_FRAGMENT_SHADER] = fragmentSrc;

		unsigned int program = glad_glCreateProgram();

		if (shaderSources.size() != 2)
			utilities::Logger("S0005", "Error: 2 Shaders required, min-max.");

		std::array<unsigned int, 2> ShaderIDs;
		int ShaderIDIndex = 0;

		for (auto& shaderSource : shaderSources) {

			GLenum type = shaderSource.first;
			const std::string& tmpSource = shaderSource.second;

			GLuint shader = glad_glCreateShader(type);

			const GLchar* sourceCStr = tmpSource.c_str();
			glad_glShaderSource(shader, 1, &sourceCStr, 0);
			glad_glCompileShader(shader);

			GLint isCompiled = 0;
			glad_glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

			if (isCompiled == GL_FALSE) {

				GLint maxLength = 0;
				glad_glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glad_glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glad_glDeleteShader(shader);

				utilities::Logger<std::string, std::string>("S0006", "Error: Could not compile shader. Info Log ->\n", std::string(infoLog.data()));
				break;
			}

			glad_glAttachShader(program, shader);
			ShaderIDs[ShaderIDIndex++] = shader;
		}

		RendererID = program;

		glad_glLinkProgram(program);
		GLint isLinked = 0;

		glad_glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE) {

			GLint maxLength = 0;
			glad_glGetShaderiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glad_glGetShaderInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glad_glDeleteProgram(program);

			for (auto id : ShaderIDs)
				glad_glDeleteShader(id);

			utilities::Logger<std::string, std::string>("S0007", "Error: Could not link shader program. Info Log -> ERR\n", std::string(infoLog.data()));

			return;
		}

		for (auto id : ShaderIDs) {
			glad_glDetachShader(program, id);
			glad_glDeleteShader(id);
		}

		// ---

		auto lastSlash = shaderPath.find_last_of("/\\");
		lastSlash = (lastSlash == std::string::npos) ? 0 : lastSlash + 1;

		auto lastDot = shaderPath.rfind('.');
		auto count = (lastDot == std::string::npos) ? shaderPath.size() - lastSlash : lastDot - lastSlash;
		name = shaderPath.substr(lastSlash, count);
	}

	std::string Shader::GetName() const {
		return name;
	}

	void Shader::Bind() const {
		glad_glUseProgram(RendererID);
	}

	void Shader::Unbind() const {
		glad_glUseProgram(0);
	}

	void Shader::SetInt(const std::string& name, int value) {
		UploadUniformInt(name, value);
	}

	void Shader::SetFloat3(const std::string& name, const glm::vec3& value) {
		UploadUniformFloat3(name, value);
	}

	void Shader::SetFloat4(const std::string& name, const glm::vec4& value) {
		UploadUniformFloat4(name, value);
	}

	void Shader::SetMat4(const std::string& name, const glm::mat4& value) {
		UploadUniformMat4(name, value);
	}

	void Shader::UploadUniformInt(const std::string& name, int value) {
		GLint location = glad_glGetUniformLocation(RendererID, name.c_str());
		glad_glUniform1i(location, value);
	}

	void Shader::UploadUniformFloat(const std::string& name, float value) {
		GLint location = glad_glGetUniformLocation(RendererID, name.c_str());
		glad_glUniform1f(location, value);
	}

	void Shader::UploadUniformFloat2(const std::string& name, const glm::vec2& value) {
		GLint location = glad_glGetUniformLocation(RendererID, name.c_str());
		glad_glUniform2f(location, value.x, value.y);
	}

	void Shader::UploadUniformFloat3(const std::string& name, const glm::vec3& value) {
		GLint location = glad_glGetUniformLocation(RendererID, name.c_str());
		glad_glUniform3f(location, value.x, value.y, value.z);
	}

	void Shader::UploadUniformFloat4(const std::string& name, const glm::vec4& value) {
		GLint location = glad_glGetUniformLocation(RendererID, name.c_str());
		glad_glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void Shader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix) {
		GLint location = glad_glGetUniformLocation(RendererID, name.c_str());
		glad_glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix) {
		GLint location = glad_glGetUniformLocation(RendererID, name.c_str());
		glad_glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}


	// ***********************************************************
	// *** Shader Library ****************************************
	// ***********************************************************

	void ShaderLibrary::Add(const std::string& name, const Shader& shader) {
		utilities::Logger("SL001", "Error: Shader already exists!");
		Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const Shader& shader) {
		auto& name = shader.GetName();
		Add(name, shader);
	}

	Shader ShaderLibrary::Load(const std::string& shaderPath) {

		Shader shader(shaderPath);

		Add(shader);

		return shader;
	}

	Shader ShaderLibrary::Load(const std::string& name, const std::string& shaderPath) {

		Shader shader(shaderPath);

		Add(name, shader);
		return shader;
	}

	Shader ShaderLibrary::Get(const std::string& name) {
		utilities::Logger("SL002", "Error: Cannot find shader.");
		return Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const {
		return Shaders.find(name) != Shaders.end();
	}
}
