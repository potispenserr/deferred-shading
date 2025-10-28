#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera() {

}

Camera::Camera(Vector4D cameraPosition, Vector4D cameraTarget, Vector4D cameraFront, Vector4D cameraUp)
{
	camPos = cameraPosition;
	camTarget = cameraTarget;
	camFront = cameraFront;
	camUp = cameraUp;
}


Matrix4D& Camera::getPerspRef()
{
	return perspective;
}

Matrix4D Camera::getPersp()
{
	return perspective;
}

void Camera::setPersp(Matrix4D persp)
{
	perspective = persp;
}

Matrix4D& Camera::getViewRef()
{
	return view;
}

Matrix4D Camera::getView()
{
	return view;
}

void Camera::setView(Matrix4D newView)
{
	view = newView;
}


void Camera::setView()
{
	glm::vec3 cameraPosition;
	cameraPosition.x = camPos.x();
	cameraPosition.y = camPos.y();
	cameraPosition.z = camPos.z();

	Vector4D camComb = camPos + camFront;
	glm::vec3 posDir;
	posDir.x = camComb.x();
	posDir.y = camComb.y();
	posDir.z = camComb.z();

	glm::mat4 glmView = glm::lookAt(cameraPosition, posDir, glm::vec3(0.0f, 1.0f, 0.0f));

	view[0][0] = glmView[0][0];
	view[0][1] = glmView[0][1];
	view[0][2] = glmView[0][2];
	view[0][3] = glmView[0][3];

	view[1][0] = glmView[1][0];
	view[1][1] = glmView[1][1];
	view[1][2] = glmView[1][2];
	view[1][3] = glmView[1][3];

	view[2][0] = glmView[2][0];
	view[2][1] = glmView[2][1];
	view[2][2] = glmView[2][2];
	view[2][3] = glmView[2][3];

	view[3][0] = glmView[3][0];
	view[3][1] = glmView[3][1];
	view[3][2] = glmView[3][2];
	view[3][3] = glmView[3][3];

	//view = view.lookat(camPos, camPos + camFront, Vector4D(0.0f, 1.0f, 0.0f));
}

Vector4D Camera::getPosition()
{
	return camPos;
}

void Camera::setPosition(Vector4D position)
{
	camPos = position;
}

