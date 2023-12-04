#include"ApplicationRenderer.h"



ApplicationRenderer::ApplicationRenderer()
{
}

ApplicationRenderer::~ApplicationRenderer()
{
}



void ApplicationRenderer::WindowInitialize(int width, int height,  std::string windowName)
{
    windowWidth = width;
    WindowHeight = height;
    lastX = windowWidth / 2.0f;
    lastY= WindowHeight / 2.0f;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* w, int x, int y)
        {
            static_cast<ApplicationRenderer*>(glfwGetWindowUserPointer(w))->SetViewPort(w, x, y);
        });

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            static_cast<ApplicationRenderer*>(glfwGetWindowUserPointer(window))->KeyCallBack(window, key, scancode, action, mods);
        });


    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xposIn, double yposIn)
        {
            static_cast<ApplicationRenderer*>(glfwGetWindowUserPointer(window))->MouseCallBack(window, xposIn, yposIn);
        });

    glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset)
        {
            static_cast<ApplicationRenderer*>(glfwGetWindowUserPointer(window))->MouseScroll(window, xoffset, yoffset);
        });
   
    
    //Init GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }




  
    defaultShader = new Shader("Shaders/Light_VertexShader.vert", "Shaders/Light_FragmentShader.frag");
    lightShader = new Shader("Shaders/lighting.vert", "Shaders/lighting.frag");
    StencilShader = new Shader("Shaders/StencilOutline.vert", "Shaders/StencilOutline.frag");
   
    SkyboxShader = new Shader("Shaders/SkyboxShader.vert", "Shaders/SkyboxShader.frag");


    //ScrollShader = new Shader("Shaders/ScrollTexture.vert", "Shaders/ScrollTexture.frag");
    render.AssignStencilShader(StencilShader);
    camera.Position = glm::vec3(0, 0, - 1.0f);
}



std::vector<ModelData> ApplicationRenderer::loadModelDataFromFile(const std::string& filePath)
{

    std::ifstream file(filePath);
    std::vector<ModelData> modelData;

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return modelData;
    }
    else
    {
        std::cerr << "File Opened >>>>>>>>>>>>>>>>>>>>>>>>>>>: " << filePath << std::endl;

    }

    std::string line;
    ModelData currentModel;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string token;
        iss >> token;

        if (token == "ModelPath:") 
        {
            iss >> currentModel.path;
        }
        else if (token == "ModelPosition:") {
            iss >> currentModel.position.x >> currentModel.position.y >> currentModel.position.z;
        }       
        else if (token == "ModelRotation:") {

            iss >> currentModel.rotation.x >> currentModel.rotation.y >> currentModel.rotation.z;

        }
      
        else if (token == "TexturePath:") 
        {

            iss >> currentModel.texturePath;

        }
        else if (token == "Transperency:")
        {

            iss >> currentModel.isTrans;

        }
        
        else if (token == "Cutoff:")
        {

            iss >> currentModel.isCutoff;

        }
      
        else if (token == "ModelScale:") {
            iss >> currentModel.scale.x >> currentModel.scale.y >> currentModel.scale.z;
            modelData.push_back(currentModel);
        }
    }

    file.close();
    return modelData;
}


