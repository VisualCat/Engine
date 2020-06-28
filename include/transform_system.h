
#ifndef __TRANSFORM_SYSTEM__
#define  __TRANSFORM_SYSTEM__ 1

#include <system.h>
#include <memory>
#include <rendercommand.h>
#include <camera.h>
#include <cordinator.h>

namespace VC {


	class TransformSystem : public System
	{
	public:
		void Init(Coordinator* cordinator);

		void Update();

	private:
		Coordinator* cordinator_;
	};

}

#endif