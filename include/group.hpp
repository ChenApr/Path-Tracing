#ifndef GROUP_H
#define GROUP_H


#include "object3d.hpp"
#include "ray.hpp"
#include "hit.hpp"
#include <iostream>
#include <vector>


// TODO: Implement Group - add data structure to store a list of Object*
class Group : public Object3D {

public:

    Group() = default;

    explicit Group (int num_objects) {
        objects.resize(num_objects, nullptr);
    }

    ~Group() override {
        for(auto object : objects) {
            if(object) delete object;
        }
        objects.clear();
    }

    bool intersect(const Ray &r, Hit &h, float tmin) override {
        bool hit_any = false;
        for(auto object : objects) {
            if(object && object->intersect(r, h, tmin)) {
                hit_any = true;
            }
        }
        return hit_any;
    }

    void addObject(int index, Object3D *obj) {
        if(index >= objects.size()) 
            objects.resize(index + 1, nullptr);
        objects[index] = obj;
    }

    int getGroupSize() {
        return objects.size();
    }

private:
    std::vector<Object3D*> objects;


};

#endif
	
