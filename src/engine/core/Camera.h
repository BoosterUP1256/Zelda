#pragma once

#include "math/Mat4.h"
#include "math/Vec2.h"

namespace Gas {

    class Camera
    {
    public:
        Vec2f position;

        

    private:
        Mat4f _projectionMatrix, _viewMatrix;
    };

}
