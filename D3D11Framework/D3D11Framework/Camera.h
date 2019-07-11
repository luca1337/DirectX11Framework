#pragma once

#include "Core.h"
#include <SimpleMath.h>
#include <Keyboard.h>

using namespace DirectX;

class Camera
{
public:
	Camera();
	void SetCameraProjection(float fov, float aspect_ratio, float z_near = 0.01f, float z_far = 1000.0f);

	const SimpleMath::Matrix& GetViewMatrix() const;
	const SimpleMath::Matrix& GetProjectionMatrix() const;

	void SetPosition(const SimpleMath::Vector3& pos);
	void SetPosition(float x, float y, float z);

	void SetRotation(const SimpleMath::Vector3& rot);
	void SetRotation(float roll, float pitch, float yaw);

	void Translate(float x, float y, float z);
	void Translate(const SimpleMath::Vector3& pos);

	void Rotate(float roll, float pitch, float yaw);
	void Rotate(const SimpleMath::Vector3& rot);

	void SetCameraSpeed(float value);
	void SetCameraRotationSpeed(float value);

	void Update(const DirectX::Keyboard::State& state);

	const SimpleMath::Vector3& GetPosition() const;
	const SimpleMath::Vector3& GetRotation() const;

	const SimpleMath::Vector3& GetForwardVector();
	const SimpleMath::Vector3& GetUpVector();
	const SimpleMath::Vector3& GetDownVector();
	const SimpleMath::Vector3& GetLeftVector();
	const SimpleMath::Vector3& GetRightVector();
	const SimpleMath::Vector3& GetBackwardVector();

private:

	void UpdateCameraMatrix();

	float camera_speed;
	float rotation_speed;

	// Camera Vectors
	SimpleMath::Vector3 position;
	SimpleMath::Vector3 rotation;

	// 3D Projection
	SimpleMath::Matrix view;
	SimpleMath::Matrix projection;

	const DirectX::XMVECTOR UP_VECTOR = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	const DirectX::XMVECTOR DOWN_VECTOR = DirectX::XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f);
	const DirectX::XMVECTOR FORWARD_VECTOR = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	const DirectX::XMVECTOR LEFT_VECTOR = DirectX::XMVectorSet(-1.0f, 0.0f, 0.0f, 0.0f);
	const DirectX::XMVECTOR RIGHT_VECTOR = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	const DirectX::XMVECTOR BACKWARD_VECTOR = DirectX::XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f);

	SimpleMath::Vector3 up;
	SimpleMath::Vector3 down;
	SimpleMath::Vector3 left;
	SimpleMath::Vector3 right;
	SimpleMath::Vector3 forward;
	SimpleMath::Vector3 backward;
};