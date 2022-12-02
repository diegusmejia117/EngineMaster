#pragma once
#include "Module.h"
#include "Math/float4x4.h"
class ModuleProgram :    public Module
{
public:

	ModuleProgram();
	~ModuleProgram();

	bool Init();
	update_status Update();
	bool CleanUp();
	char* LoadShaderSource(const char* shader_file_name);
	unsigned CompileShader(unsigned type, const char* source);
	unsigned CreateProgram(unsigned vtx_shader, unsigned frg_shader);
	void RenderVBO(unsigned vbo, unsigned program);
	void RenderTriangle(unsigned vbo, unsigned program);
	float4x4 model, view, proj;

private:
	unsigned program;
};

