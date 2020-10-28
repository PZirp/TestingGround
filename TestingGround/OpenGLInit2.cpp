#include "OpenGLInit2.h"
#include "Shader.h"
#include "stb_image.h"
#include "Camera.h"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_inverse.hpp>

const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 900;

void framebuffer_size_callback2(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput2(GLFWwindow* window, float* alpha);
int loadTexture(std::string path, int textureUnit, int samplerLocation, Shader& shader);
void moveLight(glm::vec3& lightPosition, bool* reverse);

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int OpenGLInit2::openGLInit2()
{
    //Setup finestra e context

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

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback2);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwWindowHint(GLFW_SAMPLES, 4);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_BLEND);// you enable blending function
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    //Fine setup finestra e context

    Shader squareshader("C:/Users/oeoxi/source/repos/TestingGround/TestingGround/shaders/vertexShaderSquare.vs", "C:/Users/oeoxi/source/repos/TestingGround/TestingGround/shaders/fragmentShaderSquare.fs");
    Shader lightSourceShader("C:/Users/oeoxi/source/repos/TestingGround/TestingGround/shaders/lightSource.vs", "C:/Users/oeoxi/source/repos/TestingGround/TestingGround/shaders/lightSource.fs");
   
    // set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------

    float squareVertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    unsigned int squareIndices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle        
    };

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
 
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f,  0.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
 
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f
    };

    unsigned int VAOs, EBOs, VBOs;
    glGenVertexArrays(1, &VAOs);
    glGenBuffers(1, &VBOs);
    //glGenBuffers(1, &EBOs);

    /*Inizializzo VAO del quadrato con VBO e EBO*/
    glBindVertexArray(VAOs);
    /*glBindBuffer binda il buffer su cui vogliamo lavorare al momento. glBufferData riempe il buffer con i dati che gli diamo, Fino a quando non lo bindiamo il buffer è solo memoria senza
    valore. Il binding specifica cosa ci finisce dentro*/
    glBindBuffer(GL_ARRAY_BUFFER, VBOs);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //Per adesso non sto usando l'indexed rendering quindi l'ebo non mi serve
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(squareIndices), squareIndices, GL_STATIC_DRAW);
    
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    /*Vertex attribute binding per il quadrato*/
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
    
    //Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //Normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float))); //Non uso i vertex color al momento - Sostituito con le normali dei vertici
    glEnableVertexAttribArray(1);
    //UV
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.

    glBindVertexArray(0);
    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //Non sto usando l'EBO quindi non c'è nulla di bindato 

    //Modello della fonte di luce
    unsigned int VAOl, VBOl;
    glGenVertexArrays(1, &VAOl);
    glGenBuffers(1, &VBOl);
    glBindVertexArray(VAOl);
    glBindBuffer(GL_ARRAY_BUFFER, VBOl);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //Fine setup dei modelli

    /*Creazione texture*/

    int texture1 = loadTexture("../TestingGround/textures/container2.png", 0, 4, squareshader);
    int texture2 = loadTexture("../TestingGround/textures/container2_specular.png", 1, 5, squareshader);
       
    //Fine creazione texture

    //Inputs
    float alpha = 0.0f;
    float angle = 0;
    float currentFrame = 0;

    //Matrici
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection;    
    glm::mat3 normalMatrix;

    glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 lightPosition = glm::vec3(0.0f, 0.0f, 5.0f); //E' usata nello shader del cubo di luce per muoverlo, e poi viene convertita in Camera/Eye space per essere usata nello shader del cubo per calcolare l'illuminazione
    bool reverse = false; 

    while (!glfwWindowShouldClose(window))
    {

        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput2(window, &alpha);

        //moveLight(lightPosition, &reverse);

        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);        

        lightSourceShader.use();
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPosition);
        
        model = glm::scale(model, glm::vec3(0.2f));
        glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(camera.GetViewMatrix()));
        glUniformMatrix4fv(2, 1, GL_FALSE, glm::value_ptr(projection));
        //glUniform3fv(3, 1, glm::value_ptr(glm::vec3(0.0f, 1.0f, 0.0f)));
        glUniform3fv(3, 1, glm::value_ptr(lightColor));

        glBindVertexArray(VAOl);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        projection = glm::perspective(glm::radians(camera.Zoom), 1600.0f / 900.0f, 0.1f, 100.0f);        

        squareshader.use();
        glUniform1f(12, alpha);    
        glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(projection)); //Vertex shader
        glUniformMatrix4fv(2, 1, GL_FALSE, glm::value_ptr(camera.GetViewMatrix())); //Vertex shader
        
        // Elementi della struct material
        glActiveTexture(GL_TEXTURE0); 
        glBindTexture(GL_TEXTURE_2D, texture1); //Diffuse ed Ambient Texture
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2); //Specular texture
        glUniform1f(6, 128.0f); //Shininess

        // Elementi della struct light        
        glm::vec4 eyeSpaceLightPosition = glm::vec4(lightPosition, 1.0f);
        eyeSpaceLightPosition = camera.GetViewMatrix()* eyeSpaceLightPosition;
        glm::vec3 eyeSpaceLightPositionV3 = glm::vec3(eyeSpaceLightPosition);

        glUniform3fv(7, 1, glm::value_ptr(eyeSpaceLightPositionV3));

        glUniform3fv(8, 1, glm::value_ptr(glm::vec3(0.1f, 0.1f, 0.1f))); //Intensità e colore dell'ambient
        glUniform3fv(9, 1, glm::value_ptr(lightColor)); //Intensità e colore della luce diffuse
        glUniform3fv(10, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f))); //Specular power

        // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized - Ora abbiamo più di un vao quindi serve bindarlo
        glBindVertexArray(VAOs);

        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        for (unsigned int i = 0; i < 10; i++) {
            //Setto la posizione dell'i-esimo cubo con la model matrix
            model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, (float) glfwGetTime() * glm::radians(-55.0f), glm::vec3(1.0f, 1.0f, 1.0f));
            
            //Calcolo la matrice delle normali dei vertici per l'illuminazione e la passo allo shader
            //La matrice delle normali è l'inversa trasposta della model matrix. Dato che la vogliamo in camera space, moltiplichiamo model matrix per view matrix e poi facciamo la trasposta inversa
            normalMatrix = glm::inverseTranspose(glm::mat3(camera.GetViewMatrix() * model)); 
            glUniformMatrix3fv(3, 1, GL_FALSE, glm::value_ptr(normalMatrix));

            //carico la matrice dell'i-esimo cubo nello shader
            glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(model));            

            //Disegno il cubo 
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // glBindVertexArray(0); // no need to unbind it every time 

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    //glDeleteVertexArrays(1, &VAO);
   // glDeleteBuffers(1, &VBO);
  //  glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback2(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void processInput2(GLFWwindow* window, float* alpha)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);    

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        *alpha += 0.05f;
    }
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        *alpha -= 0.05f;
    }

}

