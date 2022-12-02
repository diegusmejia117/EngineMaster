#pragma once
#include "Module.h"
#include "SDL.h"
#include "GL/glew.h"

#include "DirectXTex/DirectXTex.h"

class ModuleTexture :   public Module
{
public:
	ModuleTexture();
	~ModuleTexture();

	bool            Start();
	update_status   Update();
	bool            CleanUp();
	GLuint			GetTexture();

private:
	DirectX::ScratchImage* returnImage = new DirectX::ScratchImage;
	GLuint texture;
};

