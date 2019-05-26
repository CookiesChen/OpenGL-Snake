#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "SpriteRender.h"


// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.
class GameObject
{
public:
	// Object state
	GLfloat     headZoom;
	GLfloat		bodyZoom;
	vector<glm::vec3> body;
	vector<glm::vec3> next;
	// Render state
	Model model;
	GameObject();
	// Draw sprite
	virtual void Draw(SpriteRender& renderer);
	void eat();
	void update();
};

#endif