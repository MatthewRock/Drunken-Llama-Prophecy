#include "QuadTree.hpp"

QuadTree::QuadTree(int x, int y, int w, int h, int lev, int maxlev)
                    : m_x(x), m_y(y), m_width(w), m_height(h), m_level(lev), m_maxlevel(maxlev)
{
    if(lev == maxlev)
        return;

    m_NW = std::unique_ptr<QuadTree>(new QuadTree(x,y, m_width / 2, m_height / 2, m_level + 1, maxlev));
    m_NE = std::unique_ptr<QuadTree>(new QuadTree(x + m_width / 2, y, m_width / 2, m_height / 2, m_level + 1, maxlev));
    m_SW = std::unique_ptr<QuadTree>(new QuadTree(x, y + m_height / 2, m_width / 2, m_height / 2, m_level + 1, maxlev));
    m_SE = std::unique_ptr<QuadTree>(new QuadTree(x + m_width / 2, y + m_height / 2, m_width / 2, m_height / 2, m_level + 1, maxlev));
}

void QuadTree::Add(GameObject* obj)
{
    if(m_level == m_maxlevel)
    {
        m_objects.push_back(obj);
    }
    else
    {
        if(m_NW->contains(obj))
        {
            m_NW->Add(obj);
        }
        else if(m_NE->contains(obj))
        {
            m_NE->Add(obj);
        }
        else if(m_SW->contains(obj))
        {
            m_SW->Add(obj);
        }
        else if(m_SE->contains(obj))
        {
            m_SE->Add(obj);
        }
        else
        {
            //What the fuck?
        }
    }
}

void QuadTree::Clear()
{
    if(!(m_level == m_maxlevel))
    {
        m_NW->Clear();
        m_NE->Clear();
        m_SW->Clear();
        m_SE->Clear();
    }
    m_objects.clear();
}

bool QuadTree::contains(GameObject* obj)
{
    return !(obj->GetX() > m_x + m_width ||
             obj->GetX() + obj->GetW() < m_x ||
             obj->GetY() > m_y + m_height ||
             obj->GetY() + obj->GetH() < m_y);
}
