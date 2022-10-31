#include <ljgl.hpp>
int main(){
    GLFWwindow* window = LJGL::init(1024, 1024, "LJGL Example", 3, 3);
    LJGL::world testWorld(window);
    unsigned int suzanne = testWorld.createAddModel_EBO("suzanneLOW");
    testWorld.models[suzanne]->m_shader.createShader("GLSL/shader.vert.glsl", "GLSL/shader.frag.glsl");
    testWorld.models[suzanne]->m_shader.setUniform3f("lightPos", 0.0f, 0.0f, 1.0f);
    testWorld.models[suzanne]->m_shader.setUniform3f("objectColor", 1.0f, 1.0f, 1.0f);
    while(!glfwWindowShouldClose(window)){
        unsigned int newSuzanne = testWorld.createAddModel_EBO("suzanneLOW");
        testWorld.models[newSuzanne]->m_shader.createShader("GLSL/shader.vert.glsl", "GLSL/shader.frag.glsl");
        testWorld.models[newSuzanne]->m_shader.setUniform3f("lightPos", 0.0f, 0.0f, 1.0f);
        testWorld.models[newSuzanne]->m_shader.setUniform3f("objectColor", rand() % 100 / 100.0f, rand() % 100 / 100.0f, rand() % 100 / 100.0f);
        testWorld.models[newSuzanne]->m_model = glm::translate(testWorld.models[newSuzanne]->m_model, glm::vec3(rand() % 40 - 20, rand() % 40 - 20, rand() % 40 - 20));
        testWorld.processInput();
        testWorld.render();
    }
    return 0;
}