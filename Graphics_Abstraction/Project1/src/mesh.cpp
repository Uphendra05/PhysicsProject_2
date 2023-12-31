#include "mesh.h"
#include <string>
#include "Renderer.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture*>& textures)
{
    
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    setupMesh();
}

void Mesh::meshDraw(Shader& shader)
{

    unsigned int diffuseNr = 0;
    unsigned int specularNr = 0;
    unsigned int alphaNr = 0;
    //unsigned int normalNr = 1;
    //unsigned int emissiveNr = 1;
   // unsigned int heightNr = 1;
   

    for (unsigned int i = 0; i < textures.size(); i++)
    {
       GLCALL(glActiveTexture(GL_TEXTURE0 + i));
        std::string number;
        std::string name = textures[i]->type;
        if (name == "material.diffuse")
        {
            number = std::to_string(diffuseNr++);
            name = "diffuse";
        }
        else if (name == "material.specular")
        {
            number = std::to_string(specularNr++);
            name = "specular";
        }
        else if (name == "alphaMask")
        {
            number = std::to_string(alphaNr++);
            name = "alphaMask";
        }

        else if (name == "starAlpha")
        {
            number = std::to_string(alphaNr++);
            name = "starAlpha";
        }


        shader.setFloat("material.shininess", 128);

        if (isTransparancy)
        {
           // GLCALL(shader.setFloat("material.alpha", 1.0f));
            GLCALL(shader.setBool("isMasking", true));
        }
        else
        {
          //  GLCALL(shader.setFloat("material.alpha", 1.0f));
           shader.setBool("isMasking", false);
        }


        if (isCutOut)
        {
            GLCALL(shader.setBool("isCutout", true));
        }
        else
        {
            GLCALL(shader.setBool("isCutout", false));

        }

        if (isTextureScrolling)
        {
            GLCALL(shader.setBool("isScrollingTexture", true));

        }
        else
        {
            GLCALL(shader.setBool("isScrollingTexture", false));

        }

        if (isColorAlpha)
        {
            GLCALL(shader.setBool("isColorMultiply", true));

        }
        else
        {
            GLCALL(shader.setBool("isColorMultiply", false));

        }



     

        shader.setInt((name), i);
         //std::cout << shader.FindUniformLocations((name + number).c_str()) << std::endl;
      //  GLCALL(glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i));

        GLCALL(glBindTexture(GL_TEXTURE_2D, textures[i]->id));
    }
    GLCALL(glActiveTexture(GL_TEXTURE0));


   VAO->Bind();
   IBO->Bind();

   if (isWireFrame)
   {
       GLCALL(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
   }
   else
   {
       GLCALL(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
   }
   
   GLCALL( glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0));
   GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
   VAO->Unbind();


  /* if (isTransparancy)
   {
       glDisable(GL_BLEND);
   }
  */

}
void Mesh::meshDrawWireFrame(Shader& shader)
{


    VAO->Bind();
    IBO->Bind();

   // if (isWireFrame)
    {
        glColor3f(1.0f, 0.0f, 0.0f);
        GLCALL(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
    }
   

    GLCALL(glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0));
    GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
    VAO->Unbind();


    /* if (isTransparancy)
     {
         glDisable(GL_BLEND);
     }
    */

}

void Mesh::SetTransparency(const bool& isTransparent)
{
    this->isTransparancy = isTransparent;
}

void Mesh::SetCutOff(const bool& isCutOut)
{

    this->isCutOut = isCutOut;

}

void Mesh::TextureScrolling(const bool& isScroll)
{

    this->isTextureScrolling = isScroll;

}

void Mesh::SetColorAlpha(const bool& colorAlpha)
{
    this->isColorAlpha = colorAlpha;

}

void Mesh::setupMesh()
{
    CalculateTriangles();
    VAO = new VertexArray();
    void* pVertices = static_cast<void*>(&vertices[0]);
    unsigned int size = vertices.size() * sizeof(Vertex);
    VBO = new VertexBuffer(pVertices, size);
    layout = new VertexBufferLayout();

    layout->Push<float>(3);
    layout->Push<float>(3);
    layout->Push<float>(2);
    layout->Push<float>(4);

    VAO->AddBuffer(*VBO, *layout);
    IBO = new IndexBufferObject(&indices[0], indices.size());

}

void Mesh::CalculateTriangles()
{
    for (size_t i = 0; i < indices.size(); i += 3)
    {
        Triangles tempTri;

        tempTri.v1 = vertices[indices[i]].Position;
        tempTri.v2 = vertices[indices[i + 1]].Position;
        tempTri.v3 = vertices[indices[i + 2]].Position;

        tempTri.normal = (vertices[indices[i]].Normal +
            vertices[indices[i + 1]].Normal +
            vertices[indices[i + 2]].Normal) / 3.0f;
        triangle.push_back(tempTri);
    }
}
