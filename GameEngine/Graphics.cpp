#define _USE_MATH_DEFINES

#include "Graphics.h"

#include <SOIL.h>
#include <math.h>

#include "Shader.h"

Shader sh;

void Graphics::init()
{
	sh = Shader("testshader.vert", "testshader.frag");
	sh.use();

	sh.setFloat("ambientStrength", 0.05);

	sh.setVector3("spherePos", Vector3(-5, 5, 20));
	sh.setVector3("camPos", Vector3(0, 10, 0));
	sh.setVector3("camRot", Vector3(.3f, 0, 0));

	glEnable(GL_DEPTH_TEST);
}

void Graphics::end()
{
}

/*
void doThing(float fov) {
	int width = renderData->getWidth();
	int height = renderData->getHeight();
	float ratio = width / (float)height;

	//vector<Ray> rays;

	Vector3 spherePoint(0, 0, (float)glfwGetTime());
	Vector3 light(-50, 50, 50);
	float intensity = 50000;
	float radius = 2;

	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			Ray r = rays[y * width + x];

			Color col = Color(255, 0, 0);

			///////////////////////////
			Vector3 a = r.getOrigin();
			Vector3 n = r.getDirection();
			Vector3 ap = a - spherePoint;
			Vector3 toRay = ap - (ap.dot(n)) * n;

			Vector3 collisionPoint = toRay.normal() * radius;///////////////////////////

			//Vector3 c = spherePoint;
			//Vector3 o = r.getOrigin();
			Vector3 l = r.getDirection();
			Vector3 oc = r.getOrigin() - spherePoint;
			float loc = l.dot(oc);
			float del = sq(loc) - (oc.dot(oc) - sq(radius));
			float d1 = -loc + del;
			float d2 = -loc - del;

			Vector3 collisionPoint = r.getOrigin() + r.getDirection() * min(d1, d2);

			//del = 0 means one collision, del > 0 means two collisions, del < 0 means no collisions
			if (del >= 0) {
				col = Color(0, 0, 255);

				Vector3 toLight = light - collisionPoint;
				Vector3 normal = (collisionPoint - spherePoint).normal();
				float lightDist = toLight.magnitude();
				float sphereDist = (light - spherePoint).magnitude();

				//if (lightDist > sphereDist)
					//c = Color(0, 0, 0);
				//else {
					float brightness = normal.dot(toLight.normal());//intensity / (4 * M_PI * lightDist * lightDist);
					brightness = clamp(brightness, 0.2f, 1.0f);
					col = Color(col.r * brightness, col.g * brightness, col.b * brightness, col.a);
				//}
			}
			
			//println(D.magnitude());

			renderData->setPixel(x, y, col);
		}
	}
}*/

void Graphics::preRender()
{
}

void Graphics::render()
{
	float ratio;
	int width, height;

	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / (float)height;

	//Set a screen width and height because for some reason they aren't built into GLSL
	sh.setFloat("width", width);
	sh.setFloat("height", height);

	//Set object variables that change every frame
	sh.setVector3("lightPos", Vector3(cosf((float)glfwGetTime()) * 10, 10, 20 + sinf((float)glfwGetTime()) * 10));
	sh.setVector3("boxRot", Vector3(0, glfwGetTime(), 0));
	sh.setVector3("objColor", Vector3(1, 1, 1));

	glViewport(0, 0, width, height);
	//I don't know why drawing a single quad should need the depth buffer enabled, but everyting goes black when I turn it off.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Draw quad that fills the whole sceen.
	//Everything gets rendered onto this quad
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, -1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, -1.0, -1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1);
	glEnd();
}

void Graphics::postRender()
{
}