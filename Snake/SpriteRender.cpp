#include "SpriteRender.h"

SpriteRender::SpriteRender(Shader& shader)
{
	this->shader = shader;
	this->initRenderData();
}

SpriteRender::~SpriteRender()
{
	glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRender::DrawSprite(Model& myModel, glm::vec3 position, GLfloat zoom, GLint direction)
{
	this->shader.Use();
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, position);
	GLfloat rotate = direction * 90.0f + 180.0f;
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(zoom));

	this->shader.SetMatrix4("model", model);
	myModel.Draw(this->shader);
}

void SpriteRender::initRenderData()
{

}