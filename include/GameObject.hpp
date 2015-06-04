#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <string>
namespace Llama
{
    class GameObject
    {
        public:
            GameObject();
            virtual ~GameObject();

            virtual void Draw() = 0;

            std::string Getname() { return m_name; }
            void Setname(std::string val) { m_name = val; }
        protected:
        private:
            std::string m_name;
    };
}
#endif // GAMEOBJECT_H
