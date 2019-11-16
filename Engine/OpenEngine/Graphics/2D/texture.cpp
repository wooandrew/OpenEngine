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

#include "texture.hpp"

#include <string>

#include <STBI/stb_image.h>

namespace OpenEngine {

	Texture::Texture(const unsigned int width, const unsigned int height) : TextureDimensions(utilities::make_2d_dimension<unsigned int>(width, height)) {

		InternalFormat = GL_RGBA8;
		DataFormat = GL_RGBA;

		glad_glCreateTextures(GL_TEXTURE_2D, 1, &RendererID);
		glad_glTextureStorage2D(RendererID, 1, InternalFormat, TextureDimensions.width, TextureDimensions.height);

		glad_glTextureParameteri(RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glad_glTextureParameteri(RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glad_glTextureParameteri(RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glad_glTextureParameteri(RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	Texture::Texture(const std::string texturePath) : TexturePath(texturePath) {

		TextureDimensions = utilities::make_2d_dimension<unsigned int>(0, 0);

		RendererID = 0;

		InternalFormat = 0;
		DataFormat = 0;

		int width;
		int height;
		int channels;

		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = stbi_load(texturePath.c_str(), &width, &height, &channels, 0);

		if (data) {

			TextureDimensions = utilities::make_2d_dimension<unsigned int>(width, height);

			GLenum internalFormat = 0;
			GLenum dataFormat = 0;

			if (channels == 4) {
				internalFormat = GL_RGBA8;
				dataFormat = GL_RGBA;
			}
			else if (channels == 3) {
				internalFormat = GL_RGB8;
				dataFormat = GL_RGB;
			}
			else
				utilities::Logger("T0001", "Error: Bad channel # -> [ERR].");

			InternalFormat = internalFormat;
			DataFormat = dataFormat;

			glad_glCreateTextures(GL_TEXTURE_2D, 1, &RendererID);
			glad_glTextureStorage2D(RendererID, 1, internalFormat, TextureDimensions.width, TextureDimensions.height);

			glad_glTextureParameteri(RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glad_glTextureParameteri(RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glad_glTextureParameteri(RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glad_glTextureParameteri(RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glad_glTextureSubImage2D(RendererID, 0, 0, 0, TextureDimensions.width, TextureDimensions.height, dataFormat, GL_UNSIGNED_BYTE, data);
		}
		else
			utilities::Logger("I0002", "Error: Failed to load image -> !stbi_load().");

		stbi_image_free(data);
	}

	Texture::~Texture() {
		glad_glDeleteTextures(1, &RendererID);
	}

	const utilities::Dimensions2D<unsigned int>& Texture::GetDimensions() const {
		return TextureDimensions;
	}

	void Texture::SetData(void* data, unsigned int size) {

		unsigned int bpp = (DataFormat == GL_RGBA) ? 4 : 3;

		if (size != TextureDimensions.width * TextureDimensions.height * bpp) {
			utilities::Logger("T0003", "ERROR: LOG VALUE -> T0003");
			//return;
		}
		glad_glTextureSubImage2D(RendererID, 0, 0, 0, TextureDimensions.width, TextureDimensions.height, DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void Texture::Bind(unsigned int slot) const {
		glad_glBindTextureUnit(slot, RendererID);
	}
}
