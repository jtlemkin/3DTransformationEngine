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
#include "Util.h"
#include "PixelBuffer.h"

/****set in main()****/
//the number of pixels in the grid
size2 grid_size;

//the size of pixels sets the inital window height and width
//don't make the pixels too large or the screen size will be larger than
//your display size
int pixel_size;

/*Window information*/
size2 win_size;

void init();
void idle();
void display();
void recordPixel(vector2 loc, pixel pix);
void reshape(int width, int height);
void key(unsigned char ch, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void check();
void drawPixels();

pixelBuffer pb;

int main(int argc, char **argv)
{
  srand(1);

  //the number of pixels in the grid
  grid_size = makeSize2(128, 128);

  //the size of pixels sets the inital window height and width
  //don't make the pixels too large or the screen size will be larger than
  //your display size
  pixel_size = 4;

  /*Window information*/
  win_size = makeSize2(grid_size.height * pixel_size, grid_size.width * pixel_size);

  /* MAIN STUFF */
  pb = makePixelBuffer(grid_size, pixel_size);

  /*Set up glut functions*/
  /** See https://www.opengl.org/resources/libraries/glut/spec3/spec3.html ***/

  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  /*initialize variables, allocate memory, create buffers, etc. */
  //create window of size (win_width x win_height
  glutInitWindowSize(win_size.width,win_size.height);
  glutCreateWindow("Project 1");

  /*defined glut callback functions*/
  glutDisplayFunc(display); //rendering calls here
  glutReshapeFunc(reshape); //update GL on window size change
  glutMouseFunc(mouse);     //mouse button events
  glutPassiveMotionFunc(motion);   //mouse movement events
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
  //checks for OpenGL errors
  check();
}

//called repeatedly when glut isn't doing anything else
/*void idle()
{
    //redraw the scene over and over again
    glutPostRedisplay();
}*/

//this is where we render the screen
void display()
{
  //clears the screen
  glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
  //clears the opengl Modelview transformation matrix
  glLoadIdentity();

  displayBuffer(pb);

  //blits the current opengl framebuffer on the screen
  glutSwapBuffers();
  //checks for opengl errors
  check();
}

/*Gets called when display size changes, including initial craetion of the display*/
void reshape(int width, int height)
{
  /*set up projection matrix to define the view port*/
  //update the ne window width and height
  win_size.width = width;
  win_size.height = height;

  //creates a rendering area across the window
  glViewport(0,0,width,height);
  // up an orthogonal projection matrix so that
  // the pixel space is mapped to the grid space
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0,grid_size.width,0,grid_size.height,-10,10);

  //clear the modelview matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  //set pixel size based on width, if the aspect ratio
  //changes this hack won't work as well
  pixel_size = width/(float)grid_size.width;

  //set pixel size relative to the grid cell size
  glPointSize(pixel_size);
  //check for opengl errors
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
  int grid_x = (int)(x/pixel_size);
  int grid_y = (int)((win_size.height-y)/pixel_size);

  pixel p = getPixelAt(makeVector2(grid_x, grid_y), pb);

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
    printf ("MOUSE AT PIXEL: %d %d, GRID: %d %d\n",x,y,grid_x,grid_y);
    //printf("BUTTON UP\n");
  } else { //button clicked
    //printf("BUTTON DOWN\n");

    //mouse2 = makeVector2(x, y);
  }

  /*if (mouse1.x >= 0 && mouse2.x >= 0) {
      Line line = Line(mouse1, mouse2, coords.at(0));
      line.drawBresenham();

      mouse1 = makeVector2(-1, -1);
      mouse2 = makeVector2(-1, -1);
  }*/

  //redraw the scene after mouse click
  glutPostRedisplay();
}

//gets called when the curser moves accross the scene
void motion(int x, int y)
{
  //redraw the scene after mouse movement
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
