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

#include "collision.hpp"

#include <vector>
#include <algorithm>

#include <OpenEngine/Math/math.hpp>

namespace OpenEngine { namespace Physics {

        namespace Collision {

            bool AxisAlignedBoundingBox(const Rigidbody& left, const Rigidbody& right) {

                if ((left.x < (right.x + right.width)) && ((left.x + left.width) > right.x) && 
                    (left.y < (right.y + right.height)) && ((left.y + left.height) > right.y))
                    return true;

                return false;
            }

            bool SeparatingAxisTheorem(const Rigidbody& left, const Rigidbody& right) {

                glm::vec3 aUR = left.UpperRightVertex;      // left -> Upper Right
                glm::vec3 aUL = left.UpperLeftVertex;       // left -> Upper Left
                glm::vec3 aLR = left.LowerRightVertex;      // left -> Lower Right
                glm::vec3 aLL = left.LowerLeftVertex;       // left -> Lower Left

                glm::vec3 bUR = right.UpperRightVertex;     // right -> Upper Right
                glm::vec3 bUL = right.UpperLeftVertex;      // right -> Upper Left
                glm::vec3 bLR = right.LowerRightVertex;     // right -> Lower Right
                glm::vec3 bLL = right.LowerLeftVertex;      // right -> Lower Left

                float aMax = 0;
                float aMin = 0;
                float bMax = 0;
                float bMin = 0;

                glm::vec3 axis1 = aUR - aUL;    // left.UpperRight - left.UpperLeft
                glm::vec3 axis2 = aUR - aLR;    // left.UpperRight - left.LowerRight
                glm::vec3 axis3 = bUL - bLL;    // right.UpperLeft - right.LowerLeft
                glm::vec3 axis4 = bUL - bUR;    // right.UpperLeft - right.UpperRight

                std::vector<glm::vec3> axes;
                axes.push_back(axis1);
                axes.push_back(axis2);
                axes.push_back(axis3);
                axes.push_back(axis4);

                for (auto& axis : axes) {

                    glm::vec3 aURProject = Math::project(aUR, axis);
                    glm::vec3 aULProject = Math::project(aUL, axis);
                    glm::vec3 aLRProject = Math::project(aLR, axis);
                    glm::vec3 aLLProject = Math::project(aLL, axis);
                    
                    glm::vec3 bURProject = Math::project(bUR, axis);
                    glm::vec3 bULProject = Math::project(bUL, axis);
                    glm::vec3 bLRProject = Math::project(bLR, axis);
                    glm::vec3 bLLProject = Math::project(bLL, axis);

                    float aURDot = Math::dot(aURProject, axis);
                    float aULDot = Math::dot(aULProject, axis);
                    float aLRDot = Math::dot(aLRProject, axis);
                    float aLLDot = Math::dot(aLLProject, axis);

                    float bURDot = Math::dot(bURProject, axis);
                    float bULDot = Math::dot(bULProject, axis);
                    float bLRDot = Math::dot(bLRProject, axis);
                    float bLLDot = Math::dot(bLLProject, axis);

                    std::vector<float> aDots;
                    aDots.push_back(aURDot);
                    aDots.push_back(aULDot);
                    aDots.push_back(aLRDot);
                    aDots.push_back(aLLDot);
                    aMax = *std::max_element(aDots.begin(), aDots.end());
                    aMin = *std::min_element(aDots.begin(), aDots.end());

                    std::vector<float> bDots;
                    bDots.push_back(bURDot);
                    bDots.push_back(bULDot);
                    bDots.push_back(bLRDot);
                    bDots.push_back(bLLDot);
                    bMax = *std::max_element(bDots.begin(), bDots.end());
                    bMin = *std::min_element(bDots.begin(), bDots.end());

                    if (aMax >= bMin && bMax >= aMin)
                        continue;
                    else
                        return false;
                }

                return true;
            }

        } //namespace Collision
    } // namespace Physics
} // namespace OpenEngine
