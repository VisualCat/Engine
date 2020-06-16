
#include <GLFW/glfw3.h>
#include <app.h>

using namespace VC;

void main() {
    
    App appInstance;

    appInstance.Init();
    appInstance.Loop();
    appInstance.End();

}
