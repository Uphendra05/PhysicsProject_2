#include"SpaceShip.h"

SpaceShip::SpaceShip(GraphicsRender& render, Shader* shader, PhysicsEngine& engine, Camera& camera)
{
	this->render = &render;
	this->defaultshader = shader;
	this->engine = &engine;
	this->camera = &camera;
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
	model->transform.SetPosition(glm::vec3(0, 5, 2));
	model->transform.SetScale(glm::vec3(0.5f));
	render->AddModelsAndShader(model, defaultshader);


	SpaceShipPhysics = new PhysicsObject(model);

	SpaceShipPhysics->Initialize(SPHERE, true, DYNAMIC);
	SpaceShipPhysics->gravityValue =0;

	SpaceShipPhysics->DoCollisionCall([this](PhysicsObject* other)
		{
			glm::vec3 collisionNormal = engine->collisionNormals[0];
			glm::vec3 velocity = SpaceShipPhysics->velocity;

			// Calculate the dot product of velocity and collision normal
			float dotProduct = glm::dot(collisionNormal, velocity);

			// If the dot product is negative, it means the velocity is in the opposite direction of the collision normal
			if (dotProduct < 0.0f)
			{
				// Project velocity onto collision normal to get the component in the direction of the collision normal
				glm::vec3 velocityComponent = dotProduct * collisionNormal;

				// Update velocity to keep only the component in the direction of the collision normal
				SpaceShipPhysics->velocity = velocityComponent;

				// Print a message indicating a collision
				std::cout << "Spaceship collided. Velocity clamped." << std::endl;
			}
		});

	engine->AddPhysicsObjects(SpaceShipPhysics);



}

void SpaceShip::Update(float deltaTime)
{

	//SpaceShipPhysics->velocity = Direction * speed;

	//camera->Position = model->transform.position -  cameraOffset;

	float spaceshipPitch = glm::degrees(asin(-model->transform.GetForward().y));
	float spaceshipYaw = glm::degrees(atan2(model->transform.GetForward().x, model->transform.GetForward().z));

	// Set the camera's pitch and yaw

	// Obtain the model matrix of the spaceship
	glm::mat4 modelMatrix = model->transform.GetModelMatrix();

	// Rotate the original camera offset by the spaceship's rotation
	glm::vec3 rotatedCameraOffset = glm::rotate(glm::mat4(1.0f), glm::radians(model->transform.rotation.y), -model->transform.GetUp()) * glm::vec4(cameraOffset, 1.0f);

	// Calculate the new camera position relative to the rotated spaceship
	glm::vec3 cameraPosition = model->transform.position - rotatedCameraOffset;

	// Set the camera's position and update its view matrix
	camera->Position = cameraPosition;
	camera->updateCameraVectors();

	DrawAABBCollision(SpaceShipPhysics);
}

void SpaceShip::DrawAABBCollision(PhysicsObject* physicsObject)
{
	std::vector<cAABB> collisionAABBs = physicsObject->GetCollisionAABBs();

	for (size_t i = 0; i < collisionAABBs.size(); i++)
	{
		modelAABB m_Aabb = GetGraphicsAabb(collisionAABBs[i]);
		render->DrawAABB(m_Aabb);
	}
}

void SpaceShip::SpaceShipInputs(GLFWwindow* window, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		//Direction = glm::vec3(0, 0, 1);
		//Direction = -model->transform.GetForward();
		SpaceShipPhysics->velocity = -model->transform.GetForward() *speed;
		//camera->Position += -model->transform.GetForward() * deltaTime;
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		//Direction = glm::vec3(0, 0, -1);
		//Direction = model->transform.GetForward();
		SpaceShipPhysics->velocity = model->transform.GetForward() * speed;
	}
	else   if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		//Direction = -model->transform.GetRight();
		SpaceShipPhysics->velocity = -model->transform.GetRight() * speed;
	}
	else  if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
	//	Direction = model->transform.GetRight();
		SpaceShipPhysics->velocity = model->transform.GetRight() * speed;
	}
	else if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		//Direction = model->transform.GetUp();
		SpaceShipPhysics->velocity = model->transform.GetUp() * speed;
	}
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		//Direction = -model->transform.GetUp();

		SpaceShipPhysics->velocity = -model->transform.GetUp() * speed;
	}
	else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		
		SpaceShipPhysics->velocity = glm::vec3(0);
		
	}
	

	
}
