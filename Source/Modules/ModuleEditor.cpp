#include "Application.h"
#include "ModuleEditor.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"

ModuleEditor::ModuleEditor()
{
}

ModuleEditor::~ModuleEditor()
{
    delete editorAbout;
    delete editorLog;
    delete editorProperties;
    delete editorConfiguration;
}

bool ModuleEditor::Init() {
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
    ImGui_ImplOpenGL3_Init("#version 130");


    return true;
}

update_status ModuleEditor::PreUpdate() {


    return UPDATE_CONTINUE;
}


update_status ModuleEditor::Update() {
    editorWindowsFocused = false;
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(App->window->window);
    ImGui::NewFrame();


    if (editorWindowsEnabled) {
        if (editorAbout->aboutEnabled)
            editorAbout->ShowAboutWindow();

        editorLog->ShowLogWindow();
        editorProperties->ShowPropertiesWindow();
        editorConfiguration->ShowConfigurationWindow();
    }
    ShowMenu();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    SDL_GL_MakeCurrent(App->window->window, App->renderer->context);

    if (quit) {
        return UPDATE_STOP;
    }
    else {
        return UPDATE_CONTINUE;
    }
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


void ModuleEditor::ShowMenu() {
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Options")) {
            if (ImGui::MenuItem("Quit")) {
                quit = true;
            }
            if (ImGui::MenuItem("Github")) {
                HWND handle = NULL;
                ShellExecute(handle, NULL, "https://github.com/UriMurcia/Engine", NULL, NULL, SW_SHOWNORMAL);
            }
            if (ImGui::MenuItem("About", NULL, &editorAbout->aboutEnabled)) {

            }
            if (ImGui::MenuItem("Editor Windows", NULL, &editorWindowsEnabled)) {

            }

            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}
