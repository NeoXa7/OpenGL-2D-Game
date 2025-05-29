#include <pch.h>
#define STB_IMAGE_IMPLEMENTATION

#include "texture.h"
#include <utils/logger.h>

Texture::Texture() : texture_id(0) {}

void Texture::Generate(const char* file_path, bool flip_texture)
{
	int x, y, nrChannels;

	stbi_set_flip_vertically_on_load(flip_texture);

	unsigned char* image_data = stbi_load(file_path, &x, &y, &nrChannels, NULL);
	if (!image_data) {
		LOGGER::Error("Texture", "Failed to load Image (PATH : ", file_path, ")");
	}

	glGenTextures(1, &this->texture_id);
	glBindTexture(GL_TEXTURE_2D, this->texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (image_data) {
		if (nrChannels == 1)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, x, y, 0, GL_RED, GL_UNSIGNED_BYTE, image_data);
		}
		else if (nrChannels == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data);
		}
		else if (nrChannels == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
		}

		glGenerateMipmap(GL_TEXTURE_2D);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image_data);
}

void Texture::Use() const
{
	glBindTexture(GL_TEXTURE_2D, this->texture_id);
}

void Texture::SetActive(GLenum gl_active_num) const
{
	glActiveTexture(gl_active_num);
}