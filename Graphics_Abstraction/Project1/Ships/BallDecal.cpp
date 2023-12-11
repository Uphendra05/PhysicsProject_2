#include "BallDecal.h"

BallDecal::BallDecal(GraphicsRender& render, Shader* shader)
{

    this->renderer = &render;
    this->defaultShader = shader;

}

BallDecal::~BallDecal()
{
}

void BallDecal::Start()
{
    model = new Model("Models/DefaultSphere/Sphere_1_unit_Radius.ply");
    model->id = "SpawnPoint";
    model->transform.scale = glm::vec3(0.5);
    renderer->AddModelsAndShader(model, defaultShader);
}

void BallDecal::Update()
{
}

void BallDecal::End()
{
}

Model* BallDecal::LoadCopyModel()
{
    Model* copyModel = new Model(*this->model);
    copyModel->id = "SpawnPoint";
    copyModel->transform.scale = glm::vec3(0.5);
    renderer->AddModelsAndShader(copyModel, defaultShader);

    return copyModel;
}
