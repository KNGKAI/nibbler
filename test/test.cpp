#include <cstdlib>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

void init(void)
{
    glClearColor(0.0,0.0,0.0,0.0); //clear background color to black
    glColor3f(1.0,0.0,0.0);  //set drawing color to red
    //Setup the standard orthogonal view
    //This is a defult setting and the following statements could be removed
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-100.0,100.0,-100.0,100.0);
} 

void setPixel(int x, int y)
{
    glPointSize(2.0);
    glBegin(GL_POINTS);
    glColor3f(1, 1, 1);
    glVertex2i(x,y);
    glEnd();
    // flush the drawing to screen . 
    glFlush(); 
}
// Display callback ------------------------------------------------------------

void display()
{
    // clear the draw buffer .
    glClear(GL_COLOR_BUFFER_BIT);   // Erase everything

    // set the color to use in draw
    glColor3f(0.5, 0.5, 0.0);       
    // create a polygon ( define the vertexs) 
    glBegin(GL_POLYGON);
    {           
        glVertex2f(-0.5, -0.5);
        glVertex2f(-0.5,  0.5);
        glVertex2f( 0.5,  0.5);
        glVertex2f( 0.5, -0.5);
    }
    glEnd();
    // flush the drawing to screen . 
    glFlush(); 
}

// Keyboard callback function ( called on keyboard event handling )
void keyboard(unsigned char key, int x, int y)
{
    if (key == 'q' || key == 'Q')
        exit(EXIT_SUCCESS);
}

// Main execution  function 
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);      // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("OpenGL example");  // Create a window
    glutDisplayFunc(display);   // Register display callback
    glutKeyboardFunc(keyboard); // Register keyboard callback
    glutMainLoop();             // Enter main event loop

    return (EXIT_SUCCESS);
}










int main()
{
    Game game(GAME_WIDTH, GAME_HEIGHT);
    char c;
    
    WINDOW *w = initscr(); 
    nodelay(w, true);
    noecho();
    raw();
    curs_set(FALSE);
    cbreak();
    keypad(w, true);
    while (true)
    {
        switch (int ch = getch())
        {
            case KEY_UP:
                game.Turn(Down);
                break;
            case KEY_DOWN:
                game.Turn(Up);
                break;
            case KEY_LEFT:
                game.Turn(Left);
                break;
            case KEY_RIGHT:
                game.Turn(Right);
                break;
            default:
                break;
        }
        clear();
        game.DrawFrame();
        refresh();
    }
    endwin();
    return (0);
}