#ifdef WIN32
#include <windows.h>
#endif

#if defined (__APPLE__) || defined(MACOSX)
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
//#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#else //linux
#include <GL/gl.h>
#include <GL/glut.h>
#endif

//other includes
#include <iostream>
#include "Structs/Util.h"
#include "Structs/PixelBuffer.h"
#include "Scene.h"

/*Window information*/
size2 win_size;

std::vector<Scene> scene;

void init();
void display();
void key(unsigned char ch, int x, int y);
void mouse(int button, int state, int x, int y);
void check();

int main(int argc, char **argv)
{
  srand(1);

  /*Window information*/
  win_size = makeSize2(256 * 2, 256 * 2);

  std::string fname("/Users/jameslemkin/Developer/ecs175/hw2/test_scene");
  scene.emplace_back(fname, win_size);

  /* MAIN STUFF */
  //pb = makePixelBuffer(grid_size, pixel_size);

  /*Set up glut functions*/
  /** See https://www.opengl.org/resources/libraries/glut/spec3/spec3.html ***/

  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  /*initialize variables, allocate memory, create buffers, etc. */
  //create window of size (win_width x win_height
  glutInitWindowSize(win_size.width, win_size.height);
  glutCreateWindow("Project 2");

  /*defined glut callback functions*/
  glutDisplayFunc(display); //rendering calls here
  glutMouseFunc(mouse);     //mouse button events
  glutKeyboardFunc(key);    //Keyboard events
  //glutIdleFunc(idle);       //Function called while program is sitting "idle"

  //initialize opengl variables
  init();
  //start glut event loop
  glutMainLoop();

  return 0;
}

/*initialize gl stufff*/
void init()
{
  //set clear color (Default background to white)
  glClearColor(1.0,1.0,1.0,1.0);

  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0.0, win_size.width, 0.0, win_size.height);

  //checks for OpenGL errors
  check();
}

//this is where we render the screen
void display()
{
  //clears the screen
  glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
  //clears the opengl Modelview transformation matrix
  glLoadIdentity();

  scene[0].render();

  glFlush();

  //blits the current opengl framebuffer on the screen
  glutSwapBuffers();
  //checks for opengl errors
  check();
}

//gets called when a key is pressed on the keyboard
void key(unsigned char ch, int x, int y)
{
  switch(ch)
  {
    default:
      //prints out which key the user hit
      //printf("User hit the \"%c\" key\n",ch);
      break;
  }
  //redraw the scene after keyboard input
  glutPostRedisplay();
}

//gets called when a mouse button is pressed
void mouse(int button, int state, int x, int y)
{

  /*switch(button)
  {
      case GLUT_LEFT_BUTTON: //left button
          printf("LEFT ");
          break;
      case GLUT_RIGHT_BUTTON: //right button
          printf("RIGHT ");
      default:
          printf("UNKNOWN "); //any other mouse button
          break;
  }*/

  if(state !=GLUT_DOWN) {  //button released
    printf ("MOUSE AT PIXEL: %d %d\n",x,y);
    //printf("BUTTON UP\n");
  } else { //button clicked
    //printf("BUTTON DOWN\n");
  }

  //redraw the scene after mouse click
  glutPostRedisplay();
}

//checks for any opengl errors in the previous calls and
//outputs if they are present
void check()
{
  GLenum err = glGetError();
  if(err != GL_NO_ERROR)
  {
    printf("GLERROR: There was an error %s\n",gluErrorString(err) );
    exit(1);
  }
}
