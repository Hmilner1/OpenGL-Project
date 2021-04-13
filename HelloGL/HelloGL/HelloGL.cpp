#include "HelloGL.h"
bool cubes = false;
bool pyramid = false;
bool sphere = false;

HelloGL::HelloGL(int argc, char* argv[])
{
	InitGL(argc,argv);
	InitObjects();
	Light();
	Update();
	glutMainLoop();
}

HelloGL::~HelloGL(void)
{
	delete camera;
	for (int i = 0; i < 1; i++)
	{
		delete objects[i];
	}
	for (int i = 0; i < 1; i++)
	{
		delete object2[i];
	}
	delete _lightData;
	delete _lightPosition;
}

void mainMenuHandler(int choice)
{	
	switch (choice)
	{
	case 1:
		cubes = true;
		break;
	case 2:
		pyramid = true;
		break;
	case 3:
		sphere = true;
			break;
	case 4:
		exit(0);
		break;
	}
}

void HelloGL::InitGL(int argc, char **argv)
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glEnable(GL_DEPTH_TEST);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(900, 900);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Shape Generator");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);

	int sub1 = glutCreateMenu(mainMenuHandler);
	glutAddMenuEntry("Cube", 1);
	glutAddMenuEntry("Pyramid", 2);
	glutAddMenuEntry("Sphere", 3);

	glutCreateMenu(mainMenuHandler);
	glutAddSubMenu("Shapes", sub1);
	glutAddMenuEntry("Exit", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 800, 800);
	gluPerspective(45, 1, 0, 1000);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_CULL_FACE);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glCullFace(GL_BACK);
}

void HelloGL::InitObjects()
{
	camera = new Camera();
	Mesh* cubeMesh = MeshLoader::Load((char*)"Cube.txt");
	Mesh* pyramidMesh = MeshLoader::Load((char*)"pyramid.txt");

	Texture2D* texture = new Texture2D();
	texture->Load((char*)"crate.raw", 512, 512);

	Texture2D* texture1 = new Texture2D();
	texture1->Load((char*)"Cone.raw", 512, 512);


	for (int i = 0; i < 1; i++)
	{
		objects[i] = new Cube(cubeMesh, texture, (-4.0f), (0.0f), (-15.0f));
	}

	for (int i = 0; i < 1; i++)
	{
		object2[i] = new Pyramid(pyramidMesh, texture1, (4.0f), (0.0f), (-15.0f));
	}

	sphere1.radius = 1.0f;
	sphere1.position.x = -1.5f;
	sphere1.position.z = -15.0f;

	camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;
}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
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
	if (key == 'q')
	{
		sphere1.position.x = sphere1.position.x - 0.1f;
	}
	if (key == 'e')
	{
		sphere1.position.x = sphere1.position.x + 0.1f;
	}
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
	Vector3 v = { -0.25f, 1.2f, -2.1f };
	Color c = { 255.0f, 255.0f, 255.0f };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	DrawString("Shape Generator", &v, &c);
	if (cubes == true)
	{
		for (int i = 0; i < 1; i++)
		{
			objects[i]->Draw();
		}
	}

	if (pyramid == true)
	{
		for (int i = 0; i < 1; i++)
		{
			object2[i]->Draw();
		}
	}
	
	if (sphere == true)
	{
		drawSpheres();
	}
	glutSwapBuffers();
	glFlush();
}

void HelloGL::drawSpheres()
{
	glTranslatef(sphere1.position.x, sphere1.position.y, sphere1.position.z);
	glBegin(GL_POINTS);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	glutWireSphere(sphere1.radius, 20, 20);
	glPopMatrix();
}

void HelloGL::DrawString(const char* text, Vector3* position, Color* color)
{
	glPushMatrix();
	glTranslatef(position->x, position->y, position->z);
	glRasterPos2f(0.0f, 0.0f);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text);
	glPopMatrix();
}

void HelloGL::Light()
{
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
	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->Specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));
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
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera -> center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	glutPostRedisplay();
}