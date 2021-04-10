#include "HelloGL.h"
#include "GLUTCallbacks.h"
#include "MeshLoader.h"

Sphere sphere1;
Sphere sphere2;

HelloGL::HelloGL(int argc, char* argv[])
{
	InitGL(argc,argv);
	InitObjects();
	initSpheres();
	Light();
	Update();
	glutMainLoop();
}

void HelloGL::InitGL(int argc, char* argv[])
{
	GLUTCallbacks::Init(this);
	glutInit(&argc, argv);
	glEnable(GL_DEPTH_TEST);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(900, 900);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Simple OpenGL Program");
	glutDisplayFunc(GLUTCallbacks::Display);
	glutTimerFunc(REFRESHRATE, GLUTCallbacks::Timer, REFRESHRATE);
	glutKeyboardFunc(GLUTCallbacks::Keyboard);
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
	Mesh* cubeMesh = MeshLoader::Load((char*)"cube.txt");
	Mesh* pyramidMesh = MeshLoader::Load((char*)"pyramid.txt");

	Texture2D* texture = new Texture2D();
	texture->Load((char*)"Penguins.raw", 512, 512);

	Texture2D* texture1 = new Texture2D();
	texture1->Load((char*)"Stars.raw", 512, 512);

	for (int i = 0; i < 1; i++)
	{
		objects[i] = new Cube(cubeMesh, texture, (-4.0f), (0.0f), (-15.0f));
	}

	for (int i = 0; i < 1; i++)
	{
		object2[i] = new Cube(cubeMesh, texture, (4.0f), (0.0f), (-15.0f));
	}

	camera->eye.x = 0.0f; camera->eye.y = 0.0f; camera->eye.z = 1.0f;
	camera->center.x = 0.0f; camera->center.y = 0.0f; camera->center.z = 0.0f;
	camera->up.x = 0.0f; camera->up.y = 1.0f; camera->up.z = 0.0f;
}

void HelloGL::initSpheres()
{
	sphere1.radius = 1.0f;
	sphere2.radius = 1.0f;

	sphere1.position.x = -1.5f;
	sphere2.position.x = 1.5f;
}

void HelloGL::Light()
{
	_lightPosition = new Vector4();
	_lightPosition->x = 0.0;
	_lightPosition->y = 0.0;
	_lightPosition->z = 1.0;
	_lightPosition->w = 0.0;

	_lightData = new Lighting();
	_lightData->Ambient.x = 0.2;
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

HelloGL::~HelloGL(void)
{
	delete camera;
	for (int i =0; i < 1;  i++)
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

void HelloGL::Display()
{
	Vector3 v = { -0.04f, 0.037f, 0.9f };
	Color c = { 255.0f, 255.0f, 255.0f };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < 1; i++)
	{
		objects[i]->Draw();
	}

	for (int i = 0; i < 1; i++)
	{
		object2[i]->Draw();
	}
	DrawString("SCORE: Example", &v, &c);

	float distance = calculateDistanceSquared(sphere1, sphere2);
	drawSpheres(distance, true);
	glutSwapBuffers();
	glFlush(); 
}

void HelloGL::Update()
{
	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_AMBIENT, &(_lightData->Ambient.x));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &(_lightData->Diffuse.x));
	glLightfv(GL_LIGHT0, GL_SPECULAR, &(_lightData->Specular.x));
	glLightfv(GL_LIGHT0, GL_POSITION, &(_lightPosition->x));
	for (int i = 0; i < 1; i++)
	{
		objects[i]->Update();
	}
	gluLookAt(camera->eye.x, camera->eye.y, camera->eye.z, camera->center.x, camera -> center.y, camera->center.z, camera->up.x, camera->up.y, camera->up.z);
	glutPostRedisplay();

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
	else if (key == 'a')
	{
		for (int i = 0; i < 1; i++)
		{
			objects[i]->move(key, x, y);
		}
	}
	else if (key == 's')
	{
		for (int i = 0; i < 1; i++)
		{
			objects[i]->move(key, x, y);
		}
	}
}

void HelloGL::reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void HelloGL::DrawString(const char* text, Vector3* position, Color* color)
{
	glPushMatrix();
	glTranslatef(position->x, position->y, position->z);
	glRasterPos2f(0.0f, 0.0f);
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text);
	glPopMatrix();
}

void HelloGL::drawSpheres(float distance, bool distanceSquared)
{
	float radiusDistance;
	if (distanceSquared)
	{
		radiusDistance = pow(sphere1.radius + sphere2.radius, 2);
	}
	else
	{
		radiusDistance = sphere1.radius + sphere2.radius;
	}

	//Draw Sphere 1

	glPushMatrix();

	if (distance <= radiusDistance)
	{
		glColor3f(1, 0, 0);
	}
	else
	{
		glColor3f(0, 0, 1);
	}


	glTranslatef(sphere1.position.x, sphere1.position.y, sphere1.position.z);
	glBegin(GL_POINTS);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	glutWireSphere(sphere1.radius, 20, 20);
	glPopMatrix();

	//Draw Sphere 2
	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(sphere2.position.x, sphere2.position.y, sphere2.position.z);
	glBegin(GL_POINTS);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	glutWireSphere(sphere2.radius, 20, 20);
	glPopMatrix();
}


float HelloGL::calculateDistanceSquared(Sphere s1, Sphere s2)
{
	float distance = ((s1.position.x - s2.position.x) * (s1.position.x - s2.position.x))
		+ ((s1.position.y - s2.position.y) *
			(s1.position.y - s2.position.y))
		+ ((s1.position.z - s2.position.z) *
			(s1.position.z - s2.position.z));
	return distance;
}