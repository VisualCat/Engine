#pragma once

#ifndef __RENDER_SYSTEM__
#define  __RENDER_SYSTEM__ 1

#include <system.h>
#include <memory>
#include <rendercommand.h>
#include <camera.h>
#include <cordinator.h>

using namespace VC;


class RenderSystem : public System
{
public:
	void Init(Coordinator* cordinator);

	void Update(std::vector<RenderCommand*> *commands, Camera* camera);

private:
	Coordinator* cordinator_;
};

#endif
