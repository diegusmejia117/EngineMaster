#pragma once
#include "Module.h"
#include "Globals.h"
#include "Math/float4x4.h"
#include "Model.h"

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;

class ModuleRenderExercise : public Module
{
public:
	ModuleRenderExercise();
	~ModuleRenderExercise();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void WindowResized(unsigned width, unsigned height);
	unsigned CreateTriangleVBO();
	void DestroyVBO(unsigned vbo);
	unsigned GetProgram();

private:
	unsigned vbo;
	unsigned program;
	Model* m_model3D;
};

