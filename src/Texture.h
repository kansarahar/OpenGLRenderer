#pragma once

#include <string>

class Texture {
public:
	Texture(const std::string& path);
	Texture(const Texture& other) = delete;
	Texture& operator=(Texture& other) = delete;
	~Texture();

	void bind(unsigned slot = 0) const;
	void unbind() const;

	inline int getWidth() { return m_width; }
	inline int getHeight() { return m_height; }

private:
	unsigned m_texture_id;
	int m_width, m_height, m_bits_per_pixel;
};