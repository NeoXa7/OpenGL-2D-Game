#pragma once
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <utils/file/file_manager.h>

class Shader {
private:
	GLuint shader_id;
public:
	Shader();
	~Shader() {}

	void Compile(const char* vertex_path, const char* fragment_path, const char* geometry_path);

	GLuint GetShaderId() {
		return this->shader_id;
	}

	void Use();
	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;
	void SetMat4(const std::string& name, glm::mat4 value) const;
	void SetMat3(const std::string& name, glm::mat3 value) const;
	void SetVec3(const std::string& name, glm::vec3 value) const;
	void SetVec4(const std::string& name, glm::vec4 value) const;
};