#include "XWing.h"

XWing::XWing(GraphicsRender& render, Shader* shader, PhysicsEngine& engine, float time)
{

	this->renderer = &render;
	this->defaultShader = shader;
	this->engine = &engine;
	this->time = time;

}

XWing::~XWing()
{
}

void XWing::Start()
{
	model = new Model("Models/X-Wing/X-Wing_Attack_xyz_n_uv.ply");
	model->id = "X-Wing";
	model->transform.SetScale(glm::vec3(0.5f));
	renderer->AddModelsAndShader(model, defaultShader);

	//this->startPoint = model->transform.position;
	 
}

void XWing::Update(float deltaTime)
{

	timeStep += deltaTime / time;

	if (time == 0)
	{
		lerpValue = 1;
		timeStep = 1;
	}
	else
	{
		lerpValue = timeStep;

	}

	
		model->transform.SetPosition(Lerp(startPoint, endPoint, lerpValue));

	

}

void XWing::End()
{
}

void XWing::AssignPoint(glm::vec3& startPos, glm::vec3& endPos)
{

	this->endPoint = endPos;


}
