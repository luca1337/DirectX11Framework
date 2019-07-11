#include "Camera.h"

#include "Graphics.h"
#include "Time.h"

Camera::Camera() : view(SimpleMath::Matrix()), projection(SimpleMath::Matrix())
{
	position = SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	rotation = SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	camera_speed = 30.0f;
	rotation_speed = 1.3f;
}

void Camera::SetCameraProjection(float fov, float aspect_ratio, float z_near, float z_far)
{
	projection = DirectX::XMMatrixPerspectiveFovLH(XMConvertToRadians(fov), aspect_ratio, z_near, z_far);
}

const SimpleMath::Matrix& Camera::GetViewMatrix() const
{
	return view;
}

const SimpleMath::Matrix& Camera::GetProjectionMatrix() const
{
	return projection;
}

void Camera::SetPosition(const SimpleMath::Vector3& pos)
{
	position = pos;
	UpdateCameraMatrix();
}

void Camera::SetPosition(float x, float y, float z)
{
	position = SimpleMath::Vector3(x, y, z);
	UpdateCameraMatrix();
}

void Camera::SetRotation(const SimpleMath::Vector3& rot)
{
	rotation = rot;
	UpdateCameraMatrix();
}

void Camera::SetRotation(float roll, float pitch, float yaw)
{
	rotation = SimpleMath::Vector3(roll, pitch, yaw);
	UpdateCameraMatrix();
}

void Camera::Translate(float x, float y, float z)
{
	position.x += x;
	position.y += y;
	position.z += z;
	UpdateCameraMatrix();
}

void Camera::Translate(const SimpleMath::Vector3& pos)
{
	position.x += pos.x;
	position.y += pos.y;
	position.z += pos.z;
	UpdateCameraMatrix();
}

void Camera::Rotate(float roll, float pitch, float yaw)
{
	rotation.x += roll;
	rotation.y += pitch;
	rotation.z += yaw;
	UpdateCameraMatrix();
}

void Camera::Rotate(const SimpleMath::Vector3& rot)
{
	rotation.x += rot.x;
	rotation.y += rot.y;
	rotation.z += rot.z;
	UpdateCameraMatrix();
}

void Camera::SetCameraSpeed(float value)
{
	this->camera_speed = value;
}

void Camera::SetCameraRotationSpeed(float value)
{
	this->rotation_speed = value;
}

void Camera::Update(const DirectX::Keyboard::State& state)
{
	if (state.IsKeyDown(DirectX::Keyboard::Keys::W))
		Translate(GetForwardVector() * camera_speed * Time::GetDeltaTime());

	if (state.S)
		Translate(GetBackwardVector() * camera_speed * Time::GetDeltaTime());

	if (state.A)
		Translate(GetLeftVector() * camera_speed * Time::GetDeltaTime());

	if (state.D)
		Translate(GetRightVector() * camera_speed * Time::GetDeltaTime());

	if (state.Right)
		Rotate(0.0f, rotation_speed * Time::GetDeltaTime(), 0.0f);

	if (state.Left)
		Rotate(0.0f, -rotation_speed * Time::GetDeltaTime(), 0.0f);

	if (state.Up)
		Rotate(-rotation_speed * Time::GetDeltaTime(), 0.0f, 0.0f);

	if (state.Down)
		Rotate(rotation_speed * Time::GetDeltaTime(), 0.0f, 0.0f);

	if (state.E)
		Translate(GetUpVector() * camera_speed * Time::GetDeltaTime());

	if (state.Q)
		Translate(GetDownVector() * camera_speed * Time::GetDeltaTime());
}

const SimpleMath::Vector3& Camera::GetPosition() const
{
	return position;
}

const SimpleMath::Vector3& Camera::GetRotation() const
{
	return rotation;
}

const SimpleMath::Vector3& Camera::GetForwardVector()
{
	return forward;
}

const SimpleMath::Vector3& Camera::GetUpVector()
{
	return up;
}

const SimpleMath::Vector3 & Camera::GetDownVector()
{
	return down;
}

const SimpleMath::Vector3& Camera::GetLeftVector()
{
	return left;
}

const SimpleMath::Vector3& Camera::GetRightVector()
{
	return right;
}

const SimpleMath::Vector3& Camera::GetBackwardVector()
{
	return backward;
}

void Camera::UpdateCameraMatrix()
{
	// get current camera rotation matrix
	DirectX::XMMATRIX camera_rotation = DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);

	DirectX::XMVECTOR camera_focus = DirectX::XMVector3TransformCoord(FORWARD_VECTOR, camera_rotation);

	DirectX::XMVECTOR new_cam_focus = DirectX::XMVectorAdd(camera_focus, position);

	DirectX::XMVECTOR direction_up = DirectX::XMVector3TransformCoord(UP_VECTOR, camera_rotation);

	view = DirectX::XMMatrixLookAtLH(position, new_cam_focus, direction_up);

	DirectX::XMMATRIX view_rotation = DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);

	this->up = DirectX::XMVector3TransformCoord(UP_VECTOR, view_rotation);
	this->down = DirectX::XMVector3TransformCoord(DOWN_VECTOR, view_rotation);
	this->forward = DirectX::XMVector3TransformCoord(FORWARD_VECTOR, view_rotation);
	this->left = DirectX::XMVector3TransformCoord(LEFT_VECTOR, view_rotation);
	this->right = DirectX::XMVector3TransformCoord(RIGHT_VECTOR, view_rotation);
	this->backward = DirectX::XMVector3TransformCoord(BACKWARD_VECTOR, view_rotation);
}