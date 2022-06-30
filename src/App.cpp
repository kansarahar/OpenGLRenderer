#include "GLErrorHandling.h"
#include "Mesh.h"
#include "Geometry.h"
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

    std::vector<Vertex> cube_vertices = {
          // position                        // normal                            // color                           // texture

        // front face
        { glm::vec3(-0.5f, -0.5f,  0.5f),    glm::vec3( 0.0f,  0.0f,  1.0f),      glm::vec3(1.0f, 0.0f, 0.0f),       glm::vec2(0.0f, 0.0f) }, // 0
        { glm::vec3( 0.5f, -0.5f,  0.5f),    glm::vec3( 0.0f,  0.0f,  1.0f),      glm::vec3(1.0f, 0.0f, 0.0f),       glm::vec2(1.0f, 0.0f) }, // 1
        { glm::vec3( 0.5f,  0.5f,  0.5f),    glm::vec3( 0.0f,  0.0f,  1.0f),      glm::vec3(1.0f, 0.0f, 0.0f),       glm::vec2(1.0f, 1.0f) }, // 2
        { glm::vec3(-0.5f,  0.5f,  0.5f),    glm::vec3( 0.0f,  0.0f,  1.0f),      glm::vec3(1.0f, 0.0f, 0.0f),       glm::vec2(0.0f, 1.0f) }, // 3

        // right face
        { glm::vec3( 0.5f, -0.5f,  0.5f),    glm::vec3( 1.0f,  0.0f,  0.0f),      glm::vec3(0.0f, 1.0f, 0.0f),       glm::vec2(0.0f, 0.0f) }, // 4
        { glm::vec3( 0.5f, -0.5f, -0.5f),    glm::vec3( 1.0f,  0.0f,  0.0f),      glm::vec3(0.0f, 1.0f, 0.0f),       glm::vec2(1.0f, 0.0f) }, // 5
        { glm::vec3( 0.5f,  0.5f, -0.5f),    glm::vec3( 1.0f,  0.0f,  0.0f),      glm::vec3(0.0f, 1.0f, 0.0f),       glm::vec2(1.0f, 1.0f) }, // 6
        { glm::vec3( 0.5f,  0.5f,  0.5f),    glm::vec3( 1.0f,  0.0f,  0.0f),      glm::vec3(0.0f, 1.0f, 0.0f),       glm::vec2(0.0f, 1.0f) }, // 7

        // back face
        { glm::vec3( 0.5f, -0.5f, -0.5f),    glm::vec3( 0.0f,  0.0f, -1.0f),      glm::vec3(1.0f, 1.0f, 0.0f),       glm::vec2(0.0f, 0.0f) }, // 8
        { glm::vec3(-0.5f, -0.5f, -0.5f),    glm::vec3( 0.0f,  0.0f, -1.0f),      glm::vec3(1.0f, 1.0f, 0.0f),       glm::vec2(1.0f, 0.0f) }, // 9
        { glm::vec3(-0.5f,  0.5f, -0.5f),    glm::vec3( 0.0f,  0.0f, -1.0f),      glm::vec3(1.0f, 1.0f, 0.0f),       glm::vec2(1.0f, 1.0f) }, // 10
        { glm::vec3( 0.5f,  0.5f, -0.5f),    glm::vec3( 0.0f,  0.0f, -1.0f),      glm::vec3(1.0f, 1.0f, 0.0f),       glm::vec2(0.0f, 1.0f) }, // 11

        // left face
        { glm::vec3(-0.5f, -0.5f, -0.5f),    glm::vec3(-1.0f,  0.0f,  0.0f),      glm::vec3(0.0f, 0.0f, 1.0f),       glm::vec2(0.0f, 0.0f) }, // 12
        { glm::vec3(-0.5f, -0.5f,  0.5f),    glm::vec3(-1.0f,  0.0f,  0.0f),      glm::vec3(0.0f, 0.0f, 1.0f),       glm::vec2(1.0f, 0.0f) }, // 13
        { glm::vec3(-0.5f,  0.5f,  0.5f),    glm::vec3(-1.0f,  0.0f,  0.0f),      glm::vec3(0.0f, 0.0f, 1.0f),       glm::vec2(1.0f, 1.0f) }, // 14
        { glm::vec3(-0.5f,  0.5f, -0.5f),    glm::vec3(-1.0f,  0.0f,  0.0f),      glm::vec3(0.0f, 0.0f, 1.0f),       glm::vec2(0.0f, 1.0f) }, // 15

        // top face
        { glm::vec3(-0.5f,  0.5f,  0.5f),    glm::vec3( 0.0f,  1.0f,  0.0f),      glm::vec3(1.0f, 0.0f, 1.0f),       glm::vec2(0.0f, 0.0f) }, // 16
        { glm::vec3( 0.5f,  0.5f,  0.5f),    glm::vec3( 0.0f,  1.0f,  0.0f),      glm::vec3(1.0f, 0.0f, 1.0f),       glm::vec2(1.0f, 0.0f) }, // 17
        { glm::vec3( 0.5f,  0.5f, -0.5f),    glm::vec3( 0.0f,  1.0f,  0.0f),      glm::vec3(1.0f, 0.0f, 1.0f),       glm::vec2(1.0f, 1.0f) }, // 18
        { glm::vec3(-0.5f,  0.5f, -0.5f),    glm::vec3( 0.0f,  1.0f,  0.0f),      glm::vec3(1.0f, 0.0f, 1.0f),       glm::vec2(0.0f, 1.0f) }, // 19

        // bottom face
        { glm::vec3(-0.5f, -0.5f, -0.5f),    glm::vec3( 0.0f, -1.0f,  0.0f),      glm::vec3(0.0f, 1.0f, 1.0f),       glm::vec2(0.0f, 0.0f) }, // 20
        { glm::vec3( 0.5f, -0.5f, -0.5f),    glm::vec3( 0.0f, -1.0f,  0.0f),      glm::vec3(0.0f, 1.0f, 1.0f),       glm::vec2(1.0f, 0.0f) }, // 21
        { glm::vec3( 0.5f, -0.5f,  0.5f),    glm::vec3( 0.0f, -1.0f,  0.0f),      glm::vec3(0.0f, 1.0f, 1.0f),       glm::vec2(1.0f, 1.0f) }, // 22
        { glm::vec3(-0.5f, -0.5f,  0.5f),    glm::vec3( 0.0f, -1.0f,  0.0f),      glm::vec3(0.0f, 1.0f, 1.0f),       glm::vec2(0.0f, 1.0f) }, // 23
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

    Geometry cube_geometry(cube_vertices, cube_indices);
    Mesh* cube_mesh = new Mesh(cube_geometry, textures);
    Mesh* light_mesh = new Mesh(cube_geometry, textures);

    // shaders
    Shader* shader = new Shader("res/shaders/vertex_shaders/VertexShaderWithLighting.shader", "res/shaders/fragment_shaders/FragmentShaderWithLighting.shader");
    Shader* light_caster_shader = new Shader("res/shaders/vertex_shaders/LightCasterVertexShader.shader", "res/shaders/fragment_shaders/LightCasterFragmentShader.shader");

    shader->bind();
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
        glm::mat4 light_caster_model = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, -5.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));
        //model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 view = cam->getViewMatrix();                                                       // world -> camera view
        glm::mat4 projection = cam->getProjMatrix();                                                 // camera -> clip
        // glm::mat4 model = glm::rotate(transform_matrix, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        // glm::mat4 projection = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, 0.1f, 1.0f) * transform_matrix;

        shader->bind();
        shader->setUniformMatrix4f("u_proj", projection);
        shader->setUniformMatrix4f("u_view", view);
        shader->setUniformMatrix4f("u_model", model);
        shader->setUniform3f("u_light_color", 1.0f, 1.0f, 1.0f);
        shader->setUniform1f("u_ambient_strength", 0.1f);

        light_caster_shader->bind();
        light_caster_shader->setUniformMatrix4f("u_proj", projection);
        light_caster_shader->setUniformMatrix4f("u_view", view);
        light_caster_shader->setUniformMatrix4f("u_model", light_caster_model);
        light_caster_shader->setUniform3f("u_light_color", 1.0f, 1.0f, 1.0f);

        /* Draw */
        renderer->draw(cube_mesh, shader);
        renderer->draw(light_mesh, light_caster_shader);

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
