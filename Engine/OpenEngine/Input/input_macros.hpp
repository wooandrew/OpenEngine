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

#pragma once

#ifndef OPEN_ENGINE_INPUT_INPUT_MACROS
#define OPEN_ENGINE_INPUT_INPUT_MACROS

namespace OpenEngine {

	namespace OEKeyboardKeys {

		// ***************************************** *********************
		// *** Keyboard Input Macros *************** *********************
		// ***************************************** *********************

		constexpr int OE_KEY_SPACE = 32;
		constexpr int OE_KEY_APOSTROPHE = 39;  /* ' */
		constexpr int OE_KEY_COMMA = 44;  /* , */
		constexpr int OE_KEY_MINUS = 45;  /* - */
		constexpr int OE_KEY_PERIOD = 46;  /* . */
		constexpr int OE_KEY_SLASH = 47;  /* / */
		constexpr int OE_KEY_0 = 48;
		constexpr int OE_KEY_1 = 49;
		constexpr int OE_KEY_2 = 50;
		constexpr int OE_KEY_3 = 51;
		constexpr int OE_KEY_4 = 52;
		constexpr int OE_KEY_5 = 53;
		constexpr int OE_KEY_6 = 54;
		constexpr int OE_KEY_7 = 55;
		constexpr int OE_KEY_8 = 56;
		constexpr int OE_KEY_9 = 57;
		constexpr int OE_KEY_SEMICOLON = 59;  /* ; */
		constexpr int OE_KEY_EQUAL = 61;  /* = */
		constexpr int OE_KEY_A = 65;
		constexpr int OE_KEY_B = 66;
		constexpr int OE_KEY_C = 67;
		constexpr int OE_KEY_D = 68;
		constexpr int OE_KEY_E = 69;
		constexpr int OE_KEY_F = 70;
		constexpr int OE_KEY_G = 71;
		constexpr int OE_KEY_H = 72;
		constexpr int OE_KEY_I = 73;
		constexpr int OE_KEY_J = 74;
		constexpr int OE_KEY_K = 75;
		constexpr int OE_KEY_L = 76;
		constexpr int OE_KEY_M = 77;
		constexpr int OE_KEY_N = 78;
		constexpr int OE_KEY_O = 79;
		constexpr int OE_KEY_P = 80;
		constexpr int OE_KEY_Q = 81;
		constexpr int OE_KEY_R = 82;
		constexpr int OE_KEY_S = 83;
		constexpr int OE_KEY_T = 84;
		constexpr int OE_KEY_U = 85;
		constexpr int OE_KEY_V = 86;
		constexpr int OE_KEY_W = 87;
		constexpr int OE_KEY_X = 88;
		constexpr int OE_KEY_Y = 89;
		constexpr int OE_KEY_Z = 90;
		constexpr int OE_KEY_LEFT_BRACKET = 91;  /* [ */
		constexpr int OE_KEY_BACKSLASH = 92;  /* \ */
		constexpr int OE_KEY_RIGHT_BRACKET = 93;  /* ] */
		constexpr int OE_KEY_GRAVE_ACCENT = 96;  /* ` */
		constexpr int OE_KEY_WORLD_1 = 161; /* non-US #1 */
		constexpr int OE_KEY_WORLD_2 = 162; /* non-US #2 */

