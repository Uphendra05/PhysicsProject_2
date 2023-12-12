#pragma once
#include <iostream>
#include "../../src/GraphicsRender.h"
#include "../../src/PhysicsEngine.h"







class ShieldGlobes
{
public:

	ShieldGlobes(GraphicsRender& render, Shader* shader, PhysicsEngine& engine);
	~ShieldGlobes();

	void Start();
	void Update();
	void End();

	void CalculateHealth(int damageCount);
	void AssignWindow(GLFWwindow* window, const char* title);
	void Destroy();

	Model* model;
	GraphicsRender* renderer;
	PhysicsObject* globePhyObj;
	PhysicsEngine* engine;
	Shader* defaultShader;

	
	int currentHealth;

	
	GLFWwindow* window;
	const char* title;
private:

	int maxHealth = 100;
};

