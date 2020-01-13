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

#include "spritesheet.hpp"

#include <OpenEngine/Input/keyboard.hpp>

namespace OpenEngine {

    SpriteSheet::SpriteSheet(const std::string& SpriteSheetPath, const int rows, const int cols, const float fpt, const float speed, 
        const glm::vec2& position, const float scale, const float rotation) : rows(rows), cols(cols) {
    
        spritesheet = std::make_shared<Texture>(SpriteSheetPath);

        lock = false;

        LockUp = false;
        LockDown = false;
        LockLeft = false;
        LockRight = false;

        SpritePosition = { position.x, position.y, 0.f };
        SpriteScale = glm::vec3(scale);
        SpriteRotation = rotation;

        SpriteSpeed = speed;

        SpriteDimensions = utilities::make_2d_dimension(spritesheet->GetDimensions().width / cols, spritesheet->GetDimensions().height / rows);
        
        row = 0;
        col = 0;
        FramesPerTex = fpt;

        UpdateTex = true;
    }
    SpriteSheet::SpriteSheet(const std::string& SpriteSheetPath, const int rows, const int cols, const float fpt, const float speed, 
        const glm::vec2& position, const glm::vec2& scale, const float rotation) : rows(rows), cols(cols) {
            
        spritesheet = std::make_shared<Texture>(SpriteSheetPath);

        lock = false;

        LockUp = false;
        LockDown = false;
        LockLeft = false;
        LockRight = false;

        SpritePosition = { position.x, position.y, 0.f };
        SpriteScale = { scale.x, scale.y, 0.f };
        SpriteRotation = rotation;

        SpriteSpeed = speed;

        SpriteDimensions = utilities::make_2d_dimension(spritesheet->GetDimensions().width / cols, spritesheet->GetDimensions().height / rows);
        
        row = 0;
        col = 0;
        FramesPerTex = fpt;

        UpdateTex = false;
    }
    SpriteSheet::SpriteSheet(const std::string& SpriteSheetPath, const int rows, const int cols, const float fpt, const float speed, 
        const glm::vec3& position, const float scale, const float rotation) : rows(rows), cols(cols) {
        
        spritesheet = std::make_shared<Texture>(SpriteSheetPath);

        lock = false;

        LockUp = false;
        LockDown = false;
        LockLeft = false;
        LockRight = false;

        SpritePosition = position;
        SpriteScale = glm::vec3(scale);
        SpriteRotation = rotation;

        SpriteSpeed = speed;

        SpriteDimensions = utilities::make_2d_dimension(spritesheet->GetDimensions().width / cols, spritesheet->GetDimensions().height / rows);
        
        row = 0;
        col = 0;
        FramesPerTex = fpt;

        UpdateTex = false;
    }
    SpriteSheet::SpriteSheet(const std::string& SpriteSheetPath, const int rows, const int cols, const float fpt, const float speed, 
        const glm::vec3& position, const glm::vec3& scale, const float rotation) : rows(rows), cols(cols) {

        spritesheet = std::make_shared<Texture>(SpriteSheetPath);

        lock = false;

        LockUp = false;
        LockDown = false;
        LockLeft = false;
        LockRight = false;

        SpritePosition = position;
        SpriteScale = scale;
        SpriteRotation = rotation;

        SpriteSpeed = speed;

        SpriteDimensions = utilities::make_2d_dimension(spritesheet->GetDimensions().width / cols, spritesheet->GetDimensions().height / rows);
        
        row = 0;
        col = 0;
        FramesPerTex = fpt;

        UpdateTex = false;
    }

