#pragma once
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <utils/file/file_manager.h>
#include <libs/stb_image.h>

class Texture {
private:
	GLuint texture_id;

public:
	Texture();

	void Generate(const char* file_path, bool flip_texture);
	void Use() const ;
	void SetActive(GLenum gl_active_num) const ;

	GLuint GetTextureID() const {
		return this->texture_id;
	}
};