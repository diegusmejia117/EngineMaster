#pragma once
#include "Module.h"
#include "Globals.h"
#include <vector>
#include <string>

typedef unsigned __int8 Uint8;

class ModuleEditor : public Module
{
public:

	ModuleEditor();
	~ModuleEditor();

	bool Init();
	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

private:

	int fpsCaptures = 120;
	int currentIndex = 0;
	std::vector<float> fpsHist;
	//std::string name;



};