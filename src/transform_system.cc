
#include <transform_system.h>
#include <transform_component.h>
#include <parent_component.h>

using namespace VC;

void TransformSystem::Init(Coordinator* cordinator)
{
	cordinator_ = cordinator;
}

void TransformSystem::Update()
{
	for (u32 entity : entities_)
	{
		Transform& trans = cordinator_->GetComponent<Transform>(entity);
		Parent& parent = cordinator_->GetComponent<Parent>(entity);
		Transform& parentTransform = cordinator_->GetComponent<Transform>(parent.parent_entity);
		//Transform& relativeTrasnform = cordinator_->GetComponent<Transform>(parent.parent_entity);
		
		trans.transform = parentTransform.transform * parent.relative_transform.transform;
		/*
		trans.position = parentTransform.position + parent.relative_transform.position;
		trans.rotation = parentTransform.rotation * parent.relative_transform.rotation;
		trans.rotationFactor = parentTransform.rotationFactor + parent.relative_transform.rotationFactor;
		trans.scale = parentTransform.scale * parent.relative_transform.scale;
		*/


	}

}