void ApplicationRenderer::Start()
{
   // GLCALL(glEnable(GL_DEPTH_TEST));
    GLCALL(glDepthFunc(GL_LESS));
    GLCALL(glEnable(GL_STENCIL_TEST));
    GLCALL(glStencilFunc(GL_NOTEQUAL, 1, 0xFF));
    GLCALL(glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE));
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    skybox = new Skybox(); 
    
    skybox->AssignSkyboxShader(SkyboxShader);
    skybox->SkyboxPrerender();
    

    render.AssignCamera(&camera);

    Model* Sphere = new Model((char*)"Models/DefaultSphere/Sphere_1_unit_Radius.ply", true);


    CamPlaceholder = new Model((char*)"Models/DefaultSphere/Sphere_1_unit_Radius.ply", true);
    CamPlaceholder->transform.SetPosition(glm::vec3(-1.5f, 0.8f, 0.5));
    CamPlaceholder->transform.SetScale(glm::vec3(0.1f));

    //render.AddModelsAndShader(CamPlaceholder, defaultShader);

    
   
   // Model* Sphere = new Model();

   


     Model* Pokeball = new Model((char*)"Models/Pokeball/pokeball.obj", true);
     Model* Pokeball2 = new Model((char*)"Models/Pokeball/pokeball.obj", true);

     defaultBox = new Model("Models/Box/DefaultCube.fbx");


     Sphere->transform.position.x += 2;
     Pokeball->transform.position.x -= 2;
    
     

     Pokeball2->transform.position.x -= 5;
     Pokeball2->transform.position.y -= 0.3f;
     Pokeball2->transform.SetScale(glm::vec3(1.2f));
    Pokeball2->transform.position = Pokeball->transform.position;
         Pokeball2->transform.SetScale(glm::vec3(0.5f));

     Model* dir = new Model();
     Model* spotlight = new Model(*Sphere);
     spotlight->transform.SetPosition(glm::vec3(1.0f, 3.0f, 0.0f));
     spotlight->transform.SetRotation(glm::vec3(-90, 0, 0));
     spotlight->transform.SetScale(glm::vec3(0.1f));

     Model* spotlight2 = new Model(*Sphere);
     spotlight2->transform.SetPosition(glm::vec3(-1.0f, 3.0f, 0.0f));
     spotlight2->transform.SetRotation(glm::vec3(-90, 0, 0));
     spotlight2->transform.SetScale(glm::vec3(0.1f));

     Model* spotlight3 = new Model(*Sphere);
     spotlight3->transform.SetPosition(glm::vec3(-1.0f, 3.0f, 2.0f));
     spotlight3->transform.SetRotation(glm::vec3(-90, 0, 0));
     spotlight3->transform.SetScale(glm::vec3(0.1f));

     Model* spotlight4 = new Model(*Sphere);
     spotlight4->transform.SetPosition(glm::vec3(1.0f, 3.0f, 2.0f));
     spotlight4->transform.SetRotation(glm::vec3(-90, 0, 0));
     spotlight4->transform.SetScale(glm::vec3(0.1f));

     Model* spotlight5 = new Model(*Sphere);
     spotlight5->transform.SetPosition(glm::vec3(1.0f, 3.0f, -2.0f));
     spotlight5->transform.SetRotation(glm::vec3(-90, 0, 0));
     spotlight5->transform.SetScale(glm::vec3(0.1f));

     Model* spotlight6 = new Model(*Sphere);
     spotlight6->transform.SetPosition(glm::vec3(-1.0f, 3.0f, -2.0f));
     spotlight6->transform.SetRotation(glm::vec3(-90, 0, 0));
     spotlight6->transform.SetScale(glm::vec3(0.1f));


/////////////////////////////////////////////////////////////////////////////////////////////

     modelData = loadModelDataFromFile("Model.txt");
     TeaTable = new Model("Models/Desk/Desk.obj");
     TeaTable->transform.SetPosition(glm::vec3(modelData[9].position));
     TeaTable->transform.SetRotation(glm::vec3(0,0,0));
    // TeaTable->transform.SetScale(glm::vec3(modelData[9].scale));
     render.AddModelsAndShader(TeaTable, defaultShader);

     teaTablePhy = new PhysicsObject(TeaTable);
     teaTablePhy->physicsType = TRIANGLE;    
     teaTablePhy->Initialize(false,false,STATIC);
     PhysicsEngine.AddPhysicsObjects(teaTablePhy);

     DrawDebugModelAABB(teaTablePhy->GetModelAABB());

    


#pragma region Lights

Light directionLight;
directionLight.lightType = LightType::DIRECTION_LIGHT;
directionLight.lightModel = dir;
directionLight.ambient = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
directionLight.diffuse = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
directionLight.specular = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);



Light spot;
spot.lightType = LightType::SPOT_LIGHT;
spot.lightModel = spotlight;
spot.ambient = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
spot.diffuse = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
spot.specular = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
spot.cutOffAngle = 15;
spot.outerCutOffAngle = 35;

Light spot2;
spot2.lightType = LightType::SPOT_LIGHT;
spot2.lightModel = spotlight2;
spot2.ambient = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
spot2.diffuse = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
spot2.specular = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
spot2.cutOffAngle = 15;
spot2.outerCutOffAngle = 35;

Light spot3;
spot3.lightType = LightType::SPOT_LIGHT;
spot3.lightModel = spotlight3;
spot3.ambient = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
spot3.diffuse = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
spot3.specular = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
spot3.cutOffAngle = 15;
spot3.outerCutOffAngle = 35;

