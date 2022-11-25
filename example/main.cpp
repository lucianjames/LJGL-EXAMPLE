#include <ljgl.hpp>
int main(){
    GLFWwindow* window = LJGL::init(1024, 1024, "LJGL Example", 3, 3);
    LJGL::camera cam(window);
    unsigned int maxInstanceCount = 10000;
    LJGL::instancedModel suzanne(maxInstanceCount);
    suzanne.readVBO("normalSuzanne.vbo");
    suzanne.readEBO("normalSuzanne.ebo");
    suzanne.m_shader.createShader("GLSL/shader.vert.glsl", "GLSL/shader.frag.glsl");
    suzanne.m_shader.setUniform3f("lightPos", 1.0f, 2.0f, 4.0f);
    suzanne.m_shader.setUniform3f("objectColor", 1.0f, 0.5f, 0.25f);
    suzanne.m_texture.createTexture("cpp.png");
    for(int i=0; i<maxInstanceCount; i++){
        suzanne.addInstancePoint((rand() % 1000) / 100.0f, (rand() % 1000) / 100.0f, (rand() % 1000) / 100.0f);
    }
    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        cam.processInput();
        suzanne.m_projection = cam.getPerspectiveMatrix();
        suzanne.m_view = cam.getViewMatrix();
        suzanne.draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}