#include "ShieldGlobes.h"

ShieldGlobes::ShieldGlobes(GraphicsRender& render, Shader* shader, PhysicsEngine& engine)
{

	this->renderer = &render;
	this->defaultShader = shader;
	this->engine = &engine;
}

ShieldGlobes::~ShieldGlobes()
{
}

void ShieldGlobes::Start()
{

	this->currentHealth = this->maxHealth;


	model = new Model("Models/DefaultSphere/Sphere_1_unit_Radius.ply");
	model->id = "Globe";
	model->transform.SetScale(glm::vec3(4.45f));
	renderer->AddModelsAndShader(model, defaultShader);

	globePhyObj = new PhysicsObject(model);

	globePhyObj->Initialize(SPHERE, true, STATIC);
	globePhyObj->gravityValue = 0;

	globePhyObj->DoCollisionCall([this](PhysicsObject* other)
		{
			if (other->model->id == "X-Wing")
			{
				std::cout << "X wing hit" << std::endl;
				//this->model->transform.position = other->model->transform.position;
			}

			if (other->model->id == "Bullet")
			{
				CalculateHealth(bullet->damageCount);
				std::cout << "Current Health : " << currentHealth << std::endl;
				//this->model->transform.position = other->model->transform.position;
			}

			


		});

	engine->AddPhysicsObjects(globePhyObj);

}

void ShieldGlobes::Update()
{
}

void ShieldGlobes::End()
{
}

void ShieldGlobes::CalculateHealth(int damageCount)
{
	
    damageCount -= currentHealth;
	
    if (currentHealth <= 0)
	{
		Destroy();
	}

}

void ShieldGlobes::Destroy()
{
	std::cout << "Globe Destroyed" << std::endl;
}

void ShieldGlobes::AssignBullet(Bullet& bulletEntity)
{
	this->bullet = &bulletEntity;


}
