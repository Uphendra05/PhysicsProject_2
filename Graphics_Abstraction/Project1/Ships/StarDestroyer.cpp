#include "StartDestroyer.h"

StarDestroyer::StarDestroyer(GraphicsRender& render, Shader* shader, PhysicsEngine& engine)
{
	this->renderer = &render;
	this->defaultShader = shader;
	this->engine = &engine;
	

}

StarDestroyer::~StarDestroyer()
{
}

void StarDestroyer::Start()
{

	model = new Model("Models/StarDestroyer/Sample.ply");
	model->id = "StarDestroyer";
	model->transform.SetPosition(glm::vec3(0, 0, 0));
	model->transform.SetScale(glm::vec3(0.005f));
	renderer->AddModelsAndShader(model, defaultShader);


}

void StarDestroyer::Update(float deltaTime)
{


}

void StarDestroyer::End()
{



}
