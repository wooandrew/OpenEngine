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

#include "rigidbody.hpp"

namespace OpenEngine { namespace Physics {
    
        Rigidbody::Rigidbody() {

            LastRotation = 0;

            position = glm::vec3();
            size = glm::vec3(0.f);
            scale = glm::vec3(1.f);

            x = 0;
            y = 0;
            width = 0;
            height = 0;

            UpdateVertices();
        }
        Rigidbody::Rigidbody(const glm::vec3& _position, const glm::vec3& _size, const glm::vec3& _scale) {

            LastRotation = 0;

            position = _position;
            size = _size;
            scale = _scale;

            x = position.x - ((size.x * scale.x) / 2.f);
            y = position.y - ((size.y * scale.x) / 2.f);
            width = size.x * scale.x;
            height = size.y * scale.y;

            UpdateVertices();
        }

        void Rigidbody::Update(const glm::vec3& position, float rotation) {

            if (this->position != position)
                MoveTo(position);

            if (LastRotation != rotation) {

                LowerLeftVertex = Math::RotatePoint(LowerLeftVertex, this->position, rotation - LastRotation, Math::AngleType::degree);
                LowerRightVertex = Math::RotatePoint(LowerRightVertex, this->position, rotation - LastRotation, Math::AngleType::degree);
                UpperLeftVertex = Math::RotatePoint(UpperLeftVertex, this->position, rotation - LastRotation, Math::AngleType::degree);
                UpperRightVertex = Math::RotatePoint(UpperRightVertex, this->position, rotation - LastRotation, Math::AngleType::degree);

                LastRotation = rotation;
            }
        }

        void Rigidbody::SetScale(const glm::vec3& scale) {
            size = size * scale;
            UpdateVertices();
        }
        void Rigidbody::MoveTo(const glm::vec3& pos) {

            position = pos;

            x = position.x - ((size.x * scale.x) / 2.f);
            y = position.y - ((size.y * scale.x) / 2.f);
            width = size.x * scale.x;
            height = size.y * scale.y;

            UpdateVertices();
        }
        void Rigidbody::MoveBy(const glm::vec3& val, float dt) {

            position = position + (val * dt);

            x = position.x - ((size.x * scale.x) / 2.f);
            y = position.y - ((size.y * scale.x) / 2.f);
            width = size.x * scale.x;
            height = size.y * scale.y;

            UpdateVertices();
        }

        const glm::vec3& Rigidbody::GetPosition() const {
            return position;
        }

        void Rigidbody::UpdateVertices() {

            UpperLeftVertex  = glm::vec3(position.x - ((size.x * scale.x) / 2.f), position.y + ((size.y * scale.y) / 2.f), 0);
            UpperRightVertex = glm::vec3(position.x + ((size.x * scale.x) / 2.f), position.y + ((size.y * scale.y) / 2.f), 0);
            LowerLeftVertex  = glm::vec3(position.x - ((size.x * scale.x) / 2.f), position.y - ((size.y * scale.y) / 2.f), 0);
            LowerRightVertex = glm::vec3(position.x + ((size.x * scale.x) / 2.f), position.y - ((size.y * scale.y) / 2.f), 0);

            LowerLeftVertex = Math::RotatePoint(LowerLeftVertex, position, LastRotation, Math::AngleType::degree);
            LowerRightVertex = Math::RotatePoint(LowerRightVertex, position, LastRotation, Math::AngleType::degree);
            UpperLeftVertex = Math::RotatePoint(UpperLeftVertex, position, LastRotation, Math::AngleType::degree);
            UpperRightVertex = Math::RotatePoint(UpperRightVertex, position, LastRotation, Math::AngleType::degree);
        }
    }
}
