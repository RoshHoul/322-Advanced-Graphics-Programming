// RayTracing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <glm/glm.hpp>
#include <fstream>
#include <vector>

#include "Sphere.h"
#include "objloader.h"
#include "Raycast.h"
#include "Light.h"
#include "Box.h"

#include <Windows.h>

using namespace std;
using namespace glm;


#define PI 3.14159

vec3 PhongLighting(Raycast &ray, Sphere &object, Light &light, float &t) {
	
	//ambient light
	vec3 ambient = object.getColor() * light.getAmbientIntensity();

	//difuse light
	vec3 iPoint = ray.getOrigin() + ray.getDirection() * t;
	vec3 l = normalize(light.getPosition() - iPoint);
	vec3 n = normalize(object.normal(iPoint));
	vec3 diffuse = object.getColor() * light.getDiffuseIntensity() * (float)max(0, dot(l, n));

	//specular light 
	vec3 r = reflect(l, n);
	vec3 specularCoefficient = vec3(0.7, 0.7, 0.7);
	vec3 specular = vec3(0.7,0.7,0.7) * light.getDiffuseIntensity() * pow(max(0, dot(r, normalize(ray.getDirection()))), object.getIntensity());

	vec3 phong = clamp(ambient + specular + diffuse, 0.0f, 1.0f);

	return phong;
}

int main()
{

	const int width = 640;
	const int height = 480;

	vec3 rayDirection;
	vec3 rayOrigin(0, 0, 0);

	float t = 5000;
	float PixelNx, PixelNy, PixelNz, PixelRx, PixelRy, PixelRz, PixelCamx, PixelCamy, Iar;

	float tanvalue = tanf(15.0 * PI / 180);
	Iar = (float)width / (float)height;

	Shape *shape;
	Sphere background(vec3(0, 2, -20), 3, vec3(1.0, 0.32, 0.36), 128);
	Box box(vec3(-1, -1, -10), vec3(1, 1, -12), vec3(0.6,0.6,0.0));
	Light sun(vec3(0, 8, 0), vec3(0.5,0.5,0.5), vec3(0.8,0.8,0.8), vec3(0.8, 0.8, 0.8));

	vec3 PCamSpace;

	vec3 **image = new vec3*[width];
/*	ofstream ofs("./untitled.ppm", ios::out | ios::binary);
	ofs << "P6\n" << width << " " << height << "\n255\n";
*/

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
			
			if (background.OnIntersection(ray, t))
			{
				shape = &background;
				vec3 pixel = PhongLighting(ray, background, sun, t);
				image[x][y] = pixel;
				SetPixel(hdc, x, y, RGB(image[x][y].x * 255, image[x][y].y * 255, image[x][y].z * 255));
			}

			if (box.OnIntersection(ray, t)) {
	//			vec3 pixel = PhongLighting(ray, box, sun, t);
				image[x][y] = box.getColor();
				SetPixel(hdc, x, y, RGB(image[x][y].x * 255, image[x][y].y * 255, image[x][y].z * 255));
			}
		}
	}
/*	for (unsigned y = 0; y < height; y++)
	{
		for (unsigned x = 0; x < width; x++)
		{
			ofs << (unsigned char)(min((float)1, (float)image[x][y].x) * 255) <<
				(unsigned char)(min((float)1, (float)image[x][y].y) * 255) <<
				(unsigned char)(min((float)1, (float)image[x][y].y) * 255);
		}
	}
	ofs.close();
	*/
	
	while (true);
	return 0;
}
