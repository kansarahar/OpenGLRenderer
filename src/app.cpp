#include "GLErrorHandling.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"
#include "Camera.h"
#include "Window.h"

#include <iostream>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Camera cam;

int main(void)
{
    Camera* cam = new Camera();
    Camera* cam2 = new Camera();
    Window* window = new Window(1280, 960, "Hello World", cam);
    Window* window2 = new Window(1280, 960, "Hello World2", cam2);
    window->bind();
    
    
    /* Buffer Setup */

    float plane_vertices[] = {
        // position             // normal               // color                // texture
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, -1.0f,      1.0f, 0.0f, 0.0f,       0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,     0.0f, 0.0f, -1.0f,      0.0f, 1.0f, 0.0f,       1.0f, 0.0f,
         0.5f,  0.5f, 0.0f,     0.0f, 0.0f, -1.0f,      0.0f, 0.0f, 1.0f,       1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f,     0.0f, 0.0f, -1.0f,      1.0f, 0.0f, 0.0f,       0.0f, 1.0f,
    };

    unsigned plane_indices[] = {
        0, 1, 2,
        2, 3, 0,
    };

    float cube_vertices[] = {
        // position             // normal               // color                // texture

        // front face
        -0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,      1.0f, 0.0f, 0.0f,       0.0f, 0.0f, // 0
         0.5f, -0.5f,  0.5f,     0.0f,  0.0f,  1.0f,      1.0f, 0.0f, 0.0f,       1.0f, 0.0f, // 1
         0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,      1.0f, 0.0f, 0.0f,       1.0f, 1.0f, // 2
        -0.5f,  0.5f,  0.5f,     0.0f,  0.0f,  1.0f,      1.0f, 0.0f, 0.0f,       0.0f, 1.0f, // 3

        // right face
         0.5f, -0.5f,  0.5f,     1.0f,  0.0f,  0.0f,      0.0f, 1.0f, 0.0f,       0.0f, 0.0f, // 4
         0.5f, -0.5f, -0.5f,     1.0f,  0.0f,  0.0f,      0.0f, 1.0f, 0.0f,       1.0f, 0.0f, // 5
         0.5f,  0.5f, -0.5f,     1.0f,  0.0f,  0.0f,      0.0f, 1.0f, 0.0f,       1.0f, 1.0f, // 6
         0.5f,  0.5f,  0.5f,     1.0f,  0.0f,  0.0f,      0.0f, 1.0f, 0.0f,       0.0f, 1.0f, // 7

        // back face
         0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,      1.0f, 1.0f, 0.0f,       0.0f, 0.0f, // 8
        -0.5f, -0.5f, -0.5f,     0.0f,  0.0f, -1.0f,      1.0f, 1.0f, 0.0f,       1.0f, 0.0f, // 9
        -0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,      1.0f, 1.0f, 0.0f,       1.0f, 1.0f, // 10
         0.5f,  0.5f, -0.5f,     0.0f,  0.0f, -1.0f,      1.0f, 1.0f, 0.0f,       0.0f, 1.0f, // 11

        // left face
        -0.5f, -0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,      0.0f, 0.0f, 1.0f,       0.0f, 0.0f, // 12
        -0.5f, -0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,      0.0f, 0.0f, 1.0f,       1.0f, 0.0f, // 13
        -0.5f,  0.5f,  0.5f,    -1.0f,  0.0f,  0.0f,      0.0f, 0.0f, 1.0f,       1.0f, 1.0f, // 14
        -0.5f,  0.5f, -0.5f,    -1.0f,  0.0f,  0.0f,      0.0f, 0.0f, 1.0f,       0.0f, 1.0f, // 15

        // top face
        -0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,      1.0f, 0.0f, 1.0f,       0.0f, 0.0f, // 16
         0.5f,  0.5f,  0.5f,     0.0f,  1.0f,  0.0f,      1.0f, 0.0f, 1.0f,       1.0f, 0.0f, // 17
         0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,      1.0f, 0.0f, 1.0f,       1.0f, 1.0f, // 18
        -0.5f,  0.5f, -0.5f,     0.0f,  1.0f,  0.0f,      1.0f, 0.0f, 1.0f,       0.0f, 1.0f, // 19

        // bottom face
        -0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,      0.0f, 1.0f, 1.0f,       0.0f, 0.0f, // 20
         0.5f, -0.5f, -0.5f,     0.0f, -1.0f,  0.0f,      0.0f, 1.0f, 1.0f,       1.0f, 0.0f, // 21
         0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,      0.0f, 1.0f, 1.0f,       1.0f, 1.0f, // 22
        -0.5f, -0.5f,  0.5f,     0.0f, -1.0f,  0.0f,      0.0f, 1.0f, 1.0f,       0.0f, 1.0f, // 23
    };

    unsigned cube_indices[] = {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20,
    };



    VertexArray* va = new VertexArray();
    VertexBuffer* vb = new VertexBuffer(cube_vertices, sizeof(cube_vertices));
    IndexBuffer* ib = new IndexBuffer(cube_indices, sizeof(cube_indices) / sizeof(unsigned));

    va->addAttrib("position", GL_FLOAT, 3, false);
    va->addAttrib("normal", GL_FLOAT, 3, false);
    va->addAttrib("color", GL_FLOAT, 3, false);
    va->addAttrib("texture", GL_FLOAT, 2, true);
    va->bindBuffers(vb, ib);


    // textures
    Texture* wood_texture = new Texture("res/textures/wood.png");
    Texture* mario_texture = new Texture("res/textures/mario.png");
    wood_texture->bind(0);
    mario_texture->bind(1);

    // shaders
    Shader* shader = new Shader("res/shaders/vertex_shaders/BasicVertexShader.shader", "res/shaders/fragment_shaders/BasicFragmentShader.shader");
    shader->bind();


    // uniforms (set once)
    shader->setUniform1i("u_texture0", 0);
    shader->setUniform1i("u_texture1", 1);

    Renderer* renderer = new Renderer();

    /* Loop until the user closes the window */
    while (!window->isClosed()) {

        /* Process input */
        window->processInput();

        /* Render here */
        renderer->clear();

        /* Uniforms (set per draw) */
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));            // model -> world
        //model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 view = cam->getViewMatrix();                                                       // world -> camera view
        glm::mat4 projection = cam->getProjMatrix();                                                 // camera -> clip
        // glm::mat4 model = glm::rotate(transform_matrix, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        // glm::mat4 projection = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, 0.1f, 1.0f) * transform_matrix;
        glm::mat4 transform_matrix = projection * view * model;

        shader->bind();
        shader->setUniformMatrix4f("u_transform", transform_matrix);

        /* Draw */
        renderer->draw(va, shader);



        /* Swap front and back buffers */
        window->swapBuffers();

        /* Poll for and process events */
        window->pollEvents();
    }

    delete vb;
    delete ib;
    delete va;
    delete shader;
    delete wood_texture;
    delete mario_texture;
    delete renderer;
    delete window;
    delete window2;
    return 0;
}
