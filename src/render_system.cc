

#include <render_system.h>
#include <transform_component.h>
#include <render_component.h>

#include <buffer_rendercommand.h>
#include <material_rendercommand.h>
#include <draw_rendercommand.h>
#include <viewprojection_uniform_rendercommand.h>
#include <model_uniform_rendercommand.h>

using namespace VC;

void RenderSystem::Init(Coordinator* cordinator)
{
	cordinator_ = cordinator;
}

void RenderSystem::Update(std::vector<RenderCommand*> *commands, Camera* camera)
{
	for (u32 entity : entities_)
	{
		Transform trans = cordinator_->GetComponent<Transform>(entity);
		Render rend = cordinator_->GetComponent<Render>(entity);
		BufferCommand* bComand = new BufferCommand();
		bComand->setGeometry(rend.geo.ID);


		MaterialCommand* mComand = new MaterialCommand();
		mComand->setMaterial(rend.mat.ID);

		DrawCommand* dCommand = new DrawCommand();
		dCommand->setGeometry(rend.geo.ID);
		dCommand->setMaterial(rend.mat.ID);

		commands->push_back(bComand);
		commands->push_back(mComand);

		//Uniform condition
		//model
		ModelUniformCommand* muComand = new ModelUniformCommand();
		muComand->setMaterial(rend.mat);
		muComand->setTransform(trans);
		commands->push_back(muComand);
		//ViewProjection
		ViewProjectionUniformCommand* vpuCommand = new ViewProjectionUniformCommand();
		vpuCommand->setCamera(camera);
		vpuCommand->setMaterial(rend.mat);

		commands->push_back(vpuCommand);

		commands->push_back(dCommand);
	}
}
