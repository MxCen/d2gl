#include "pch.h"
#include "texture.h"
#include "frame_buffer.h"

namespace d2gl {

uint32_t active_texture_slot = 0;
GLuint current_binded_texture[32] = { 0 };

Texture::Texture(const TextureCreateInfo& info)
	: m_width(info.size.x), m_height(info.size.y), m_layer_count(info.layer_count), m_format(info.format), m_internal_format(Texture::getInternalFormat(info.format)),
	  m_slot(info.slot), m_target(info.layer_count == 1 ? GL_TEXTURE_2D : GL_TEXTURE_2D_ARRAY), m_type(GL_UNSIGNED_BYTE), m_channel(info.format == GL_RED ? 1 : 4)
{
	glGenTextures(1, &m_id);
	bind();

	glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, info.min_filter);
	glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, info.mag_filter);
	glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	if (m_target == GL_TEXTURE_2D)
		glTexImage2D(m_target, 0, m_internal_format, m_width, m_height, 0, m_format, m_type, 0);
	else
		glTexImage3D(m_target, 0, m_internal_format, m_width, m_height, m_layer_count, 0, m_format, m_type, 0);

	if (info.min_filter != GL_LINEAR && info.mag_filter != GL_NEAREST)
		glGenerateMipmap(m_target);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_id);
}

void Texture::bind()
{
	if (active_texture_slot != m_slot) {
		glActiveTexture(GL_TEXTURE0 + m_slot);
		active_texture_slot = m_slot;
	}

	if (current_binded_texture[m_slot] == m_id)
		return;

	glBindTexture(m_target, m_id);
	current_binded_texture[m_slot] = m_id;
}

void Texture::fill(const uint8_t* pixels, uint32_t width, uint32_t height, uint32_t offset_x, uint32_t offset_y, uint32_t layer)
{
	bind();

	if (m_target == GL_TEXTURE_2D)
		glTexSubImage2D(m_target, 0, offset_x, offset_y, width, height, m_format, m_type, pixels);
	else
		glTexSubImage3D(m_target, 0, offset_x, offset_y, layer, width, height, 1, m_format, m_type, pixels);
}

void Texture::fillArray(const uint8_t* pixels, uint32_t div_x, uint32_t div_y)
{
	fill(pixels, m_width, m_height);
}

void Texture::fillFromBuffer(const std::unique_ptr<FrameBuffer>& fbo, uint32_t index)
{
	fbo->bind(false);
	glReadBuffer(GL_COLOR_ATTACHMENT0 + index);
	const auto width = fbo->getWidth();
	const auto height = fbo->getHeight();

	bind();
	glCopyTexSubImage2D(m_target, 0, (m_width - width) / 2, (m_height - height) / 2, 0, 0, width, height);
}

GLint Texture::getInternalFormat(GLenum format)
{
	switch (format) {
		case GL_RGBA: return GL_RGBA8;
		case GL_BGRA: return GL_RGBA8;
		case GL_RED: return GL_R8;
	}
	return GL_RGBA8;
}

}