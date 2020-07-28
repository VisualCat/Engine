
#include <imgui_handler.h>
#include <glm/gtx/matrix_decompose.hpp>
#include <parent_component.h>

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
      if (ImGui::CollapsingHeader("Transform", &transform))
      {
        Transform& trans = cordinator_->GetComponent<Transform>(selectedEntity_);
        
        Parent& parent = cordinator_->GetComponent<Parent>(selectedEntity_);

        glm::mat4 transformMatrix;

        glm::vec3 scale;
        glm::quat rotation;
        glm::vec3 translation;
        glm::vec3 skew;
        glm::vec4 perspective;

        if (parent.parent_entity == selectedEntity_)
        {
            transformMatrix = trans.transform;

            glm::decompose(transformMatrix, scale, rotation, translation, skew, perspective);
            rotation = glm::conjugate(rotation);

            glm::vec3 rotationInDegrees = glm::eulerAngles(rotation);
            rotationInDegrees *= 180.0f;
            rotationInDegrees /= 3.1416f;

            float pos[3] = { translation.x, translation.y, translation.z };
            float rot[3] = { rotationInDegrees.x, rotationInDegrees.y, rotationInDegrees.z };
            float sc[3] = { scale.x, scale.y, scale.z };

            ImGui::InputFloat3("Position", pos, 2);
            ImGui::InputFloat3("Rotation", rot, 0);
            ImGui::InputFloat3("Scale", sc, 2);

            translation = glm::vec3(pos[0], pos[1], pos[2]);
            scale = glm::vec3(sc[0], sc[1], sc[2]);


            transformMatrix = glm::mat4(1.0f);
            transformMatrix = glm::translate(transformMatrix, translation);
            transformMatrix = glm::rotate(transformMatrix, glm::radians(180.0f), glm::vec3(rot[0], rot[1], rot[2]));

            trans.transform = glm::scale(transformMatrix, scale);
        }
        else {
            transformMatrix = parent.relative_transform.transform;

            glm::decompose(transformMatrix, scale, rotation, translation, skew, perspective);
            rotation = glm::conjugate(rotation);

            glm::vec3 rotationInDegrees = glm::eulerAngles(rotation);
            rotationInDegrees *= 180.0f;
            rotationInDegrees /= 3.1416f;

            float pos[3] = { translation.x, translation.y, translation.z };
            float rot[3] = { rotationInDegrees.x, rotationInDegrees.y, rotationInDegrees.z };
            float sc[3] = { scale.x, scale.y, scale.z };

            ImGui::InputFloat3("Position", pos, 2);
            ImGui::InputFloat3("Rotation", rot, 0);
            ImGui::InputFloat3("Scale", sc, 2);

            translation = glm::vec3(pos[0], pos[1], pos[2]);
            scale = glm::vec3(sc[0], sc[1], sc[2]);


            transformMatrix = glm::mat4(1.0f);
            transformMatrix = glm::translate(transformMatrix, translation);
            //transformMatrix = glm::rotate(transformMatrix, glm::radians(180.0f), glm::vec3(rot[0], rot[1], rot[2]));

            parent.relative_transform.transform = glm::scale(transformMatrix, scale);
        }

        


      }

    }


    ImGui::End();

  }
}
