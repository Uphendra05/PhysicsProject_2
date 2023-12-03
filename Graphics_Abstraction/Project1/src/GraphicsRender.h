#pragma once

#include "Renderer.h"
#include"model.h"
#include "Shader.h"
#include "Camera.h"


struct ModelAndShader
{

};

struct CompareDistances
{
	const glm::vec3& cameraPos;

	explicit CompareDistances(const glm::vec3& cameraPosition) : cameraPos(cameraPosition) {}

	bool operator()(const Model* lhs, const Model* rhs) const
	{
		glm::vec3 diff1 = cameraPos - lhs->transform.position;
		glm::vec3 diff2 = cameraPos - rhs->transform.position;

		return glm::dot(diff2, diff2) < glm::dot(diff1, diff1);
	}
};

struct modelAABB
{
	modelAABB() {}
	modelAABB(glm::vec3 min, glm::vec3 max)
	{
		this->min = min;
		this->max = max;
	}
	glm::vec3 min;
	glm::vec3 max;
};



class GraphicsRender
{
public:
	GraphicsRender();
	~GraphicsRender();

	void AddModelsAndShader(Model* model, Shader* Shader);
	void AddAlphaModelsAndShader(Model* model, Shader* Shader);
	void AddModelsAndShader(Model& model, Shader& Shader);

	void AddTransparentModels(Model* model, Shader* Shader);
	
	void AssignStencilShader( Shader* Shader);

	void AssignCamera(Camera* cam);

	void SortObject();
	
	std::vector<Model*> GetModelList();

	void DrawDebugModelAABB(const modelAABB& aabb, glm::vec4 color);
	
	
	void Draw();

	Model* selectedModel;
	

private:
	Shader* m_StencilShader;

	void ClearData();

	std::vector<Model*> m_Models;
	std::vector<Shader*> m_Shaders;

	std::vector<Model*> m_transparentModels;
	std::vector<Shader*> m_transparentShaders;

	Camera* cam;

};

