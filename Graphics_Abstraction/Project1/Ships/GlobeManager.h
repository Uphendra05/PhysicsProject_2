#pragma once
#include <iostream>
#include "../../Ships/ShieldGlobes.h"

class GlobeManager
{
public:
	GlobeManager(GraphicsRender& render, Shader* shader, PhysicsEngine& engine);
	~GlobeManager();

	void Start();
	void Update();
	void End();

	ShieldGlobes* ShieldOne;
	ShieldGlobes* ShieldTwo;

};

