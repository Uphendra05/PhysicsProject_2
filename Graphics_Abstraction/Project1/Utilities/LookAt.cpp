#include "LookAt.h"

LookAt::LookAt(Model* currentTransform, Model* lookAtTransform)
{

	this->currentTransform = currentTransform;
	this->lookAtTransfrom = lookAtTransform;


}

LookAt::~LookAt()
{
}

void LookAt::Start()
{


}

void LookAt::Update()
{

	forward = glm::normalize(lookAtTransfrom->transform.position - currentTransform->transform.position);
	right = glm::normalize(glm::cross(glm::vec3(0,1,0), forward));
	up = glm::normalize(glm::cross(forward, right));

	currentTransform->transform.SetOrientationFromDirections(up, right);

	/*
	lookAtTransfrom->transform.SetOrientationFromDirections(up, -right);*/

	//currentTransform->transform.SetRotation(lookAtTransfrom->transform.rotation + lookAtOffset);
	
	
}

void LookAt::End()
{


}
