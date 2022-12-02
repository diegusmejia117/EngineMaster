#include "Globals.h"
#include "ModuleCamera.h"
#include "Application.h"
#include "GL/glew.h"
#include "Geometry/Frustum.h"
#include "Math/float3x3.h"
#include "Math/float3.h"
#include "SDL/include/SDL.h"


typedef unsigned __int8 Uint8;

ModuleCamera::ModuleCamera()
{
}

ModuleCamera::~ModuleCamera()
{
}

bool ModuleCamera::Start()
{
	
	frustum.SetKind(FrustumSpaceGL, FrustumRightHanded);


	float aspect = SCREEN_WIDTH / SCREEN_HEIGHT;
	frustum.SetViewPlaneDistances(0.1f, 100.0f);
	frustum.SetHorizontalFovAndAspectRatio(math::pi / 3.0f, aspect);
	frustum.SetFront(-vec::unitZ);
	frustum.SetUp(vec::unitY);
	SetPos(float3(1.0f, 1.0f, 10.0f));

	


	//LookAt(100, 0, 50);
	
	return true;
}

update_status ModuleCamera::Update()
{
	const Uint8* keyboard = SDL_GetKeyboardState(NULL);
	Uint32 SDL_GetMouseState(int* x, int* y);


	SDL_Event event;



		return UPDATE_CONTINUE;
	
}

bool ModuleCamera::CleanUp()
{
	return false;
}

void ModuleCamera::SetFOV(float degree, float aspectRadio)
{
	frustum.SetHorizontalFovAndAspectRatio(DegToRad(degree), aspectRadio);
}

void ModuleCamera::SetAspectRatio(float vFOV,float aspectRadio)
{
	frustum.SetVerticalFovAndAspectRatio(vFOV, aspectRadio);
}

void ModuleCamera::SetPlaneDistances(float nearPlaneDistance, float farPlaneDistance)
{
	frustum.SetViewPlaneDistances(nearPlaneDistance, farPlaneDistance);
}

void ModuleCamera::LookAt(float x, float y, float z)
{
	Frustum* frustum = GetFrustum();
	vec direction = vec(x, y, z) - frustum->Pos();
	direction.Normalize();
	vec up = vec::unitY;

	//Rotate(float3x3::LookAt(frustum->Front().Normalized(), direction, frustum->Up().Normalized(), up));
}


void ModuleCamera::SetPos(const vec& pos)
{
	frustum.SetPos(pos);
}

void ModuleCamera::SetUp(const vec& up)
{
	frustum.SetUp(up);
}

void ModuleCamera::SetFront(const vec& front)
{
	frustum.SetFront(front);
}

void ModuleCamera::Translate(const vec& tranlate)
{
	GetFrustum()->SetPos(GetFrustum()->Pos() + tranlate);
}

void ModuleCamera::SetOrientation(float3 i_ori)
{
	frustum.SetUp(i_ori);
}

void ModuleCamera::SetOrientation(float i_x, float i_y, float i_z)
{
	SetOrientation(float3(i_x, i_y, i_z));
}

void ModuleCamera::LookAt(float3 i_lookAt)
{
	frustum.SetFront(i_lookAt);
}

//void ModuleCamera::LookAt(float i_x, float i_y, float i_z)
//{
//	LookAt(float3(i_x, i_y, i_z));
//}

//void ModuleCamera::Rotate(const float3x3& rotationMatrix)
//{
//	Frustum* frustum = GetFrustum();
//	vec oldFront = frustum->Front().Normalized();
//	vec oldUp = frustum->Up().Normalized();
//	frustum->SetFront(rotationMatrix * oldFront);
//	frustum->SetUp(rotationMatrix * oldUp);
//}

void ModuleCamera::Rotate(float3 i_thetasRad)
{
	float3x3 rotationX = float3x3::RotateAxisAngle(frustum.WorldRight(), i_thetasRad.x);
	float3x3 rotationY = float3x3::RotateY(i_thetasRad.y);
	float3x3 rotationZ = float3x3::RotateAxisAngle(frustum.Front(), i_thetasRad.z);

	float3x3 rotationMat = rotationY * rotationX * rotationZ;

	float3 oldFront = frustum.Front().Normalized();
	LookAt(rotationMat.MulDir(oldFront));

	float3 oldUp = frustum.Up().Normalized();
	SetOrientation(rotationMat.MulDir(oldUp));
}




float4x4 ModuleCamera::GetProjectionMatrix()
{
	Frustum frustum;

	GetFrustum()->SetKind(FrustumSpaceGL, FrustumRightHanded);

	GetFrustum()->SetHorizontalFovAndAspectRatio(DegToRad(90.0f), 1.0f);
	GetFrustum()->SetViewPlaneDistances(0.1f, 100.0f);
	

	GetFrustum()->SetPos(float3(0.0f, 1.0f, -5.0f));
	GetFrustum()->SetFront(float3::unitZ);
	GetFrustum()->SetUp(float3::unitY);
	float4x4 projectionGL = frustum.ProjectionMatrix().Transposed(); 
	
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(*projectionGL.v);

	return projectionGL;
}

float4x4 ModuleCamera::GetViewMatrix()
{
	
	float3x3 rotationMatrix; 
	GetFrustum()->SetPos(float3::zero);
	GetFrustum()->SetFront(rotationMatrix.WorldX());
	GetFrustum()->SetUp(rotationMatrix.WorldY());
	
	float4x4 viewGL = float4x4(GetFrustum()->ViewMatrix()).Transposed();

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(*viewGL.v);

	return viewGL;
}

Frustum* ModuleCamera::GetFrustum()
{
	return &frustum;
}

void ModuleCamera::Focus() {

	float aspect = SCREEN_WIDTH / SCREEN_HEIGHT;
	frustum.SetViewPlaneDistances(0.1f, 100.0f);
	frustum.SetHorizontalFovAndAspectRatio(math::pi / 3.0f, aspect);
	frustum.SetFront(-vec::unitZ);
	frustum.SetUp(vec::unitY);
	SetPos(float3(1.0f, 1.0f, 10.0f));




	LookAt(0, 0, 0);
}

