

#ifndef __WAVE_MOVEMENT_SYSTEM__
#define  __WAVE_MOVEMENT_SYSTEM__ 1

#include <system.h>
#include <memory>
#include <camera.h>
#include <cordinator.h>
#include <chrono>

namespace VC {

  class WaveMovementSystem : public System
  {
  public:
    void Init(Coordinator* cordinator);

    void Update(float time);

  private:
    Coordinator* cordinator_;
    u32 counter_;
    s32 directionModifier_;
  };

}

#endif
