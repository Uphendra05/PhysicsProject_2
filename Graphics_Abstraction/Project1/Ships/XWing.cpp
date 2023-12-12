#include "XWing.h"

XWing::XWing(GraphicsRender& render, Shader* shader, PhysicsEngine& engine, float time)
{

	this->renderer = &render;
	this->defaultShader = shader;
	this->engine = &engine;
	this->time = time;

}

XWing::XWing(const XWing& CopyEntity)
{

	this->renderer = CopyEntity.renderer;
	this->defaultShader = CopyEntity.defaultShader;
	this->engine = CopyEntity.engine;
	this->time = CopyEntity.time;

}



XWing::~XWing()
{
}

void XWing::Start()
{
	model = new Model("Models/X-Wing/X-Wing_Attack_xyz_n_uv.ply");
	model->id = "X-Wing";
	model->transform.SetPosition(glm::vec3(0, 21, 0));
	model->transform.SetScale(glm::vec3(0.5f));
	renderer->AddModelsAndShader(model, defaultShader);

	//this->startPoint = model->transform.position;

	shipPhyObj = new PhysicsObject(model);

	shipPhyObj->Initialize(SPHERE, true, DYNAMIC);
	shipPhyObj->gravityValue = 0;

	shipPhyObj->DoCollisionCall([this](PhysicsObject* other)
		{
			if (other->model->id == "StarDestroyer")
			{
				std::cout << "Collided " << std::endl;
				shipPhyObj->velocity = -model->transform.GetForward() * speed;
				model->transform.SetRotation(glm::vec3(0,90,0));
				shipPhyObj->collisionCallbool = false;

				isCollided = true;
			}

			
			
			
		});

	engine->AddPhysicsObjects(shipPhyObj);
	 
}

void XWing::Update(float deltaTime)
{

	/*timeStep += deltaTime / time;

	if (time == 0)
	{
		lerpValue = 1;
		timeStep = 1;
	}
	else
	{
		lerpValue = timeStep;

	}

	
		model->transform.SetPosition(Lerp(startPoint, endPoint, lerpValue));*/


	if (!isCollided)
	{
		shipPhyObj->velocity = model->transform.GetForward() * speed;

	}

	

}

void XWing::End()
{
}

void XWing::AssignPoint(glm::vec3& startPos, glm::vec3& endPos)
{

	this->endPoint = endPos;


}
