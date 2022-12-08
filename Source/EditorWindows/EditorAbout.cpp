#include "EditorAbout.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "ModuleEditor.h"
#include "ModuleHardware.h"

#include <string>

EditorAbout::EditorAbout()
{
}

void EditorAbout::ShowAboutWindow() {

    std::string windowName = std::string("About");
    ImGui::SetNextWindowSize(ImVec2(400.0f, 200.0f), ImGuiCond_FirstUseEver);
    if (ImGui::Begin(windowName.c_str(), &aboutEnabled, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Creative Engine");
        ImGui::Separator();
        ImGui::Text("This engine has been developed for the UPC Master in Advanced Programming for AAA Videogames");
        ImGui::Text("Author: Oriol Murcia Catalan");

        ImGui::Separator();

        ImGui::TextColored(App->editor->titleColor, "Libraries:");
        ImVec2 sizeLibraries = ImVec2(0, ImGui::GetTextLineHeightWithSpacing() * 5);
        ImGui::BeginChildFrame(ImGui::GetID("libraries"), sizeLibraries);
        ImGui::Text("DirectXTex: %s", App->hardware->directXTexVersion);
        ImGui::Text("Assimp: %s", App->hardware->assimpVersion);
        ImGui::Text("glew: %s", App->hardware->glewVersion);
        ImGui::Text("MathGeoLib: %s", App->hardware->mathgeolibVersion);
        ImGui::Text("ImGui: %s", App->hardware->imguiVersion);
        ImGui::EndChildFrame();

        ImGui::Separator();

        ImGui::Text("Engine licensed under the MIT License.");


        if (ImGui::IsWindowFocused()) {
            App->editor->editorWindowsFocused = true;
        }
    }
    ImGui::End();
}