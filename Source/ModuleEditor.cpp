#include "ModuleEditor.h"
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

ModuleEditor::ModuleEditor()
{
}

ModuleEditor::~ModuleEditor()
{
}

bool ModuleEditor::Init()
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

	fpsHist = std::vector<float>(fpsCaptures);


	return true;
}

bool ModuleEditor::Start()
{
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
	ImGui_ImplOpenGL3_Init(GLSL_VERSION);

	ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(1.0f, 1.0f, 1.0f, 0.10f));
	ImGui::PushStyleColor(ImGuiCol_PlotHistogram, (ImVec4)ImColor(0.54f, 0.43f, 0.12f, 0.97f));


	return true;
}



update_status ModuleEditor::PreUpdate()
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

update_status ModuleEditor::Update()
{

	//ImGui::CaptureMouseFromApp(true);
	//ImGui::CaptureKeyboardFromApp(true);

	static float f = 0.0f;
	static int counter = 0;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	bool show_demo_window = true;
	static bool show_another_window = false;
	char gameobName[256] = "GameObject";

	float* ms_log = nullptr;
	float* fps_log = nullptr;
	float* stable_fps_log = nullptr;
	unsigned last_ms_log;
	int fps_offset;
	int stable_offset;


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

		ms_log = new float[60];
		fps_log = new float[60];
		stable_fps_log = new float[60];
		last_ms_log = SDL_GetTicks();
		fps_offset = 0;
		stable_offset = 0;

		//ms_log[fps_offset] = frame_timer.Read();
		/*if (ms_log[fps_offset] == 0) ms_log[fps_offset] = 1;
		fps_log[fps_offset] = 1000 / ms_log[fps_offset];*/
		//frame_timer.Start();

		/*if(stable_timer.Read() >= 500.0f)
		{
	
		stable_offset++;
		if (stable_offset > 59) stable_offset = 0;
		stable_fps_log[stable_offset] = 2.0f * stable_frame_counter;
		}*/
		

		if (ImGui::BeginChild("Transform")) {

			

			ImGui::Text("Position");
			//ImGui::SameLine();
			//ImGui::InputFloat("X",0.0f*, 0.0f*);
			ImGui::Text("Rotation");
			ImGui::Text("Scale");
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

			/*char title[50];
			sprintf_s(title, 50, "Framerate(Current) %.1f", fps_log[fps_offset]);
			ImGui::PlotHistogram("currentFrames", &fps_log[0], 60, fps_offset, title, 0.0f, 120.0f, ImVec2(310, 100));

			sprintf_s(title, 50, "Framerate(Current) %.1f", ms_log[fps_offset]);
			ImGui::PlotHistogram("currentFrames", &ms_log[0], 60, fps_offset, title, 0.0f, 120.0f, ImVec2(310, 100));*/

			
			ImGui::EndChild;
		}

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color);
		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::EndMenu();
	}

	if (ImGui::Begin("FPS")) {
		float maxFPS = App->GetFPS();
		ImGui::SliderFloat("Max FPS", &maxFPS, 0.f, 120.f, "%.1f", ImGuiSliderFlags_AlwaysClamp);
		App->SetFPS(maxFPS);

		int deltaTime = App->GetDeltaTime();
		fpsHist[currentIndex] = 1000.f / deltaTime;

		char title[50];
		sprintf_s(title, 50, "Framerate %.1f", fpsHist[currentIndex]);
		ImGui::PlotHistogram("##framerate", &fpsHist[0], fpsCaptures, 0, title, 0.0f, 120.f, ImVec2(310, 100));

		if (currentIndex < fpsCaptures - 1) {
			++currentIndex;
		}
		else {

			fpsHist.erase(fpsHist.begin());
			fpsHist.push_back(0);
		}
	}
	

	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me")) {
			show_another_window = false;
		}

		
	}


	ImGui::End();

	return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
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


bool ModuleEditor::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	return false;
}
