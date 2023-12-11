#include "GlobeManager.h"

GlobeManager::GlobeManager(GraphicsRender& render, Shader* shader, PhysicsEngine& engine)
{
	ShieldOne = new ShieldGlobes(render, shader, engine);
	ShieldTwo = new ShieldGlobes(render, shader, engine);


}

GlobeManager::~GlobeManager()
{
}

void GlobeManager::Start()
{
	ShieldOne->Start();
	ShieldTwo->Start();


	ShieldOne->model->transform.position = glm::vec3(-5, 10, 25);
	ShieldOne->model->isWireFrame = true;
	ShieldTwo->model->transform.position = glm::vec3(5, 10, 25);
	ShieldTwo->model->isWireFrame = true;

}

void GlobeManager::Update()
{
}

void GlobeManager::End()
{
}
