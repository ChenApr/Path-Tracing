#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "object3d.hpp"
#include <vecmath.h>
#include <cmath>
#include <iostream>
using namespace std;

// TODO: implement this class and add more fields as necessary,
class Triangle: public Object3D {

public:
	Triangle() = delete;

    // a b c are three vertex positions of the triangle
	Triangle( const Vector3f& a, const Vector3f& b, const Vector3f& c, Material* m) : Object3D(m) {
		vertices[0] = a;
		vertices[1] = b;
		vertices[2] = c;
		normal = Vector3f::cross(b - a, c - a).normalized();
	}

	bool intersect( const Ray& ray,  Hit& hit , float tmin) override {
		Vector3f RO = ray.getOrigin();
		Vector3f Rd = ray.getDirection();

		Vector3f E1 = vertices[0] - vertices[1];
		Vector3f E2 = vertices[0] - vertices[2];
		Vector3f S = vertices[0] - RO;

		Matrix3f d12 = Matrix3f(Rd, E1, E2);
		Matrix3f s12 = Matrix3f(S, E1, E2);
		Matrix3f ds2 = Matrix3f(Rd, S, E2);
		Matrix3f d1s = Matrix3f(Rd, E1, S);

		float d12d = d12.determinant();
		float s12d = s12.determinant();
		float ds2d = ds2.determinant();
		float d1sd = d1s.determinant();

		float t = s12d / d12d;
		float beta = ds2d / d12d;
		float gamma = d1sd / d12d;

		if(t <= 0) return false;
		if(beta < 0 || beta > 1 || gamma < 0 || gamma > 1 || beta + gamma > 1) return false;

		if(t < tmin) return false;
		if(t > hit.getT()) return false;

		hit.set(t, this->material, normal);

        return true;
	}
	Vector3f normal;
	Vector3f vertices[3];
protected:

};

#endif //TRIANGLE_H
