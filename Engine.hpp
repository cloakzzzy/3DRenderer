#pragma once
#include <iostream>
#include "Window.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"
#include "Scene.hpp"
#include "DirectionalLight.hpp"
#include "Box.hpp"

class Engine {
	inline static bool Created = false;


public:
	void Initialize();

	e_Window CreateWindow(std::string WindowTitle, unsigned int ScreenWidth, unsigned int ScreenHeight, float Red, float Green, float Blue);

	e_Sphere CreateSphere(float pos_x, float pos_y, float pos_z, float radius, unsigned char red, unsigned char green, unsigned char blue);

	e_Box CreateBox(float pos_x, float pos_y, float pos_z, float length, float width, float height, float rot_x, float rot_y, unsigned char red, unsigned char green, unsigned char blue);

	e_Camera CreateCamera(float CameraSpeed, float Sensitivity, float Fov, float Aspect, float Near, float Far);

	e_Scene CreateScene();



	e_DirectionalLight CreateDirectionalLight(float dir_x, float dir_y, float dir_z);

};



