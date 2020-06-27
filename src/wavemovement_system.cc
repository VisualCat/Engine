

#include <wavemovement_system.h>
#include <transform_component.h>

using namespace VC;

void WaveMovementSystem::Init(Coordinator * cordinator)
{
  cordinator_ = cordinator;
  directionModifier_ = 1;
  counter_ = 0;
}

void WaveMovementSystem::Update()
{

  for (u32 entity : entities_)
  {
    Transform trans = cordinator_->GetComponent<Transform>(entity);

    if (counter_ < 30)
    {
      trans.position.y += directionModifier_;
      counter_++;
    }
    else {
      directionModifier_ *= -1;
      counter_ = 0;
    }
    

  }

}
