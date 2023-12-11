#pragma once
#include <iostream>
#include "../../src/GraphicsRender.h"
#include "../../src/PhysicsEngine.h"
#include "../../Ships/Bullet.h"

class ShieldGlobes
{
public:

	ShieldGlobes(GraphicsRender& render, Shader* shader, PhysicsEngine& engine);
	~ShieldGlobes();

	void Start();
	void Update();
	void End();

	void CalculateHealth(int damageCount);
	void Destroy();

	Model* model;
	GraphicsRender* renderer;
	PhysicsObject* globePhyObj;
	PhysicsEngine* engine;
	Shader* defaultShader;

	void AssignBullet(Bullet& bulletEntity);
	

private:

	Bullet* bullet;
	int currentHealth;
	
	int maxHealth = 100;
};

