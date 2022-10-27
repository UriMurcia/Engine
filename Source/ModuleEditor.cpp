#include "Application.h"
#include "ModuleEditor.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"


ModuleEditor::ModuleEditor()
{}

ModuleEditor::~ModuleEditor()
{}

bool ModuleEditor::Init() {
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;


    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->getContext());
    ImGui_ImplOpenGL3_Init("#version 130");


    
    return true;
}

update_status ModuleEditor::Update() {
    //ImGui_ImplOpenGL3_NewFrame();
    //ImGui_ImplSDL2_NewFrame(App->window->window);
    //ImGui::NewFrame();

    //ImGui::Render();
    //ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


    return UPDATE_CONTINUE;
}


bool ModuleEditor::CleanUp() {
    return true;
}