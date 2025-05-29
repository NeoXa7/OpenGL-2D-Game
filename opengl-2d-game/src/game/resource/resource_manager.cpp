#include <pch.h>
#include "resource_manager.h"
#include <utils/logger.h>

std::map<std::string, Shader> ResourceManager::shaders;
std::map<std::string, Texture> ResourceManager::textures;

Shader ResourceManager::LoadShader(const char* vertex_path, const char* fragment_path, const char* geometry_path, const char* shader_name)
{
	Shader tmp_shader;
	tmp_shader.Compile(vertex_path, fragment_path, geometry_path);

	shaders[shader_name] = tmp_shader;
	return shaders[shader_name];
}

Shader ResourceManager::GetShader(const char* shader_name)
{
	auto it = shaders.find(shader_name);
	if (it == shaders.end()) {
		LOGGER::Error("ResourceManager","Couldn't find shader (", shader_name, ")");
	}
	//else {
	//	LOGGER::Information("ResourceManager", "Found Shader (", shader_name, ")");
	//}

	return shaders[shader_name];
}

Texture ResourceManager::LoadTexture(const char* texture_path, const char* texture_name, bool flip_texture)
{
	Texture tmp_texture;
	tmp_texture.Generate(texture_path, flip_texture);

	textures[texture_name] = tmp_texture;
	return textures[texture_name];
}

Texture ResourceManager::GetTexture(const char* texture_name)
{
	auto it = textures.find(texture_name);
	if (it == textures.end()) {
		LOGGER::Error("ResourceManager", "Couldn't find Texture (", texture_name, ")");
	}
	//else {
	//	LOGGER::Information("ResourceManager", "Found Texture (", texture_name, ")");
	//}

	return textures[texture_name];
}
