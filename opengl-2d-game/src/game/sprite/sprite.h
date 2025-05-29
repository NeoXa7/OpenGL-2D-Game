#pragma once
#include <GLFW/glfw3.h>
#include <graphics/shader.h>
#include <graphics/texture.h>
#include <utils/color.h>

class SpriteRenderer {
private:
	Shader sprite_shader;
	GLuint VBO, VAO, EBO;

public:
	SpriteRenderer(const Shader& Sprite_Shader);

	void InitializeVertexData();
	void RenderSprite(const Texture& texture, glm::vec3 position, glm::vec3 size = glm::vec3(10.0f, 10.0f, 0.0f), float rotation = 0.0f, Color sprite_color = Color(255, 255, 255, 255));
	void Delete();
};