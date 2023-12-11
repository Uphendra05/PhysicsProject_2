#pragma once
#include <iostream>
#include <vector>
#include "../../src/GraphicsRender.h"
#include <random>
class RandomPoints
{

public:
	RandomPoints(GraphicsRender& render, Shader* shader);
	~RandomPoints();

	void Start();
	void Update();



	glm::vec3 GetRandomPointAInSpace();
	glm::vec3 GetRandomPointBInSpace();

	void DrawPath(Model* PointA, Model* PointB);

	


	Model* spawnPoint;
	GraphicsRender* renderer;
	Shader* defaultShader;


private:

	int RandomPointsGenerator(int min, int max);


};

