#include "Camera.h"

Camera::Camera() : 
	m_pos(glm::vec3(0.0f, 0.0f, 1.0f)),
	m_up(glm::vec3(0.0f, 1.0f, 0.0f)),
	m_front(glm::vec3(0.0f, 0.0f, -1.0f)),
	m_translation_speed(3.0f), m_rotation_speed(0.001f),
	m_pitch(0.0f), m_yaw(0.0f),
	m_fov(glm::quarter_pi<float>())
{}


glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(m_pos, m_pos + m_front, m_up);
}

glm::mat4 Camera::getProjMatrix() {
	return glm::perspective(m_fov, 1.33f, 0.1f, 100.0f);
}

void Camera::rotate(float delta_yaw, float delta_pitch) {
	m_yaw += delta_yaw * m_rotation_speed;
	m_pitch += delta_pitch * m_rotation_speed;

	constexpr float thresh = glm::half_pi<float>() * 0.98f;
	if (m_pitch > thresh)
		m_pitch = thresh;
	if (m_pitch < -thresh)
		m_pitch = -thresh;

	if (m_yaw > glm::pi<float>())
		m_yaw -= glm::two_pi<float>();
	if (m_yaw < glm::pi<float>())
		m_yaw += glm::two_pi<float>();

	m_front = glm::vec3(
		 glm::sin(m_yaw) * glm::cos(m_pitch),
		 glm::sin(m_pitch),
		-glm::cos(m_yaw) * glm::cos(m_pitch)
	);
}

void Camera::changeFov(float delta_fov) {
	constexpr float min_fov = glm::radians(1.0f);
	constexpr float max_fov = glm::radians(90.0f);
	m_fov += delta_fov * 0.01f;
	if (m_fov < min_fov)
		m_fov = min_fov;
	if (m_fov > max_fov)
		m_fov = max_fov;
}

void Camera::moveUp(float delta_time) {
	m_pos += m_up * m_translation_speed * delta_time;
}

void Camera::moveDown(float delta_time) {
	m_pos -= m_up * m_translation_speed * delta_time;
}

void Camera::moveRight(float delta_time) {
	m_pos += glm::normalize(glm::cross(m_front, m_up)) * m_translation_speed * delta_time;
}

void Camera::moveLeft(float delta_time) {
	m_pos -= glm::normalize(glm::cross(m_front, m_up)) * m_translation_speed * delta_time;
}

void Camera::moveForward(float delta_time) {
	m_pos += glm::normalize(m_front - glm::dot(m_front, m_up)) * m_translation_speed * delta_time;
}

void Camera::moveBackward(float delta_time) {
	m_pos -= glm::normalize(m_front - glm::dot(m_front, m_up)) * m_translation_speed * delta_time;
}