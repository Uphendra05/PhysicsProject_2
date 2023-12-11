#pragma once

#include <iostream>
#include "../../src/GraphicsRender.h"
#include "../../src/PhysicsEngine.h"
#include "../../Ships/BallDecal.h"

class Bullet
{

public:
	Bullet(GraphicsRender& render, Shader* shader, PhysicsEngine& engine);
	~Bullet();

	void Start();
	void Update(float deltaTime);
	void End();

	void AssignBallDecal(BallDecal& decal);

	Model* model;
	GraphicsRender* renderer;
	PhysicsObject* bulletPhyObj;
	PhysicsEngine* engine;
	Shader* defaultShader;

	Model* decalModel;

	BallDecal* decal;

	float speed = 10;
	int damageCount = 25;

private:


};

