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
            PlayableCharacter() = default;
            PlayableCharacter(std::string, const char*, Window&, int, int);
            ~PlayableCharacter() = default;

            void Draw();
            void Move(int, int);
            void Teleport(int,int);
            std::pair<int, int> GetPosition()       {   return m_position;  }
            std::pair<int, int> GetAnimationOffset();
        protected:
        private:
        std::pair<int, int> m_position;
        std::pair<int, int> m_translocation;
        AnimationHandler m_tex;
    };
}
#endif // PLAYABLECHARACTER_H
