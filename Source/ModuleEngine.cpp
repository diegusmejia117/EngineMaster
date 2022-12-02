#include "ModuleEngine.h"
#include "ModuleWindow.h"
#include "Application.h"
#include "ModuleRender.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "GL/glew.h"
#include <stdio.h>
#include <SDL.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif

ModuleEngine::ModuleEngine()
{
}

ModuleEngine::~ModuleEngine()
{
}

bool ModuleEngine::Init()
{
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_MakeCurrent(App->window->window, App->renderer->context);
	SDL_GL_SetSwapInterval(1); // Enable vsync
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();

	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
	io.ConfigWindowsMoveFromTitleBarOnly = true;

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		io.ConfigViewportsNoAutoMerge = false;
		io.ConfigViewportsNoTaskBarIcon = true;
	}

	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
		io.ConfigDockingTransparentPayload = true;
	}

	


	return true;
}

bool ModuleEngine::Start()
{
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
	ImGui_ImplOpenGL3_Init(GLSL_VERSION);
	
	ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(1.0f, 1.0f, 1.0f, 0.10f));
	ImGui::PushStyleColor(ImGuiCol_PlotHistogram, (ImVec4)ImColor(0.54f, 0.43f, 0.12f, 0.97f));


	return true;
}



update_status ModuleEngine::PreUpdate()
{
	bool show_demo_window = true;
	bool show_another_window = false;


	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		ImGui_ImplSDL2_ProcessEvent(&event);
		if (event.type == SDL_QUIT)
			return UPDATE_STOP;
		if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(App->window->window))
			return UPDATE_STOP;
	}


	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();

	

	return UPDATE_CONTINUE;
}

update_status ModuleEngine::Update()
{

	//ImGui::CaptureMouseFromApp(true);
	//ImGui::CaptureKeyboardFromApp(true);

	static float f = 0.0f;
	static int counter = 0;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	bool show_demo_window = true;
	static bool show_another_window = false;
	char gameobName[256] = "GameObject";
	float fps_log[] = { 0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f };

	
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			//ShowExampleMenuFile();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	//ImGui::ShowDemoWindow();

	if (ImGui::Begin(gameobName)) {

		

		ImGui::Checkbox("Enabled", &show_another_window);
		ImGui::SameLine();
		ImGui::InputText("Name", gameobName, 256);
		
		if(ImGui::BeginChild("Transform")) {


			ImGui::Text("Position");
			//ImGui::SameLine();
			//ImGui::InputFloat("X",0.0f*, 0.0f*);
			ImGui::Text("Rotation");
			ImGui::Text("Scale");
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			/*char title[50];
			sprintf_s(title, 50, "Framerate(Current) %.1f", fps_log[fps_log.size()-1]);
			ImGui::PlotHistogram("currentFrames", 60, title, 0.0f, 120.0f, ImVec2(310, 100));*/



			ImGui::EndChild;
		}
		/*ImGui::MenuItem("Test", "",true);
		ImGui::MenuItem("Test", "", false);
		ImGui::MenuItem("Test", "", false);*/
		
	
		//ImGui::PlotHistogram("FrameGraph", ImGui::GetIO().Framerate, 0, 0);
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color);
		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);
		
		ImGui::EndMenu();
	}

	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me")) {
			show_another_window = false;
		}
			
		ImGui::End();
	}



	return UPDATE_CONTINUE;
}

update_status ModuleEngine::PostUpdate()
{


	ImGuiIO& io = ImGui::GetIO(); (void)io;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glEnable(GL_DEPTH_TEST);

	

	ImGui::Render();
	
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();
	SDL_GL_MakeCurrent(App->window->window, App->renderer->context);

	return UPDATE_CONTINUE;
}


bool ModuleEngine::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	return false;
}
