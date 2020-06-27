

#include <wavemovement_system.h>
#include <transform_component.h>
#include <math.h>

using namespace VC;

void WaveMovementSystem::Init(Coordinator* cordinator)
{
  cordinator_ = cordinator;
  directionModifier_ = 1;
  counter_ = 0;
}

void WaveMovementSystem::Update(float time)
{

  for (u32 entity : entities_)
  {

    Transform& trans = cordinator_->GetComponent<Transform>(entity);
    trans.position.y += sinf(time) * 0.2f;
    /*
    if (counter_ < 30)
    {
      trans.position.y += directionModifier_*0.5f;
      counter_++;
    }
    else {
      directionModifier_ *= -1;
      counter_ = 0;
    }
    */
    

  }

}
