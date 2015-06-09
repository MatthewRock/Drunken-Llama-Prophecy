#include "PlayableCharacter.hpp"
namespace Llama
{
    PlayableCharacter::PlayableCharacter(std::string n, const char* filename, Window& win, int x, int y, GameLogic& logic, Land& land) : Character(filename, win, x, y, 10, 1, 1, 0), m_map(&land)
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
        m_tex.Draw(std::make_pair(9,9), (m_stats.hp - m_damage)*48/m_stats.hp);
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
    void PlayableCharacter::Attack(int x, int y)
    {
        Character::Attack(GetPosition().first -x + ((GetPosition().second % 2 == 0) ? -1 : 0), 0);
        m_map->DamageMonster(x, y, m_stats.str);

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
                        m_translocation = MoveQ();
                        if(m_map->IsThereMonster(GetPosition().first + m_translocation.first, GetPosition().second+m_translocation.second))
                            Order(ATTACK, GetPosition().first + m_translocation.first, GetPosition().second+m_translocation.second);
                        else
                            if(m_map->IsPassable(GetPosition().first + m_translocation.first, GetPosition().second+m_translocation.second))
                                Order(MOVE, 'q', 0);
                            else
                                m_translocation = std::make_pair(0,0);
                    break;
                    case SDLK_w:
                        m_translocation = MoveW();
                        if(m_map->IsThereMonster(GetPosition().first + m_translocation.first, GetPosition().second+m_translocation.second))
                            Order(ATTACK, GetPosition().first + m_translocation.first, GetPosition().second+m_translocation.second);
                        else
                            if(m_map->IsPassable(GetPosition().first + m_translocation.first, GetPosition().second+m_translocation.second))
                                Order(MOVE, 'w', 0);
                            else
                                m_translocation = std::make_pair(0,0);
                    break;
                    case SDLK_e:
                        m_translocation = MoveE();
                        if(m_map->IsThereMonster(GetPosition().first + m_translocation.first, GetPosition().second+m_translocation.second))
                            Order(ATTACK, GetPosition().first + m_translocation.first, GetPosition().second+m_translocation.second);
                        else
                            if(m_map->IsPassable(GetPosition().first + m_translocation.first, GetPosition().second+m_translocation.second))
                                Order(MOVE, 'e', 0);
                            else
                                m_translocation = std::make_pair(0,0);
                    break;
                    case SDLK_z:
                        m_translocation = MoveZ();
                        if(m_map->IsThereMonster(GetPosition().first + m_translocation.first, GetPosition().second+m_translocation.second))
                            Order(ATTACK, GetPosition().first + m_translocation.first, GetPosition().second+m_translocation.second);
                        else
                            if(m_map->IsPassable(GetPosition().first + m_translocation.first, GetPosition().second+m_translocation.second))
                                Order(MOVE, 'z', 0);
                            else
                                m_translocation = std::make_pair(0,0);
                    break;
                    case SDLK_c:
                        m_translocation = MoveC();
                        if(m_map->IsThereMonster(GetPosition().first + m_translocation.first, GetPosition().second+m_translocation.second))
                            Order(ATTACK, GetPosition().first + m_translocation.first, GetPosition().second+m_translocation.second);
                        else
                            if(m_map->IsPassable(GetPosition().first + m_translocation.first, GetPosition().second+m_translocation.second))
                                Order(MOVE, 'c', 0);
                            else
                                m_translocation = std::make_pair(0,0);
                    break;
                    case SDLK_s:
                        m_translocation = MoveS();
                        if(m_map->IsThereMonster(GetPosition().first + m_translocation.first, GetPosition().second+m_translocation.second))
                            Order(ATTACK, GetPosition().first + m_translocation.first, GetPosition().second+m_translocation.second);
                        else
                            if(m_map->IsPassable(GetPosition().first + m_translocation.first, GetPosition().second+m_translocation.second))
                                Order(MOVE, 's', 0);
                            else
                                m_translocation = std::make_pair(0,0);
                    break;
                    case SDLK_a:
                        m_translocation = MoveA();
                        if(m_map->IsThereMonster(GetPosition().first + m_translocation.first, GetPosition().second+m_translocation.second))
                            Order(ATTACK, GetPosition().first + m_translocation.first, GetPosition().second+m_translocation.second);
                        else
                            if(m_map->IsPassable(GetPosition().first + m_translocation.first, GetPosition().second+m_translocation.second))
                                Order(MOVE, 'a', 0);
                            else
                                m_translocation = std::make_pair(0,0);
                    break;
                    case SDLK_d:
                        m_translocation = MoveD();
                        if(m_map->IsThereMonster(GetPosition().first + m_translocation.first, GetPosition().second+m_translocation.second))
                            Order(ATTACK, GetPosition().first + m_translocation.first, GetPosition().second+m_translocation.second);
                        else
                            if(m_map->IsPassable(GetPosition().first + m_translocation.first, GetPosition().second+m_translocation.second))
                                Order(MOVE, 'd', 0);
                            else
                                m_translocation = std::make_pair(0,0);
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
