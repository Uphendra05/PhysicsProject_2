#pragma once
#include <iostream>
#include "../../src/GraphicsRender.h"
#include "../../src/PhysicsEngine.h"
#include "../../Utilities/Lerp.h"

class XWing
{

public:

	XWing(GraphicsRender& render, Shader* shader, PhysicsEngine& engine, float time);
	~XWing();

	void Start();
	void Update(float deltaTime);
	void End();

	void AssignPoint(glm::vec3& startPos, glm::vec3& endPos);

	Model* model;
	GraphicsRender* renderer;
	PhysicsObject* shipPhyObj;
	PhysicsEngine* engine;
	Shader* defaultShader;
	bool isReached;

	float lerpValue = 0;
	float timeStep = 0;

	glm::vec3 startPoint;


private:

	glm::vec3 endPoint;

	float time;
	






};

