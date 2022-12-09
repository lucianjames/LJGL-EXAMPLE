#include <ljgl.hpp>
int main(){
    GLFWwindow* window = LJGL::init(1024, 1024, "LJGL Example", 3, 3);
    LJGL::camera cam(window);
    unsigned int maxInstanceCount = 10000;
    LJGL::instancedModel suzannes(maxInstanceCount);
    suzannes.readVBO("normalSuzanne.vbo");
    suzannes.readEBO("normalSuzanne.ebo");
    suzannes.m_shader.createShader("GLSL/shader.vert.glsl", "GLSL/shader.frag.glsl");
    suzannes.m_shader.setUniform3f("lightPos", 1.0f, 2.0f, 4.0f);
    suzannes.m_shader.setUniform3f("objectColor", 1.0f, 1.0f, 1.0f);
    suzannes.m_texture.createTexture("cpp.png");
    std::vector<float> instancePositions;
    for(int i=0; i<maxInstanceCount*3; i++){
        instancePositions.push_back((rand()/(float)RAND_MAX)*10.0f);
    }
    suzannes.setInstancePositions(instancePositions);
    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        cam.processInput();
        suzannes.m_projection = cam.getPerspectiveMatrix();
        suzannes.m_view = cam.getViewMatrix();
        suzannes.draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}