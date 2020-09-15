 
#ifndef __IMGUI_HANDLER__
#define __IMGUI_HANDLER__ 1

#include <vector>
#include <string>
#include <platform_types.h>
#include <imgui.h>
#include <transform_component.h>
#include <cordinator.h>

namespace VC {

  class ImGuiHandler {

  public:

    void Init(Coordinator *cordinator);

    void HierarchyWindow(std::vector<u32> *entities);

    void InspectorWindow();

    void RenderWindow();

  private:

    void InitWindowInfo(ImVec2 windowPos, ImVec2 windowSize);

    Coordinator *cordinator_;
    u32 selectedEntity_ = 0;
    bool isAnyEntitySelected_ = false;
    u16 flags_ = 0;

  };

  

}
#endif // !__IMGUI_HANDLER__

