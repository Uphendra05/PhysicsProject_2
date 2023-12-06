#include"SpaceShip.h"

SpaceShip::SpaceShip(GraphicsRender& render, Shader* shader, PhysicsEngine& engine)
{
	this->render = &render;
	this->defaultshader = shader;
	this->engine = &engine;
}

SpaceShip::SpaceShip()
{
}

SpaceShip::~SpaceShip()
{
}

void SpaceShip:: LoadModel()
{
	model = new Model("Models/Spaceship/Spaceship.obj");
	model->id = "SpaceShip";
	render->AddModelsAndShader(model, defaultshader);


	SpaceShipPhysics = new PhysicsObject(model);

	SpaceShipPhysics->Initialize(SPHERE, true, DYNAMIC);
	SpaceShipPhysics->gravityValue =0;

	SpaceShipPhysics->DoCollisionCall([this](PhysicsObject* other)
		{

		});

	engine->AddPhysicsObjects(SpaceShipPhysics);



}

void SpaceShip::Update(float deltaTime)
{

	SpaceShipPhysics->velocity = Direction * speed;
}

void SpaceShip::SpaceShipInputs(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		Direction = glm::vec3(0, 0, 1);
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		Direction = glm::vec3(0, 0, -1);
	}
	else  
	{
		Direction = glm::vec3(0, 0, 0);
	}

}
