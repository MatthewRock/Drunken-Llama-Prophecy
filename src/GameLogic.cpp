#include "GameLogic.hpp"

namespace Llama
{
    void GameLogic::ProcessInput(SDL_Event& event)
    {
        //For every function in our list
        for(auto it = m_ProcessingRulesList.begin(); it != m_ProcessingRulesList.end(); ++it)
        {
            //If the function qualifies input as valid for turn processing, raise flag and stop searching.
            if((*it)(event))
            {
                m_ProcessTurn = true;
                return;
            }
        }
    }
    /// \brief Processess turn(activates enteties, moves map, etc), but rather than on its own, invokes other instances.
    void GameLogic::ProcessTurn()
    {
        //Process...
        if(m_ProcessTurn)
        {

            m_ProcessTurn = false; // After processing, set flag to false once again.
        }

    }
    void GameLogic::AddRule(std::function<bool(SDL_Event&)>&& func)
    {
        m_ProcessingRulesList.push_back(func);
    }
}
