#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
#include "Shader.h"
#include "Model.h"

class SpriteRender
{
public:
	// Constructor (inits shaders/shapes)
	SpriteRender(Shader& shader);
	// Destructor
	~SpriteRender();
	// Renders a defined quad textured with given sprite
	void DrawSprite(Model& myModel, glm::vec3 position, GLfloat scale_factor, GLint direction);
private:
	// Render state
	Shader shader;
	GLuint quadVAO;
	// Initializes and configures the quad's buffer and vertex attributes
	void initRenderData();
};

#endif