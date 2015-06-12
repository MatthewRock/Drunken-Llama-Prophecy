#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>

class GameObject
{
    public:
        GameObject() = default;
        virtual ~GameObject() = default;


        std::string Getname() { return m_name; }
        void Setname(std::string val) { m_name = val; }
    protected:
    private:
        std::string m_name;
};

#endif // GAMEOBJECT_H
