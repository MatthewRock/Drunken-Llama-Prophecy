#ifndef PLAYABLECHARACTER_H
#define PLAYABLECHARACTER_H
#include "Character.hpp"
#include "Texture.hpp"
namespace Llama
{
    class PlayableCharacter : public Character
    {
        public:
            PlayableCharacter();
            PlayableCharacter(std::string, const char*, Window&, int, int);
            virtual ~PlayableCharacter();

            void Draw();
            void Move();

        protected:
        private:
        int m_x, m_y;
        Texture m_tex;
    };
}
#endif // PLAYABLECHARACTER_H
