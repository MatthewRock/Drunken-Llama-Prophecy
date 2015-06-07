#include "PlayableCharacter.hpp"
namespace Llama
{
    PlayableCharacter::PlayableCharacter(std::string n, const char* filename, Window& win, int x, int y, GameLogic& logic) : Character(filename, win, x, y)
    {
        m_translocation = std::make_pair(0, 0);
        Setname(n);
        logic.AddRule([](SDL_Event& event)
                      {
                            if(event.type == SDL_KEYDOWN)
                            {
                                switch(event.key.keysym.sym)
                                {
                                    case SDLK_q:
                                    case SDLK_w:
                                    case SDLK_e:
                                    case SDLK_z:
                                    case SDLK_c:
                                    case SDLK_s:
                                    case SDLK_a:
                                    case SDLK_d:
                                    case SDLK_SPACE:
                                        return true;
                                }
                            }
                            return false;
                      });
    }
    void PlayableCharacter::Draw()
    {
        m_tex.Draw(std::make_pair(9,9));
        if(m_tex.IsIdle())
            m_translocation = std::make_pair(0, 0);
    }

    void PlayableCharacter::Order(Orders ord, int x, int y)
    {
        m_ordersQueue.push(std::make_tuple(ord, x, y));

    }
    void PlayableCharacter::Execute()
    {
        if(!m_ordersQueue.empty() && IsIdle())
        {
            OrderExecutor(m_ordersQueue.front());
            m_ordersQueue.pop();
        }
    }



    void PlayableCharacter::HandleEvents(SDL_Event& event)
    {
        if(event.type == SDL_KEYDOWN)
        {
            if(event.key.keysym.sym == SDLK_BACKSPACE)
            {
                decltype(m_ordersQueue) temp;
                std::swap(m_ordersQueue, temp);
            }

            if(IsIdle())
                switch(event.key.keysym.sym)
                {
                    case SDLK_q:
                        //Order(MOVE, (GetPosition().second % 2 == 1) ? -1 : 0, -1 );
                        Order(MOVE, 'q', 0);
                    break;
                    case SDLK_w:
                        //Order(MOVE, 0, -1);
                        Order(MOVE, 'w',0);
                    break;
                    case SDLK_e:
                        //Order(MOVE, (GetPosition().second % 2 == 0) ? 1 : 0, -1);
                        Order(MOVE, 'e',0);
                    break;
                    case SDLK_z:
                       // Order(MOVE, (GetPosition().second % 2 == 1) ? -1 : 0, 1);
                       Order(MOVE, 'z',0);
                    break;
                    case SDLK_c:
                       // Order(MOVE, (GetPosition().second % 2 == 0) ? 1 : 0, 1 );
                       Order(MOVE, 'c',0);
                    break;
                    case SDLK_s:
                        //Order(MOVE, 0, 1);
                        Order(MOVE, 's',0);
                    break;
                    case SDLK_a:
                      //  Order(MOVE, -1, 0);
                      Order(MOVE, 'a',0);
                    break;
                    case SDLK_d:
                      //  Order(MOVE, 1, 0);
                      Order(MOVE, 'd',0);
                    break;
                    case SDLK_SPACE:
                        Order(ATTACK, 0, 0);
                    break;
                    default:
                    break;
                }
        }
    }
}
