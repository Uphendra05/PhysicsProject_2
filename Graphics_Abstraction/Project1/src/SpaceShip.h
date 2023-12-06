#pragma once
#include"PhysicsEngine.h"
#include "GraphicsRender.h"

class SpaceShip
{
public:
	SpaceShip(GraphicsRender& render, Shader* shader, PhysicsEngine& engine);
	SpaceShip();
	~SpaceShip();


	Model* model;
	PhysicsObject* SpaceShipPhysics;

	void LoadModel();

	void Update(float deltaTime);
	void SpaceShipInputs(GLFWwindow* window);

private:
	GraphicsRender* render;
	Shader* defaultshader;
	PhysicsEngine* engine;


	float speed = 2;
	glm::vec3 Direction = glm::vec3(0, 0, 0);
};

