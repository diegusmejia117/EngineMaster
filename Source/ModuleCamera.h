#pragma once
#include "Module.h"
#include "Geometry/Frustum.h"

class ModuleCamera : public Module
{
public:
	ModuleCamera();
	~ModuleCamera();

	bool            Start();
	update_status   Update();
	bool            CleanUp();

	float4x4 GetProjection() {
		return frustum.ProjectionMatrix();
	}
	float4x4 GetView() {
		return frustum.ViewMatrix();
	}



	void SetFOV(float degree, float aspectRadio);
	void SetAspectRatio(float vFOV, float aspectRadio);
	void SetPlaneDistances(float nearPlaneDistance, float farPlaneDistance);
	void SetPos(const vec& pos);
	void SetUp(const vec& up);
	void SetFront(const vec& front);
	void Translate(const vec& tranlate);

	void Rotate(const float3x3& rotationMatrix);

	void LookAt(float x, float y, float z);
	void LookAt(float3 i_lookAt);
	void Focus();

	void SetOrientation(float3 i_ori);
	void SetOrientation(float i_x, float i_y, float i_z);

	float4x4 GetProjectionMatrix();
	float4x4 GetViewMatrix();
	Frustum* GetFrustum();
	

	void Rotate(float3 i_thetasRad);
	void Rotate(float i_thetaXRad, float i_thetaYRad, float i_thetaZRad);
private:
	Frustum frustum;
	float velocity = 0.4f;

};

