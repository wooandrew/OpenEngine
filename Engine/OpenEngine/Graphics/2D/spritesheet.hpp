// OpenEngine (c) Andrew Woo, 2019-2020
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
 * Copyright 2019-2020 Andrew Woo
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

#pragma once

#ifndef OPEN_ENGINE_2D_SPRITESHEET_CHPP
#define OPEN_ENGINE_2D_SPRITESHEET_CHPP

#include <string>
#include <vector>

#include <GLM/glm.hpp>

#include <OpenEngine/Input/keymap.hpp>
#include <OpenEngine/Graphics/2D/texture.hpp>

#include <ASWL/utilities.hpp>

namespace OpenEngine {

    class SpriteSheet {

        /// OpenEngine -> Sprite Sheet & Image Atlas Class \\\

    public:

        SpriteSheet(const std::string& SpriteSheetPath, const int rows, const int cols, const float fpt, const float speed,
                    const glm::vec2& position = glm::vec2(), const float scale = 0, const float rotation = 0);
        SpriteSheet(const std::string& SpriteSheetPath, const int rows, const int cols, const float fpt, const float speed,
                    const glm::vec2& position = glm::vec2(), const glm::vec2& scale = glm::vec2(), const float rotation = 0);
        SpriteSheet(const std::string& SpriteSheetPath, const int rows, const int cols, const float fpt, const float speed,
                    const glm::vec3& position = glm::vec3(), const float scale = 0, const float rotation = 0);
        SpriteSheet(const std::string& SpriteSheetPath, const int rows, const int cols, const float fpt, const float speed,
                    const glm::vec3& position = glm::vec3(), const glm::vec3& scale = glm::vec3(), const float rotation = 0);

        virtual void UpdateSprite(float dt);

        const std::shared_ptr<Texture>& GetSpriteSheet() const;

        void Lock(bool lock = false);
        void Lock(std::vector<MovementMacros> directions, std::vector<bool> lock);

        void SetSpriteSpeed(float speed);

        void SetSpritePosition(const float position);
        void SetSpritePosition(const glm::vec2& position);
        void SetSpritePosition(const glm::vec3& position);
        const glm::vec3& GetSpritePosition() const;

        void SetSpriteRotation(float rotation);
        const float GetSpriteRotation() const;

        void SetSpriteScale(const float scale);
        void SetSpriteScale(const glm::vec2& scale);
        void SetSpriteScale(const glm::vec3& scale);
        const glm::vec3& GetSpriteScale() const;

        const utilities::Dimensions2D<int>& GetSpriteDimensions() const;

        const int GetRow() const;
        const int GetCol() const;

        void SetFramesPerTex(float fpt);
        const float GetFramesPerTex() const;

        void SetUpdateTex(bool update);
        const bool GetUpdateTex() const;

    protected:

        std::shared_ptr<Texture> spritesheet;

        bool lock;

        bool LockUp;
        bool LockDown;
        bool LockLeft;
        bool LockRight;

        float SpriteSpeed;

        glm::vec3 SpritePosition;
        float SpriteRotation;
        glm::vec3 SpriteScale;

        utilities::Dimensions2D<int> SpriteDimensions;
        
        int row;
        int col;

        const int rows;
        const int cols;
        float FramesPerTex;

        bool UpdateTex;
    };
}

#endif // !OPEN_ENGINE_2D_SPRITESHEET_CHPP
