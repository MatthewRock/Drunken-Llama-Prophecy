#include "Sounds.hpp"

namespace Llama
{
    namespace Sounds
    {
        void BGM::Load(const char* filename)
        {
            if(!m_music)
                m_music = std::unique_ptr<Mix_Music, decltype(&Mix_FreeMusic)>(Mix_LoadMUS(filename), Mix_FreeMusic);
            if(!m_music)
                throw LoadException(filename);
        }

        void BGM::Play(int loops)
        {
            if(!m_music)
            {
                throw PlayException();
            }
            else
            {
                Mix_PlayMusic(m_music.get(), loops);
            }
        }

        void BGM::Stop()
        {
            Mix_HaltMusic();
        }

        void BGM::Pause()
        {
            Mix_PauseMusic();
        }

        void BGM::Resume()
        {
            Mix_ResumeMusic();
        }

        BGM::BGM(const char* filename) : m_music(nullptr, Mix_FreeMusic)
        {
            if(filename)
                Load(filename);
        }

        void SFX::Load(const char* filename)
        {
            if(!m_sound)
                m_sound = std::unique_ptr<Mix_Chunk, decltype(&Mix_FreeChunk)>(Mix_LoadWAV(filename), Mix_FreeChunk);
            if(!m_sound)
                throw LoadException(filename);
        }

        void SFX::Play(int channel, int repeats)
        {
            if(!m_sound)
                throw PlayException();
            else
                Mix_PlayChannel(channel, m_sound.get(), repeats);
        }

        SFX::SFX(const char* filename) : m_sound(nullptr, Mix_FreeChunk)
        {
            if(filename)
                Load(filename);
        }

        void SetBGMVolume(int volume)
        {
            Mix_VolumeMusic(volume);
        }

        int GetBGMVolume()
        {
            return Mix_VolumeMusic(-1);
        }

        bool Init()
        {
            return Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048);
        }

        void Close()
        {
            Mix_Quit();
        }
    }
}


