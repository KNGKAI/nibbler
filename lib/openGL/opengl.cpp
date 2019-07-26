#include "opengl.hpp"
#include "ncurses.h"
#include "Game.hpp"

OpenGL::OpenGL()
{
    this->command = nullptr;
}
OpenGL::~OpenGL()
{
    return;
}

void OpenGL::open()
{
    if (this->init) { return; }
    glfwInit();
    this->window = glfwCreateWindow(500, 500, "Nibbler OpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);
    this->init = true;
}

void OpenGL::close()
{
    if (this->init) { glfwTerminate(); }
}

int OpenGL::getCommand()
{
    if (this->command == nullptr)
        return -1;
    return this->command->command;
}

void OpenGL::processInput()
{
    int command;

    command = 0;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) { command = 32; }
    else if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { command = 27; }
    else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) { command = KEY_UP; }
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) { command = KEY_DOWN; }
    else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) { command = KEY_LEFT; }
    else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) { command = KEY_RIGHT; }
    else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) { command = 49; }
    else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) { command = 50; }
    else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) { command = 51; }
    c_queue * node = new c_queue;
    node->command = command;
    node->next = this->command;
    this->command = node;
}
void OpenGL::render(Map &m)
{
    float a;
    float b;
    float w;
    float h;

    glClear(GL_COLOR_BUFFER_BIT);
    //Draw background
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_POLYGON);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(-1.0f, 1.0f);
    glEnd();
    w = 1.0f / m.GetWidth() * 2;
    h = 1.0f / m.GetHeight() * 2;
    for (int x = 0; x < m.GetWidth(); x++)
    {
        for (int y = 0; y < m.GetHeight(); y++)
        {
            a = (float)(x) / m.GetWidth() * 2 - 1;
            b = (float)(y) / m.GetHeight() * 2 - 1;
            switch (m.GetNode(x, y))
            {
                case NODE_EMPTY:
                    glColor3f(0.0f, 0.0f, 0.0f);
                    break;
                case NODE_WALL:
                    glColor3f(1.0f, 0.0f, 0.0f);
                    break;
                case NODE_PLAYER:
                    glColor3f(0.0f, 0.0f, 1.0f);
                    break;
                case NODE_TREAT:
                    glColor3f(0.0f, 1.0f, 0.0f);
                    break;                
                default:
                    glColor3f(1.0f, 0.0f, 1.0f);
                    break;
            }
            this->drawCell(a, b, w, h);
        }
    }
    glFlush();
    glfwSwapBuffers(window);
    glfwPollEvents(); 
}

void OpenGL::drawCell(float x, float y, float w, float h)
{
    glBegin(GL_POLYGON);
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x, y + h);
    glEnd();
}