    void SpriteSheet::UpdateSprite(float dt) {

        static float dFPT = 0;

        if (!lock) {

            if (Keyboard::KeyIsPressed(KeyMap::KM_Up) && !LockUp) {

                row = 2;

                dFPT += FramesPerTex * dt;

                if (dFPT > FramesPerTex / 20) {

                    col++;
                    dFPT = 0;

                    UpdateTex = true;
                }

                SpritePosition.y += SpriteSpeed * dt;
            }
            if (Keyboard::KeyIsPressed(KeyMap::KM_Down) && !LockDown) {

                row = 3;

                dFPT += FramesPerTex * dt;

                if (dFPT > FramesPerTex / 20) {

                    col++;
                    dFPT = 0;

                    UpdateTex = true;
                }

                SpritePosition.y -= SpriteSpeed * dt;
            }
            if (Keyboard::KeyIsPressed(KeyMap::KM_Left) && !LockLeft) {

                row = 0;

                dFPT += FramesPerTex * dt;

                if (dFPT > FramesPerTex / 20) {

                    col++;
                    dFPT = 0;

                    UpdateTex = true;
                }

                SpritePosition.x -= SpriteSpeed * dt;
            }
            if (Keyboard::KeyIsPressed(KeyMap::KM_Right) && !LockRight) {

                row = 1;

                dFPT += FramesPerTex * dt;

                if (dFPT > FramesPerTex / 20) {

                    col++;
                    dFPT = 0;

                    UpdateTex = true;
                }

                SpritePosition.x += SpriteSpeed * dt;
            }

            row = row % rows;
            col = col % cols;
        }
        

        /*// Flip Through Sprite Sheet in Order | Left -> Right, Top -> Bottom
        if (col < cols)
            col++;
        if (col >= cols)
            row++;
        */

        if (Keyboard::KeyIsPressed(KeyMap::rLeft)) {
            SpriteRotation += 500.f * dt;
            SpriteRotation = std::fmodf(SpriteRotation, 360);
        }
        else if (Keyboard::KeyIsPressed(KeyMap::rRight)) {
            SpriteRotation -= 500.f * dt;
            SpriteRotation = std::fmodf(SpriteRotation, 360);
        }
    }

    const std::shared_ptr<Texture>& SpriteSheet::GetSpriteSheet() const {
        return spritesheet;
    }

    void SpriteSheet::Lock(bool lock) {
        this->lock = lock;
    }
    void SpriteSheet::Lock(std::vector<MovementMacros> directions, std::vector<bool> lock) {

        if (directions.size() != lock.size()) {
            utilities::Logger<std::string, std::string>("SS_01", "Error: directions size does not match lock size -> [", std::to_string(directions.size()), " ,", std::to_string(lock.size()), "].");
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

    void SpriteSheet::SetSpriteSpeed(float speed) {
        SpriteSpeed = speed;
    }

    void SpriteSheet::SetSpritePosition(const float position) {
        SpritePosition = glm::vec3(position);
    }
    void SpriteSheet::SetSpritePosition(const glm::vec2& position){
        SpritePosition = { position.x, position.y, 0.f };
    }
    void SpriteSheet::SetSpritePosition(const glm::vec3& position) {
        SpritePosition = position;
    }
    const glm::vec3& SpriteSheet::GetSpritePosition() const {
        return SpritePosition;
    }

    void SpriteSheet::SetSpriteRotation(float rotation) {
        SpriteRotation = rotation;
    }
    const float SpriteSheet::GetSpriteRotation() const {
        return SpriteRotation;
    }

    void SpriteSheet::SetSpriteScale(const float scale) {
        SpriteScale = glm::vec3(scale);
    }
    void SpriteSheet::SetSpriteScale(const glm::vec2& scale) {
        SpriteScale = { scale.x, scale.y, 0.f };
    }
    void SpriteSheet::SetSpriteScale(const glm::vec3& scale){
        SpriteScale = scale;
    }
    const glm::vec3& SpriteSheet::GetSpriteScale() const {
        return SpriteScale;
    }

    const utilities::Dimensions2D<int>& SpriteSheet::GetSpriteDimensions() const {
        return SpriteDimensions;
    }

    const int SpriteSheet::GetRow() const {
        return row;
    }
    const int SpriteSheet::GetCol() const {
        return col;
    }

    void SpriteSheet::SetFramesPerTex(float fpt) {
        FramesPerTex = fpt;
    }
    const float SpriteSheet::GetFramesPerTex() const {
        return FramesPerTex;
    }

    void SpriteSheet::SetUpdateTex(bool update) {
        UpdateTex = update;
    }
    const bool SpriteSheet::GetUpdateTex() const {
        return UpdateTex;
    }
}
