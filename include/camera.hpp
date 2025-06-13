#ifndef CAMERA_H
#define CAMERA_H

#include "ray.hpp"
#include <vecmath.h>
#include <float.h>
#include <cmath>


class Camera {
public:
    Camera(const Vector3f &center, const Vector3f &direction, const Vector3f &up, int imgW, int imgH) {
        this->center = center;
        this->direction = direction.normalized();
        this->horizontal = Vector3f::cross(this->direction, up).normalized();
        this->up = Vector3f::cross(this->horizontal, this->direction);
        this->width = imgW;
        this->height = imgH;
    }

    // Generate rays for each screen-space coordinate
    virtual Ray generateRay(const Vector2f &point) = 0;
    virtual ~Camera() = default;

    int getWidth() const { return width; }
    int getHeight() const { return height; }

protected:
    // Extrinsic parameters
    Vector3f center;
    Vector3f direction;
    Vector3f up;
    Vector3f horizontal;
    // Intrinsic parameters
    int width;
    int height;
};

// TODO: Implement Perspective camera
// You can add new functions or variables whenever needed.
class PerspectiveCamera : public Camera {

public:
    PerspectiveCamera(const Vector3f &center, const Vector3f &direction,
            const Vector3f &up, int imgW, int imgH, float angle) : Camera(center, direction, up, imgW, imgH) {
        // angle is in radian.
        float half_ang = angle / 2.0f;
        fx = fy = imgH / (2 * tan(half_ang));

        cx = imgW / 2.0f;
        cy = imgH / 2.0f;
    }

    Ray generateRay(const Vector2f &point) override {
        // 
        float u = point.x();
        float v = point.y();

        float dRc_x = (u - cx) / fx;
        float dRc_y = (cy - v) / fy;

        Vector3f dRc = Vector3f(dRc_x, dRc_y, 1.0f).normalized();


        Matrix3f R = Matrix3f(horizontal, -up, direction);

        Vector3f dRw = R * dRc;


        return Ray(center, dRw);
    }

private:
    float fx, fy;
    float cx, cy;
};

#endif //CAMERA_H
