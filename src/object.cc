
#include <object.h>

//Commands include
#include <buffer_rendercommand.h>
#include <material_rendercommand.h>
#include <draw_rendercommand.h>
#include <viewprojection_uniform_rendercommand.h>

using namespace VC;

void Object::setGeometry(Geometry newGeo)
{

#ifdef VERBOSE
  if (newGeo == nullptr)
  {
    printf("Geometry set in object is null\n");
  }
#endif

  geometry_ = newGeo;

}

void Object::setMaterial(Material newMat)
{

#ifdef VERBOSE
  if (newMat == nullptr)
  {
    printf("Material set in object is null\n");
  }
#endif

  material_ = newMat;

}

Geometry Object::getGeometry()
{
  return geometry_;
}

Material Object::getMaterial()
{
  return material_;
}

void Object::draw(std::vector<RenderCommand*> *commandsList, Camera *myCamera)
{

  BufferCommand* bComand = new BufferCommand();
  bComand->setGeometry(geometry_.ID);
  
  
  MaterialCommand* mComand = new MaterialCommand();
  mComand->setMaterial(material_.ID);

  DrawCommand* dCommand = new DrawCommand();
  dCommand->setGeometry(geometry_.ID);
  dCommand->setMaterial(material_.ID);

  commandsList->push_back(bComand);
  commandsList->push_back(mComand);

  //Uniform condition
  //ViewProjection
  ViewProjectionUniformCommand* vpuCommand = new ViewProjectionUniformCommand();
  vpuCommand->setCamera(myCamera);
  vpuCommand->setMaterial(material_);
  commandsList->push_back(vpuCommand);

  commandsList->push_back(dCommand);

}
