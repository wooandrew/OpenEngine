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

#include "audio.hpp"

#include <map>

#include <irrKlang/src/irrKlang.h>
#include <ASWL/utilities.hpp>

namespace OpenEngine {

	struct AudioStorage {

		irrklang::ISound* background;
		std::map<std::string, irrklang::ISoundSource*> AudioMap;
		irrklang::ISoundEngine* AudioEngine;
	};

	static AudioStorage* storage;

	void Audio::init(const std::string& background, const float volume) {

		storage = new AudioStorage();

		//irrklang::E_SOUND_ENGINE_OPTIONS = 
		storage->AudioEngine = irrklang::createIrrKlangDevice(irrklang::ESOD_AUTO_DETECT, irrklang::ESEO_MULTI_THREADED | irrklang::ESEO_LOAD_PLUGINS);

		if (background != "")
			SetBackground(background, volume);
	}
	void Audio::shutdown() {
		storage->AudioEngine->drop();
		delete storage;
	}

	void Audio::AddFile(const std::string& name, const std::string& path) {

		auto search = storage->AudioMap.find(name);

		if (search == storage->AudioMap.end()) {

			irrklang::ISoundSource* sound = storage->AudioEngine->addSoundSourceFromFile(path.c_str());
			storage->AudioMap.insert(std::make_pair(name, sound));
		}
		else
			utilities::Logger<std::string, std::string>("A0001", "Error: Audio file [", path, "] has already been added.");
	}
	void Audio::RemoveFile(const std::string& name) {

		auto search = storage->AudioMap.find(name);

		if (search == storage->AudioMap.end())
			storage->AudioMap.erase(name);
		else
			utilities::Logger<std::string, std::string>("A0002", "Error: Audio file [", name, "] cannot be found.");
	}

	void Audio::PlayAudio(const std::string& name, const float volume) {

		auto search = storage->AudioMap.find(name);

		if (search != storage->AudioMap.end()) {

			search->second->setDefaultVolume(volume);
			storage->AudioEngine->play2D(search->second);
		}
		else
			utilities::Logger<std::string, std::string>("A0003", "Error: Audio file [", name, "] cannot be found.");
	}

	void Audio::SetBackground(const std::string& sound, const float volume) {

		if (storage->background != nullptr)
			storage->background->drop();

		storage->background = storage->AudioEngine->play2D(sound.c_str(), true, false, true);

		storage->background->setVolume(volume);
	}
	void Audio::PlayBackground(const float volume) {

		if (storage->background != nullptr)
			return;

		storage->background->setVolume(volume);
		storage->background->setIsPaused(false);
	}
	void Audio::PauseBackground() {

		if (storage->background != nullptr)
			return;

		storage->background->setIsPaused();
	}
	void Audio::StopBackground() {

		if (storage->background != nullptr)
			return;

		storage->background->stop();
	}

	void Audio::StopAll() {
		storage->AudioEngine->stopAllSounds();
	}
}
