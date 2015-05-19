#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <vector>
#include <memory>

class GameObject
{
    int _x,_y,_w,_h;
    public:
        GameObject(int x, int y, int w, int h) : _x(x), _y(y), _w(w), _h(h){}
        int GetW() { return _w;}
        int GetX() { return _x;}
        int GetY() { return _y;}
        int GetH() { return _h;}
};

class QuadTree
{
    public:
        QuadTree(int x, int y, int w, int h, int lev, int maxlev);
        ~QuadTree() = default;

        void Add(GameObject* obj);
        void Clear();
        bool Collides(GameObject* first, GameObject* other);
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
