#ifndef GAMELOGIC_HPP
#define GAMELOGIC_HPP

#include "SDL2/SDL.h"
#include <functional>
#include <list>
namespace Llama
{
    class GameLogic
    {
        public:
            GameLogic() = default;
            ~GameLogic() = default;

            /// \brief Checks if input qualifies for new turn.
            void ProcessInput(SDL_Event& event);
            /// \brief Processess turn(activates enteties, moves map, etc), but rather than on its own, invokes other instances.
            void ProcessTurn();
            void AddRule(std::function<bool(SDL_Event&)>&& func);

        protected:
        private:
            bool m_ProcessTurn;
            /// \brief List of unary functions taking SDL_Event, which returns true if the input qualifies for processing turn.
            std::list<std::function<bool(SDL_Event&)> > m_ProcessingRulesList;
    };
}
#endif // GAMELOGIC_HPP
