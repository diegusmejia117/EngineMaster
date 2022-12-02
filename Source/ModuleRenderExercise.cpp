#include "ModuleRenderExercise.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "SDL.h"
#include "GL/glew.h"
#include "ModuleProgram.h"


//#include <assimp/scene.h>

ModuleRenderExercise::ModuleRenderExercise()
{
}

ModuleRenderExercise::~ModuleRenderExercise()
{
}

bool ModuleRenderExercise::Start()
{
	
    vbo = CreateTriangleVBO();
    //vertex shader
    char* vertexSource = App->program->LoadShaderSource("Shaders/default_vertex.glsl");
    unsigned int vertexShader = App->program->CompileShader(GL_VERTEX_SHADER, vertexSource);

    //fragment shader
    char* fragment = App->program->LoadShaderSource("Shaders/default_fragment.glsl");
    unsigned int fragmentShader = App->program->CompileShader(GL_FRAGMENT_SHADER, fragment);


    program = App->program->CreateProgram(vertexShader, fragmentShader);

    m_model3D = Model::LoadFromFile("models/BakerHouse.fbx");


    return true;
}

update_status ModuleRenderExercise::PreUpdate()
{
    return UPDATE_CONTINUE;
}

update_status ModuleRenderExercise::Update()
{
    //App->program->RenderVBO(vbo, program);
    App->program->RenderTriangle(vbo,program);
    m_model3D->Draw();

    return UPDATE_CONTINUE;
}

update_status ModuleRenderExercise::PostUpdate()
{
    return UPDATE_CONTINUE;
}

bool ModuleRenderExercise::CleanUp()
{
    return false;
}

void ModuleRenderExercise::WindowResized(unsigned width, unsigned height)
{
}

unsigned ModuleRenderExercise::CreateTriangleVBO()
{
  
    float vtx_data[] = { 
                        -0.5f, -0.5f, 0.0f,
                         0.12f,-0.5f, 0.0f,
                        -0.5f, 0.5f, 0.0f,

                        -0.5f, 0.5f, 0.0f,
                        0.12f, -0.5f, 0.0f,
                        0.12f, 0.5f, 0.0f,
        

                        //TextCoords

                        0.0f, 0.0f,
                        1.0f, 0.0f,
                        0.0f, 1.0f,

                        0.0f, 1.0f,
                        1.0f, 0.0f,
                        1.0f, 1.0f

                         };

   
    unsigned vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
    glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);

    return vbo;
}

void ModuleRenderExercise::DestroyVBO(unsigned vbo)
{
    glDeleteBuffers(1, &vbo);
}

unsigned ModuleRenderExercise::GetProgram()
{
    return program;
}
