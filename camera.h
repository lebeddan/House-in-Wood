//----------------------------------------------------------------------------------------
/**
 * \file    camera.h
 * \author  Lebedev Daniil
 * \date    2022
 * \brief   An abstract camera class that processes input data and calculates the corresponding Eulerian angles, vectors and matrices
 */
 //----------------------------------------------------------------------------------------


#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "glm/gtx/string_cast.hpp"
#include "data.h"

#include <vector>

using namespace std;
/// Class that holds info about a camera.
/*
  This class contains information about the camera..
*/
class Camera
{
public:
    glm::vec3 Position; ///<position vector of camera
    glm::vec3 Front;///<Front vector of camera contains data of view dir
    glm::vec3 Up;///<Up vector of camera
    glm::vec3 Right;///<Right vector of camera
    glm::vec3 WorldUp;//<WorldUp vector of camera
    
    float Yaw;///<Yaw euler angle of camera
    float Pitch;///<Pitch euler angle of camera

    float MovementSpeed;///<MovementSpeed number of camera
    float MouseSensitivity;///<MouseSensitivity number of camera
    float Zoom;///<Zoom number of camera

    /// Constructor
    /**
      Constructor used vectors

      \param[in] position start position of camera in scene.
      \param[in] up  camera start UP vector.
      \param[in] yaw  start yaw angle of camera.
      \param[in] pitch  start pitch angle of camera.
    */
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = upStartPos, float yaw = YAW, float pitch = PITCH);
   // Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);



    /// Matrix in LookAt form
    /**
      Function that return a simple LookAt() matrix
    */
    glm::mat4 GetViewMatrix();

    /// Increase/Decrease speed depends on direction  
    /**
      Function processing input data received from keyboard
  
      \param[in] direction to move camera.
      \param[in] deltaTime the interval in seconds from the last frame to the current one.
      \param[in] increaseSpeed flag to start move faster.
    */
    void ProcessKeyboard(Camera_Movement direction, float deltaTime, bool increaseSpeed);

    /// Move camera   
    /**
     Function processing input data received from the mouse 

      \param[in] xoffset offset to x axis.
      \param[in] yoffset offset to y axis.
      \param[in] constaintPitch flag to control pitch of camera.
    */
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
  
   /// Zoom camera   
   /**
     Function processing input data received from the mouse wheel 

     \param[in] yoffset offset to y axis.
   */
    void ProcessMouseScroll(float yoffset);

    /// Turn on static camera   
   /**
     Function change static cameras

     \param[in] NstaticView number of static view.
   */
    void updatePosition(int NstaticView);

   /// Collisions   
   /**
     Function check if camera does not go beyond the boundaries of the scene

     \param[in] newPos updated camera position.
   */
    bool checkCollision(glm::vec3 newPos);
 

private:
    /// Update camera vectors   
    /**
        Calculates the front vector from the Euler angles of the camera   
    */
    void updateCameraVectors();
};

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) 
{
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    Front = frontStartPos;
    MovementSpeed = SPEED;
    MouseSensitivity = SENSITIVITY;
    Zoom = ZOOM;
    updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime, bool increaseSpeed)
{
    float velocity;
    // If LEFT SHIFT was pressed, increase speed
    if (!increaseSpeed)
        velocity = MovementSpeed * deltaTime;
    else
        velocity = (shiftSpeed) * deltaTime;

    glm::vec3 newPos;
    if (direction == FORWARD)
    {
        newPos = Position + Front * velocity;
        if (checkCollision(newPos)) Position = newPos;
    }   
    if (direction == BACKWARD)
    {
        newPos = Position - Front * velocity;
        if (checkCollision(newPos)) Position = newPos;
    }
    if (direction == LEFT) 
    {
        newPos = Position - Right * velocity;
        if (checkCollision(newPos)) Position = newPos;
    }
    if (direction == RIGHT)
    {
        newPos = Position + Right * velocity;
        if (checkCollision(newPos)) Position = newPos;
    }
        
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // If users tries make wierd moves, set pitch to default values
    if (constrainPitch)
    {
        if (Pitch > maxPitch)
            Pitch = maxPitch;
        if (Pitch < minPitch)
            Pitch = minPitch;
    }

    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
    if (Zoom >= zoomMin && Zoom <= zoomMax)
        Zoom -= yoffset;
    if (Zoom <= zoomMin)
        Zoom = zoomMin;
    if (Zoom >= zoomMax)
        Zoom = zoomMax;
}

void Camera::updateCameraVectors()
{
    // Calculate new Front, Right, Up vectors
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));  
    Up = glm::normalize(glm::cross(Right, Front));
}

void Camera::updatePosition(int NstaticView)
{
    switch (NstaticView)
    {
        case 0: 
            Position = staticView1Outside;
            Pitch = staticPitch1;
            Yaw = staticYaw1;
            updateCameraVectors();
            break;
        case 1:
            Position = staticView2Outside;
            Pitch = staticPitch2;
            Yaw = staticYaw2;
            updateCameraVectors();
            break;
        case 2:
            Position = staticView3Inside;
            Pitch = staticPitch3;
            Yaw = staticYaw3;
            updateCameraVectors();
            break;
        case 3:
            Position = staticView4InsideKitchen;
            Pitch = staticPitch4;
            Yaw = staticYaw4;
            updateCameraVectors();
            break;
        default:
            break;
    }
}

bool Camera::checkCollision(glm::vec3 newPos)
{
    // Return true if camera tries exit from the boundaries of the scene
    if (newPos.x > sceneInfo.x || newPos.x < -sceneInfo.x) return false;

    if (newPos.y > sceneInfo.y || newPos.y < 0.0f) return false;

    if (newPos.z > sceneInfo.z || newPos.z < -sceneInfo.z) return false;

    return true;
}
#endif

