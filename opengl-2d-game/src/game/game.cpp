#include <pch.h>
#include "game.h"


Game::Game(const char* name) : m_GameState(ACTIVE), m_Name(name), m_Renderer(nullptr), m_Player(nullptr), m_SpriteRenderer(nullptr), m_SoundEngine(nullptr) {}

Game::~Game() {
	delete m_Player;
	delete m_SpriteRenderer;

	for (Entity* bottom_obs : m_BottomObstacles) {
		delete bottom_obs;
	}
	m_BottomObstacles.clear();

	for (Entity* top_obs : m_TopObstacles) {
		delete top_obs;
	}
	m_TopObstacles.clear();
}

bool Game::CheckCollision(Entity& object_1, Entity& object_2)
{
	const float padding = 5.0f;

	glm::vec2 o1_min = glm::vec2(object_1.Position.x + padding, object_1.Position.y + padding);
	glm::vec2 o1_max = glm::vec2(object_1.Position.x + object_1.Size.x - padding, object_1.Position.y + object_1.Size.y - padding);

	glm::vec2 o2_min = glm::vec2(object_2.Position.x, object_2.Position.y);
	glm::vec2 o2_max = glm::vec2(object_2.Position.x + object_2.Size.x, object_2.Position.y + object_2.Size.y);

	bool collisionX = o1_max.x >= o2_min.x && o2_max.x >= o1_min.x;
	bool collisionY = o1_max.y >= o2_min.y && o2_max.y >= o1_min.y;

	/*sprite_renderer->RenderSprite(
		ResourceManager::GetTexture("box"),
		glm::vec3(o1_min.x, o1_min.y, 0.0f),
		glm::vec3(o1_max.x - o1_min.x, o1_max.y - o1_min.y, 0.0f),
		0.0f,
		Color(255, 0, 0, 255)
	);*/

	return collisionX && collisionY;
}

void Game::PlayScoreSound(int milestone) {
	if (m_LastScoreMilestone < milestone) {
		m_SoundEngine->play2D("assets/sounds/point.wav", false);
		m_LastScoreMilestone = milestone;
	}
}

void Game::RestartGame() {
	m_Player->Position.y = m_Renderer->GetHeight() / 2.0f;
	m_Player->Velocity = glm::vec3(0.0f);
	m_Player->Destroyed = false;

	m_Score = 0;

	// Reset top obstacles
	for (size_t i = 0; i < m_TopObstacles.size(); i++) {
		m_TopObstacles[i]->Velocity.x = -150.0f;
		m_TopObstacles[i]->Position.x = m_Renderer->GetWidth() + i * m_ObstacleSpacing;
		m_TopObstacles[i]->Position.y = 0.0f;

		float randomHeight = topHeightDist(rng);
		m_TopObstacles[i]->Size.y = randomHeight;

		m_TopObstacles[i]->Destroyed = (i == 4);
	}

	// Reset bottom obstacles
	for (size_t i = 0; i < m_BottomObstacles.size(); i++) {
		m_TopObstacles[i]->Velocity.x = -150.0f;
		float randomHeight = bottomHeightDist(rng);
		m_BottomObstacles[i]->Size.y = randomHeight;

		m_BottomObstacles[i]->Position.x = m_Renderer->GetWidth() + i * m_ObstacleSpacing;
		m_BottomObstacles[i]->Position.y = m_Renderer->GetHeight() - randomHeight;

		m_BottomObstacles[i]->Destroyed = (i == 4);
	}
}

