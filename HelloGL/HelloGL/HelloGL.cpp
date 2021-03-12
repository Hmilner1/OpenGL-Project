#include "HelloGL.h"
#include "GLUTCallbacks.h"
#include "MeshLoader.h"

HelloGL::HelloGL(int argc, char* argv[])
{
	InitGL(argc,argv);
	InitObjects();
	glutMainLoop();
}

void HelloGL::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glEnable(GL_DEPTH_TEST);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Simple OpenGL Program");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 800, 800);
	gluPerspective(45, 1, 0, 1000);
	glEnable(GL_CULL_FACE);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glCullFace(GL_BACK);
}

void HelloGL::InitObjects()
{
	camera = new Camera();
	Mesh* cubeMesh = MeshLoader::Load((char*)"cube.txt");
	Mesh* pyramidMesh = MeshLoader::Load((char*)"pyramid.txt");

	Texture2D* texture = new Texture2D();
	texture->Load((char*)"Penguins.raw", 512, 512);

	for (int i = 0; i < 500; i++)
	{
		objects[i] = new Cube(cubeMesh, texture, ((rand() % 400) / 10.0f) - 20.0f, ((rand() %
			200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
	}
	for (int i = 500; i < 1000; i++)
	{
		objects[i] = new Pyramid(pyramidMesh,((rand() % 400) / 10.0f) - 20.0f,
			((rand() % 200) / 10.0f) - 10.0f, -(rand() % 1000) / 10.0f);
	}

	camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 5.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;
}

HelloGL::~HelloGL(void)
{
	delete camera;
	for (int i =0; i < 1000;  i++)
	{ 
		delete objects[i];
	}
}

void HelloGL::Display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < 1000; i++)
	{
		objects[i]->Draw();
	}
	glutSwapBuffers();
	glFlush(); 
}

void HelloGL::Update()
{
	glLoadIdentity();
	for (int i = 0; i < 1000; i++)
	{
		objects[i]->Update();
	}
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera -> center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	glutPostRedisplay();

}

void HelloGL::Keyboard(unsigned char key, int x, int y)
{
	if (key == 'e')
	{
		camera->eye.x += 0.1f;
		camera->center.x += 0.1f;
	}
	else if (key == 'q')
	{
		camera->eye.x -= 0.1f;
		camera->center.x -= 0.1f;
	}
	else if (key == 's')
	{
		camera->eye.z += 0.1f;
		camera->center.z += 0.1f;
	}
	else if (key == 'w')
	{
		camera->eye.z -= 0.1f;
		camera->center.z -= 0.1f;
	}
}
