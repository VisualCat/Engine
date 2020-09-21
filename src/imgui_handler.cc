
#include <constraints.h>

#include <imgui_handler.h>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <parent_component.h>

using namespace VC;

void ImGuiHandler::Init(Coordinator *cordinator)
{
  cordinator_ = cordinator;
}

void ImGuiHandler::InitWindowInfo(ImVec2 windowPos, ImVec2 windowSize) {
  ImGui::SetNextWindowPos(windowPos);
  ImGui::SetNextWindowSize(windowSize);
  ImGui::SetNextWindowBgAlpha(1.0f);
  flags_ = (ImGuiWindowFlags_::ImGuiWindowFlags_NoResize || ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar);
}

void ImGuiHandler::HierarchyWindow(std::vector<u32> *entities)
{
  InitWindowInfo(ImVec2(0.0f, 0.0f), ImVec2(kWindowWidth * 1.5f / 8.0f, kWindowHeight * 3.0f / 4.0f));
  
  if (ImGui::Begin("Hierarchy", nullptr, flags_))
  {
    ImGui::Text("Hierarchy");
    ImGui::Separator();
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

  InitWindowInfo(ImVec2(kWindowWidth * 6.5f / 8.0f, 0.0f),
    ImVec2(kWindowWidth * 1.5f / 8.0f, kWindowHeight * 3.0f / 4.0f));

  if (ImGui::Begin("Inspector", nullptr, flags_))
  { 
    ImGui::Text("Inspector");
    ImGui::Separator();
    if (isAnyEntitySelected_)
    {

      bool transform = true;

      if (ImGui::CollapsingHeader("Transform", &transform))
      {
        Transform& trans = cordinator_->GetComponent<Transform>(selectedEntity_);
        
        Parent& parent = cordinator_->GetComponent<Parent>(selectedEntity_);

        glm::mat4 transformMatrix;

        glm::vec3 scale;
        glm::vec3 translation;
        glm::quat rotation;
        glm::vec3 skew;
        glm::vec4 perspective;

        if (parent.parent_entity == selectedEntity_)
        {
            transformMatrix = trans.transform;
        }
        else {
            transformMatrix = parent.relative_transform.transform;
        }

        glm::decompose(transformMatrix, scale, rotation, translation, skew, perspective);
        rotation = glm::conjugate(rotation);

        glm::vec3 rotationInDegrees = glm::eulerAngles(rotation);
        //rotationInDegrees *= 180.0f;
        //rotationInDegrees /= 3.1416f;

        float pos[3] = { translation.x, translation.y, translation.z };
        float rot[3] = { rotationInDegrees.x, rotationInDegrees.y, rotationInDegrees.z };
        float sc[3] = { scale.x, scale.y, scale.z };

        ImGui::InputFloat3("Position", pos, 2);
        ImGui::InputFloat3("Rotation", rot, 0);
        ImGui::InputFloat3("Scale", sc, 2);

        translation = glm::vec3(pos[0], pos[1], pos[2]);
        scale = glm::vec3(sc[0], sc[1], sc[2]);

        glm::mat4 scalar = glm::mat4(1.0f);
        scalar = glm::scale(scalar, scale);

        glm::mat4 rotator = glm::eulerAngleXYX(rot[0], rot[1], rot[2]);

        glm::mat4 translator = glm::mat4(1.0f);
        translator = glm::translate(translator, translation);

        if (parent.parent_entity == selectedEntity_)
        {
          trans.transform = translator * rotator * scalar;
        }
        else {
          parent.relative_transform.transform = translator * rotator * scalar;
        }
       

      }
    }
    ImGui::End();
  }
}

void RenderWindow() {

    

}

