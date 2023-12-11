#pragma once
#include <iostream>
#include "../../src/GraphicsRender.h"
#include "../../src/PhysicsEngine.h"

class StarDestroyer
{
public:
	StarDestroyer(GraphicsRender& render, Shader* shader, PhysicsEngine& engine);
	~StarDestroyer();


	void Start();
	void Update(float deltaTime);
	void End();

	Model* model;
	GraphicsRender* renderer;
	PhysicsObject* shipPhyObj;
	PhysicsEngine* engine;
	Shader* defaultShader;


private:

};


