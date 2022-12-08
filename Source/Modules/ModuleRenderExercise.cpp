#include "Globals.h"
#include "Application.h"
#include "ModuleRenderExercise.h"
#include "ModuleProgram.h"
#include "float3x3.h"
#include "ModuleCameraEditor.h"
#include "ModuleTexture.h"
#include "ModuleEditor.h"

#include <vector>


ModuleRenderExercise::ModuleRenderExercise()
{
}

// Destructor
ModuleRenderExercise::~ModuleRenderExercise()
{
    for (int i = 0; i < models3d.size(); i++) {
        delete models3d[i];
    }
}

bool ModuleRenderExercise::Init() {
    
    LoadModel3D("GameObjects/BakerHouse.fbx");

    return true;
}


update_status ModuleRenderExercise::Update() {

    for (int i = 0; i < models3d.size(); i++) {
        models3d[i]->Update();
    }
    
    return UPDATE_CONTINUE;
}

void ModuleRenderExercise::LoadModel3D(const char* file_name) {

    //For this assignment we only want 1 object to be in the scene
    if (models3d.size() == 1) {delete(models3d[0]);
        models3d.erase(models3d.begin());
    }
    Model* model3D = new Model();
    model3D->Load(file_name);
    models3d.push_back(model3D);

    //Change SetPropertiesWindow for selected Model3D when object selection is created
    App->editor->editorProperties->SetPropertiesWindow(std::move(*model3D));
}