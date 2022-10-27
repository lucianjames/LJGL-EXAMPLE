#include <ljgl.hpp>

int main(){
    // Take user input for the object to load
    std::string objToLoad;
    std::cout << "Enter the object to load: ";
    std::cin >> objToLoad;

    // === Set up a GLFW window, and init GLAD ===
    GLFWwindow* window = LJGL::init(512, 512, "LJGL Example", 3, 3);

    // === Create GL objects ===
    LJGL::camera cam(window); // Create a camera object, this also sets up callbacks
    LJGL::model_EBO object(objToLoad); // Create a model object
    object.m_shader.createShader("GLSL/shader.vert.glsl", "GLSL/shader.frag.glsl");
    object.m_shader.setUniform3f("lightPos", 3.0f, 1.0f, 2.0f);

    // === Main loop === //
    while (!glfwWindowShouldClose(window)){
        // === Camera movement ===
        cam.processMovement(); // Process camera movement (WASD)
        object.m_view = cam.getViewMatrix(); // Get the view matrix from the camera object
        object.m_projection = cam.getPerspectiveMatrix(); // Update the projection matrix

        // === Model movement ===
        object.m_model = glm::rotate(object.m_model, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        // === Render ===
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color and depth buffer
        object.draw();

        // === Swap buffers ===
        glfwSwapBuffers(window);
        glfwPollEvents();

        // === Close window if escape is pressed ===
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){ glfwSetWindowShouldClose(window, true); }
    }

    return 0;
}
