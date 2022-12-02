#include "ModuleProgram.h"
#include "Globals.h"
#include "ModuleDebugDraw.h"
#include "Application.h"
#include "ModuleCamera.h"
#include "ModuleTexture.h"


#include "GL/glew.h"
#include "Geometry/Frustum.h"
#include "Math/float3x3.h"
#include "Math/float3.h"
#include "DebugDraw.h"

using namespace std;

ModuleProgram::ModuleProgram()
{
}

ModuleProgram::~ModuleProgram()
{
}

bool ModuleProgram::Init()
{
	return true;
}

update_status ModuleProgram::Update()
{

	return UPDATE_CONTINUE;
}

bool ModuleProgram::CleanUp()
{
	return false;
}

char* ModuleProgram::LoadShaderSource(const char* shader_file_name)
{
	char* data = nullptr;
	FILE* file = nullptr;
	fopen_s(&file, shader_file_name, "rb");


	if (file)
	{
		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		data = (char*)malloc(size + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, size, file);
		data[size] = 0;
		fclose(file);
	}

	return data;
}

unsigned ModuleProgram::CompileShader(unsigned type, const char* source)
{
	unsigned shader_id = glCreateShader(type);
	glShaderSource(shader_id, 1, &source, 0);
	glCompileShader(shader_id);
	int res = GL_FALSE;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &res);
	if (res == GL_FALSE)
	{
		int len = 0;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &len);
		if (len > 0)
		{
			int written = 0;
			char* info = (char*)malloc(len);
			glGetShaderInfoLog(shader_id, len, &written, info);
		
			free(info);
		}
	}
	return shader_id;
}
unsigned ModuleProgram::CreateProgram(unsigned vtx_shader, unsigned frg_shader)
{
	unsigned program_id = glCreateProgram();
	glAttachShader(program_id, vtx_shader);
	glAttachShader(program_id, frg_shader);
	glLinkProgram(program_id);
	int res;
	glGetProgramiv(program_id, GL_LINK_STATUS, &res);
	if (res == GL_FALSE)
	{
		int len = 0;
		glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &len);
		if (len > 0)
		{
			int written = 0;
			char* info = (char*)malloc(len);
			glGetProgramInfoLog(program_id, len, &written, info);
		
			free(info);
		}
	}
	glDeleteShader(vtx_shader);
	glDeleteShader(frg_shader);
	return program_id;
}

void ModuleProgram::RenderVBO(unsigned vbo, unsigned program)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glUseProgram(program);


	// 1 triangle to draw = 3 vertices


	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void ModuleProgram::RenderTriangle(unsigned vbo, unsigned program)
{
	//Dibujar Quad Babuino

	proj = App->camera->GetFrustum()->ProjectionMatrix();

	view = App->camera->GetFrustum()->ViewMatrix();

	 /*model = float4x4::float4x4::FromTRS(float3(2.0f, 0.0f, 0.0f), float4x4::RotateZ(pi / 4.0f),float3(2.0f, 1.0f, 0.0f));

	 glUseProgram(program);

	 glUniformMatrix4fv(0, 1, GL_TRUE, &proj[0][0]);
	 glUniformMatrix4fv(1, 1, GL_TRUE, &view[0][0]);
	 glUniformMatrix4fv(2, 1, GL_TRUE, &model[0][0]);


	 glBindBuffer(GL_ARRAY_BUFFER, vbo);
	 glEnableVertexAttribArray(0);
	 glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	 glEnableVertexAttribArray(1);
	 glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 6 * 3));


	 glBindTexture(GL_TEXTURE_2D, App->texture->GetTexture());
	 glUniform1i(glGetUniformLocation(program, "mytexture"), 0);

	 glDrawArrays(GL_TRIANGLES, 0, 6);*/
	App->draw->Draw(view, proj, SCREEN_WIDTH, SCREEN_HEIGHT);
}
