//#include "GlobeManager.h"
//
//GlobeManager::GlobeManager(GraphicsRender& render, Shader* shader, PhysicsEngine& engine, GLFWwindow* window)
//{
//	ShieldOne = new ShieldGlobes(render, shader, engine);
//	ShieldTwo = new ShieldGlobes(render, shader, engine);
//	
//
//
//	
//	ShieldOne->AssignWindow(window, titleOne);
//
//	
//
//
//	ShieldTwo->AssignWindow(window, titleTwo);
//
//}
//
//GlobeManager::~GlobeManager()
//{
//}
//
//void GlobeManager::Start()
//{
//	ShieldOne->Start();
//	ShieldTwo->Start();
//
//
//	ShieldOne->model->transform.position = glm::vec3(-5, 10, 25);
//	ShieldOne->model->id = "GlobeOne";
//	ShieldOne->model->meshes[0]->isWireFrame = true;
//
//	ShieldTwo->model->transform.position = glm::vec3(5, 10, 25);
//	ShieldTwo->model->id = "GlobeTwo";
//	ShieldTwo->model->meshes[0]->isWireFrame = true;
//
//}
//
//void GlobeManager::Update()
//{
//	ManageHealthForGlobes();
//}
//
//void GlobeManager::End()
//{
//}
//
//void GlobeManager::ManageHealthForGlobes()
//{
//
//	/*std::cout << "Shield One Current Health : " << ShieldOne->currentHealth << std::endl;
//	std::cout << "Shield Two Current Health : " << ShieldTwo->currentHealth << std::endl;*/
//	
//
//	if (ShieldOne->currentHealth <= 0)
//	{
//		ShieldOne->model->isVisible = false;
//	}
//
//	if (ShieldTwo->currentHealth <= 0)
//	{
//		ShieldTwo->model->isVisible = false;
//
//	}
//
//
//	if (ShieldOne->currentHealth <= 0 && ShieldTwo->currentHealth <= 0)
//	{
//
//		std::cout << "Initiate Star Destroyer Self Destruction" << std::endl;
//	}
//
//
//}
