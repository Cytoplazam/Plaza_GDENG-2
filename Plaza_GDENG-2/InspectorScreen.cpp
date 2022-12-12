#include "InspectorScreen.h"

InspectorScreen::InspectorScreen() :AUIScreen("inspector")
{
}

InspectorScreen::~InspectorScreen()
{
}

void InspectorScreen::drawUI()
{
	ImGuiStyle& style = ImGui::GetStyle();

	if (ImGui::Begin("Inspector Window"))
	{
		if (GameObjectManager::get()->getSelectedObject() != nullptr)
		{
			string name = GameObjectManager::get()->getSelectedObject()->getName();
			Vector3D pos = GameObjectManager::get()->getSelectedObject()->getLocalPosition();
			Vector3D rot = GameObjectManager::get()->getSelectedObject()->getLocalRotation();
			Vector3D scale = GameObjectManager::get()->getSelectedObject()->getLocalScale();
			ImGui::Text(name.c_str());
			static char str0[128] = "";
			ImGui::InputTextWithHint("Object Name", name.c_str(), str0, IM_ARRAYSIZE(str0));
			if (ImGui::Button("Save Name"))
			{
				GameObjectManager::get()->getSelectedObject()->changeName(str0);
			}
			float vec3a[3] = { pos.m_x, pos.m_y, pos.m_z };
			ImGui::DragFloat3("Position", vec3a);
			GameObjectManager::get()->getSelectedObject()->setPos(vec3a[0], vec3a[1], vec3a[2]);
			float vec3b[3] = { rot.m_x, rot.m_y, rot.m_z };
			ImGui::DragFloat3("Rotation", vec3b);
			GameObjectManager::get()->getSelectedObject()->setRot(vec3b[0], vec3b[1], vec3b[2]);
			float vec3c[3] = { scale.m_x, scale.m_y, scale.m_z };
			ImGui::DragFloat3("Scale", vec3c);
			GameObjectManager::get()->getSelectedObject()->setScale(vec3c[0], vec3c[1], vec3c[2]);
			/*if (ImGui::Button("Delete Object"))
			{
				GameObjectManager::get()->delObject(GameObjectManager::get()->getSelectedObject());
				GameObjectManager::get()->setSelectedObject(NULL);
			}*/
			/*if (ImGui::Button("Attach Rigidody"))
			{
				GameObjectManager::get()->getSelectedObject()->ComputeLocalMatrix();
				GameObjectManager::get()->getSelectedObject()->attachComponent(new PhysicsComponent(("PhysicsComponent"), GameObjectManager::get()->getSelectedObject()));
			}*/
		}
	}

	ImGui::End();
}
