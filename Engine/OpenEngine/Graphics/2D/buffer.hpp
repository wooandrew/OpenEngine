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

#ifndef OPEN_ENGINE_2D_BUFFER_CHPP
#define OPEN_ENGINE_2D_BUFFER_CHPP

#include <string>
#include <vector>
#include <initializer_list>

#include <ASWL/utilities.hpp>

namespace OpenEngine {

	enum class ShaderDataType {

		None = 0,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Bool
	};

	static int ShaderDataTypeSize(ShaderDataType type) {

		switch (type) {

		case ShaderDataType::Float:    return 4;
		case ShaderDataType::Float2:   return 4 * 2;
		case ShaderDataType::Float3:   return 4 * 3;
		case ShaderDataType::Float4:   return 4 * 4;
		case ShaderDataType::Mat3:     return 4 * 3 * 3;
		case ShaderDataType::Mat4:     return 4 * 4 * 4;
		case ShaderDataType::Int:      return 4;
		case ShaderDataType::Int2:     return 4 * 2;
		case ShaderDataType::Int3:     return 4 * 3;
		case ShaderDataType::Int4:     return 4 * 4;
		case ShaderDataType::Bool:     return 1;
		}

		utilities::Logger("B0001", "Error: Unknown ShaderDataType [].");
		return 0;
	}

	struct BufferElement {

		std::string name;
		ShaderDataType type;
		unsigned int size;
		size_t offset;
		bool normalized;

		BufferElement() = default;

		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false) : name(name), type(type), size(ShaderDataTypeSize(type)), offset(0), normalized(normalized) {}

		uint32_t GetComponentCount() const
		{
			switch (type) {

			case ShaderDataType::Float:   return 1;
			case ShaderDataType::Float2:  return 2;
			case ShaderDataType::Float3:  return 3;
			case ShaderDataType::Float4:  return 4;
			case ShaderDataType::Mat3:    return 3 * 3;
			case ShaderDataType::Mat4:    return 4 * 4;
			case ShaderDataType::Int:     return 1;
			case ShaderDataType::Int2:    return 2;
			case ShaderDataType::Int3:    return 3;
			case ShaderDataType::Int4:    return 4;
			case ShaderDataType::Bool:    return 1;
			}

			utilities::Logger("B0001", "Error: Unknown ShaderDataType [].");
			return 0;
		}
	};

	class BufferLayout {

		/// OpenEngine -> Buffer Layout class \\\

	public:

		BufferLayout();
		BufferLayout(const std::initializer_list<BufferElement>& elements);

		inline unsigned int GetStride() const {
			return stride;
		}
		inline const std::vector<BufferElement>& GetElements() const {
			return elements;
		}


		std::vector<BufferElement>::iterator begin();
		std::vector<BufferElement>::iterator end();
		std::vector<BufferElement>::const_iterator begin() const;
		std::vector<BufferElement>::const_iterator end() const;

	private:

		void CalculateOffsetsAndStride();

		std::vector<BufferElement> elements;
		unsigned int stride;
	};

	class VertexBuffer {

	public:

		VertexBuffer(float* vertices, unsigned int size);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;

		const BufferLayout& GetLayout() const;
		void SetLayout(const BufferLayout& layout);

	private:

		unsigned int RendererID;
		BufferLayout layout;
	};

	class IndexBuffer {

		/// OpenEngine -> Index Buffer class \\\

	public:

		IndexBuffer(unsigned int* indices, unsigned int count);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		unsigned int GetCount() const;

	private:

		unsigned int RendererID;
		unsigned int count;
	};
}

#endif // !OPEN_ENGINE_2D_BUFFER_CHPP
