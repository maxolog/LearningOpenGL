#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <shader_s.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);



// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;



int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif



    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    //float vertices[] = {
    //     0.5f,  0.5f, 0.0f,  // top right
    //     0.5f, -0.5f, 0.0f,  // bottom right
    //    -0.5f, -0.5f, 0.0f,  // bottom left
    //    -0.5f,  0.5f, 0.0f  // top left 
    //};


    // build and compile shader program using the shader class 
    //----------------------------------------------------------
    Shader changingColorTriangle("shaders/3.3.shaderSourceChangingColorTrig.vs", "shaders/3.3.fragmentSourceChangingColorTrig.fs");
    // creating shader program for the second triangle using shader class
    Shader rgbTriangle("shaders/3.3.shaderSourceRGBTrig.vs", "shaders/3.3.fragmentSourceRGBTrig.fs");

    float vertRGBTriangle[] = {
        // first triangle
         0.0f,  -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.9f, 1.2f,  // bott left
         0.25f, 0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  0.9f, 0.2f,  // top
         0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  -0.1f, 0.2f  // bott right
    };
    unsigned int indRGBTriangle[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    float vertColorChangeTriangle[] = {
     // second triangle pos 
        -0.5f, 0.0f, 0.0f, //bott left
        0.0, 0.5f, 0.0f,   // top
        0.0, 0.0, 0.0,     // bott right
    };



    unsigned int RGBTrigVBO, RGBTrigVAO, RGBTrigEBO;
    unsigned int ColorChangeTriangleVBO, ColorChangeTriangleVAO, ColorChangeTriangleEBO;

    // creating VAO VBO EBO for trinagle1
    glGenVertexArrays(1, &RGBTrigVAO);
    glGenBuffers(1, &RGBTrigVBO);
    glGenBuffers(1, &RGBTrigEBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(RGBTrigVAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, RGBTrigVBO); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertRGBTriangle), vertRGBTriangle, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RGBTrigEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indRGBTriangle), indRGBTriangle, GL_STATIC_DRAW);


    //poss attrib
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //texture coord attribuite
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    

    //creating VAO VBO EBO for trinagle2
    glGenVertexArrays(1, &ColorChangeTriangleVAO);
    glGenBuffers(1, &ColorChangeTriangleVBO);
    glGenBuffers(1, &ColorChangeTriangleEBO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(ColorChangeTriangleVAO);

    //setting up VBO 
    glBindBuffer(GL_ARRAY_BUFFER, ColorChangeTriangleVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertColorChangeTriangle), vertColorChangeTriangle, GL_STATIC_DRAW);

    //setting up EBO
    //glBindBuffer(GL_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indTriangle2), indTriangle2, GL_STATIC_DRAW);

    //setting up how to read vertex data for triangle 2
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);



    //load and create a texture
    //----------------------------------------
    unsigned int seriiTexture;
    glGenTextures(1, &seriiTexture);
    glBindTexture(GL_TEXTURE_2D, seriiTexture);

    //set the texture wrapping/filtering options on the current bound texture obj
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load("textures/fnaf.jpeg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else 
    {
        std::cout << "FAILED TO LOAD TEXTURE" << std::endl;
    }

    //freeing texture data
    stbi_image_free(data);




    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    //toogle to switch barckground light
    // bool toggle = false;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        //rendering commands
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        // //renderinf two sreen color based on a flag toggle
        // if (toggle) {
        //    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        //    toggle = false;
        // }
        // else {
        //    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        //    toggle = true;
        // }
        
        glClear(GL_COLOR_BUFFER_BIT);

        //glUseProgram(shaderProgram);
        rgbTriangle.use();

        glBindTexture(GL_TEXTURE_2D, seriiTexture);
        glBindVertexArray(RGBTrigVAO);


        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);



        changingColorTriangle.use();

        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(changingColorTriangle.ID, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        float offset = -0.5f;
        changingColorTriangle.setFloat("xOffset", offset);


        glBindVertexArray(ColorChangeTriangleVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }



    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}






// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
