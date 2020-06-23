#ifndef __VC_VIEWPROJECTION_UNIFORM_RENDERCOMMAND__
#define __VC_VIEWPROJECTION_UNIFORM_RENDERCOMMAND__ 1

#include <rendercommand.h>
#include <material.h>
#include <platform_types.h>
#include <camera.h>

namespace VC {

  class ViewProjectionUniformCommand : public RenderCommand {

  public:

    virtual ~ViewProjectionUniformCommand();
    ViewProjectionUniformCommand();

    virtual void Action() override;

    void setCamera(Camera* cam);
    void setMaterial(Material mat);

  private:

    Camera *camera_;
    Material material_;

  };

}

#endif
