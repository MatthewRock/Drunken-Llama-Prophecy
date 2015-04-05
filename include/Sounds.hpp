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
            Mix_Music* m_music;     //Pointer to music data for SDL_Mixer

        public:
            void Load(const char* filename);    //Loads sound file. Supports *.ogg and *.wmv files.
            void Play(int loops);               //Plays loops number of times sound loaded with Load.
                                                    //loops - defines how many times music will be played (default - 0 loops indefinitely).
            void Stop();                        //Stops playing music.  (duh)
            void Pause();                       //Pauses music.  (duh)
            void Resume();                      //If paused resumes music from where it has been paused. (duh)

            BGM();
            BGM(const char* filename);          //constructor loading sound data from file.
            ~BGM();

        };

        class SFX
        {
        private:
            Mix_Chunk* m_sound;
        public:
            void Load(const char* filename);    //Loads sound file. Supports *.wmv files.
            void Play(int channel, int repeats);//Plays file loaded with Load. (duh)
                                                    //Channel - selects mixer channel on which sound will be played (default - -1 assigns first free channel).
                                                    //Repeats - decides how many times sound will be repeated (default - 0 plays sound one time).
            SFX();
            SFX(const char* filename);          //constructor loading sound data from file.
            ~SFX();
        };

        void Init();
        void Close();
        void SetBGMVolume(int volume);
        int GetBGMVolume();
    }
}


#endif
