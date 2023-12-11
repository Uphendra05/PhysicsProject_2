#include "Bullet.h"

Bullet::Bullet(GraphicsRender& render, Shader* shader, PhysicsEngine& engine)
{
	this->renderer = &render;
	this->defaultShader = shader;
	this->engine = &engine;

}

Bullet::~Bullet()
{
}

void Bullet::Start()
{
	

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

			if (other->model->id == "Globe")
			{
				std::cout << "Bullet : Collided with Globe" << std::endl;
				//model->isVisible = false;
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

void Bullet::End()
{
}

void Bullet::AssignBallDecal(BallDecal& decal)
{
	this->decal = &decal;
}
