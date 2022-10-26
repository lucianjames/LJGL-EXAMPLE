#include <ljgl.hpp>

float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;
float fov = 45.0f;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
bool firstMouse = true;

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if (firstMouse){
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;
    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    yaw   += xoffset;
    pitch += yoffset;
    if(pitch > 89.0f){ pitch = 89.0f; }
    if(pitch < -89.0f){ pitch = -89.0f; }
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    fov -= (float)yoffset;
    /*
    if (fov < 1.0f){ fov = 1.0f; }
    if (fov > 45.0f){ fov = 45.0f; }
    */ // Clamping FOV is cringe, I love weird FOV
}


int main(){
    // Take user input for the object to load
    std::string objToLoad;
    std::cout << "Enter the object to load: ";
    std::cin >> objToLoad;

    // === Set up a GLFW window, and init GLAD ===
    GLFWwindow* window = LJGL::setup("3D spinning object"); // Setup function exists just to move all the boilerplate crap out of sight
    glEnable(GL_DEPTH_TEST); // Enable depth testing - emsures that objects are drawn in the right order
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Enable wireframe for model debugging
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    


    LJGL::model_EBO object;
    object.readVBO(objToLoad + ".vbo");
    object.readEBO(objToLoad + ".ebo");
    object.m_shader.createShader("GLSL/shader.vert.glsl", "GLSL/shader.frag.glsl");
    object.m_shader.setUniform3f("lightPos", 1.0f, 10.0f, 2.0f);

    // === Define transforms ===
    // === perspective/view transforms:
    int m_viewport[4]; // Stores the viewport size
    glGetIntegerv(GL_VIEWPORT, m_viewport); // Gets the viewport size
    glm::mat4 perspective = glm::perspective(glm::radians(45.0f), (float)m_viewport[2] / (float)m_viewport[3], 0.1f, 100.0f); // Define the perspective projection matrix
    glm::mat4 model = glm::mat4(1.0f); // Define a model matrix for the square

    // === Main loop === //
    while (!glfwWindowShouldClose(window)){
        // === Unbind/reset stuff (best practice or something) ===
        glUseProgram(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        // === Render ===
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Set the background color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color and depth buffer

        // Update cameraPos if the user is pressing a key
        float cameraSpeed = 0.05f;
        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){ cameraPos += cameraSpeed * cameraFront; }
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){ cameraPos -= cameraSpeed * cameraFront; }
        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){ cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed; }
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){ cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed; }

        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        object.setViewT(view);

        // Set up the perspective projection matrix to ensure that the suzanne is rendered correctly if the window is resized:
        glGetIntegerv(GL_VIEWPORT, m_viewport); // Get the viewport size (maybe code to only do upon resize? - would required messy global variables)
        perspective = glm::perspective(glm::radians(fov), (float)m_viewport[2] / (float)m_viewport[3], 0.1f, 100.0f); // Update the perspective projection matrix
        object.setProjectionT(perspective); // Set the perspective projection matrix

        // Rotate and draw the suzanne :D
        model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.5f)); // Rotate the suzanne
        object.setModelT(model); // Set the model matrix
        object.draw();

        // === Swap buffers ===
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}
