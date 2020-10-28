#include "OpenGLInit.h"
#include "Shader.h"
#include <iostream>


const char* vertexShaderSource = "#version 430 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"   ourColor = aColor;\n"
"}\0";

const char* fragmentShaderSource = "#version 430 core\n"
"in vec3 ourColor;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor, 1.0f);\n"
"}\n\0";

const char* fragmentShaderSourcex = "#version 430 core\n"
"out vec4 FragColor;\n"
"layout (location = 0) uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"/*vec4(0.0f, 1.0f, 1.0f, 1.0f);\n*/
"}\n\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

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


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    /*int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shaderx
    int fragmentShaderx = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderx, 1, &fragmentShaderSourcex, NULL);
    glCompileShader(fragmentShaderx);
    // check for shader compile errors
    glGetShaderiv(fragmentShaderx, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShaderx, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    //glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // link shadersx
    int shaderProgramx = glCreateProgram();
    glAttachShader(shaderProgramx, vertexShader);
    glAttachShader(shaderProgramx, fragmentShaderx);
    glLinkProgram(shaderProgramx);
    // check for linking errors
    glGetProgramiv(shaderProgramx, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramx, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderx);*/

    Shader shader("C:/Users/oeoxi/source/repos/TestingGround/TestingGround/vShader.vs", "C:/Users/oeoxi/source/repos/TestingGround/TestingGround/fShader.fs" );
    Shader shaderx("C:/Users/oeoxi/source/repos/TestingGround/TestingGround/vShader.vs", "C:/Users/oeoxi/source/repos/TestingGround/TestingGround/fShader2.fs");
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
    
    unsigned int indices[] = {  // note that we start from 0!
        //0, 1, 3,  // first Triangle
        //1, 2, 3   // second Triangle
        0,1,2,
      //  3,4,5
    };

    unsigned int VBO, VAO, EBO, VBOx, VAOx;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAOx);
    glGenBuffers(1, &VBOx);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

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
    


    glViewport(0, 0, 1600, 900);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.2f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
       // glUseProgram(shaderProgram);
        shader.use();
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        //int vertexColorLocation = glGetUniformLocation(shaderProgramx, "ourColor");
       // glUseProgram(shaderProgramx);
        shaderx.use();
        glUniform4f(0, 0.0f, greenValue, 0.0f, 1.0f);

        glBindVertexArray(VAOx);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        // glBindVertexArray(0); // no need to unbind it every time 

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    //glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}