#include "Bullet.h"

Bullet::Bullet(GraphicsRender& render, Shader* shader, PhysicsEngine& engine)
{
	this->renderer = &render;
	this->defaultShader = shader;
	this->engine = &engine;

	ShieldOne = new ShieldGlobes(render, shader, engine);
	ShieldTwo = new ShieldGlobes(render, shader, engine);
}

Bullet::~Bullet()
{
}

void Bullet::Start()
{
	ShieldOne->Start();
	ShieldTwo->Start();

	ShieldOne->model->transform.position = glm::vec3(-5, 10, 25);
	ShieldOne->model->id = "GlobeOne";
	ShieldOne->model->meshes[0]->isWireFrame = true;

	ShieldTwo->model->transform.position = glm::vec3(6, 10, 25);
	ShieldTwo->model->id = "GlobeTwo";
	ShieldTwo->model->meshes[0]->isWireFrame = true;



	model = new Model("Models/Bullet/TearDropBullet.ply");
	model->id = "Bullet";
	model->transform.SetPosition(glm::vec3(0, 10, 0));
	model->transform.SetScale(glm::vec3(3.45f));
	renderer->AddModelsAndShader(model, defaultShader);

	bulletPhyObj = new PhysicsObject(model);

	bulletPhyObj->Initialize(SPHERE, true, DYNAMIC);
	bulletPhyObj->gravityValue = 0;

	bulletPhyObj->DoCollisionCall([this](PhysicsObject* other)
		{
			if (other->model->id == "X-Wing")
			{
				//this->model->transform.position = other->model->transform.position;
			}

			if (other->model->id == "StarDestroyer")
			{
				std::cout << "Collided with Star Destroyer" << std::endl;
				model->isVisible = false;
				bulletPhyObj->collisionCallbool = false;
				decal->LoadCopyModel()->transform.position = this->model->transform.position;
				
			}

			if (other->model->id == "GlobeOne")
			{
				std::cout << "Bullet : Collided with GlobeOne" << std::endl;
				ShieldOne->CalculateHealth(damageCount);
				std::cout<<"Shield One Health:" << ShieldOne->currentHealth << std::endl;
				model->isVisible = false;
				bulletPhyObj->collisionCallbool = false;
				isCollided = true;
			}

			if (other->model->id == "GlobeTwo")
			{
				std::cout << "Bullet : Collided with GlobeTwo" << std::endl;
				ShieldTwo->CalculateHealth(damageCount);
				std::cout << "Shield Two Health:" << ShieldTwo->currentHealth << std::endl;
				model->isVisible = false;
				bulletPhyObj->collisionCallbool = false;
				isCollided = true;
			}

			
		});

	engine->AddPhysicsObjects(bulletPhyObj);
}

void Bullet::Update(float deltaTime)
{
	bulletPhyObj->velocity = model->transform.GetForward() * speed;
	
}

void Bullet::SeparateUpdate(GLFWwindow* window, Shader* shader)
{
	ManageHealth(window, shader);
}

void Bullet::End()
{
}

void Bullet::AssignBallDecal(BallDecal& decal)
{
	this->decal = &decal;
}

void Bullet::ManageHealth(GLFWwindow* window, Shader* shader)
{
	std::cout << "Shield One Health:" << ShieldOne->currentHealth << std::endl;

	std::cout << "Shield Two Health:" << ShieldTwo->currentHealth << std::endl;


	


	if (ShieldOne->currentHealth <= 0)
	{
		ShieldOne->model->isVisible = false;
	}

	if (ShieldTwo->currentHealth <= 0)
	{
		ShieldTwo->model->isVisible = false;

	}

	int health1 = ShieldOne->currentHealth;
	int health2 = ShieldTwo->currentHealth;


	health1 = std::min(std::max(ShieldOne->currentHealth, 0), 100);
	health2 = std::min(std::max(ShieldTwo->currentHealth, 0), 100);

    std::string health = formatHealthString(health1, health2);

	glfwSetWindowTitle(window, health.c_str());

	if (ShieldOne->currentHealth <= 0 && ShieldTwo->currentHealth <= 0)
	{
		destruct = true;
		/*shader->setBool("isDestroyed", true);
		shader->setFloat("explosionOffset", 10*10);*/
		glfwSetWindowTitle(window, "Initiated Star Destroyer Self Destruction");
		std::cout << "Initiated Star Destroyer Self Destruction" << std::endl;
	}
}


