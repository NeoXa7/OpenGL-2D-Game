#include <pch.h>
#include "shader.h"
#include <utils/logger.h>

Shader::Shader() {}

void Shader::Compile(const char* vertex_path, const char* fragment_path, const char* geometry_path)
{
	std::string vShaderFile = FileManager::ReadFile(vertex_path);
	std::string fShaderFile = FileManager::ReadFile(fragment_path);
	std::string gShaderFile{};

	const char* vShaderCode = vShaderFile.c_str();
	const char* fShaderCode = fShaderFile.c_str();
	const char* gShaderCode = nullptr;

	if (geometry_path != nullptr) {
		gShaderFile = FileManager::ReadFile(geometry_path);
		gShaderCode = gShaderFile.c_str();
	}

	//std::cout << std::endl;
	//std::cout << "Vertex Shader : \n\n" << vShaderCode << '\n';
	//std::cout << std::endl;
	//std::cout << "Fragment Shader : \n\n" << fShaderCode << '\n';
	//std::cout << std::endl;
	//std::cout << std::endl;

	// vertex shader
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vShaderCode, NULL);
	glCompileShader(vertex_shader);

	int vShaderSuccess;
	char vShaderInfoLogs[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &vShaderSuccess);
	if (!vShaderSuccess)
	{
		glGetShaderInfoLog(vertex_shader, sizeof(vShaderInfoLogs), NULL, vShaderInfoLogs);
		LOGGER::Error("Shader", "Vertex Shader Compilation Failed (Path : ", vertex_path, ")");
		std::cout << "Logs : " << vShaderInfoLogs << '\n';
	}
	else if (vShaderSuccess)
	{
		LOGGER::Information("Shader", "Vertex Shader Compiled (Path : ", vertex_path, ")");
	}

	// fragment shader
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fShaderCode, NULL);
	glCompileShader(fragment_shader);

	int fShaderSuccess;
	char fShaderInfoLogs[512];
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &fShaderSuccess);
	if (!fShaderSuccess)
	{
		glGetShaderInfoLog(fragment_shader, sizeof(fShaderInfoLogs), NULL, fShaderInfoLogs);
		LOGGER::Error("Shader", "Fragment Shader Compilation Failed (Path : ", fragment_path, ")");
		std::cout << "Logs : " << fShaderInfoLogs << '\n';
	}
	else if (fShaderSuccess)
	{
		LOGGER::Information("Shader", "Fragment Shader Compiled (Path : ", fragment_path, ")");
	}

	// geomtry shader
	GLuint geometry_shader = 0;
	if (gShaderCode != nullptr) {
		geometry_shader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometry_shader, 1, &gShaderCode, NULL);
		glCompileShader(geometry_shader);

		int gShaderSuccess;
		char gShaderInfoLogs[512];
		glGetShaderiv(geometry_shader, GL_COMPILE_STATUS, &gShaderSuccess);
		if (!gShaderSuccess)
		{
			glGetShaderInfoLog(geometry_shader, sizeof(gShaderInfoLogs), NULL, gShaderInfoLogs);
			LOGGER::Error("Shader", "Geometry Shader Compilation Failed (Path : ", geometry_path, ")");
			std::cout << "Logs : " << gShaderInfoLogs << '\n';
		}
		else if (gShaderSuccess)
		{
			LOGGER::Information("Shader", "Geometry Shader Compiled (Path : ", geometry_path, ")");
		}
	}

	this->shader_id = glCreateProgram();
	glAttachShader(this->shader_id, vertex_shader);
	glAttachShader(this->shader_id, fragment_shader);

	if (gShaderCode != nullptr) {
		glAttachShader(this->shader_id, geometry_shader);
	}

	glLinkProgram(this->shader_id);

	int vfShaderProgramSuccess;
	char vfShaderProgramInfoLogs[512];
	glGetProgramiv(this->shader_id, GL_LINK_STATUS, &vfShaderProgramSuccess);
	if (!vfShaderProgramSuccess)
	{
		glGetProgramInfoLog(this->shader_id, sizeof(vfShaderProgramInfoLogs), NULL, vfShaderProgramInfoLogs);
		LOGGER::Error("Shader", "Linking Shader Program ID Failed");
		std::cout << "Logs : " << vfShaderProgramInfoLogs << '\n';
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	if (gShaderCode != nullptr) {
		glDeleteShader(geometry_shader);
	}
	std::cout << std::endl;
}

void Shader::Use()
{
	glUseProgram(this->shader_id);
}

void Shader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(this->shader_id, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(this->shader_id, name.c_str()), value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(this->shader_id, name.c_str()), value);
}

void Shader::SetMat4(const std::string& name, glm::mat4 value) const
{
	glUniformMatrix4fv(glGetUniformLocation(this->shader_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetMat3(const std::string& name, glm::mat3 value) const
{
	glUniformMatrix3fv(glGetUniformLocation(this->shader_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetVec3(const std::string& name, glm::vec3 value) const
{
	glUniform3f(glGetUniformLocation(this->shader_id, name.c_str()), value.x, value.y, value.z);
}

void Shader::SetVec4(const std::string& name, glm::vec4 value) const
{
	glUniform4f(glGetUniformLocation(this->shader_id, name.c_str()), value.x, value.y, value.z, value.w);
}
