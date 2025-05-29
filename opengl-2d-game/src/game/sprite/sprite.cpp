#include <pch.h>
#include "sprite.h"

SpriteRenderer::SpriteRenderer(const Shader& Sprite_Shader) : sprite_shader(Sprite_Shader) , VBO(0), VAO(0), EBO(0) {
	this->InitializeVertexData();
}

void SpriteRenderer::InitializeVertexData()
{
	float vertices[] = {
		// positions          	// texture coords			
		 0.5f,  0.5f, 0.0f,		1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f    // top left 
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void SpriteRenderer::RenderSprite(const Texture& texture, glm::vec3 position, glm::vec3 size, float rotation, Color sprite_color)
{
	this->sprite_shader.Use();

	glm::mat4 model_matrix = glm::mat4(1.0f);
	model_matrix = glm::translate(model_matrix, position);
	model_matrix = glm::translate(model_matrix, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
	model_matrix = glm::rotate(model_matrix, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	model_matrix = glm::scale(model_matrix, size);

	sprite_shader.SetMat4("model_matrix", model_matrix);
	sprite_shader.SetVec4("sprite_color", glm::vec4(sprite_color.x, sprite_color.y, sprite_color.z, sprite_color.w));

	texture.SetActive(GL_TEXTURE0);
	texture.Use();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void SpriteRenderer::Delete()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