void Game::Initialize() {
	// shaders
	ResourceManager::LoadShader("assets/shaders/sprite.vertex", "assets/shaders/sprite.frag", nullptr, SPRITE_SHADER);

	// textures
	ResourceManager::LoadTexture("assets/textures/sky.jpg", BACKGROUND_TEXTURE, false);
	ResourceManager::LoadTexture("assets/textures/player_entity.png", PLAYER_ENTITY_TEXTURE, false);
	ResourceManager::LoadTexture("assets/textures/pipe_1.png", OBSTACLE_ENTITY_TEXTURE, false);
	ResourceManager::LoadTexture("assets/textures/box.png", COLLISON_BOX_TEXTURE, false);

	m_SpriteRenderer = new SpriteRenderer(ResourceManager::GetShader(SPRITE_SHADER));

	// creating entities

	// player
	glm::vec3 player_entity_size = glm::vec3(50.0f, 50.0f, 0.0f);
	glm::vec3 player_entity_position = glm::vec3((m_Renderer->GetWidth() - player_entity_size.x) / 2.0f, (m_Renderer->GetHeight() - player_entity_size.y) / 2.0f, 0.0f);
	glm::vec3 player_entity_velocity = glm::vec3(4.0f, 0.0f, 0.0f);
	Color player_entity_color = Color(255, 255, 255, 255);
	m_Player = new Entity(ResourceManager::GetTexture(PLAYER_ENTITY_TEXTURE), player_entity_position, player_entity_size, player_entity_velocity, player_entity_color);

	// top obstacles
	for (size_t i = 0; i < 7; i++)
	{
		glm::vec3 top_obstacle_size = glm::vec3(52.0f, 150.0f, 0.0f);
		glm::vec3 top_obstacle_position = glm::vec3(m_Renderer->GetWidth() + i * m_ObstacleSpacing, 0.0f, 0.0f); // Top of screen
		glm::vec3 top_obstacle_velocity = glm::vec3(-this->m_ObstacleVelocity, 0.0f, 0.0f);
		Color top_obstacle_color = Color(m_ObstacleColor);

		Entity* temp_obstacle = new Entity(ResourceManager::GetTexture(OBSTACLE_ENTITY_TEXTURE), top_obstacle_position, top_obstacle_size, top_obstacle_velocity, top_obstacle_color);
		temp_obstacle->Rotation = 180.0f;
		m_TopObstacles.push_back(temp_obstacle);
	}

	// down obstacles
	for (size_t i = 0; i < 7; i++)
	{
		glm::vec3 bottom_obstacle_size = glm::vec3(52.0f, 150.0f, 0.0f);
		glm::vec3 bottom_obstacle_position = glm::vec3(m_Renderer->GetWidth() + i * m_ObstacleSpacing, m_Renderer->GetHeight() - bottom_obstacle_size.y, 0.0f);
		glm::vec3 bottom_obstacle_velocity = glm::vec3(-this->m_ObstacleVelocity, 0.0f, 0.0f);
		Color bottom_obstacle_color = Color(m_ObstacleColor);

		Entity* temp_obstacle = new Entity(ResourceManager::GetTexture(OBSTACLE_ENTITY_TEXTURE), bottom_obstacle_position, bottom_obstacle_size, bottom_obstacle_velocity, bottom_obstacle_color);
		m_BottomObstacles.push_back(temp_obstacle);
	}
}

void Game::ProcessInputs() {
	bool isMenuKeyPressed = m_Renderer->GetKey(this->m_MenuKey) == GLFW_PRESS;

	if (isMenuKeyPressed && !this->m_MenuKeyLastPressed) {
		if (m_GameState == ACTIVE) {
			m_GameState = MENU;
		}
		else {
			m_GameState = ACTIVE;
		}
	}

	this->m_MenuKeyLastPressed = isMenuKeyPressed;

	("Game Inputs"); {
		if (this->m_GameState == ACTIVE) {
			float velocity = (m_Player->Velocity.x * 100.0f) * m_Renderer->GetDeltaTime();

			if (m_Player->Position.x > m_Renderer->GetWidth() - m_Player->Size.x)
				m_Player->Position.x = m_Renderer->GetWidth() - m_Player->Size.x;

			if (m_Renderer->GetKey(GLFW_KEY_H) == GLFW_PRESS) {
				m_Player->Size += 2.0f;
			}

			bool isJumpKeyPressed = m_Renderer->GetKey(m_JumpKey) == GLFW_PRESS;

			if (isJumpKeyPressed && !this->m_JumpKeyLastPressed) {
				m_Player->Velocity.y = -350.0f;
			}

			this->m_JumpKeyLastPressed = isJumpKeyPressed;
		}
	}
}

