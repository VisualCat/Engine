#ifndef __MODEL_UNIFORM_RENDERCOMMAND__
#define __MODEL_UNIFORM_RENDERCOMMAND__ 1

#include <rendercommand.h>
#include <material.h>
#include <platform_types.h>
#include <transform_component.h>

namespace VC {

	class ModelUniformCommand : public RenderCommand {

	public:

		virtual ~ModelUniformCommand();
		ModelUniformCommand();

		virtual void Action() override;


		void setMaterial(Material mat);
		void setTransform(Transform trans);

	private:

		Transform trans_;
		Material material_;

	};

}

#endif
