#pragma once
#include <iostream>
#include "../../Ships/ShieldGlobes.h"
#include <sstream>

class GlobeManager
{
public:
	GlobeManager(GraphicsRender& render, Shader* shader, PhysicsEngine& engine, Bullet& bullet,GLFWwindow* window);
	~GlobeManager();

	void Start();
	void Update();
	void End();

	void ManageHealthForGlobes();

	ShieldGlobes* ShieldOne;
	ShieldGlobes* ShieldTwo;

	const char* titleOne = "X wing Hit Shield One Sir !";
	const char* titleTwo = "X Wing Hit Shield Two Sir !";

};

