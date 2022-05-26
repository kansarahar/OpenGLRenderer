#include "GLErrorHandling.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"

#include <iostream>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float y = 0.0f;
float x = 0.0f;

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        y += 0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        y -= 0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        x += 0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        x -= 0.01f;
    }
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    int window_width = 1280;
    int window_height = 960;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(window_width, window_height, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    if (glewInit() != GLEW_OK)
        std::cout << "Error in glewInit" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    
    
    
    /* Buffer Setup */

    float vertices[] = {
        // position             // color                // texture
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,       0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,       1.0f, 0.0f,
         0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,       1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,       0.0f, 1.0f,
    };

    unsigned indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray* va = new VertexArray();
    VertexBuffer* vb = new VertexBuffer(vertices, sizeof(vertices));
    IndexBuffer* ib = new IndexBuffer(indices, sizeof(indices) / sizeof(unsigned));

    va->addAttrib("position", GL_FLOAT, 3, false);
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
    while (!glfwWindowShouldClose(window)) {


        /* Process input */
        processInput(window);

        /* Render here */
        renderer->clear(GL_COLOR_BUFFER_BIT);

        /* Uniforms (set per draw) */
        glm::mat4 transform_matrix(1.0);
        transform_matrix = glm::translate(transform_matrix, glm::vec3(x, y, 0.0f));
        //transform_matrix = glm::rotate(transform_matrix, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        shader->bind();
        shader->setUniformMatrix4f("u_transform", transform_matrix);

        /* Draw */
        renderer->draw(va, shader);



        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    delete vb;
    delete ib;
    delete va;
    delete shader;
    delete wood_texture;
    delete mario_texture;
    delete renderer;
    glfwTerminate();
    return 0;
}
