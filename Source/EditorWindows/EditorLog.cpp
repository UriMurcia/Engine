#include "EditorLog.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "ModuleEditor.h"


EditorLog::EditorLog()
{
}

void EditorLog::AddTextToLog(char* const text) {
    textsLog.push_back(text);
}

void EditorLog::ShowLogWindow() {
    bool enabled;

    std::string windowName = std::string("Log");
    ImGui::SetNextWindowSize(ImVec2(400.0f, 200.0f), ImGuiCond_FirstUseEver);
    if (ImGui::Begin(windowName.c_str(), &enabled, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::TextColored(App->editor->titleColor, "LOG_ENGINE:                                                   ");
        ImGui::Separator();

        for (int i = 0; i < textsLog.size(); i++)
        {
            ImGui::Text(textsLog[i].c_str());
        }

        if (ImGui::IsWindowFocused()) {
            App->editor->editorWindowsFocused = true;
        }
    }

    ImGui::End();
}