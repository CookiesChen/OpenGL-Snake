#include "Game.h"
#include "SpriteRender.h"
#include "ResourceManager.h"
#include "Shader.h"

SpriteRender *Renderer;
Model *table;
Model *ball;

Game::Game(GLuint width, GLuint height)
	: State(GAME_ACTIVE), Keys()
{
	this->Width = width;
	this->Height = height;
	this->camera = Camera();
	this->camera.setPosition(glm::vec3(0.0f, 70.0f, 40.0f));
	this->camera.setPitch(-60.0f);

	count = 0;
	total = 60;
	press_key = 3;
	State = GAME_ACTIVE;
	momentum = 2.5f;

	srand((unsigned)time(NULL));
}

Game::~Game()
{

}

void Game::Init()
{
	// 加载着色器
	ResourceManager::LoadShader("model.vs", "model.fs", nullptr, "sprite");

	// 加载游戏对象
	ResourceManager::LoadGameObject("model/chicken/Mesh_Hen.obj", "snake");
	// 初始化游戏对象数据
	ResourceManager::GetGameObject("snake").headZoom = 0.04f;
	ResourceManager::GetGameObject("snake").bodyZoom = 0.03f;
	ResourceManager::GetGameObject("snake").body[0].z = press_key;

	// Configure shaders
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = this->camera.GetViewMatrix();
	projection = glm::perspective(glm::radians(45.0f), (float)Width /(float)Height, 0.1f, 100.0f);
	//projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);

	ResourceManager::GetShader("sprite").Use().SetMatrix4("view", view);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	ResourceManager::GetShader("sprite").SetVector3f("viewPos", this->camera.getPostion());

	Renderer = new SpriteRender(ResourceManager::GetShader("sprite"));
	table = new Model("model/table/BasketBallCourt.obj");
	ball = new Model("model/food/basketball.obj");

	getFood();
}

void Game::ProcessInput(GLfloat dt)
{
	GLint direction = ResourceManager::GetGameObject("snake").body[0].z;
	if (this->Keys[GLFW_KEY_A] && (direction == 0 || direction == 2))
	{
		press_key = 1;
	}
	else if (this->Keys[GLFW_KEY_D] && (direction == 0 || direction == 2))
	{
		press_key = 3;
	}
	else if (this->Keys[GLFW_KEY_W] && (direction == 1 || direction == 3))
	{
		press_key = 0;
	}
	else if (this->Keys[GLFW_KEY_S] && (direction == 1 || direction == 3))
	{
		press_key = 2;
	}
}

void Game::Update(GLfloat dt)
{
	// 降频插值
	count++;
	if (count >= 60 && State == GAME_ACTIVE) {
		ResourceManager::GetGameObject("snake").update();
		ResourceManager::GetGameObject("snake").body[0].z = press_key;
		count = 0;
		float x = ResourceManager::GetGameObject("snake").body[0].x,
			y = ResourceManager::GetGameObject("snake").body[0].y;
		int direction = (int)ResourceManager::GetGameObject("snake").body[0].z;
		for (int i = 1, len = ResourceManager::GetGameObject("snake").body.size(); i < len; i++) {
			float bx = ResourceManager::GetGameObject("snake").body[i].x;
			float by = ResourceManager::GetGameObject("snake").body[i].y;
			if ((x - bx)* (x - bx)+ (y - by)* (y - by) < 1.0f) {
				State = GAME_MENU;
				break;
			}
		}
	}
	this->DoCollisions();
	if (State == GAME_ACTIVE) {
		float dis = momentum / 60.0f;
		for (int i = 0, len = ResourceManager::GetGameObject("snake").next.size(); i < len; i++) {
			switch ((int)ResourceManager::GetGameObject("snake").body[i].z)
			{
			case 0:
				ResourceManager::GetGameObject("snake").next[i].y -= dis;
				break;
			case 1:
				ResourceManager::GetGameObject("snake").next[i].x -= dis;
				break;
			case 2:
				ResourceManager::GetGameObject("snake").next[i].y += dis;
				break;
			case 3:
				ResourceManager::GetGameObject("snake").next[i].x += dis;
				break;
			default:
				break;
			}
		}
	}
}

void Game::Render()
{
	ResourceManager::GetGameObject("snake").Draw(*Renderer);
	Renderer->DrawSprite(*table, glm::vec3(0.0f, -2.0f, 0.0f), 2.5f, 1);
	Renderer->DrawSprite(*ball, glm::vec3(food_pos.x, 0.0f, food_pos.y), 7.5f, 0);
}

void Game::DoCollisions() {
	// 边界检测
	float width = 35.0f, height = 17.5f;
	int x = ResourceManager::GetGameObject("snake").body[0].x,
		y = ResourceManager::GetGameObject("snake").body[0].y;
	if (x > width || x < -width || y > height || y < -height) {
		State = GAME_MENU;
	}

	// 食物检测
	if ((food_pos.x - x) * (food_pos.x - x) + (food_pos.y - y) * (food_pos.y - y) < 1.0f) {
		getFood();
		ResourceManager::GetGameObject("snake").eat();
	}
}

void Game::getFood() {
	while (true) {
		bool flag = true;
		food_pos = glm::vec2((rand() % 28 - 14) * 2.5, (rand() % 14 - 7) * 2.5);
		float x = food_pos.x, y = food_pos.y;
		for (int i = 0, len = ResourceManager::GetGameObject("snake").body.size(); i < len; i++) {
			float bx = ResourceManager::GetGameObject("snake").body[i].x;
			float by = ResourceManager::GetGameObject("snake").body[i].y;
			if ((x - bx) * (x - bx) + (y - by) * (y - by) < 1.0f) {
				flag = false;
				break;
			}
		}
		if (flag) break;
	}
}