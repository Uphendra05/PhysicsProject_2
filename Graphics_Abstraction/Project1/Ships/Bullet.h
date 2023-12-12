#pragma once

#include <iostream>
#include "../../src/GraphicsRender.h"
#include "../../src/PhysicsEngine.h"
#include "../../Ships/BallDecal.h"
#include "../../Ships/ShieldGlobes.h"
#include <string>





class Bullet
{

public:
	Bullet(GraphicsRender& render, Shader* shader, PhysicsEngine& engine);
	~Bullet();

	void Start();
	void Update(float deltaTime);
	void SeparateUpdate(GLFWwindow* window, Shader* shader);
	void End();

	void AssignBallDecal(BallDecal& decal);

	void ManageHealth(GLFWwindow* window, Shader* shader);

	Model* model;
	GraphicsRender* renderer;
	PhysicsObject* bulletPhyObj;
	PhysicsEngine* engine;
	Shader* defaultShader;

	Model* decalModel;

	BallDecal* decal;

	ShieldGlobes* ShieldOne;
	ShieldGlobes* ShieldTwo;

	

	std::string formatHealthString(int health1, int health2) {
		return "Shield One Health : " + std::to_string(health1) +
			"               Shield Two Health : " + std::to_string(health2);
	}
	
	float speed = 10;
	int damageCount = 25;
	bool isCollided;
	bool destruct;

private:


};

