#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <map>
#include <utility>
#include <memory>

namespace Llama
{
    template <class KeyType, class ElementType>
    class Manager
    {
        private:
            std::map<KeyType, std::unique_ptr<ElementType> > m_container;

        public:
            Manager() = default;
            Manager(const Manager& other) = delete;

            ~Manager() = default;

            void Insert(KeyType key, ElementType* elem)
            {
                m_container.insert(std::pair<KeyType, std::unique_ptr<ElementType> >(key, std::unique_ptr<ElementType>(elem)));
            }

            void Erase(KeyType key)
            {
                m_container.erase(key);
            }

            ElementType& GetElement(KeyType key)
            {
                return m_container[key];
            }

            ElementType& operator[](KeyType key)
            {
                return m_container[key];
            }

            inline auto Beginning() -> decltype( m_container.begin())
            {
                return m_container.begin();
            }

            inline auto End() -> decltype( m_container.end())
            {
                return m_container.end();
            }

    };
}
#endif //MANAGER_HPP

