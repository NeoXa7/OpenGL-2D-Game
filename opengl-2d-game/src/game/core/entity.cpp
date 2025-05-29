#include "pch.h"
#include "entity.h"

Entity::Entity(const Texture& sprite_texture, glm::vec3 position, glm::vec3 size, glm::vec3 velocity, Color sprite_color) : Lifes(3), Rotation(0.0f), Destroyed(false) {
	this->SpriteTexture = sprite_texture;
	this->Position = position;
	this->Size = size;
	this->Velocity = velocity;
	this->SpriteColor = sprite_color;
}

void Entity::Render(SpriteRenderer& sprite) {
	sprite.RenderSprite(this->SpriteTexture, this->Position, this->Size, this->Rotation, this->SpriteColor);
}
