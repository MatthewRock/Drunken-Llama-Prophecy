#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <vector>
#include <memory>

class GameObject
{
    public:
        int GetW() { return 0;}
        int GetX() { return 0;}
        int GetY() { return 0;}
        int GetH() { return 0;}
};

class QuadTree
{
    public:
        QuadTree(int x, int y, int w, int h, int lev, int maxlev);
        ~QuadTree() = default;

        void Add(GameObject* obj);
        void Clear();
    protected:
    private:

    int m_x,m_y,m_width,m_height;
    int m_level, m_maxlevel;
    std::vector<GameObject*> m_objects;

    std::unique_ptr<QuadTree> m_NW;
    std::unique_ptr<QuadTree> m_NE;
    std::unique_ptr<QuadTree> m_SW;
    std::unique_ptr<QuadTree> m_SE;

    bool contains(GameObject* obj);
};

#endif // QUADTREE_HPP
