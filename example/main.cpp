#include <ljgl.hpp>
int main(){
    GLFWwindow* window = LJGL::init(512, 512, "LJGL Example", 3, 3);
    LJGL::world testWorld(window);
    unsigned int suzanne = testWorld.createAddModel_EBO("suzanne");
    testWorld.models[suzanne]->m_shader.createShader("GLSL/shader.vert.glsl", "GLSL/shader.frag.glsl");
    testWorld.models[suzanne]->m_shader.setUniform3f("lightPos", 10.0f, 5.0f, 2.5f);
    while(!glfwWindowShouldClose(window)){
        testWorld.processInput();
        testWorld.render();
    }
    return 0;
}