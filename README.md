<img sytle="width:100%" src="https://media.discordapp.net/attachments/645325484875448326/645363334635454486/oelogoblack.png" />
<div style="width:100%;display:flex;justify-content:center;">

![GitHub top language](https://img.shields.io/github/languages/top/wooandrew/OpenEngine)
![License](https://img.shields.io/badge/license-Modified%20MIT-green)
![GitHub repo size](https://img.shields.io/github/repo-size/wooandrew/OpenEngine)
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/wooandrew/OpenEngine)
![Website](https://img.shields.io/website?down_color=red&down_message=offline&up_color=green&up_message=online&url=https%3A%2F%2Fwooandrew.github.io%2F)

</div>

# OpenEngine
OpenEngine is a library-only game engine developed on the OpenGL API using related dependencies. 
The purpose of this project was to shorten the time it takes to create a game from scratch. In other
words, this project is intended for developers who do not want to use a pre-existing game engine
such as Unity or Unreal Engine, but also do not want to waste time programming an entire engine for a
simple game.

> OpenEngine was built on CMake using the MSVC C++ Compiler.\
> This is to attempt OS cross-compadibility, however, the project\
> itself was built on and is optimized for Windows. In theory, this\
> project should work on other operating systems (macOS, Linux) but\
> has not been tested on such systems.

`Version 0.1.0`\
`Does OpenEngine Use Semantic Versioning? Not currently.`


## Dependencies
OpenEngine uses several dependencies. Here is a list:
```
Required:
- GLFW                    version 3.3
- GLAD                    version 4.6 Core
- stb_image               version 2.23
- GLM                     version 0.9.9
- irrKlang                version 1.6
- ASWL Utilities          version 0.1
```
The `ASWL Utilities` library is a self-made general utility library. 
It is included in the `misc/` folder, and is required for proper functionality.
You must download and build the remaining dependencies, as they are not included in this repository.

## "Features"
I put quotes around because these aren't really features. Not technically, anyways. It's just a list of what 
you can do.

- Basic quad rendering
- Texture loading
- GLSL shader parser (broken as of 11/16/19, replaced with hardcoded shader, and pending fix)
- Overloadable sprite class (by which I mean I provided a very basic update function that should really be 
    changed individually)
- Keyboard input
- Keymap (kinda)
- Mouse input (no scroll wheel as of 11/16/19)
- Audio playback (hoorah irrKlang)
- Easy splash screens (I'm really proud of this one)
- Basic orthographic camera (should work for most 2D games)
- A very, very rudimentary button class

#### Stuff I plan to add

In (hopefully) the next major update:

- Spritesheet rendering
- "Animatable" splash screens
- Window resizing capability (I was too lazy to add it)
- Scroll wheel support
- Font/text rendering
- Active camera
- Render layers
- Math elements (rotation, dot, project, etc.)
- Physics elements (Separating Axis Theorem collision, rigidbody)

In the near future:

- Joystick support
- UI Elements (text box, menus, etc.)
- Other stuff probably

In the very, very distant future:

- 3D space support
- 3D animation support
- 3D mesh loading
- Alot of other 3D stuff I'm sure

## Credits

- Programing: Andrew Woo
- Logo Design: Andrew Woo, Abby Mills

## License
```
Modified MIT & Public Domain

This software is dual-licensed to the public domain and under the following
   license:

Copyright 2019 Andrew Woo

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