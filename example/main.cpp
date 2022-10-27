#include <ljgl.hpp>
int main(){
    GLFWwindow* window = LJGL::init(512, 512, "LJGL Example", 3, 3);
    LJGL::camera cam(window); // Create a camera object, this also sets up callbacks
    LJGL::model_EBO object("suzanne"); // Create a model object
    object.m_shader.createShader("GLSL/shader.vert.glsl", "GLSL/shader.frag.glsl");
    object.m_shader.setUniform3f("lightPos", 3.0f, 1.0f, 2.0f);
    while (!glfwWindowShouldClose(window)){
        cam.processInput(); // Process camera movement (WASD), mouse movement and scrolling is handled by a callback. Also processes ESC/clicking to determine if the mouse should be captured
        object.m_view = cam.getViewMatrix(); // Get the view matrix from the camera object
        object.m_projection = cam.getPerspectiveMatrix(); // Update the projection matrix
        object.m_model = glm::rotate(object.m_model, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color and depth buffer
        object.draw(); // Draw the object
        glfwSwapBuffers(window); // Swap the buffers
        glfwPollEvents(); // Poll for events
    }
    return 0;
}