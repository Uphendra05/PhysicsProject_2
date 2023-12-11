#include "RandomPoints.h"

RandomPoints::RandomPoints(GraphicsRender& render, Shader* shader)
{
	this->renderer = &render;
	this->defaultShader = shader;
	
}

RandomPoints::~RandomPoints()
{
}

void RandomPoints::Start()
{
	spawnPoint = new Model("Models/IsoSphere/Isoshphere.ply");
	spawnPoint->id = "SpawnPoint";	
	spawnPoint->transform.scale = glm::vec3(0.5);
	renderer->AddModelsAndShader(spawnPoint, defaultShader);


}


void RandomPoints::Update()
{
}

glm::vec3 RandomPoints::GetRandomPointAInSpace()
{

	int x = RandomPointsGenerator(-50, -30);
	int y = RandomPointsGenerator(-10, 15);
	int z = RandomPointsGenerator(10, 30);

	return glm::vec3(x,y,z);
}

glm::vec3 RandomPoints::GetRandomPointBInSpace()
{

	int x = RandomPointsGenerator(30, 50);
	int y = RandomPointsGenerator(-10, 15);
	int z = RandomPointsGenerator(10, 30);

	return glm::vec3(x, y, z);
}

void RandomPoints::DrawPath(Model* PointA, Model* PointB)
{
	// point a - point b - > start point is a 



	
}

int RandomPoints::RandomPointsGenerator(int min, int max)
{
	

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(min, max - 1);
	int random_number = distribution(gen);
	return random_number;
	
}
