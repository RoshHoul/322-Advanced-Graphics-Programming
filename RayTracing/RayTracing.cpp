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

#include <Windows.h>

using namespace std;
using namespace glm;


#define PI 3.14159

int main()
{

	const int width = 640;
	const int height = 480;

	vec3 rayDirection;
	vec3 rayOrigin(0, 0, 0);

	float PixelNx, PixelNy, PixelNz, PixelRx, PixelRy, PixelRz, PixelCamx, PixelCamy, Iar;

	float tanvalue = tanf(15.0 * PI / 180);



	Iar = (float)width / (float)height;

	Sphere background(vec3(0, 0, -20), 3, vec3(1.0, 0.32, 0.36));
	Sphere topLeft(vec3(-2, -2, -18), 0.2 , vec3(0.0, 0.4, 0.8));

	//lights
	vec3 ambientIntensity(0.5, 0.5, 0.5);
	Light sun(vec3(0, 8, 0), vec3(0.8,0.8,0.8), vec3(0.8, 0.8, 0.8));


	vec3 PCamSpace;
	vec3 **image = new vec3*[width];
	ofstream ofs("./untitled.ppm", ios::out | ios::binary);
	ofs << "P6\n" << width << " " << height << "\n255\n";

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
		//	Raycast ray(vec3(x, y, 0), vec3(0,0,1));
			float t = 5000;
			
			image[x][y] = vec3(1, 1, 1);
			SetPixel(hdc, x, y, RGB(image[x][y].x * 255, image[x][y].y * 255, image[x][y].z * 255));
			
			if (background.OnIntersection(ray, t))
			{

				//ambient light
				vec3 ambient = background.getColor() * ambientIntensity;

				//difuse light
				vec3 iPoint = ray.getOrigin() + ray.getDirection() * t;
				vec3 l = normalize(sun.getPosition() - iPoint);
				vec3 n = normalize(background.normal(iPoint));
				vec3 diffuse = background.getColor() * sun.getDiffuseIntensity() * (float)max(0, dot(l, n));

				if (background.getColor() == vec3(0, 0, 0)) {
					cout << "fuckoff1" << endl;
				
				}
				else if (sun.getDiffuseIntensity() == vec3(0,0,0)) {
					cout << "fuckoff2" << endl;
				}
				else if (float(max(0, dot(l,n)))) {
					cout << "fuckoff3" << endl;
				}
				else if (background.getColor() == vec3(0, 0, 0)) {
					cout << "must be kidding me" << endl;
				}
				//specular light
				//vec3 r = 2 * (dot(l, n)) * n - l;
				vec3 r = reflect(l, n);
				vec3 specular = vec3(0.7,0.7,0.7) * sun.getDiffuseIntensity() * pow(max(0, dot(r, normalize(ray.getDirection()))), 128);

				image[x][y]=  clamp(ambient + specular + diffuse, 0.0f, 1.0f);
			
				SetPixel(hdc, x, y, RGB(image[x][y].x * 255, image[x][y].y * 255, image[x][y].z * 255));
			}

		}
	}
	for (unsigned y = 0; y < height; y++)
	{
		for (unsigned x = 0; x < width; x++)
		{
			ofs << (unsigned char)(min((float)1, (float)image[x][y].x) * 255) <<
				(unsigned char)(min((float)1, (float)image[x][y].y) * 255) <<
				(unsigned char)(min((float)1, (float)image[x][y].y) * 255);
		}
	}
	ofs.close();
	while (true);
	return 0;
}
