#include "PlayableCharacter.hpp"
namespace Llama
{
    PlayableCharacter::PlayableCharacter(std::string n, const char* filename, Window& win, int x, int y, GameLogic& logic) : m_tex(filename, win, 63, 63)
    {
        m_position = std::make_pair(x, y);
        m_translocation = std::make_pair(0, 0);
        Setname(n);
        logic.AddRule([](SDL_Event& event)
                      {
                            if(event.type == SDL_KEYDOWN && event.key.repeat == 0)
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
    void PlayableCharacter::Move(int x, int y)
    {
        std::pair<int,int> coordsffs;
        switch(x)
        {
            case 'q':
            coordsffs = MoveQ();
            break;
            case 'w':
            coordsffs = MoveW();
            break;
            case 'e':
            coordsffs = MoveE();
            break;
            case 'a':
            coordsffs = MoveA();
            break;
            case 's':
            coordsffs = MoveS();
            break;
            case 'd':
            coordsffs = MoveD();//hehehehehehe
            break;
            case 'z':
            coordsffs = MoveZ();
            break;
            case 'c':
            coordsffs = MoveC();
            break;

        }
        //m_translocation = std::make_pair(x, y);
        m_position.first += coordsffs.first;
        m_position.second += coordsffs.second;
        if( (coordsffs.first < 0) || ( (m_position.second % 2 == 1) && (coordsffs.second!=0) && (coordsffs.first == 0) ) )
        {
            m_tex.InitiateAnimation(AnimationHandler::WALK_LEFT);
        }
        else
        {
            m_tex.InitiateAnimation(AnimationHandler::WALK_RIGHT);
        }

    }
    void PlayableCharacter::Attack(int x, int y)
    {
        m_tex.InitiateAnimation(AnimationHandler::ATTACK_ANIM);
    }
    void PlayableCharacter::Execute()
    {
        if(!m_ordersQueue.empty() && IsIdle())
        {
            OrderExecutor(m_ordersQueue.front());
            m_ordersQueue.pop();
        }
    }
    void PlayableCharacter::OrderExecutor(std::tuple<Orders, int, int> ord)
    {
        switch(std::get<0>(ord))
        {
            case MOVE:
                Move(std::get<1>(ord), std::get<2>(ord));
            break;
            case ATTACK:
                Attack(std::get<1>(ord), std::get<2>(ord));
            default:
            break;
        }
    }
    void PlayableCharacter::Teleport(int x,int y)
    {
        m_position.first  = x;
        m_position.second = y;
    }
    std::pair<int, int> PlayableCharacter::GetAnimationOffset()
    {
        return std::make_pair( ((m_translocation.first - ((m_translocation.second != 0) ? (m_position.second % 2) - 0.5 : 0) )  * 56  )* (m_tex.getAnimationLength() - m_tex.getFrame()) / m_tex.getAnimationLength()  , (m_translocation.second * 41) * ( m_tex.getAnimationLength()- m_tex.getFrame()) / m_tex.getAnimationLength());
    }
    std::pair<int,int> PlayableCharacter::MoveQ()
    {
        return std::make_pair( (GetPosition().second % 2 == 1) ? -1 : 0, -1 );
    }
    std::pair<int,int> PlayableCharacter::MoveW()
    {
        return std::make_pair( 0, -1);
    }
    std::pair<int,int> PlayableCharacter::MoveE()
    {
        return std::make_pair( (GetPosition().second % 2 == 0) ? 1 : 0, -1);
    }
    std::pair<int,int> PlayableCharacter::MoveZ()
    {
        return std::make_pair( (GetPosition().second % 2 == 1) ? -1 : 0, 1);
    }
    std::pair<int,int> PlayableCharacter::MoveS()
    {
        return std::make_pair( 0, 1);
    }
    std::pair<int,int>PlayableCharacter::MoveA()
    {
        return std::make_pair( -1, 0);
    }
    std::pair<int,int>PlayableCharacter::MoveD()// hehehehehe
    {
        return std::make_pair( 1, 0);
    }
    std::pair<int,int> PlayableCharacter::MoveC()
    {
        return std::make_pair( (GetPosition().second % 2 == 0) ? 1 : 0, 1 );
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
