#pragma once
#include <iostream>
#include "../../src/GraphicsRender.h"

class BallDecal
{

public:
	BallDecal(GraphicsRender& render, Shader* shader);
	~BallDecal();

	void Start();
	void Update();
	void End();

	Model* LoadCopyModel();

	Model* model;
	GraphicsRender* renderer;
	Shader* defaultShader;

private:

	


};

