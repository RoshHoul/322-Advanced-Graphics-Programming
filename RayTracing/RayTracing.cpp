// RayTracing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//Include "pch.h" is VS header, which enables compiling the program. University computers use
// "stdafx.h" as precompiled header, so if the program won't start try changing it (here and in every class)
#include "pch.h"

#define KEY_UP 72
#define KEY_DOWN 80

#include <iostream>
#include <glm/glm.hpp>
#include <fstream>
#include <vector>

#include "Sphere.h"
#include "Raycast.h"
#include "Light.h"
#include "Box.h"
#include "Triangle.h"
#include "Object.h"
#include "Plane.h"
#include <string>
#include <Windows.h>
#include <conio.h>

using namespace std;
using namespace glm;


#define PI 3.14159


bool shadow(Raycast ray, Light light, vector<Sphere> spheres, float t)
{
	vec3 shade;

	vec3 ip = ray.getOrigin() + ray.getDirection() * t;
	vec3 L = light.getPosition() - ip;
	float dist = length(L);
	ip += normalize(L) * 0.001f;
	Raycast ShadowRay = Raycast(ip, normalize(L));
	for (int i = 0; i < spheres.size(); i++)
	{
		Sphere current = spheres[i];

		if (current.OnIntersection(ShadowRay, t))
		{
			if (t < dist)
			{
				return true;
			}
		}
	}
	return false;
}

vec3 PhongLighting(Raycast &ray, Shape *object, Light &light, float &t) {
	
	
	//ambient light
	vec3 ambient = object->getColor() * light.getAmbientIntensity();

	//difuse light
	vec3 iPoint = ray.getOrigin() + ray.getDirection() * t;
	vec3 l = normalize(light.getPosition() - iPoint);
	vec3 n = normalize(object->normal(iPoint));
	vec3 diffuse = object->getColor() * light.getDiffuseIntensity() * (float)max(0, dot(l, n));

	//specular light 
	vec3 r = reflect(l, n);
	vec3 specularCoefficient = vec3(0.7, 0.7, 0.7);
	vec3 specular = specularCoefficient * light.getDiffuseIntensity() * pow(max(0, dot(r, normalize(ray.getDirection()))), object->getIntensity());

	vec3 phong = clamp(ambient + diffuse + specular , 0.0f, 1.0f);
	return phong;
}

void gameLoop(vec3 **image, int width, int height, Plane ground, Light sun, vector<Sphere> objects) {

	float PixelNx, PixelNy, PixelNz, PixelRx, PixelRy, PixelRz, PixelCamx, PixelCamy, Iar;

	vec3 rayDirection;
	vec3 rayOrigin(0, 0, 0);
	Shape *shape;

	vec3 PCamSpace;
	float t = 5000;
	float tanvalue = tanf(15.0 * PI / 180);
	Iar = (float)width / (float)height;
	HDC hdc = GetDC(GetConsoleWindow());

	for (int i = 0; i < width; i++)
	{
		image[i] = new vec3[height];
	}
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{

			PixelNx = (x + 0.5) / (float)width;
			PixelNy = (y + 0.5) / (float)height;

			PixelRx = 2 * PixelNx - 1;
			PixelRy = 1 - 2 * PixelNy;

			PixelRx = (2 * PixelNx - 1) * Iar;
			PixelRy = 1 - 2 * PixelNy;

			PixelCamx = PixelRx * tanvalue;
			PixelCamy = PixelRy * tanvalue;

			PCamSpace.x = PixelCamx;
			PCamSpace.y = PixelCamy;
			PCamSpace.z = -1;

			rayDirection = PCamSpace - rayOrigin;
			normalize(rayDirection);

			Raycast ray(rayOrigin, rayDirection);
			
			image[x][y] = vec3(1, 1, 1);
			SetPixel(hdc, x, y, RGB(image[x][y].x * 255, image[x][y].y * 255, image[x][y].z * 255));
			
			if (ground.OnIntersection(ray, t)) {
				shape = &ground;
				bool shade = shadow(ray, sun, objects, t);
				vec3 sh;
				if (shade)
					sh = sun.getAmbientIntensity();
				else
					sh = vec3(1.0, 1.0, 1.0);

				vec3 pixel = PhongLighting(ray, shape, sun, t);
				image[x][y] = pixel * sh;
				SetPixel(hdc, x, y, RGB(image[x][y].x * 255, image[x][y].y * 255, image[x][y].z * 255));
			}
			
			for (int i = 0; i < objects.size(); i++) {
				if (objects[i].OnIntersection(ray, t))
				{
					bool shade = shadow(ray, sun, objects, t);
					vec3 sh;
					if (shade)
						sh = sun.getAmbientIntensity();
					else
						sh = vec3(1.0, 1.0, 1.0);

					shape = &objects[i];
					vec3 pixel = PhongLighting(ray, shape, sun, t) * sh;
					image[x][y] = pixel;
					SetPixel(hdc, x, y, RGB(image[x][y].x * 255, image[x][y].y * 255, image[x][y].z * 255));
				}
			}
		}
	}
	

}

int main()
{

	const int width = 640;
	const int height = 480;


	vector<Sphere> objects;
	Sphere redSphere(vec3(0, 2, -20), 3, vec3(1.0, 0.32, 0.36), 128);
	objects.push_back(redSphere);
	Sphere purpleSphere(vec3(3, 1, -18), 2, vec3(0.4, 0, 0.9), 128);
	objects.push_back(purpleSphere);
	Sphere yellowSphere(vec3(-4, 2, -17), 3, vec3(1, 0.87, 0), 128);
	objects.push_back(yellowSphere);

	Plane ground(vec3(0, -1.5, -20), vec3(0, 1, 0), vec3(0, 1, 0), 64);

	Light sun(vec3(0, 8, 0), vec3(0.5,0.5,0.5), vec3(0.8,0.8,0.8), vec3(0.8, 0.8, 0.8));


	vec3 **image = new vec3*[width];
	
	gameLoop(image, width, height, ground, sun, objects);

	int c = 0;
	while (1) {
		c = _getch();

		switch (c) {
		case KEY_UP:
			objects[0].movePosition(vec3(0,1,0));
			gameLoop(image, width, height, ground, sun, objects);
		case KEY_DOWN:
			objects[0].movePosition(vec3(0, -1, 0));
			gameLoop(image, width, height, ground, sun, objects);
		}
		
	}

	return 0;
}
