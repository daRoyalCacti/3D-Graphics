#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>


struct playerCamera {
	glm::vec3 Position = glm::vec3(1.0f, 2.0f, 0.0f);
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	float Yaw = 230.0f;
	float Pitch = -40.0f;
	float fov = 45.0f;
  float MovementSpeed = 1.0f; //is changed first frame but just to be safe
  float targetSpeed = 5.0f;
	float MouseSensitivity = 0.1f;
	glm::vec3 temp;

	inline void updateCameraVectors() {
		Front = glm::normalize(glm::vec3(
			cos(glm::radians(Yaw)) * cos(glm::radians(Pitch)),
			sin(glm::radians(Pitch)),
			sin(glm::radians(Yaw)) * cos(glm::radians(Pitch))
		) );

		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));
	}

	inline void processMouse(float xoff, float yoff) {
		xoff *= MouseSensitivity;
		yoff *= MouseSensitivity;

		Yaw += xoff;
		Pitch += yoff;

		if (Pitch > 89.9f) Pitch = 89.9f;
		if (Pitch < -89.9f) Pitch = -89.9f;
	}

	inline void move_forward(){
		temp = -glm::normalize(glm::cross(Right, WorldUp))*MovementSpeed;
		Position.x += temp.x;
		Position.z += temp.z;
	}

	inline void move_backward(){
		temp = -glm::normalize(glm::cross(Right, WorldUp))*MovementSpeed;
		Position.x -= temp.x;
		Position.z -= temp.z;
	}

	inline void move_left(){
		temp = Right * MovementSpeed;
		Position.x -= temp.x;
		Position.z -= temp.z;
	}

	inline void move_right() {
		temp = Right * MovementSpeed;
		Position.x += temp.x;
		Position.z += temp.z;
	}

	inline void move_up() {
		Position.y += MovementSpeed;
	}

	inline void move_down() {
		Position.y -= MovementSpeed;
	}

	inline glm::mat4 view(){
		return glm::lookAt(Position, Position + Front, Up);
	}

	inline glm::mat4 proj(float ratio){
		return glm::perspective(glm::radians(fov), ratio, 0.1f, 10.0f);
	}



};
