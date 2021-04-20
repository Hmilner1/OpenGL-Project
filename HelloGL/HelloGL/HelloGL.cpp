#include "HelloGL.h"
//bools to draw correct shapes
bool cubes = false;
bool pyramid = false;
bool sphere = false;
bool intro = true;
HelloGL::HelloGL(int argc, char* argv[])
{
	//calls all relivent functions
	InitGL(argc,argv);
	InitObjects();
	Light();
	Update();
	glutMainLoop();
}

HelloGL::~HelloGL(void)
{
	//deconstructor
	delete camera;
	for (int i = 0; i < 1; i++)
	{
		delete objects[i];
	}
	for (int i = 0; i < 1; i++)
	{
		delete object2[i];
	}
	for (int i = 0; i < 1; i++)
	{
		delete object3[i];
	}
	delete _lightData;
	delete _lightPosition;
}

void mainMenuHandler(int choice)
{	
	//handles the the menu selections
	switch (choice)
	{
	//sets the relivent shape to true and the rest to false
	case 1:
		cubes = true;
		pyramid = false;
		sphere = false;
		intro = false;
		break;
	case 2:
		pyramid = true;
		cubes = false;
		sphere = false;
		intro = false;
		break;
	case 3:
		sphere = true;
		cubes = false;
		pyramid = false;
		intro = false;
			break;
	case 4:
		exit(0);
		break;
	}
}

void HelloGL::InitGL(int argc, char **argv)
{
	//sets up the window and its information
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glEnable(GL_DEPTH_TEST);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(900, 900);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Shape Generator");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	//sub shape menu
	int sub1 = glutCreateMenu(mainMenuHandler);
	glutAddMenuEntry("Cube", 1);
	glutAddMenuEntry("Pyramid", 2);
	glutAddMenuEntry("Sphere", 3);
	//main menu
	glutCreateMenu(mainMenuHandler);
	glutAddSubMenu("Shapes", sub1);
	glutAddMenuEntry("Exit", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 800, 800);
	gluPerspective(45, 1, 1, 1000);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_CULL_FACE);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glCullFace(GL_BACK);
}

void HelloGL::InitObjects()
{
	//creates new camera
	camera = new Camera();
	//loads in the shapes information from the correct file 
	Mesh* cubeMesh = MeshLoader::Load((char*)"Cube.txt");
	Mesh* pyramidMesh = MeshLoader::Load((char*)"pyramid.txt");

	//loads the textures from files 
	Texture2D* texture = new Texture2D();
	texture->Load((char*)"crate.raw", 512, 512);
	Texture2D* texture1 = new Texture2D();
	texture1->Load((char*)"Start.raw", 512, 512);
	Texture2D* texture2 = new Texture2D();
	texture2->Load((char*)"cone.raw", 512, 512);

	//loads cube and sets position and texture 
	for (int i = 0; i < 1; i++)
	{
		objects[i] = new Cube(cubeMesh, texture, (-4.0f), (0.0f), (-15.0f));
	}
	for (int i = 0; i < 1; i++)
	{
		object3[i] = new Cube(cubeMesh, texture1, (0.0f), (0.0f), (-2.4f));
	}
	//loads pyramid and sets position and texture 
	for (int i = 0; i < 1; i++)
	{
		object2[i] = new Pyramid(pyramidMesh, texture2, (4.0f), (0.0f), (-15.0f));
	}
	//sets sphere position 
	sphere1.radius = 1.0f;
	sphere1.position.x = -1.5f;
	sphere1.position.z = -15.0f;
	//sets camera position 
	camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	//handles all user inputs and controls 
	//cube
	if (key == 'd')
	{
		for (int i = 0; i < 1; i++)
		{
			objects[i]->move(key, x, y);
		}
	}
	if (key == 'a')
	{
		for (int i = 0; i < 1; i++)
		{
			objects[i]->move(key, x, y);
		}
	}
	if (key == 's')
	{
		for (int i = 0; i < 1; i++)
		{
			objects[i]->move(key, x, y);
		}
	}
	//sphere
	if (key == 'q')
	{
		sphere1.position.x = sphere1.position.x - 0.1f;
	}
	if (key == 'e')
	{
		sphere1.position.x = sphere1.position.x + 0.1f;
	}
	//camera
	if (key == 'r')
	{
		camera->eye.z += 0.1f;
	}
	if (key == 'f')
	{
		camera->eye.z -= 0.1f;
	}
}

void HelloGL::Display()
{
	//text position and colour 
	Vector3 v = { -0.25f, 1.2f, -2.1f };
	Color c = { 255.0f, 255.0f, 255.0f };
	//resetsfoe eatch shape
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//displays the correct shape depending on what is chosen
	if (intro == true)
	{
		for (int i = 0; i < 1; i++)
		{
			object3[i]->Draw();

		}
	}
	if (cubes == true)
	{
		for (int i = 0; i < 1; i++)
		{
			objects[i]->Draw();
			DrawString("Cube", &v, &c); 
		}
	}
	if (pyramid == true)
	{
		for (int i = 0; i < 1; i++)
		{
			object2[i]->Draw();
			DrawString("Pyramid", &v, &c);
		}
	}
	if (sphere == true)
	{
		drawSpheres();
		DrawString("Sphere", &v, &c);
	}
	glutSwapBuffers();
	glFlush();
}

void HelloGL::drawSpheres()
{
	//handles sphere
	glTranslatef(sphere1.position.x, sphere1.position.y, sphere1.position.z);
	glBegin(GL_POINTS);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	glutSolidSphere(sphere1.radius, 20, 20);
	glPopMatrix();
}

void HelloGL::DrawString(const char* text, Vector3* position, Color* color)
{
	//handles text
	glPushMatrix();
	glTranslatef(position->x, position->y, position->z);
	glRasterPos2f(0.0f, 0.0f);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text);
	glPopMatrix();
}

void HelloGL::Light()
{
	//defines lighting information 
	_lightPosition = new Vector4();
	_lightPosition->x = 0.0;
	_lightPosition->y = 0.0;
	_lightPosition->z = 1.0;
	_lightPosition->w = 0.0;
	_lightData = new Lighting();
	_lightData->Ambient.x = 0.1;
	_lightData->Ambient.y = 0.2;
	_lightData->Ambient.z = 0.2;
	_lightData->Ambient.w = 1.0;
	_lightData->Diffuse.x = 0.8;
	_lightData->Diffuse.y = 0.8;
	_lightData->Diffuse.z = 0.8;
	_lightData->Diffuse.w = 1.0;
	_lightData->Specular.x = 0.2;
	_lightData->Specular.y = 0.2;
	_lightData->Specular.z = 0.2;
	_lightData->Specular.w = 1.0;
}

void HelloGL::Update()
{
	//lighting update
	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->Specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));
	//updates the correct shape 
	if (cubes == true)
	{
		for (int i = 0; i < 1; i++)
		{
			objects[i]->Update();
		}
	}
	if (pyramid == true)
	{
		for (int i = 0; i < 1; i++)
		{
			object2[i]->Update();
		}
	}
	//updates camera
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera -> center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	glutPostRedisplay();
}