#include "OpenGLInit.h"
#include "Shader.h"
#include "stb_image.h"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, float* alpha);

int OpenGLInit::openGLInit()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1600, 900, "BEST THING IN THE WORLD", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader shader("C:/Users/oeoxi/source/repos/TestingGround/TestingGround/vShader.vs", "C:/Users/oeoxi/source/repos/TestingGround/TestingGround/fShader.fs");
    Shader shaderx("C:/Users/oeoxi/source/repos/TestingGround/TestingGround/vShader.vs", "C:/Users/oeoxi/source/repos/TestingGround/TestingGround/fShader2.fs");
    Shader squareshader("C:/Users/oeoxi/source/repos/TestingGround/TestingGround/squareVertexShader.vs", "C:/Users/oeoxi/source/repos/TestingGround/TestingGround/fShader3.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
    float vertices[] = {
         0.4f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,// top right
         0.4f, -0.4f, 0.0f,  0.0f, 1.0f, 0.0f,// bottom right
        -0.4f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f, // top left 
    };


    float verticesx[] = {
    0.3f, -0.4f, 0.0f,  // bottom right
        -0.5f, -0.4f, 0.0f,  // bottom left
        -0.5f, 0.4f, 0.0f   // top left 
    };

    float squareVertices[] = {
        // positions          // colors           // texture coords
         0.17f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.17f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    unsigned int indices[] = {  // note that we start from 0!
        //0, 1, 3,  // first Triangle
        //1, 2, 3   // second Triangle
        0,1,2,
        //  3,4,5
    };

    unsigned int squareIndices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle        
    };

    unsigned int VBO, VAO, EBO, VBOx, VAOx, VAOs, EBOs, VBOs;
    glGenVertexArrays(1, &VAO);
    glGenVertexArrays(1, &VAOs);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBOs);
    glGenBuffers(1, &EBOs);
    glGenVertexArrays(1, &VAOx);
    glGenBuffers(1, &VBOx);

    /*Inizializzo VAO del quadrato con VBO e EBO*/
    glBindVertexArray(VAOs);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs);
    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(squareIndices), squareIndices, GL_STATIC_DRAW);
    /*Vertex attribute binding per il quadrato*/
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    /*glBindBuffer binda il buffer su cui vogliamo lavorare al momento. glBufferData riempe il buffer con i dati che gli diamo, Fino a quando non lo bindiamo il buffer è solo memoria senza
    valore. Il binding specifica cosa ci finisce dentro*/
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
   // glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        /*Praticamente nello shader tu crei delle variabili in certe posizioni. Supponiamo in queste variabili ci siano la posizione di un vertice, e il colore.
    Tu crei un VBO, lo bindi, e ci metti dentro posizioni e colori (da un array qualunque).
    Poi queste info come vengono interpretate da OpenGL?
    Nello shader, quegli attributi sono solo dei vec3, e ci puoi mettere quello che ti pare.
    Quindi, devi dire a OpenGL che cosa sono rispettivamente.
    Lo facciamo con glVertexAttribPointer. Questa funzione praticamente fa questo: in posizione #, l'attributo ha n componenti, di tipo int/float/che è, è normalizzato o no, lo stride  e da dove iniziare a leggere
    in quel buffer.
    Quindi con la prima chiamata diamo un senso al vec3 tre della posizione, per esempio, e con la seconda gli diciamo come interpretare i colori.
    glVertexAttribPointer è specifico per i vertici, e sa come interpretare un buffer craeto con GL_ARRAY_BUFFER (quindi un VBO). Se l'attributo nello shader è un uniform, o un sampler, si usa
    glUniform o altro.*/

    glBindVertexArray(VAOx);
    glBindBuffer(GL_ARRAY_BUFFER, VBOx);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesx), verticesx, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    /*Creazione texture*/
    int height, width, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* textureData = stbi_load("../TestingGround/textures/container.jpg", &height, &width, &nrChannels, 0);

    unsigned int texture1;
    
    if (textureData != nullptr) {        
        glGenTextures(1, &texture1);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    } 
    
    stbi_image_free(textureData);

    textureData = stbi_load("../TestingGround/textures/ciao.png", &height, &width, &nrChannels, 0);

    unsigned int texture2;

    if (textureData != nullptr) {
        glGenTextures(1, &texture2);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    //Associo le texture unit all'uniform nello shader
    squareshader.use();
    glUniform1i(2, 0);
    glUniform1i(3, 1);

    glEnable(GL_BLEND);// you enable blending function
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glViewport(0, 0, 1600, 900);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    float alpha = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        processInput(window, &alpha);

        glClearColor(0.2f, 0.2f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        shader.use();
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        //glUniform1i(2, 1);
        //shader.setInt(2,1)j
        shader.setFloat(0, 0.5f);;
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        shaderx.use();
        glUniform4f(2, 0.0f, greenValue, 0.0f, 1.0f);
        shaderx.setFloat(0, 0.5f);
        glBindVertexArray(VAOx);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);


        //Transform square
       // glm::mat4 trans1 = glm::mat4(1.0f);
        //trans1 = glm::rotate(trans1, glm::radians(45.0f), glm::vec3(0.0, 0.0, 1.0));
        //trans1 = glm::translate(trans1, glm::vec3(0.5f, -0.5f, 0.0f));
        //trans1 = glm::rotate(trans1, (float) glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        //float scaleAmount = sin(glfwGetTime());
        //trans1 = glm::scale(trans1, glm::vec3(scaleAmount, scaleAmount, scaleAmount));

       /*glm::mat4 projection;
       projection = glm::ortho(0.0f, 1600.0f, 0.0f, 900.0f, 0.1f, 100.0f);
       glm::mat4 view = glm::mat4(1.0f);
       view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));*/

        squareshader.use();
        squareshader.setFloat(0,-0.4f);  //Offset
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glBindVertexArray(VAOs);
        glUniform1f(4, alpha);
       // glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(trans1));
       // glUniformMatrix4fv(5, 1, GL_FALSE, glm::value_ptr(projection));
       // glUniformMatrix4fv(6, 1, GL_FALSE, glm::value_ptr(view));
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glBindVertexArray(0); // no need to unbind it every time 

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, float* alpha)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        *alpha += 0.05f;
    }
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        *alpha -= 0.05f;
    }
        

}