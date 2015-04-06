#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

/** \brief  This header implements the class Timer.
            Timer allows the creation of clock, with various precisions available,
            is available for C++11 standard, generic.
 */

namespace Llama
{
    typedef std::chrono::high_resolution_clock  Timer_Clock_Precise;
    typedef std::chrono::steady_clock           Timer_Clock_Steady;
    typedef std::chrono::system_clock           Timer_Clock_System;


    typedef std::chrono::hours                  Timer_Precision_Hour;
    typedef std::chrono::minutes                Timer_Precision_Minute;
    typedef std::chrono::seconds                Timer_Precision_Seconds;
    typedef std::chrono::milliseconds           Timer_Precision_Milliseconds;
    typedef std::chrono::microseconds           Timer_Precision_Microseconds;
    typedef std::chrono::nanoseconds            Timer_Precision_Nanoseconds;

    template<typename Clock_Type = Timer_Clock_Precise, typename Time_Precision = Timer_Precision_Milliseconds>
    class Timer
    {
        typename Clock_Type::time_point startTime;
        long long pauseTime;

        bool started;
        bool paused;

    public:
        /// \brief Default constructor of Timer. Setting everything to 0 and false.
        Timer() : pauseTime(0), started(false), paused(false) {}
        /// \brief Start counting time. It basically sets startTicks to current ticks from SDL_GetTicks(), and sets started to true.
        void Start();
        /// \brief Set flags to false.
        void Stop();
        /// \brief Keeps value of ticks when timer has stopped. Will be used to resume timer.
        void Pause();
        /// \brief starts counting time from the stopped time.
        void Unpause();
        /// \brief Return startTicks(if running), pausedTicks(if paused), or 0 if timer isn't started
        int GetTicks();

        inline bool IsPaused() { return paused;};
        inline bool IsStarted() { return started;};
        inline int Seconds(int s) { return s*1000;}
        inline int Seconds(double s) { return s*1000;}
        static inline auto GetCurrentTime() -> decltype(Clock_Type::now()) { return Clock_Type::now(); }
    };

    template <typename Clock_Type, typename Time_Precision>
    void Timer<Clock_Type, Time_Precision>::Start()
    {
        //Set flags
        started = true;
        paused = false;
        //Time that passes when we're paused. Currently 0 - we just started.
        pauseTime = 0;
        //Set starting time point.
        startTime = Clock_Type::now();
    }
    template <typename Clock_Type, typename Time_Precision>
    void Timer<Clock_Type, Time_Precision>::Stop()
    {
        //Zero flags. Everything else will be cleaned up in proper starting functions
        //Also, since we've stopped, now there is no sense to check time from clock.
        started = false;
        paused = false;
    }
    template <typename Clock_Type, typename Time_Precision>
    void Timer<Clock_Type, Time_Precision>::Pause()
    {
        //If timer isn't paused, and is running
        if(started && (!paused))
        {
            //Pause it
            paused = true;
            //Count the time that passed from start till now
            std::chrono::duration<double> time = Clock_Type::now() - startTime;
            //And return it in milliseconds.
            pauseTime += std::chrono::duration_cast<Time_Precision>(time).count();

        }

    }
    template <typename Clock_Type, typename Time_Precision>
    void Timer<Clock_Type, Time_Precision>::Unpause()
    {
        //If program is paused(can only be paused when running)
        if(paused)
        {
            //Start from now.
            //We don't have to set
            startTime = Clock_Type::now();
            //We aren't paused anymore.
            paused = false;
        }
    }
    template <typename Clock_Type, typename Time_Precision>
    int Timer<Clock_Type, Time_Precision>::GetTicks()
    {
        if(started)
        {
            if(paused)
            {
                return pauseTime;
            }
            else
            {
                //Count the time that passed from start till now
                std::chrono::duration<double> time = Clock_Type::now() - startTime;
                //And return it in milliseconds.
                return std::chrono::duration_cast<Time_Precision>(time).count() + pauseTime;
            }
        }
        return 0;
    }
};
#endif // TIMER_HPP
