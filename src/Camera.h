#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera {
public:
	Camera();

	glm::mat4 getViewMatrix();
	glm::mat4 getProjMatrix();

	void moveUp(float delta_time);
	void moveDown(float delta_time);
	void moveLeft(float delta_time);
	void moveRight(float delta_time);
	void moveForward(float delta_time);
	void moveBackward(float delta_time);
	void rotate(float delta_yaw, float delta_pitch);
	void changeFov(float delta_fov);

	inline glm::vec3 getPosition() { return m_pos; }
	inline glm::vec3 getFront() { return m_front; }
	inline glm::vec3 getUp() { return m_up; }
	inline float getTranslationSpeed() { return m_translation_speed; }
	inline float getRotationSpeed() { return m_rotation_speed; }
	inline float getPitch() { return m_pitch; }
	inline float getYaw() { return m_yaw; }
	inline float getFov() { return m_fov; }

	inline void setPosition(glm::vec3 position) { m_pos = position; }
	inline void setTranslationSpeed(float speed) { m_translation_speed = speed; }
	inline void setRotationSpeed(float speed) { m_rotation_speed = speed; }

private:
	glm::vec3 m_pos, m_front, m_up;
	float m_translation_speed, m_rotation_speed;
	float m_pitch, m_yaw; // in radians
	float m_fov; // in radians
};