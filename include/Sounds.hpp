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
        //Class presenting interface for programmers to select if music should be played or not(like muting in settings)
        //Name is java-like to discourage them from using it where it shouldn't be used.
        class IsMusicPlayedVolumeHandler
        {
            static bool IsVolumePlayedWanted;

            public:
                static bool IsMuted() { return IsVolumePlayedWanted; }
                static void Mute();
                static void UnMute();
                static void Toggle() { IsVolumePlayedWanted ? Mute() : UnMute(); }
        };

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

            static void Stop();
            static void Pause();
            static void Resume();
            static void Rewind();
            static void Toggle();
            static bool Playing(){return Mix_PlayingMusic();}

            BGM(const char* filename = nullptr);
            BGM(const BGM& other) = delete;
            BGM(BGM&& other) = delete;
            ~BGM() = default;
        };

        class SFX
        {
        private:
            static int __volume;
            std::unique_ptr<Mix_Chunk, decltype(&Mix_FreeChunk)> m_sound;
        public:
            void Load(const char* filename);
            void Play(int repeats = 0, int channel = -1);

            SFX(const char* filename = nullptr);
            SFX(const SFX& other) = delete;
            SFX(SFX&& other) = delete;

            static int GetVolume()
            {
                return __volume;
            }
            static void SetVolume(int volume = 128)
            {
                __volume = volume;
            }

            ~SFX() = default;
        };

        bool Init();
        void Close();

        inline int BGM_GetVolume()
        {
            return Mix_VolumeMusic(-1);
        }
        inline void BGM_SetVolume(int volume = 128)
        {
            Mix_VolumeMusic(volume);
        }
    }
}


#endif
