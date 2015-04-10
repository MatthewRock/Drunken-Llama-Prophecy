#include "Sounds.hpp"
#include <sstream> //stringstream
namespace Llama
{
    namespace Sounds
    {
        /// \brief Loads WAVE, MOD, MIDI, OGG, MP3 or FLAC music to BGM object from \filename. Throws \LoadException on failure.
        /// \param filename const char* : Path to music file.
        void BGM::Load(const char* filename)
        {
            //If music isn't already loaded, attempt to load it.
            if(!m_music)
                m_music = std::unique_ptr<Mix_Music, decltype(&Mix_FreeMusic)>(Mix_LoadMUS(filename), Mix_FreeMusic);
            //If music didn't load, throw exception.
            if(!m_music)
                throw LoadException(filename);
        }
        /// \brief Starts playing music. Stops playing all other BGMs.
        /// \param loops int : Natural number indicating number of times music should be played. By default music is played indefinitely.
        void BGM::Play(int loops)
        {
            //Under attempt to play unitialized music, throw exception.
            if(!m_music)
            {
                throw PlayException();
            }
            else
            {
                Mix_PlayMusic(m_music.get(), loops);
            }
        }
        /// \brief Stops playing any BGM music.
        void BGM::Stop()
        {
            Mix_HaltMusic();
        }
        /// \brief Pauses current music. Can be resumed later.
        void BGM::Pause()
        {
            Mix_PauseMusic();
        }
        /// \brief Resumes
        void BGM::Resume()
        {
            Mix_ResumeMusic();
        }
        /// \brief Rewinds (instantly) current music to the beginning of sample.
        void BGM::Rewind()
        {
            Mix_RewindMusic();
        }
        /// \brief Toggles between pause and resume.
        void BGM::Toggle()
        {
            if(Mix_PausedMusic())
                Resume();
            else
                Pause();
        }
        /// \param filename const char* : Path to music file. By default no file is loaded.
        BGM::BGM(const char* filename) : m_music(nullptr, Mix_FreeMusic)
        {
            // If file was provided, load it.
            if(filename)
                Load(filename);
        }
        /// \brief Loads WAVE sample to SFX object from \filename. Throws \LoadException on failure.
        /// \param filename const char* : Path to music file.
        void SFX::Load(const char* filename)
        {
            //If sample isn't already loaded, attempt to load it.
            if(!m_sound)
                m_sound = std::unique_ptr<Mix_Chunk, decltype(&Mix_FreeChunk)>(Mix_LoadWAV(filename), Mix_FreeChunk);
            //If sample didn't load, throw exception.
            if(!m_sound)
                throw LoadException(filename);
        }
        /// \brief Plays SFX sample.
        /// \param channel int : channel to play on; by default: first unreserved channel
        /// \param repeats int : number of repeats(sample will be played repeats+1 times). By default sample isn't repeated.
        void SFX::Play(int repeats, int channel)
        {
            if(!m_sound)
                throw PlayException();
            else
            {
                // Explanation: From what I see, it looks like setting volume is simple assignment operation, so it shouldn't be expensive.
                // Given that there is no way to set same volume to all samples(you have to set volume manually to each sample), I find it the best way
                // To assign volume every time that you play. It is a bit more memory savy(otherwise each sample would have current_volume int)
                // And each time we use Play() we would have to check if current_volume == __volume. This is both simpler, and - I hope - more effective.
                Mix_VolumeChunk(m_sound.get(), __volume);
                Mix_PlayChannel(channel, m_sound.get(), repeats);
            }
        }
        /// \param filename int repeats = const char* : path to sample(WAV) file. By default no file is loaded.
        SFX::SFX(const char* filename) : m_sound(nullptr, Mix_FreeChunk)
        {
            // If file was provided, load it.
            if(filename)
                Load(filename);
        }
        /// \brief Initializes systems required for playing music. Intended to be used in Initializer.
        bool Init()
        {
            //Load music modules.
            Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG);
            LOG_STRING("Music systems initialized.");

            SDL_version compile_version;
            SDL_MIXER_VERSION(&compile_version);
            std::stringstream compiled;
            compiled << "Compiled with SDL_Mixer ";
            compiled << static_cast<int>(compile_version.major);
            compiled << ".";
            compiled << static_cast<int>(compile_version.minor);
            compiled << ".";
            compiled << static_cast<int>(compile_version.patch);
            LOG_STRING(compiled.str());

            const SDL_version* linkedVersion = Mix_Linked_Version();
            std::stringstream linked;
            linked << "Linked with SDL_Mixer ";
            linked << static_cast<int>(linkedVersion->major);
            linked << ".";
            linked << static_cast<int>(linkedVersion->minor);
            linked << ".";
            linked << static_cast<int>(linkedVersion->patch);
            LOG_STRING(linked.str());

            return Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048);

        }
        /// \ brief Closes systems required for playing music. Intended to be used in Initializer.
        void Close()
        {
            Mix_Quit();
        }
        int SFX::__volume = 128;
    }
}


