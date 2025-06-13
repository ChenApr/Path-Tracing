#ifndef PLANE_H
#define PLANE_H

#include "object3d.hpp"
#include <vecmath.h>
#include <cmath>

// TODO: Implement Plane representing an infinite plane
// function: ax+by+cz=d
// choose your representation , add more fields and fill in the functions

class Plane : public Object3D {
public:
    Plane() = default;

    Plane(const Vector3f &normal, float d, Material *m) : Object3D(m) {
        this->normal = normal.normalized();
        this->d = d;
    }

    ~Plane() override = default;

    bool intersect(const Ray &r, Hit &h, float tmin) override {

        Vector3f RO = r.getOrigin();
        Vector3f Rd = r.getDirection().normalized();
        Vector3f n = this->normal.normalized();
        
        float d = this->d;
        float nRO = Vector3f::dot(n, RO);
        float nRd = Vector3f::dot(n, Rd);

        if(fabs(nRd) < 1e-8) return false;
        
        float t = - (- d + nRO) / nRd;
        
        if(t <= 0) return false;
        if(t < tmin) return false;
        if (t > h.getT()) return false;

        if(nRd >= 1e-8) n = -n;

        h.set(t, this->material, n);

        return true;
    }

protected:
    Vector3f normal;
    float d;
};

#endif //PLANE_H
		

