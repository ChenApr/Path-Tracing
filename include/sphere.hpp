#ifndef SPHERE_H
#define SPHERE_H

#include "object3d.hpp"
#include <vecmath.h>
#include <cmath>

// TODO: Implement functions and add more fields as necessary

class Sphere : public Object3D {
public:
    Sphere() {
        // unit ball at the center
        this->center = Vector3f::ZERO;
        this->radius = 1.0;
        this->material = nullptr;
    }

    Sphere(const Vector3f &center, float radius, Material *material) : Object3D(material) {
        this->center = center;
        this->radius = radius;
    }

    ~Sphere() override = default;

    bool intersect(const Ray &r, Hit &h, float tmin) override {
        //
        Vector3f Pc = this->center;
        Vector3f RO = r.getOrigin();
        Vector3f Rd = r.getDirection().normalized();
        Vector3f l = Pc - RO;

        float l_square = l.squaredLength();
        float r_square = this->radius * this->radius;

        float tp = Vector3f::dot(l, Rd);
        float tp_square = tp * tp;

        if(l_square - r_square > 1e-4 && tp < 0) return false;

        float d_square = l_square - tp_square;

        if(d_square - r_square > 1e-4) return false;

        float t_prime_square = r_square - d_square;
        float t_prime =  sqrt(t_prime_square);

        float t;
        if(l_square - r_square > 1e-4) {
            t = tp - t_prime;
            
        } else if(l_square - r_square < -1e-4) {
            t = tp + t_prime;
        } else {
            return false;
        }
        if(t < tmin) return false;
        if(t > h.getT()) return false;

        Vector3f t_point = RO + Rd * t;
        Vector3f N = (t_point - Pc).normalized();
            
        h.set(t, this->material, N);
            
        return true;
    }

protected:
    Vector3f center;
    float radius;
};


#endif
