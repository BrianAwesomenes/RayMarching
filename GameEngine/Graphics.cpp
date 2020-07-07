#define _USE_MATH_DEFINES

#include "Graphics.h"

#include <stdlib.h>
#include <stdio.h>
#include <SOIL.h>
#include <vector>
#include <math.h>

#include "Shader.h"
#include "Matrix.h"
#include "RenderData.h"
#include "Ray.h"
#include "print.h"
#include "Mathcros.h"

using std::vector;
using namespace math;

Shader sh;

void Graphics::init()
{
	sh = Shader("testshader.vert", "testshader.frag");
	sh.use();

	sh.setFloat("ambientStrength", 0);

	sh.setVector3("spherePos", Vector3(-5, 5, 20));
	sh.setVector3("camPos", Vector3(0, 10, 0));
	sh.setVector3("camRot", Vector3(.3f, 0, 0));

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glEnable(GL_DEPTH_TEST);
}

void Graphics::end()
{
}

float baseBrightness = 5;

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

	sh.setFloat("width", width);
	sh.setFloat("height", height);
	sh.setVector3("lightPos", Vector3(cosf((float)glfwGetTime()) * 10, 10, 20 + sinf((float)glfwGetTime()) * 10));
	sh.setVector3("boxRot", Vector3(0, glfwGetTime(), 0));

	/*
	if (renderData == nullptr || renderData->getWidth() != width || renderData->getHeight() != height) {
		renderData = new RenderData(width, height);

		println("Retarget");

		delete[] rays;
		rays = new Ray[width * height];

		int width = renderData->getWidth();
		int height = renderData->getHeight();
		float ratio = width / (float)height;

		float fov = 75;

		Vector3 origin = Vector3(0, 0, 0);

		Vector3 fwd = Vector3(0, 0, 1);
		Vector3 rgt = Vector3(1, 0, 0);
		Vector3 up = fwd.cross(rgt);

		float hDist = tanf(fov / 2);
		float vDist = hDist / ratio;

		float increment = hDist / (width / 2);
		Vector3 offset = rgt * (increment / 2) + up * (increment / 2);

		Vector3 start = origin + fwd - rgt * hDist - up * vDist;

		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				Vector3 pos = start + offset + rgt * increment * x + up * increment * y;
				Ray r = Ray(origin, pos - origin);

				rays[y * width + x] = r;
			}
		}
	}*/

	//doThing(75);

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, renderData->getData());
	//glGenerateMipmap(GL_TEXTURE_2D);

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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