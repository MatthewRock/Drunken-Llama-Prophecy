#ifndef SOUNDS_HPP
#define SOUNDS_HPP

#include <SDL2/SDL_mixer.h>
#include "Logger.hpp"
#include <exception>
#include <string>

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
                std::string errormsg = "Sound module error: Couldn't load file: "+filename;
                LOG_STRING(errormsg);
                return errormsg.c_str();
            }
            public:
            LoadException(std::string f) : exception()
            {
                    filename = f;
            }
        };

        class BGM                   //Object class to store and play background music
        {

        private:
            Mix_Music* m_music;

        public:
            void Load(const char* filename);
            void Play(int loops);
            void Stop();
            void Pause();
            void Resume();

            BGM();
            BGM(const char* filename);
            ~BGM();

        };

        class SFX
        {
        private:
            Mix_Chunk* m_sound;
        public:
            void Load(const char* filename);
            void Play(int channel, int repeats);

            SFX();
            SFX(const char* filename);
            ~SFX();
        };

        void Init();
        void Close();
        void SetBGMVolume(int volume);
        int GetBGMVolume();
    }
}


#endif
