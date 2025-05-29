#pragma once
#include <renderer/renderer.h>
#include <graphics/shader.h>
#include <graphics/texture.h>
#include <utils/logger.h>
#include <game/resource/resource_manager.h>
#include <game/core/entity.h>
#include <game/gui/gui.h>

#define SPRITE_SHADER "sprite_shader"

#define PROJECTION_MATRIX "projection_matrix"

#define BACKGROUND_TEXTURE "window_background_image"
#define PLAYER_ENTITY_TEXTURE "player_texture"
#define OBSTACLE_ENTITY_TEXTURE "obstacle_texture"
#define COLLISON_BOX_TEXTURE "box_texture"

enum State : int {
	ACTIVE,
	INACTIVE,
	MENU
};

class Game {
private:
	Renderer::OpenGL* m_Renderer;
	ISoundEngine* m_SoundEngine;
	State m_GameState;
	const char* m_Name;

private:
	int m_MenuKey = GLFW_KEY_HOME;
	bool m_MenuKeyLastPressed = false;

	int m_JumpKey = GLFW_KEY_SPACE;
	bool m_JumpKeyLastPressed = false;

	std::mt19937 rng;
	std::uniform_real_distribution<float> topHeightDist;
	std::uniform_real_distribution<float> bottomHeightDist;

private:
	Entity* m_Player;
	std::vector<Entity*> m_TopObstacles;
	std::vector<Entity*> m_BottomObstacles;
	SpriteRenderer* m_SpriteRenderer;

	float m_LastScoreTime = 0.0f;
	int m_LastScoreMilestone = 0;

	bool m_NightSky = false;

	int m_Score = 0;
	float m_Gravity = 9.807f * 150.0f;
	float m_ObstacleVelocity = 150.0f;
	float m_ObstacleSpacing = 200.0f;
	Color m_ObstacleColor = Color(255, 255, 255, 220);

	void RestartGame();
	bool CheckCollision(Entity& object_1, Entity& object_2);
	void PlayScoreSound(int milestone);

public: // Functions
	Game(const char* name);
	~Game();

	void Initialize();
	void ProcessInputs();

	void Update();
	void Render();

public: // Getters
	const char* GetName() {
		return this->m_Name;
	}

	State GetGameState() {
		return this->m_GameState;
	}

	int GetMenuKey() {
		return this->m_MenuKey;
	}

	float GetGravity() {
		return this->m_Gravity;
	}

public: // Setters
	void SetRenderer(Renderer::OpenGL* renderer) {
		this->m_Renderer = renderer;
	}

	void SetSoundEngine(ISoundEngine* sound_engine) {
		this->m_SoundEngine = sound_engine;
	}

	void SetGameState(State state) {
		m_GameState = state;
	}

	void SetName(const char* name) {
		this->m_Name = name;
	}

	void SetMenuKey(int key) {
		this->m_MenuKey = key;
	}

	float SetGravity(float val) {
		this->m_Gravity = val;
	}
};