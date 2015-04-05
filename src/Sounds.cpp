#include "Sounds.hpp"

namespace Llama
{
    namespace Sounds
    {
        void BGM::Load(const char* filename)
        {
          m_music = Mix_LoadMUS(filename);
          if (m_music == NULL)
            throw LoadException(filename);
        }

        void BGM::Play(int loops=-1)
        {
            if (m_music == NULL)
            {
                throw PlayException();
            }
            else
            {
                Mix_PlayMusic(m_music, loops);
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

        BGM::BGM()
        {
          m_music = NULL;
        }

        BGM::BGM(const char* filename)
        {
          Load(filename);
        }

        BGM::~BGM()
        {
          Mix_FreeMusic(m_music);
        }


        void SFX::Load(const char* filename)
        {
            m_sound = Mix_LoadWAV(filename);
            if ( m_sound == NULL )
                throw LoadException(filename);
        }

        void SFX::Play(int channel = -1, int repeats = 0)
        {
            if ( m_sound == NULL )
                throw PlayException();
            else
                Mix_PlayChannel(channel, m_sound, repeats);
        }

        SFX::SFX()
        {
            m_sound = NULL;
        }

        SFX::SFX(const char* filename)
        {
            Load(filename);
        }

        SFX::~SFX()
        {
            Mix_FreeChunk(m_sound);
        }

        void SetBGMVolume(int volume)
        {
          Mix_VolumeMusic(volume);
        }

        int GetBGMVolume()
        {
          Mix_VolumeMusic(-1);
        }

        void Init()
        {
          Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048);
        }

        void Close()
        {
          Mix_Quit();
        }
    }
}


