#include "Application.h"
#include "ModuleEditor.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"



ModuleEditor::ModuleEditor()
{
}

ModuleEditor::~ModuleEditor()
{}

bool ModuleEditor::Init() {
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    /*io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
    io.ConfigWindowsMoveFromTitleBarOnly = true;

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        io.ConfigViewportsNoAutoMerge = false;
        io.ConfigViewportsNoTaskBarIcon = true;
    }

    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
        io.ConfigDockingTransparentPayload = true;
    }*/

    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
    ImGui_ImplOpenGL3_Init("#version 130");


    return true;
}

update_status ModuleEditor::PreUpdate() {


    return UPDATE_CONTINUE;
}


update_status ModuleEditor::Update() {

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(App->window->window);
    ImGui::NewFrame();

    ImGui::ShowDemoWindow(&show_demo_window);

    //ShowAboutWindow();
    showLogWindow();
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    SDL_GL_MakeCurrent(App->window->window, App->renderer->context);

    
    return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate() {


    return UPDATE_CONTINUE;
}

bool ModuleEditor::CleanUp() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    return true;
}


void ModuleEditor::AddTextToLog(char *const text) {
    textsLog.push_back(text);
}

void ModuleEditor::showLogWindow() {
    bool enabled;

    std::string windowName = std::string("Log");
    ImGui::SetNextWindowSize(ImVec2(400.0f, 200.0f), ImGuiCond_FirstUseEver);
    if (ImGui::Begin(windowName.c_str())) {
        ImGui::Text("LOG_ENGINE:                                                   ");
        ImGui::Separator();
        for (int i = 0; i < textsLog.size(); i++)
        {
            ImGui::Text(textsLog[i]);
        }
    }
    
    ImGui::End();
}

void ModuleEditor::ShowAboutWindow() {
    bool enabled;

    std::string windowName = std::string("About");
    if (ImGui::Begin(windowName.c_str(), &enabled, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Creative Engine");
        ImGui::Separator();
        ImGui::Text("This engine has been developed for the UPC Master in Advanced Programming for AAA Videogames");
        ImGui::Text("Author: Oriol Murcia Catalan");

        ImGui::Separator();

        ImVec2 sizeLibraries = ImVec2(0, ImGui::GetTextLineHeightWithSpacing() * 4);
        ImGui::BeginChildFrame(ImGui::GetID("libraries"), sizeLibraries);
        ImGui::Text("Library 1: ");
        ImGui::Text("Library 2: ");
        ImGui::EndChildFrame();

        ImGui::Separator();

        ImGui::Text("Engine License: UriM");

    }
    ImGui::End();
}