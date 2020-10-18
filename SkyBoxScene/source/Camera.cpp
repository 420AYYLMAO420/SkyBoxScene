#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) 
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
    Position = glm::vec3(posX, posY, posZ);
    WorldUp = glm::vec3(upX, upY, upZ);
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

void Camera::ProcessKeyboard(CameraDirection direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == CameraDirection::IN)
        Position += Front * velocity;
    if (direction == CameraDirection::OUT)
        Position -= Front * velocity;
    if (direction == CameraDirection::LEFT)
        Position -= Right * velocity;
    if (direction == CameraDirection::RIGHT)
        Position += Right * velocity;
    if (direction == CameraDirection::UP) //move up
        Position += Up * velocity;
    if (direction == CameraDirection::DOWN) //move down
        Position -= Up * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset,
    GLboolean constrainPitch)
{
    static float prevX = 0.f, prevY = 0.f;
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    if (prevY != yoffset)
        Pitch += yoffset;
    if (prevX != xoffset)
        Yaw += xoffset;

    prevX = xoffset;
    prevY = yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up = glm::normalize(glm::cross(Right, Front));
}