#include "Camera.h"

//Lookat -> Projection -> Viewport
Camera::Camera(float aspect) : _viewMatrix(1.0f), _eye(0.0f, 0.0f, 1.0f), _center(0.0f, 0.0f, 0.0f), _up(0.0f, 1.0f, 0.0f) {
	UpdateViewer();
	void UpdatePerspective(float _near, float _far, float _fov, float _aspectRatio);
	_aspectRatio = aspect;
}

void Camera::RepositionCamera(const glm::vec3& eye, const glm::vec3& center, const glm::vec3& up) {
	//Get new parameters
	_eye = eye;
	_center = center;
	_up = up;
	//Recenter - Use Lookat function
	UpdateViewer();
}

void Camera::UpdateViewer() {
	//constrcut the LookAt matrix
	/*
	//view_matrix paramteres
	glm::vec3 forward = glm::normalize(_center - _eye);
	glm::vec3 right = glm::normalize(glm::cross(forward, _up));
	glm::vec3 trueUp = glm::cross(right, forward);

	// Build the translation matrix
	glm::mat4 translation = glm::mat4(1.0f);
	translation[3][0] = -_eye.x;
	translation[3][1] = -_eye.y;
	translation[3][2] = -_eye.z;

	// Build the rotation matrix
	glm::mat4 rotation = glm::mat4(1.0f);
	rotation[0][0] = right.x;  rotation[1][0] = right.y;  rotation[2][0] = right.z;
	rotation[0][1] = trueUp.x; rotation[1][1] = trueUp.y; rotation[2][1] = trueUp.z;
	rotation[0][2] = -forward.x; rotation[1][2] = -forward.y; rotation[2][2] = -forward.z;

	_viewMatrix = rotation * translation;
	*/

	_viewMatrix = glm::lookAt(_eye, _center, _up);
}

void Camera::UpdatePerspective(float near, float far, float fov, float aspect){
	//
	float top = near * tan(fov / 2.0f);  // Top of the frustum
	float right = top * aspect;        // Right of the frustum

	_projectionMatrix[0][0] = near / right;  // Scale X
	_projectionMatrix[1][1] = near / top;  // Scale Y
	_projectionMatrix[2][2] = -(far + near) / (far - near);  // Scale Z
	_projectionMatrix[2][3] = -1.0f;  // Perspective divide
	_projectionMatrix[3][2] = -(2.0f * far * near) / (far - near);  // Translate Z

}