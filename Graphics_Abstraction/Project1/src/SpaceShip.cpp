#include"SpaceShip.h"

SpaceShip::SpaceShip(GraphicsRender& render, Shader* shader, PhysicsEngine& engine, Camera& camera)
{
	this->render = &render;
	this->defaultshader = shader;
	this->engine = &engine;
	this->camera = &camera;

	InputManager::GetInstance().AddListener(this);
}

SpaceShip::SpaceShip()
{
}

SpaceShip::~SpaceShip()
{
}

void SpaceShip:: LoadModel()
{
	model = new Model("Models/Spaceship/Ship2.obj");
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

			float dotProduct = glm::dot(collisionNormal, velocity);

			if (dotProduct < 0.0f)
			{
				
				glm::vec3 velocityComponent = dotProduct * collisionNormal;

			
				SpaceShipPhysics->velocity = velocityComponent;

			}
			if (!collisionDrawBallList.empty())
			{
				int size = collisionDrawBallList.size();

				if (size>50)
				{
					// Deleting the last model of debuging green balls 
				 render->RemoveModels(collisionDrawBallList[collisionDrawBallList.size() - 1]);
				}
			}

			if (engine->collisionPoints.size()>0)
			{
				glm::vec3 collisionPoint = engine->collisionPoints[0];

				Model* drawModel = new Model(*collisionBall);
				drawModel->transform.SetPosition(collisionPoint);
				drawModel->transform.SetScale(glm::vec3(0.2f));
				render->AddModelsAndShader(drawModel, defaultshader);
				collisionDrawBallList.push_back(drawModel);
			}

		});

	engine->AddPhysicsObjects(SpaceShipPhysics);




	glm::vec3 forward = model->transform.GetForward();

	camera->transform.SetPosition(model->transform.position + forward * followDistance + glm::vec3(0, yoffset, 0));

	glm::vec3 cameraForwad = glm::normalize(model->transform.position - camera->transform.position);
	glm::vec3 cameraright = glm::normalize(glm::cross(glm::vec3(0, 1, 0), cameraForwad));
	glm::vec3 cameraup = glm::normalize(glm::cross(cameraForwad, cameraright));

	camera->transform.SetOrientationFromDirections(cameraup, cameraright);
}

void SpaceShip::SetCollissionPointSphere(Model* model)
{
	collisionBall = model;
}

void SpaceShip::Update(float deltaTime)
{

	glm::vec3 forward = model->transform.GetForward();
	//camera->SetCameraPosition(model->transform.position + forward  *followDistance + glm::vec3(0, yoffset, 0));
	camera->transform.SetPosition(model->transform.position + forward * followDistance + glm::vec3(0, yoffset, 0));
	
	DrawAABBCollision(SpaceShipPhysics);
}

void SpaceShip::DrawAABBCollision(PhysicsObject* physicsObject)
{
	if (!isDebugAAABDraw)
	{
		return;
	}
	std::vector<cAABB> collisionAABBs = physicsObject->GetCollisionAABBs();

	for (size_t i = 0; i < collisionAABBs.size(); i++)
	{
		modelAABB m_Aabb = GetGraphicsAabb(collisionAABBs[i]);
		render->DrawAABB(m_Aabb);
	}
}



void SpaceShip::OnKeyPressed(const int& key)
{
	if (key == GLFW_KEY_W)
	{
		SpaceShipPhysics->velocity = -model->transform.GetForward() * speed;
	}
	else if(key == GLFW_KEY_S)
	{
		SpaceShipPhysics->velocity = model->transform.GetForward() * speed;
	}

	else if (key == GLFW_KEY_D)
	{
		SpaceShipPhysics->velocity = -model->transform.GetRight() * speed;
	}

	else if (key == GLFW_KEY_A)
	{
		SpaceShipPhysics->velocity = model->transform.GetRight() * speed;
	}
	else if (key == GLFW_KEY_Q)
	{
		SpaceShipPhysics->velocity = model->transform.GetUp() * speed;
	}
	else if (key == GLFW_KEY_E)
	{
		SpaceShipPhysics->velocity = -model->transform.GetUp() * speed;
	}


	else if (key == GLFW_KEY_LEFT)  //LEFT
	{
		model->transform.SetRotation(glm::vec3(model->transform.rotation.x ,
			model->transform.rotation.y +rotationAngle,
			model->transform.rotation.z));

	}

	else if (key == GLFW_KEY_RIGHT) //RIGHT
	{
		model->transform.SetRotation(glm::vec3(model->transform.rotation.x,
			model->transform.rotation.y - rotationAngle,
			model->transform.rotation.z));

	}
	else if (key == GLFW_KEY_UP) //UP
	{
		model->transform.SetRotation(glm::vec3(model->transform.rotation.x ,
			model->transform.rotation.y,
			model->transform.rotation.z - rotationAngle));

	}
	else if (key == GLFW_KEY_DOWN) //DOWN
	{
		model->transform.SetRotation(glm::vec3(model->transform.rotation.x ,
			model->transform.rotation.y,
			model->transform.rotation.z + rotationAngle));

	}

	//camera->SetCameraPosition(model->transform.position + model->transform.GetForward() * followDistance + glm::vec3(0, yoffset, 0));

	glm::vec3 cameraForwad = glm ::normalize(model->transform.position - camera->transform.position);
	glm::vec3 cameraright = glm::normalize(glm::cross(glm::vec3(0, 1, 0), cameraForwad));
	glm::vec3 cameraup = glm::normalize(glm::cross(cameraForwad, cameraright));

	camera->transform.SetOrientationFromDirections(cameraup, cameraright);
    if (key == GLFW_KEY_0)
	{
		isDebugAAABDraw = !isDebugAAABDraw;
	}
}

void SpaceShip::OnKeyReleased(const int& key)
{
}

void SpaceShip::OnKeyHeld(const int& key)
{
}
