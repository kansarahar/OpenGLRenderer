#include "Texture.h"
#include "GLErrorHandling.h"

#include <GL/glew.h>

#include <stb_image/stb_image.h>

Texture::Texture(const std::string& path)
	: m_texture_id(0), m_width(0), m_height(0), m_bits_per_pixel(0)
{
	stbi_set_flip_vertically_on_load(1);
	unsigned char* img_data = nullptr;
	img_data = stbi_load(path.c_str(), &m_width, &m_height, &m_bits_per_pixel, 4);

	// bind texture
	GLCALL(glGenTextures(1, &m_texture_id));
	GLCALL(glBindTexture(GL_TEXTURE_2D, m_texture_id));

	// set how to interpolate/extrapolate between pixel values
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	
	// set how to treat texture coords outside x:(0,1), y:(0,1)
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data));
	GLCALL(glBindTexture(GL_TEXTURE_2D, 0)); // unbind texture

	if (img_data)
		stbi_image_free(img_data);
}

Texture::~Texture() {
	glDeleteTextures(1, &m_texture_id);
}

void Texture::bind(unsigned slot /* = 0*/) const {
	GLCALL(glActiveTexture(GL_TEXTURE0 + slot));
	GLCALL(glBindTexture(GL_TEXTURE_2D, m_texture_id));
}

void Texture::unbind() const {
	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
}