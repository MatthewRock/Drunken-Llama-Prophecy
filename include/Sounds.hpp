#ifndef SOUNDS_HPP
#define SOUNDS_HPP

#include <SDL2/SDL_mixer.h>
#include "Logger.hpp"
#include <exception>
#include <string>
#include <memory>

namespace Llama
{
    namespace Sounds
    {
        class PlayException : public std::exception
        {
            virtual const char* what() const throw()
            {
                std::string errormsg="Sound module error: Couldn't play. File not loaded.";
                LOG_STRING(errormsg);
                return errormsg.c_str();
            }
        };

        class LoadException : public std::exception
        {
            std::string filename;
            virtual const char* what() const throw()
            {
                std::string errormsg = "Sound module error: Couldn't load file: " + filename;
                LOG_STRING(errormsg);
                return errormsg.c_str();
            }
            public:
            LoadException(std::string f) : exception()
            {
                    filename = f;
            }
        };

        class BGM
        {

        private:
            std::unique_ptr<Mix_Music, decltype(&Mix_FreeMusic)> m_music;

        public:
            void Load(const char* filename);
            void Play(int loops = -1);
            void Stop();
            void Pause();
            void Resume();
            BGM(const char* filename = nullptr);
            ~BGM() = default;
        };

        class SFX
        {
        private:
            std::unique_ptr<Mix_Chunk, decltype(&Mix_FreeChunk)> m_sound;
        public:
            void Load(const char* filename);
            void Play(int channel = -1, int repeats = 0);

            SFX(const char* filename = nullptr);
            ~SFX() = default;
        };

        bool Init();
        void Close();

        void SetBGMVolume(int volume);
        int GetBGMVolume();
    }
}


#endif
