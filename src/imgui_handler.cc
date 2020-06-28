
#include <imgui_handler.h>

using namespace VC;

void ImGuiHandler::Init(Coordinator *cordinator)
{
  cordinator_ = cordinator;
}

void ImGuiHandler::HierarchyWindow(std::vector<u32> *entities)
{
  if (ImGui::Begin("Hierarchy"))
  {
    if (ImGui::TreeNode("Entities List"))
    {

      std::vector<u32> entitiesVec = *entities;

      u32 numOfEntities = entitiesVec.size();
      for (u32 n = 0; n < numOfEntities; n++)
      {
        Transform& trans = cordinator_->GetComponent<Transform>(n);
        u32 currentEntity = entitiesVec[n];
        //Name of entity, now using its id
        std::string item = std::to_string(currentEntity);
        if (ImGui::Selectable(item.c_str())) {
          selectedEntity_ = currentEntity;
          isAnyEntitySelected_ = true;
        }

        if (ImGui::IsItemActive() && !ImGui::IsItemHovered())
        {
          int n_next = n + (ImGui::GetMouseDragDelta(0).y < 0.f ? -1 : 1);
          if (n_next >= 0 && n_next < numOfEntities)
          {
            u32 thisIndexEntity = currentEntity;
            entitiesVec[n] = entitiesVec[n_next];
            entitiesVec[n_next] = thisIndexEntity;
            ImGui::ResetMouseDragDelta();
          }
        }
      }
      ImGui::TreePop();

      *entities = entitiesVec;

    }
    ImGui::End();

  }
}

void ImGuiHandler::InspectorWindow()
{

  if (ImGui::Begin("Inspector"))
  {

    if (isAnyEntitySelected_)
    {
      bool transform = true;
      ImGui::SetNextWindowSize(ImVec2(300.0f, 100.0f));
      if (ImGui::BeginChild("Transform"))
      {

        ImGui::Text("MAAAAAAAAAAAAAN\n");

        ImGui::EndChild();
      }

    }


    ImGui::End();

  }
}
