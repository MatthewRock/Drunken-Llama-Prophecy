#include "Character.hpp"
namespace Llama
{
    void Character::OrderExecutor(std::tuple<Orders, int, int> ord)
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

    void Character::Teleport(int x,int y)
    {
        m_position.first  = x;
        m_position.second = y;
    }


    std::pair<int, int> Character::GetAnimationOffset()
    {
        return std::make_pair( (m_tex.IsIdle()) ? 0 : ((m_translocation.first - ((m_translocation.second != 0) ? (m_position.second % 2) - 0.5 : 0) )  * 56  )* (m_tex.getAnimationLength() - m_tex.getFrame()) / m_tex.getAnimationLength()  , (m_tex.IsIdle()) ? 0 : (m_translocation.second * 41) * ( m_tex.getAnimationLength()- m_tex.getFrame()) / m_tex.getAnimationLength());
    }

    std::pair<int,int> Character::MoveQ()
    {
        return std::make_pair( (GetPosition().second % 2 == 1) ? -1 : 0, -1 );
    }
    std::pair<int,int> Character::MoveW()
    {
        return std::make_pair( 0, -1);
    }
    std::pair<int,int> Character::MoveE()
    {
        return std::make_pair( (GetPosition().second % 2 == 0) ? 1 : 0, -1);
    }
    std::pair<int,int> Character::MoveZ()
    {
        return std::make_pair( (GetPosition().second % 2 == 1) ? -1 : 0, 1);
    }
    std::pair<int,int> Character::MoveS()
    {
        return std::make_pair( 0, 1);
    }
    std::pair<int,int> Character::MoveA()
    {
        return std::make_pair( -1, 0);
    }
    std::pair<int,int> Character::MoveD()// hehehehehe
    {
        return std::make_pair( 1, 0);
    }
    std::pair<int,int> Character::MoveC()
    {
        return std::make_pair( (GetPosition().second % 2 == 0) ? 1 : 0, 1 );
    }
    void Character::Move(int x, int y)
    {
        switch(x)
        {
            case 'q':
            m_translocation = MoveQ();
            break;
            case 'w':
            m_translocation = MoveW();
            break;
            case 'e':
            m_translocation = MoveE();
            break;
            case 'a':
            m_translocation = MoveA();
            break;
            case 's':
            m_translocation = MoveS();
            break;
            case 'd':
            m_translocation = MoveD();//hehehehehehe
            break;
            case 'z':
            m_translocation = MoveZ();
            break;
            case 'c':
            m_translocation = MoveC();
            break;

        }
        m_position.first += m_translocation.first;
        m_position.second += m_translocation.second;
        if( (m_translocation.first < 0) || ( (m_position.second % 2 == 1) && (m_translocation.second!=0) && (m_translocation.first == 0) ) )
        {
            m_tex.InitiateAnimation(AnimationHandler::WALK_LEFT);
        }
        else
        {
            m_tex.InitiateAnimation(AnimationHandler::WALK_RIGHT);
        }

    }
    void Character::Attack(int x, int y)
    {
        m_translocation = std::make_pair(0,0);
        m_tex.InitiateAnimation(AnimationHandler::ATTACK_ANIM);
    }
}
