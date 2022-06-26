#pragma once

class IndexBuffer {
private:
	unsigned m_index_buffer_id;
	unsigned m_count;
public:
	IndexBuffer(const unsigned* data, unsigned count);
	IndexBuffer(const IndexBuffer& other);
	IndexBuffer& operator=(const IndexBuffer& other);
	~IndexBuffer();

	void bind() const;
	void unbind() const;

	inline unsigned getCount() const { return m_count; }
};