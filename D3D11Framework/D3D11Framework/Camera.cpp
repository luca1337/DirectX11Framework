#include "Camera.h"

Camera::Camera() : view(SimpleMath::Matrix()), projection(SimpleMath::Matrix())
{
	position = SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	rotation = SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
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
	SimpleMath::Matrix camera_rotation = DirectX::XMMatrixRotationRollPitchYaw(rotation.y, rotation.z, rotation.x);

	SimpleMath::Vector3 camera_focus = SimpleMath::Vector3::Transform(FORWARD_VECTOR, camera_rotation);

	camera_focus += position;

	SimpleMath::Vector3 direction_up = SimpleMath::Vector3::Transform(UP_VECTOR, camera_rotation);

	view = XMMatrixLookAtLH(position, camera_focus, direction_up);

	SimpleMath::Matrix view_rotation = DirectX::XMMatrixRotationRollPitchYaw(rotation.y, rotation.z, rotation.x);

	this->up = SimpleMath::Vector3::Transform(UP_VECTOR, view_rotation);
	this->down = SimpleMath::Vector3::Transform(DOWN_VECTOR, view_rotation);
	this->forward = SimpleMath::Vector3::Transform(FORWARD_VECTOR, view_rotation);
	this->left = SimpleMath::Vector3::Transform(LEFT_VECTOR, view_rotation);
	this->right = SimpleMath::Vector3::Transform(RIGHT_VECTOR, view_rotation);
	this->backward = SimpleMath::Vector3::Transform(BACKWARD_VECTOR, view_rotation);
}