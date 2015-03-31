#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <map>
#include <pair>

namespace Llama
{
    template <class KeyType, class ElementType>
    class Manager
    {
        public:
            Manager() = default;
            Manager(const Manager& other) = delete;

            ~Manager() = default;
            void insert(KeyType key, ElementType elem)
            {
                m_container.insert(std::pair<KeyType, ElementType>(key, elem));
            }
            void erase(KeyType key)
            {
                m_container.erase(key);
            }
            ElementType& getElement(KeyType key)
            {
                return m_container[key];
            }

            ElementType& operator[](KeyType key)
            P
            {
                return m_container[key];
            }

        private:
            std::map<KeyType, ElementType> m_container;
    };
}
#endif //MANAGER_HPP

