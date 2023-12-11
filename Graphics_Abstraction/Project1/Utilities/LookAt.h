#pragma once

#include <iostream>
#include "../../src/Transform.h"
#include "../../src/model.h"

class LookAt
{
public:
	LookAt(Model* currentTransform,Model* lookAtTransform);
	~LookAt();

	void Start();
	void Update();
	void End();

	glm::vec3 lookAtOffset = glm::vec3(0, 0, 0);


private:

	Model* currentTransform;
	Model* lookAtTransfrom;

	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;


};

