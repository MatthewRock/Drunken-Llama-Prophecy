#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <utility>

class Camera
{
    public:
        Camera() : m_cameraX(0), m_cameraY(0) {};
        inline std::pair<int, int> GetXY() { return {m_cameraX, m_cameraY}; };
        inline void UpdateXY(int dx, int dy);
        ~Camera() = default;
    protected:
    private:
    int m_cameraX;
    int m_cameraY;
};

void Camera::UpdateXY(int dx, int dy)
{
    m_cameraX += dx;
    m_cameraY += dy;
}
#endif // CAMERA_HPP
