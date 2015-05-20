#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
namespace Llama
{
    class Character
    {
        public:
            std::string GetName()       {   return m_name;  }
            void SetName(std::string n) {   m_name = n;     }
            virtual void Draw() = 0;
            virtual void Move() = 0;

            Character();
            virtual ~Character();
        protected:
        private:
            std::string m_name;
    };
}
#endif // CHARACTER_H
