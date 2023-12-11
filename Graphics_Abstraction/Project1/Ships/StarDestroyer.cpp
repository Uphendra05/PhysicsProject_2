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

	model = new Model("Models/StarDestroyer/StarDestroyer.ply");
	model->id = "StarDestroyer";
	model->transform.SetPosition(glm::vec3(0, 0, 0));
	model->transform.SetScale(glm::vec3(0.045f));
	renderer->AddModelsAndShader(model, defaultShader);

	shipPhyObj = new PhysicsObject(model);

	shipPhyObj->Initialize(MESH_TRIANGLES, true, STATIC);
	shipPhyObj->gravityValue = 0;

	shipPhyObj->DoCollisionCall([this](PhysicsObject* other)
		{
			//glm::vec3 collisionNormal = engine->collisionNormals[0];
			//glm::vec3 velocity = shipPhyObj->velocity;

			//// Calculate the dot product of velocity and collision normal
			//float dotProduct = glm::dot(collisionNormal, velocity);

			//// If the dot product is negative, it means the velocity is in the opposite direction of the collision normal
			//if (dotProduct < 0.0f)
			//{
			//	// Project velocity onto collision normal to get the component in the direction of the collision normal
			//	glm::vec3 velocityComponent = dotProduct * collisionNormal;

			//	// Update velocity to keep only the component in the direction of the collision normal
			//	shipPhyObj->velocity = velocityComponent;

			//	// Print a message indicating a collision
			//	std::cout << "Spaceship collided. Velocity clamped." << std::endl;
			//}
		});

	engine->AddPhysicsObjects(shipPhyObj);



}

void StarDestroyer::Update(float deltaTime)
{


}

void StarDestroyer::End()
{



}
