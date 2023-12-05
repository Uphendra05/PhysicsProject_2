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

private:
	GraphicsRender* render;
	Shader* defaultshader;
	PhysicsEngine* engine;

};

