#include "EditorProperties.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "ModuleEditor.h"


EditorProperties::EditorProperties()
{
}

EditorProperties::~EditorProperties()
{
    model3Dselected = new Model();
    delete model3Dselected;
    model3Dselected = NULL;
}

void EditorProperties::SetPropertiesWindow(Model&& model3D) {
    model3Dselected = new Model();
    delete model3Dselected;
    model3Dselected = &model3D;
}

void EditorProperties::ShowPropertiesWindow() {
    bool enabled;

    std::string windowName = std::string("Properties");
    ImGui::SetNextWindowSize(ImVec2(400.0f, 200.0f), ImGuiCond_FirstUseEver);
    if (ImGui::Begin(windowName.c_str(), &enabled, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::TextColored(App->editor->titleColor, "TRANSFORMATION");
        ImGui::Text("Position: x = %f; y = %f; z = %f", model3Dselected->position.x, model3Dselected->position.y, model3Dselected->position.z);
        ImGui::Text("Scale: %f", model3Dselected->scale);
        ImGui::Text("Rotation: x = %f; y = %f; z = %f", model3Dselected->rotation.x, model3Dselected->rotation.y, model3Dselected->rotation.z);

        ImGui::Separator();
        ImGui::TextColored(App->editor->titleColor, "GEOMETRY");
        ImGui::Text("Total Num Triangles: %i", model3Dselected->numTriangles);
        ImGui::Text("Total Num Vertices: %i", model3Dselected->numVertices);

        ImGui::Separator();

        for (int i = 0; i < model3Dselected->meshes.size(); i++) {
            ImGui::Text("Mesh %i:", (i + 1));
            ImGui::Text("Num Triangles: %i", model3Dselected->meshes[i]->numFaces);
            ImGui::Text("Num Vertices: %i", model3Dselected->meshes[i]->numVertices);
            ImGui::Separator();
        }

        ImGui::TextColored(App->editor->titleColor, "TEXTURE");
        ImGui::Text("Texture size: %iX%i", model3Dselected->meshes[0]->textureWidth, model3Dselected->meshes[0]->textureHeight);

        ImGui::Separator();

        if (ImGui::IsWindowFocused()) {
            App->editor->editorWindowsFocused = true;
        }
    }

    ImGui::End();
}