int loadTexture(std::string path, int textureUnit, int samplerLocation, Shader& shader)
{
    int height, width, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* textureData = stbi_load(path.c_str(), &height, &width, &nrChannels, 0);

    unsigned int texture;

    //glActiveTexture(GL_TEXTURE0); si usa per decidere a quale texture unit legare la texture che stai caricando. Da 0 a 15. Devi prima attivarla e poi fare il bind della texture
    //Dopo aver caricato la texture dal disco, si usa glGenTExture per generare la texture, e ritorna un handle alla texture (che è solo un uint).
    //Poi si attiva la texture unit che si vuole usare e si fa il bind. Poi si possono settare tutte le varie opzioni su come la texture deve comportarsi

    if (textureData != nullptr) {
        glGenTextures(1, &texture);
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_2D, texture);
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

    stbi_image_free(textureData);

    //Associo le texture unit all'uniform nello shader. Dopo aver caricato la texture e averla bindata ad una texture unit, va associata ad un sampler nello shader. 
    //glUniform1i(2, 0); in questa chiamata il primo argomento è il numero della location dell'uniform sampler da associare alla texture, il secondo è il numero della texture unit 
    // Il primo sampler2d è associato automaticamente, quindi la texture in TEXTURE0 funziona sempre, ma se non associ le texture seguenti, opengl userà sempre la prima texture che gli hai dato 

    shader.use();
    glUniform1i(samplerLocation, textureUnit);
    return texture;
}

void moveLight(glm::vec3& lightPosition, bool* reverse)
{
    if (!*reverse) {
        lightPosition[2] = lightPosition[2] - (deltaTime * 10);
        if (lightPosition[2] <= -15.0f) {
        *reverse = true;
        }
    } else if (*reverse) {
        lightPosition[2] = lightPosition[2] + (deltaTime * 10);
        if (lightPosition[2] >= 5.0f) {
        *reverse = false;
        }
    }
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}