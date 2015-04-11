#ifndef HEX_HPP
#define HEX_HPP

#include "Printable.hpp"
#include "Manager.hpp"
#include "Texture.hpp"

namespace Llama
{
    class Hex : public Printable
    {
        public:
            Hex();
            void Update(){};
            void Draw(){};
            int GetW(){};
            int GetH(){};

        protected:
        private:

        decltype(Manager<int,Texture>::GetIteratorType()) m_Tex;
    };
}
#endif // HEX_HPP
