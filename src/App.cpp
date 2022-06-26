#include "GLErrorHandling.h"
#include "Mesh.h"
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
    Window* window = new Window(1280, 960, "OpenGL Renderer", cam);
    
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

    std::vector<glm::vec3> cube_positions = {
        // front face
        glm::vec3(-0.5f, -0.5f,  0.5f), // 0
        glm::vec3( 0.5f, -0.5f,  0.5f), // 1
        glm::vec3( 0.5f,  0.5f,  0.5f), // 2
        glm::vec3(-0.5f,  0.5f,  0.5f), // 3

        // right face
        glm::vec3( 0.5f, -0.5f,  0.5f), // 4
        glm::vec3( 0.5f, -0.5f, -0.5f), // 5
        glm::vec3( 0.5f,  0.5f, -0.5f), // 6
        glm::vec3( 0.5f,  0.5f,  0.5f), // 7

        // back face
        glm::vec3( 0.5f, -0.5f, -0.5f), // 8
        glm::vec3(-0.5f, -0.5f, -0.5f), // 9
        glm::vec3(-0.5f,  0.5f, -0.5f), // 10
        glm::vec3( 0.5f,  0.5f, -0.5f), // 11

        // left face
        glm::vec3(-0.5f, -0.5f, -0.5f), // 12
        glm::vec3(-0.5f, -0.5f,  0.5f), // 13
        glm::vec3(-0.5f,  0.5f,  0.5f), // 14
        glm::vec3(-0.5f,  0.5f, -0.5f), // 15

        // top face
        glm::vec3(-0.5f,  0.5f,  0.5f), // 16
        glm::vec3( 0.5f,  0.5f,  0.5f), // 17
        glm::vec3( 0.5f,  0.5f, -0.5f), // 18
        glm::vec3(-0.5f,  0.5f, -0.5f), // 19

        // bottom face
        glm::vec3(-0.5f, -0.5f, -0.5f), // 20
        glm::vec3( 0.5f, -0.5f, -0.5f), // 21
        glm::vec3( 0.5f, -0.5f,  0.5f), // 22
        glm::vec3(-0.5f, -0.5f,  0.5f), // 23
    };
    std::vector<glm::vec3> cube_normals = {
        // front face
        glm::vec3( 0.0f,  0.0f,  1.0f),
        glm::vec3( 0.0f,  0.0f,  1.0f),
        glm::vec3( 0.0f,  0.0f,  1.0f),
        glm::vec3( 0.0f,  0.0f,  1.0f),

        // right face
        glm::vec3( 1.0f,  0.0f,  0.0f),
        glm::vec3( 1.0f,  0.0f,  0.0f),
        glm::vec3( 1.0f,  0.0f,  0.0f),
        glm::vec3( 1.0f,  0.0f,  0.0f),

        // back face
        glm::vec3( 0.0f,  0.0f, -1.0f),
        glm::vec3( 0.0f,  0.0f, -1.0f),
        glm::vec3( 0.0f,  0.0f, -1.0f),
        glm::vec3( 0.0f,  0.0f, -1.0f),

        // left face
        glm::vec3(-1.0f,  0.0f,  0.0f),
        glm::vec3(-1.0f,  0.0f,  0.0f),
        glm::vec3(-1.0f,  0.0f,  0.0f),
        glm::vec3(-1.0f,  0.0f,  0.0f),

        // top face
        glm::vec3( 0.0f,  1.0f,  0.0f),
        glm::vec3( 0.0f,  1.0f,  0.0f),
        glm::vec3( 0.0f,  1.0f,  0.0f),
        glm::vec3( 0.0f,  1.0f,  0.0f),

        // bottom face
        glm::vec3( 0.0f, -1.0f,  0.0f),
        glm::vec3( 0.0f, -1.0f,  0.0f),
        glm::vec3( 0.0f, -1.0f,  0.0f),
        glm::vec3( 0.0f, -1.0f,  0.0f),
    };
    std::vector<glm::vec3> cube_colors = {
        // front face
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),

        // right face
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),

        // back face
        glm::vec3(1.0f, 1.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 0.0f),

        // left face
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),

        // top face
        glm::vec3(1.0f, 0.0f, 1.0f),
        glm::vec3(1.0f, 0.0f, 1.0f),
        glm::vec3(1.0f, 0.0f, 1.0f),
        glm::vec3(1.0f, 0.0f, 1.0f),

        // bottom face
        glm::vec3(0.0f, 1.0f, 1.0f),
        glm::vec3(0.0f, 1.0f, 1.0f),
        glm::vec3(0.0f, 1.0f, 1.0f),
        glm::vec3(0.0f, 1.0f, 1.0f),
    };
    std::vector<glm::vec2> cube_textures = {
        // front face
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 1.0f),

        // right face
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 1.0f),

        // bottom face
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 1.0f),

        // left face
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 1.0f),

        // top face
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 1.0f),

        // bottom face
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 1.0f),
    };
    std::vector<unsigned> cube_indices = {
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

    // textures
    Texture* wood_texture = new Texture("res/textures/wood.png");
    Texture* mario_texture = new Texture("res/textures/mario.png");
    std::vector<Texture*> textures;
    textures.push_back(wood_texture);
    textures.push_back(mario_texture);

    std::vector<Vertex> vertices;
    std::vector<unsigned> indices;
    for (int v = 0; v < cube_positions.size(); v++)
        vertices.push_back({ cube_positions[v], cube_normals[v], cube_colors[v], cube_textures[v] });
    for (int i = 0; i < cube_indices.size(); i++)
        indices.push_back(cube_indices[i]);

    Mesh* cube_mesh = new Mesh(vertices, indices, textures);

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

        shader->bind();
        shader->setUniformMatrix4f("u_proj", projection);
        shader->setUniformMatrix4f("u_view", view);
        shader->setUniformMatrix4f("u_model", model);

        /* Draw */
        renderer->draw(cube_mesh, shader);

        /* Swap front and back buffers */
        window->swapBuffers();

        /* Poll for and process events */
        window->pollEvents();
    }

    delete shader;
    delete wood_texture;
    delete mario_texture;
    delete renderer;
    delete window; // delete window AFTER buffers have been deleted
    return 0;
}
