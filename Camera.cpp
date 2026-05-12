#include "Camera.hpp"
#include <glew.h>
#include "Scene.hpp"

e_Camera::e_Camera(float CameraSpeed, float Sensitivity, float Fov, float Aspect, float Near, float Far) {
    fov = Fov;
    aspect = Aspect;
    nea = Near;
    fa = Far;
    this->CameraSpeed = CameraSpeed;
    this->Sensitivity = Sensitivity;
}

void e_Camera::Mouse_SetLookAt(float xposIn, float yposIn, float ScreenWidth, float ScreenHeight) {

    if (first) {
        lastX = ScreenWidth / 2;
        lastY = ScreenHeight / 2;
    }

    first = false;

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    xoffset *= 1 / Sensitivity;
    yoffset *= 1 / Sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    yawdir.x = cos(glm::radians(yaw));
    yawdir.y = sin(glm::radians(yaw));

    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction = glm::normalize(direction);
}

void e_Camera::Controller_HandleRightStick(float SensitivityX, float SensitivityY, float Xdegrees, float Ydegrees, float deadzone) {
    float x = Xdegrees;
    float y = Ydegrees;

    if ((x < deadzone and x > -deadzone)) {
        x = 0;
    }
    if (y < deadzone and y > -deadzone) {
        y = 0;
    }
    yaw += x * SensitivityX;
    pitch -= y * SensitivityY;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    yawdir.x = cos(glm::radians(yaw));
    yawdir.y = sin(glm::radians(yaw));

    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction = glm::normalize(direction);
}

void e_Camera::Controller_HandleLeftStick(float Xdegrees, float Ydegrees, float speed, float deadzone, float dt) {
    float x = Xdegrees;
    float y = Ydegrees;

    if ((x < deadzone and x > -deadzone)) {
        x = 0;
    }
    if (y < deadzone and y > -deadzone) {
        y = 0;
    }
    position.x -= speed * dt * y * yawdir.x;
    position.z -= speed * dt * y * yawdir.y;
    position += speed * dt * x * glm::normalize(glm::cross(direction, up));
}

void e_Camera::HandleMovement(bool Forward, bool Back, bool Left, bool Right, bool Up, bool Down, float DeltaTime){

    if (Forward) {
        position.x += CameraSpeed * DeltaTime * yawdir.x;
        position.z += CameraSpeed * DeltaTime * yawdir.y;
    }
    if (Back) {
        position.x -= CameraSpeed * DeltaTime * yawdir.x;
        position.z -= CameraSpeed * DeltaTime * yawdir.y;
    }
    if (Left) {
        position -= glm::normalize(glm::cross(direction, up)) * CameraSpeed * DeltaTime;
    }
    if (Right) {
        position += glm::normalize(glm::cross(direction, up)) * CameraSpeed * DeltaTime;
    }
    
    if (Up) {
        position.y += CameraSpeed * DeltaTime;
    }
    if (Down) {
        position.y -= CameraSpeed * DeltaTime;
    }
}