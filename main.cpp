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
#include "Scene.h"

/*Window information*/
size2 win_size;

std::vector<Scene> scene;

std::string fname;

void init();
void display();
void key(unsigned char ch, int x, int y);
void mouse(int button, int state, int x, int y);
void check();
void runHW2UI();

int main(int argc, char **argv)
{
  if (argc != 2) {
    std::cout << "Please specify the absolute file path you'd like to load the polyhedra\n";
    return -1;
  }

  srand(1);

  /*Window information*/
  win_size = makeSize2(256 * 3, 256 * 3);

  std::string temp(argv[1]);
  fname = temp;

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
  //redraw the scene after keyboard input
  glutPostRedisplay();
}

//gets called when a mouse button is pressed
void mouse(int button, int state, int x, int y)
{
  if(state !=GLUT_DOWN) {  //button released
    runHW2UI();
    glutPostRedisplay();
  }
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

void runHW2UI() {
  std::cout << "IDs of polygons are between 0 and " << scene[0].getNumPolyhedra() - 1 << "\n";
  std::cout << "Choose a command:\n";
  std::cout << "Translate: transl <POLYGON_ID> <X> <Y> <Z>\n";
  std::cout << "Rotate:    rot <POLYGON_ID> <ANGLE> <P1X> <P1Y> <P1Z> <P2X> <P2Y> <P2Z>\n";
  std::cout << "Scale:     scale <POLYGON_ID> <SCALE_FACTOR>\n";

  std::string choice;
  std::cin >> choice;

  int polygonID;
  std::cin >> polygonID;

  if (choice.compare("transl") == 0) {
    float x, y, z;
    std::cin >> x >> y >> z;

    scene[0].polyhedra[polygonID].translate(x, y, z);
  } else if (choice.compare("rot") == 0) {
    float angle;
    vector3 p1, p2;

    std::cin >> angle;
    std::cin >> p1.x >> p1.y >> p1.z >> p2.x >> p2.y >> p2.z;

    scene[0].polyhedra[polygonID].rotate(angle, p1, p2);
  } else if (choice.compare("scale") == 0) {
    float factor;
    std::cin >> factor;

    scene[0].polyhedra[polygonID].scale(factor);
  }

  scene[0].writePolyhedron(fname);

  glutPostRedisplay();
}
