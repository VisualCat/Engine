#ifndef __VC_OBJECT__
#define __VC_OBJECT__ 1

#include <geometry.h>
#include <material.h>
#include <vector>

#include <rendercommand.h>

namespace VC {

  class Object {

  public:

    void setGeometry(Geometry *newGeo);
    void setMaterial(Material *newMat);

    Geometry* getGeometry();
    Material* getMaterial();

    void draw(std::vector<RenderCommand*> *comandsList);

  private:
    Geometry *geometry_;
    Material *material_;

  };

}


#endif


