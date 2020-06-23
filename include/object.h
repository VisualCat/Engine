#ifndef __VC_OBJECT__
#define __VC_OBJECT__ 1

#include <geometry.h>
#include <material.h>
#include <vector>
#include <camera.h>

#include <rendercommand.h>

namespace VC {

  class Object {

  public:

    void setGeometry(Geometry newGeo);
    void setMaterial(Material newMat);

    Geometry getGeometry();
    Material getMaterial();

    void draw(std::vector<RenderCommand*> *commandsList, Camera *myCamera);

  private:
    Geometry geometry_;
    Material material_;

  };

}


#endif


