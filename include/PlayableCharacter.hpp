#ifndef PLAYABLECHARACTER_H
#define PLAYABLECHARACTER_H

#include <utility>
#include "Character.hpp"
#include "AnimationHandler.hpp"
namespace Llama
{
    class PlayableCharacter : public Character
    {
        public:
            PlayableCharacter();
            PlayableCharacter(std::string, const char*, Window&, int, int);
            virtual ~PlayableCharacter();

            void Draw();
            void Move(int, int);
            std::pair<int, int> GetPosition()  {   return m_position;  }
        protected:
        private:
        std::pair<int, int> m_position;
        std::pair<int, int> m_translocation;
        AnimationHandler m_tex;
    };
}
#endif // PLAYABLECHARACTER_H
