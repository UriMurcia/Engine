#include "EditorConfiguration.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "ModuleEditor.h"
#include "ModuleHardware.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCameraEditor.h"
#include "ModuleWindow.h"


EditorConfiguration::EditorConfiguration()
{
}


void EditorConfiguration::ShowConfigurationWindow() {
    bool enabled;

    float dt = 1000.0f / (float)App->dt;

    if (fpsLog.size() == 100) {
        fpsLog.erase(fpsLog.begin());
    }

    fpsLog.push_back(floor(dt));


    std::string windowName = std::string("Configuration");
    ImGui::SetNextWindowSize(ImVec2(400.0f, 200.0f), ImGuiCond_FirstUseEver);

    if (ImGui::Begin(windowName.c_str(), &enabled, ImGuiWindowFlags_AlwaysAutoResize)) {
        if (ImGui::CollapsingHeader("FPS Graph"))
        {
            ImGui::PlotHistogram("##framerate", &fpsLog[0], fpsLog.size(), 0, "Framerate", 0.0f, 100.0f, ImVec2(310, 100));
        }


        if (ImGui::CollapsingHeader("Configuration"))
        {
            static ImGuiSliderFlags flags = ImGuiSliderFlags_None;


            ImGui::TextColored(App->editor->titleColor, "Window Display");

            static int selected = 1;
            if (ImGui::Selectable("Fullscreen", selected == 0)) {
                selected = 0;
                App->window->SetWindowFullScreen();
            }
            if (ImGui::Selectable("Resizable Screen", selected == 1)) {
                selected = 1;
                App->window->SetWindowResizable();
            }
            if (ImGui::Selectable("Borderless Screen", selected == 2)) {
                selected = 2;
                App->window->SetWindowBorderless();
            }

            ImGui::Separator();

            ImGui::TextColored(App->editor->titleColor, "Inputs");

            ImGui::SliderFloat("Camera Speed", &App->input->camMoveSpeed, 0.001f, 0.05f, "%.3f", flags);

            ImGui::Separator();

            ImGui::TextColored(App->editor->titleColor, "Camera");

            ImGui::SliderFloat("Horizontal Fov", &App->cameraEditor->FOV, 60.f, 120.f, "%.f", flags);
            App->cameraEditor->SetFOV(App->cameraEditor->FOV);

            static float farPlane = App->cameraEditor->frustum.FarPlaneDistance();
            ImGui::SliderFloat("View Distance", &farPlane, 10.f, 500.f, "%.f", flags);
            App->cameraEditor->SetPlaneDistances(0.1f, farPlane);

            ImGui::Separator();

            ImGui::TextColored(App->editor->titleColor, "Render");

            ImGui::Text("Background Color:");
            ImGui::ColorEdit3("MyColor##1", (float*)&App->renderer->backgroundColor, flags);

        }


        if (ImGui::CollapsingHeader("Information Output"))
        {
            ImGui::PlotHistogram("##framerate", &fpsLog[0], fpsLog.size(), 0, "Framerate", 0.0f, 100.0f, ImVec2(310, 100));
            ImGui::Text("SDL version: %s", App->hardware->sdlVersion);
            ImGui::Text("GLEW version: %s", App->hardware->glewVersion);

            ImGui::Separator();

            ImGui::Text("CPUs: %i (Cache: %i kb)", App->hardware->cpuCount, App->hardware->cacheLineSize);
            ImGui::Text("System RAM: %.1fGb", App->hardware->ram);

            ImGui::Separator();

            ImGui::Text("GPU Vendor: %s", App->hardware->gpuVendor);
            ImGui::Text("GPU Renderer: %s", App->hardware->gpuRenderer);
            ImGui::Text("GPU OpenGL Version: %s", App->hardware->gpuOpenglVersion);

            ImGui::Text("VRAM total: %.1f Mb", App->hardware->totalRam);
            ImGui::Text("VRAM used: %.1f Mb", App->hardware->ramUsed);
            ImGui::Text("VRAM Available: %.1f Mb", App->hardware->currentRamAvailabe);
        }

        if (ImGui::IsWindowFocused()) {
            App->editor->editorWindowsFocused = true;
        }
    }
    ImGui::End();
}