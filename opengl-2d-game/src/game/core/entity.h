#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <game/sprite/sprite.h>
#include <utils/color.h>

class Entity {
public:
	Texture SpriteTexture;
	glm::vec3 Position, Size, Velocity;
	Color SpriteColor;

	int Lifes;
	float Rotation;
	bool Destroyed;

	Entity(const Texture& sprite_texture, glm::vec3 position, glm::vec3 size, glm::vec3 velocity, Color sprite_color = Color(255, 255, 255, 255));
	virtual void Render(SpriteRenderer& sprite);
};