#pragma once
#include <map>
#include <graphics/shader.h>
#include <graphics/texture.h>

class ResourceManager {
public:
	static std::map<std::string, Shader> shaders;
	static std::map<std::string, Texture> textures;

	static Shader LoadShader(const char* vertex_path, const char* fragment_path, const char* geometry_path, const char* shader_name);
	static Shader GetShader(const char* shader_name);

	static Texture LoadTexture(const char* texture_path, const char* texture_name, bool flip_texture);
	static Texture GetTexture(const char* texture_name);
};