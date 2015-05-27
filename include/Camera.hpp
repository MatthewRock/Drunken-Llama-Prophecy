#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <utility>

namespace Llama
{
    class Camera
    {
        public:
            Camera() = default;
            inline std::pair<int, int> GetXY() { return {m_cameraX, m_cameraY} };
            inline void UpdateXY(int x, int y);
            ~Camera() = default;
        protected:
        private:
        int m_cameraX;
        int m_cameraY;
    };

    void Camera::UpdateXY(int x, int y)
    {
        m_cameraX += x;
        m_cameraY += y;
    }
}
#endif // CAMERA_HPP
