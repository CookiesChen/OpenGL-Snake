#include "GameObject.h"

GameObject::GameObject(){
	this->body = vector<glm::vec3>();
	this->body.push_back(glm::vec3(2.5f, 0.0f, 3.0f));
}

void GameObject::Draw(SpriteRender& renderer)
{
	for (int i = 0, len = next.size(); i < len; i++) {
		float zoom = i == 0? headZoom : bodyZoom;
		renderer.DrawSprite(model, glm::vec3(next[i].x, 0.0f, next[i].y), zoom, body[i].z);
	}
}

void GameObject::eat() {
	int count = body.size();
	body.push_back(glm::vec3(body[count - 1].x, body[count - 1].y, -1));
}

void GameObject::update() {
	float momentum = 2.5f;
	for (int i = 0, len = body.size(); i < len; i++) {
		switch ((int)body[i].z)
		{
		case 0:
			body[i].y -= momentum;
			break;
		case 1:
			body[i].x -= momentum;
			break;
		case 2:
			body[i].y += momentum;
			break;
		case 3:
			body[i].x += momentum;
			break;
		default:
			break;
		}
	}
	for (int i =body.size() - 1; i >= 1; i--) {
		body[i].z = body[i - 1].z;
	}
	next = body;
}