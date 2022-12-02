#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleRenderExercise;
class ModuleProgram;
class ModuleEngine;
class ModuleEditor;
class ModuleDebugDraw;
class ModuleCamera;
class ModuleTexture;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();

public:
	ModuleEditor* editor = nullptr;
	ModuleWindow* window = nullptr;
	ModuleRender* renderer = nullptr;
	ModuleInput* input = nullptr;
	ModuleProgram* program = nullptr;
	ModuleCamera* camera = nullptr;
	ModuleRenderExercise* renderer2 = nullptr;
	ModuleEngine* engine = nullptr;
	ModuleDebugDraw* draw = nullptr;
	ModuleTexture* texture = nullptr;

	int GetDeltaTime() {
		return m_deltaTime;
	}

	float GetFPS() {
		return m_framesPerSecond;
	}

	void SetFPS(float i_framesPerSecond) {
		m_framesPerSecond = i_framesPerSecond;
	}

private:

	std::list<Module*> modules;
	

	float m_framesPerSecond = 60.f;

	/*Timer* m_timer = nullptr;*/
	int m_prevTime = 0;
	int m_deltaTime = 0;


};

extern Application* App;