		/* Function keys */
		constexpr int OE_KEY_ESCAPE = 256;
		constexpr int OE_KEY_ENTER = 257;
		constexpr int OE_KEY_TAB = 258;
		constexpr int OE_KEY_BACKSPACE = 259;
		constexpr int OE_KEY_INSERT = 260;
		constexpr int OE_KEY_DELETE = 261;
		constexpr int OE_KEY_RIGHT = 262;
		constexpr int OE_KEY_LEFT = 263;
		constexpr int OE_KEY_DOWN = 264;
		constexpr int OE_KEY_UP = 265;
		constexpr int OE_KEY_PAGE_UP = 266;
		constexpr int OE_KEY_PAGE_DOWN = 267;
		constexpr int OE_KEY_HOME = 268;
		constexpr int OE_KEY_END = 269;
		constexpr int OE_KEY_CAPS_LOCK = 280;
		constexpr int OE_KEY_SCROLL_LOCK = 281;
		constexpr int OE_KEY_NUM_LOCK = 282;
		constexpr int OE_KEY_PRINT_SCREEN = 283;
		constexpr int OE_KEY_PAUSE = 284;
		constexpr int OE_KEY_F1 = 290;
		constexpr int OE_KEY_F2 = 291;
		constexpr int OE_KEY_F3 = 292;
		constexpr int OE_KEY_F4 = 293;
		constexpr int OE_KEY_F5 = 294;
		constexpr int OE_KEY_F6 = 295;
		constexpr int OE_KEY_F7 = 296;
		constexpr int OE_KEY_F8 = 297;
		constexpr int OE_KEY_F9 = 298;
		constexpr int OE_KEY_F10 = 299;
		constexpr int OE_KEY_F11 = 300;
		constexpr int OE_KEY_F12 = 301;
		constexpr int OE_KEY_F13 = 302;
		constexpr int OE_KEY_F14 = 303;
		constexpr int OE_KEY_F15 = 304;
		constexpr int OE_KEY_F16 = 305;
		constexpr int OE_KEY_F17 = 306;
		constexpr int OE_KEY_F18 = 307;
		constexpr int OE_KEY_F19 = 308;
		constexpr int OE_KEY_F20 = 309;
		constexpr int OE_KEY_F21 = 310;
		constexpr int OE_KEY_F22 = 311;
		constexpr int OE_KEY_F23 = 312;
		constexpr int OE_KEY_F24 = 313;
		constexpr int OE_KEY_F25 = 314;
		constexpr int OE_KEY_KP_0 = 320;
		constexpr int OE_KEY_KP_1 = 321;
		constexpr int OE_KEY_KP_2 = 322;
		constexpr int OE_KEY_KP_3 = 323;
		constexpr int OE_KEY_KP_4 = 324;
		constexpr int OE_KEY_KP_5 = 325;
		constexpr int OE_KEY_KP_6 = 326;
		constexpr int OE_KEY_KP_7 = 327;
		constexpr int OE_KEY_KP_8 = 328;
		constexpr int OE_KEY_KP_9 = 329;
		constexpr int OE_KEY_KP_DECIMAL = 330;
		constexpr int OE_KEY_KP_DIVIDE = 331;
		constexpr int OE_KEY_KP_MULTIPLY = 332;
		constexpr int OE_KEY_KP_SUBTRACT = 333;
		constexpr int OE_KEY_KP_ADD = 334;
		constexpr int OE_KEY_KP_ENTER = 335;
		constexpr int OE_KEY_KP_EQUAL = 336;
		constexpr int OE_KEY_LEFT_SHIFT = 340;
		constexpr int OE_KEY_LEFT_CONTROL = 341;
		constexpr int OE_KEY_LEFT_ALT = 342;
		constexpr int OE_KEY_LEFT_SUPER = 343;
		constexpr int OE_KEY_RIGHT_SHIFT = 344;
		constexpr int OE_KEY_RIGHT_CONTROL = 345;
		constexpr int OE_KEY_RIGHT_ALT = 346;
		constexpr int OE_KEY_RIGHT_SUPER = 347;
		constexpr int OE_KEY_MENU = 348;

		constexpr int OE_INPUT_UP = OE_KEY_W;
		constexpr int OE_INPUT_LEFT = OE_KEY_A;
		constexpr int OE_INPUT_DOWN = OE_KEY_S;
		constexpr int OE_INPUT_RIGHT = OE_KEY_D;
	}


	namespace OEMouseKeys {

		// ***************************************** *********************
		// *** Mouse Input Macros ****************** *********************
		// ***************************************** *********************

		constexpr int OE_MOUSE_BUTTON_1 = 0;
		constexpr int OE_MOUSE_BUTTON_2 = 1;
		constexpr int OE_MOUSE_BUTTON_3 = 2;
		constexpr int OE_MOUSE_BUTTON_4 = 3;
		constexpr int OE_MOUSE_BUTTON_5 = 4;
		constexpr int OE_MOUSE_BUTTON_6 = 5;
		constexpr int OE_MOUSE_BUTTON_7 = 6;
		constexpr int OE_MOUSE_BUTTON_8 = 7;

		constexpr int OE_MOUSE_BUTTON_LEFT = OE_MOUSE_BUTTON_1;
		constexpr int OE_MOUSE_BUTTON_RIGHT = OE_MOUSE_BUTTON_2;
		constexpr int OE_MOUSE_BUTTON_MIDDLE = OE_MOUSE_BUTTON_3;
	}
}

#endif // !OPEN_ENGINE_INPUT_INPUT_MACROS	
