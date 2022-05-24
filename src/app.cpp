#include "gl_error_handling.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_array.h"
#include "shader.h"

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
        std::cout << "Error in glewInit" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    
    
    
    /* --------------------------------- Buffer Setup --------------------------------- */


    float positions[] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f,
    };

    unsigned indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    VertexArray* va = new VertexArray();
    VertexBuffer* vb = new VertexBuffer(positions, 4 * 2 * sizeof(float));
    VertexBufferLayout* layout = new VertexBufferLayout();
    layout->push<float>(2);
    va->addBuffer(vb, layout);
    IndexBuffer* ib = new IndexBuffer(indices, 6);


    // shaders
    Shader* shader = new Shader("res/shaders/vertex_shaders/basic_vertex_shader.shader", "res/shaders/fragment_shaders/basic_fragment_shader.shader");
    shader->bind();

    // uniforms (set once per draw)
    shader->setUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

    // unbinding buffers and shaders
    shader->unbind();
    va->unbind();
    vb->unbind();
    ib->unbind();
    
    
    
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);



        shader->bind();
        va->bind();
        ib->bind();
        GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));      // draw from index buffer



        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    delete vb;
    delete ib;
    delete layout;
    delete va;
    delete shader;

    glfwTerminate();
    return 0;
}