#include <ljgl.hpp>
int main(){
    GLFWwindow* window = LJGL::init(1024, 1024, "LJGL Example", 3, 3);
    LJGL::world testWorld(window);
    unsigned int suzanne = testWorld.createAddModel_EBO("suzanneLOW");
    testWorld.models[suzanne]->m_shader.createShader("GLSL/shader.vert.glsl", "GLSL/shader.frag.glsl");
    testWorld.models[suzanne]->m_shader.setUniform3f("lightPos", 0.0f, 0.0f, 1.0f);
    
    unsigned int frame = 0;
    double startFrameTime = 0;

    while(!glfwWindowShouldClose(window)){
        if(frame%100 == 0){
            startFrameTime = glfwGetTime();
        }
        unsigned int newSuzanne = testWorld.createAddModel_EBO("suzanneLOW");
        testWorld.models[newSuzanne]->m_shader.createShader("GLSL/shader.vert.glsl", "GLSL/shader.frag.glsl");
        testWorld.models[newSuzanne]->m_shader.setUniform3f("lightPos", 0.0f, 0.0f, 1.0f);
        testWorld.models[newSuzanne]->m_model = glm::translate(testWorld.models[newSuzanne]->m_model, glm::vec3(rand() % 40 - 20, rand() % 40 - 20, rand() % 40 - 20));
        testWorld.processInput();
        testWorld.render();
        // Every 100 frames print the number of monkeys in the world, and the frame rate (frametime)
        if(frame % 100 == 0){
            std::cout << "Number of monkeys: " << testWorld.models.size() << std::endl;
            std::cout << "Frame time: " << glfwGetTime() - startFrameTime << std::endl;

        }
        frame++;
    }
    return 0;
}