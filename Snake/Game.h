#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include <stdlib.h>
#include <time.h> 

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game
{
public:
	// ��Ϸ״̬
	GameState  State;
	GLboolean  Keys[1024];
	GLuint     Width, Height;
	Camera camera;
	int count;
	int total;
	int press_key;
	float momentum;
	glm::vec2 food_pos;
	// ���캯��/��������
	Game(GLuint width, GLuint height);
	~Game();
	// ��ʼ����Ϸ״̬���������е���ɫ��/����/�ؿ���
	void Init();
	// ��Ϸѭ��
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();
	void DoCollisions();
	void getFood();
};

#endif // !GAME_H