void Game::Update()
{
	glm::mat4 projection_matrix = glm::ortho(0.0f, static_cast<float>(m_Renderer->GetWidth()), static_cast<float>(m_Renderer->GetHeight()), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader(SPRITE_SHADER).SetMat4(PROJECTION_MATRIX, projection_matrix);
	m_Renderer->UpdateFramebufferSize();

	if (this->m_Score == 5) {
		this->m_ObstacleVelocity = 200.0f;
		this->PlayScoreSound(5);
	}

	if (this->m_Score == 10) {
		this->m_ObstacleVelocity = 250.0f;
		this->PlayScoreSound(20);
	}
	
	if (this->m_Score == 20) {
		this->m_ObstacleVelocity = 300.0f;
		this->PlayScoreSound(30);
	}

	std::random_device rd;
	rng = std::mt19937(rd()); // seed with random device
	topHeightDist = std::uniform_real_distribution<float>(200.0f, 320.0f);
	bottomHeightDist = std::uniform_real_distribution<float>(100.0f, 200.0f);

	if (m_GameState == ACTIVE) {
		float current_time = m_Renderer->GetTime();

		if ((current_time > 0.5f) && current_time - this->m_LastScoreTime >= 1.0f) {
			this->m_Score += 1;
			this->m_LastScoreTime = current_time;
		}

		// gravity for the player entity (gravity lol)
		m_Player->Velocity.y += this->m_Gravity * m_Renderer->GetDeltaTime();
		m_Player->Position.y += m_Player->Velocity.y * m_Renderer->GetDeltaTime();
		m_Player->Rotation += m_Player->Velocity.y * m_Renderer->GetDeltaTime();

		if (m_Player->Position.y > m_Renderer->GetHeight() - m_Player->Size.y) {
			m_Player->Position.y = m_Renderer->GetHeight() - m_Player->Size.y;
			m_Player->Velocity.y = 0.0f;
			m_Player->Destroyed = true;
		}

		if (m_Player->Position.y < 0.0f) {
			m_Player->Position.y = 0.0f;
			m_Player->Velocity.y = 0.0f;
		}

		if (m_Player->Destroyed) {
			this->m_GameState = INACTIVE;
		}
	}
}

void Game::Render() {
	// background 
	m_SpriteRenderer->RenderSprite(
		ResourceManager::GetTexture(BACKGROUND_TEXTURE),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(m_Renderer->GetWidth(), m_Renderer->GetHeight(), 0.0f),
		0.0f, Color(255, 255, 255, 255)
	);

	if (m_GameState == INACTIVE) {
		ImGui::SetCursorPos(ImVec2((m_Renderer->GetWidth() - 150.0f) / 2.0f, (m_Renderer->GetHeight() - 50.0f) / 2.0f));
		if (gui::Button("Restart", 150.0f, 50.0f)) {
			this->m_GameState = ACTIVE;
			this->RestartGame();
		}
	}

	if (m_GameState == ACTIVE && !m_Player->Destroyed) {
		m_Player->Render(*m_SpriteRenderer);

		gui::text(("Score : " + std::to_string(this->m_Score)).c_str());
		gui::slider<float>("Gravity", &this->m_Gravity, 0.0f, 5000);
		gui::slider<float>("Obstacles Velocity", &this->m_ObstacleVelocity, 10.0f, 1000.0f);
		//gui::checkbox("NightSky", &this->m_NightSky);

		if (m_Renderer->GetTime() > 0.5f) { 
			// top obstacles physics
			for (Entity*& Obstacles : m_TopObstacles) {
				if (!Obstacles->Destroyed) {
					Obstacles->Velocity.x = -this->m_ObstacleVelocity;

					if (this->CheckCollision(*m_Player, *Obstacles)) {
						PlaySoundA("assets/sounds/hit.wav", NULL, SND_FILENAME | SND_ASYNC);
						m_Player->Destroyed = true;
					}

					Obstacles->Position.x += Obstacles->Velocity.x * m_Renderer->GetDeltaTime();

					if (Obstacles->Position.x + Obstacles->Size.x <= 0.0f) {
						Obstacles->Position.x = m_Renderer->GetWidth();

						float randomHeight = topHeightDist(rng);
						Obstacles->Size.y = randomHeight;
						Obstacles->Position.y = 0.0f;
					}

					if (!Obstacles->Destroyed)
						Obstacles->Render(*m_SpriteRenderer);
				}
			}

			// bottom obstacles physics
			for (Entity*& Obstacles : m_BottomObstacles) {
				if (!Obstacles->Destroyed) {
					Obstacles->Velocity.x = -this->m_ObstacleVelocity;

					if (this->CheckCollision(*m_Player, *Obstacles)) {
						PlaySoundA("assets/sounds/hit.wav", NULL, SND_FILENAME | SND_ASYNC);
						m_Player->Destroyed = true;
					}

					Obstacles->Position.x += Obstacles->Velocity.x * this->m_Renderer->GetDeltaTime();

					if (Obstacles->Position.x + Obstacles->Size.x <= 0.0f) {
						Obstacles->Position.x = m_Renderer->GetWidth();

						float randomHeight = bottomHeightDist(rng);
						Obstacles->Size.y = randomHeight;
						Obstacles->Position.y = m_Renderer->GetHeight() - randomHeight;
					}

					if (!Obstacles->Destroyed)
						Obstacles->Render(*m_SpriteRenderer);
				}
			}
		}
		
	}
}