Light spot4;
spot4.lightType = LightType::SPOT_LIGHT;
spot4.lightModel = spotlight4;
spot4.ambient = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
spot4.diffuse = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
spot4.specular = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
spot4.cutOffAngle = 15;
spot4.outerCutOffAngle = 35;

Light spot5;
spot5.lightType = LightType::SPOT_LIGHT;
spot5.lightModel = spotlight5;
spot5.ambient = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
spot5.diffuse = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
spot5.specular = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
spot5.cutOffAngle = 15;
spot5.outerCutOffAngle = 35;

Light spot6;
spot6.lightType = LightType::SPOT_LIGHT;
spot6.lightModel = spotlight6;
spot6.ambient = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
spot6.diffuse = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
spot6.specular = glm::vec4(5.0f, 5.0f, 5.0f, 1.0f);
spot6.cutOffAngle = 15;
spot6.outerCutOffAngle = 35;


#pragma endregion

     

     //Mesh Renderer
     //render.AddModelsAndShader(Sphere, defaultShader);

    
     
    // render.AddModelsAndShader(Pokeball, defaultShader);
  

     
     render.selectedModel = nullptr;

     render.AddModelsAndShader(dir,lightShader);
     render.AddModelsAndShader(spotlight, lightShader);
     render.AddModelsAndShader(spotlight2, lightShader);
     render.AddModelsAndShader(spotlight3, lightShader);
     render.AddModelsAndShader(spotlight4, lightShader);
     render.AddModelsAndShader(spotlight5, lightShader);
     render.AddModelsAndShader(spotlight6, lightShader);

     

     //LightRenderer
     lightManager.AddNewLight(directionLight);
     lightManager.AddNewLight(spot);
     lightManager.AddNewLight(spot2);
     lightManager.AddNewLight(spot3);
     lightManager.AddNewLight(spot4);
     lightManager.AddNewLight(spot5);
     lightManager.AddNewLight(spot6);
     lightManager.SetUniforms(defaultShader->ID);
   

     defaultShader->Bind();
     defaultShader->setInt("skybox", 0);

     moveCam.AssignCam(&camera);

    
}

void ApplicationRenderer::PreRender()
{

}

void ApplicationRenderer::Render()
{
    Start();
    Material material(128.0f);
    glm::vec3 pos(5, 0, 0);
   // glEnable(GL_BLEND);
  //  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    while (!glfwWindowShouldClose(window))
    {
        Clear();


        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        scrollTime += deltaTime;

        ProcessInput(window);

        glm::mat4 _projection = glm::perspective(glm::radians(camera.Zoom), (float)windowWidth / (float)WindowHeight, 0.1f, 100.0f);
        glm::mat4 _view = camera.GetViewMatrix();
        glm::mat4 _skyboxview = glm::mat4(glm::mat3(camera.GetViewMatrix()));


        PreRender(); //Update call BEFORE  DRAW

        glDepthFunc(GL_LEQUAL);
        SkyboxShader->Bind();
        SkyboxShader->setMat4("view", _skyboxview);
        SkyboxShader->setMat4("projection", _projection);

        skybox->Skyboxrender();
        glDepthFunc(GL_LESS); 


        defaultShader->Bind();
       // material.SetMaterialProperties(*defaultShader);
     //   lightManager.UpdateUniformValuesToShader(defaultShader);
        lightManager.UpdateUniformValues(defaultShader->ID);
       

         defaultShader->setMat4("projection", _projection);
         defaultShader->setMat4("view", _view);
         defaultShader->setVec3("viewPos", camera.Position.x, camera.Position.y, camera.Position.z);
         defaultShader->setFloat("time", scrollTime);
         defaultShader->setBool("isDepthBuffer", false);

         lightShader->Bind();
         lightShader->setVec3("objectColor", glm::vec3(1, 1, 1));
         lightShader->setMat4("projection", _projection);
         lightShader->setMat4("view", _view);

         StencilShader->Bind();
         StencilShader->setMat4("projection", _projection);
         StencilShader->setMat4("view", _view);

        /* ScrollShader->Bind();
         ScrollShader->setMat4("ProjectionMatrix", _projection);*/
        

       

         
  
         
         // make models that it should not write in the stencil buffer
         render.Draw();
       

         if (cameraMoveToTarget)
         {
             camera.UpdateCameraPosition(deltaTime);

         }
       
    
        
      
     

         PostRender(); // Update Call AFTER  DRAW

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}

void ApplicationRenderer::PostRender()
{
   // glDisable(GL_BLEND);

    PhysicsEngine.Update(deltaTime);

 
    DrawDebugBvhNodeAABB(teaTablePhy->BvhAABBTree->root);
}

void ApplicationRenderer::Clear()
{
    GLCALL(glClearColor(0.1f, 0.1f, 0.1f, 0.1f));
    GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
}

void ApplicationRenderer::ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed=25;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(FORWARD, deltaTime * cameraSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime * cameraSpeed);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(LEFT, deltaTime * cameraSpeed);

    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.ProcessKeyboard(RIGHT, deltaTime * cameraSpeed);

    }


}

