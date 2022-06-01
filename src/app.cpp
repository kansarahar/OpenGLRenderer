#include "GLErrorHandling.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderer.h"
#include "Camera.h"

#include <iostream>
#include <algorithm>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Camera cam;

float delta_time = 0.0f, time_prev_frame = 0.0f, time_curr_frame = 0.0f;
void processInput(GLFWwindow* window) {
    // set up timing so that movement is at the same speed on any device
    time_curr_frame = (float)glfwGetTime();
    delta_time = time_curr_frame - time_prev_frame;
    time_prev_frame = time_curr_frame;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cam.moveForward(delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cam.moveBackward(delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cam.moveLeft(delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cam.moveRight(delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        cam.moveUp(delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
        cam.moveDown(delta_time);
    }
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

bool firstMouse = true;
float last_mouse_x = 400, last_mouse_y = 300;
void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        last_mouse_x = xpos;
        last_mouse_y = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - last_mouse_x;
    float yoffset = last_mouse_y - ypos;
    last_mouse_x = xpos;
    last_mouse_y = ypos;
    cam.rotate(xoffset, yoffset);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    cam.changeFov(-yoffset);
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

    /* Window inputs */
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);


    if (glewInit() != GLEW_OK)
        std::cout << "Error in glewInit" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    
    
    
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
    while (!glfwWindowShouldClose(window)) {


        /* Process input */
        processInput(window);

        /* Render here */
        renderer->clear();

        /* Uniforms (set per draw) */
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));            // model -> world
        //model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 view = cam.getViewMatrix();                                                       // world -> camera view
        glm::mat4 projection = cam.getProjMatrix();                                                 // camera -> clip
        // glm::mat4 model = glm::rotate(transform_matrix, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        // glm::mat4 projection = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, 0.1f, 1.0f) * transform_matrix;
        glm::mat4 transform_matrix = projection * view * model;

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
