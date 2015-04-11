#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <map>
#include <utility>
#include <memory>
#include <type_traits>

namespace Llama
{
    /// \brief Allows storing pointers to \ElementType, and accessing them with \KeyType, or iterating through Manager.
    template <class KeyType, class ElementType>
    class Manager
    {
        private:
            typedef std::map<KeyType, std::unique_ptr<ElementType> > ManagerMap;
            ManagerMap m_container;

        public:
            Manager()
            {
                //static_assert(std::is_move_constructible<ElementType>::value,
                //"The element must be moveable in order to be used with Manager!");
            }
            Manager(const Manager& other) = delete;
            Manager(Manager&& other) = delete;
            ~Manager() = default;

            void Insert(KeyType key, ElementType* elem)
            {
                m_container.insert(std::pair<KeyType, std::unique_ptr<ElementType> >(key, std::unique_ptr<ElementType>(elem)));
            }
            /// \brief Deletes all elements stored under \key.
            void Erase(KeyType key)
            {
                m_container.erase(key);
            }
            ElementType* GetElement(KeyType key)
            {
                return m_container[key].get();
            }
            ElementType* operator[](KeyType key)
            {
                return m_container[key].get();
            }
            /// \brief Returns iterator to first element of Manager.
            inline auto Beginning() -> decltype( m_container.begin())
            {
                return m_container.begin();
            }
            /// \brief Returns const iterator to place past last element of Manager.
            inline auto End() -> decltype( m_container.end())
            {
                return m_container.end();
            }

            static auto GetIteratorType() -> decltype( m_container.begin())
            {
                return ManagerMap().begin();
            }
    };
}
#endif //MANAGER_HPP