void ApplicationRenderer::DrawDebugModelAABB( const cAABB& aabb)
{
    
  
        glm::vec3 targetExtents = 0.5f * (aabb.maxV - aabb.minV);
        glm::vec3 center = 0.5f * (aabb.minV + aabb.maxV);

        Model* debugCube = new Model(*defaultBox);
        debugCube->transform.SetPosition(center);
        debugCube->transform.SetRotation(glm::vec3(0));
        debugCube->transform.SetScale(targetExtents);
        //render.AddModelsAndShader(debugCube, defaultShader);
        debugCube->isWireFrame = true;
        debugCube->Draw(*lightShader);



    
}

void ApplicationRenderer::DrawDebugBvhNodeAABB(BvhNode* node)
{
    if (node ==nullptr)
    {
        return;
    }
    //if (node->nodeIndex == recusiveCount)
    //{
    //    DrawDebugModelAABB(node->GetModelAABB());
    //   return;
    //}

    if (node->trianglesIndex.size() != 0)
    {
        DrawDebugModelAABB(node->UpdateAABB());
    }

    if (node->leftChild == nullptr) return;

    DrawDebugBvhNodeAABB(node->leftChild);
    DrawDebugBvhNodeAABB(node->rightChild);


}




 void ApplicationRenderer::SetViewPort(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

 void ApplicationRenderer::KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
 {  
         if (key == GLFW_KEY_V && action == GLFW_PRESS)
         {

            
             std::cout << "V pressed" << std::endl;

             std::vector<Model*> listOfModels = render.GetModelList();
            


             selectedModelCount++;

             if (selectedModelCount > listOfModels.size()-1)
             {
                 selectedModelCount = 0;
             }

            
             render.selectedModel = listOfModels[selectedModelCount];


         }

         if (key == GLFW_KEY_X && action == GLFW_PRESS)
         {
             render.selectedModel = nullptr;

         }
         if (key == GLFW_KEY_C && action == GLFW_PRESS)
         {
             cameraMoveToTarget = !cameraMoveToTarget;
             camera.SetTargetPosition(CamPlaceholder->transform.position);

             if (cameraMoveToTarget)
             {
                 //camera.Position = glm::vec3(0);
             }
         }
         if (key == GLFW_KEY_1 && action == GLFW_PRESS)
         {
             
             camera.SetTargetPosition(CamPlaceholder->transform.position);

              
         }

         if (key == GLFW_KEY_2 && action == GLFW_PRESS)
         {

             camera.SetTargetPosition(plant2->transform.position);

             //cameraMoveToTarget = !cameraMoveToTarget;

         }

         if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
         {
             recusiveCount--;
         }
         if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
         {
             recusiveCount++;
         }
         if (key == GLFW_KEY_R && action == GLFW_PRESS)
         {
             TeaTable->transform.position.x += 5;
             TeaTable->transform.SetRotation(glm::vec3(
                 TeaTable->transform.rotation.x + 30, TeaTable->transform.rotation.y, TeaTable->transform.rotation.z));
             TeaTable->transform.scale.x += 5;
             TeaTable->transform.scale.y += 5;
             TeaTable->transform.scale.z += 5;
         }
         
 }

 void ApplicationRenderer::MouseCallBack(GLFWwindow* window, double xposIn, double yposIn)
 {

    float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);
     
        if (firstMouse)
        {

        }

         if (firstMouse)
         {
             lastX = xpos;
             lastY = ypos;
             firstMouse = false;
         }
     
         float xoffset = xpos - lastX;
         float yoffset = lastY - ypos;
     
         lastX = xpos;
         lastY = ypos;
     
         if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
         {
             camera.ProcessMouseMovement(xoffset, yoffset);
         }
 }

 void ApplicationRenderer::MouseScroll(GLFWwindow* window, double xoffset, double yoffset)
 {
     camera.ProcessMouseScroll(static_cast<float>(yoffset));
 }
