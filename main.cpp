
#include <SDL3/SDL.h>
#include <GL/glew.h>
#include <iostream>
#include "Scene.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"
#include "DirectionalLight.hpp"
#include "Window.hpp"
#include "Engine.hpp"
#include "Box.hpp"

int main()
{
    Engine e;
    e.Initialize();



    e_Window win = e.CreateWindow("Window2", 800, 600, 0.7, 0.7, 0.7);

    e_Scene scene = e.CreateScene();

    
    e_Camera cam = e.CreateCamera(
        5.0, 7,  
        100, 
        win.GetAspect(), 0.2, 200.f);


    e_Sphere s = e.CreateSphere(0.0f, 10.0f, 1.0f, 0.5f, 0.f, 255.f, 0.f);
    scene.Add(s);
    e_Sphere s1 = e.CreateSphere(-10.0f, 1.0f, 1.0f, 1.0f, 0.f, 0.f, 128.f);
    scene.Add(s1);
    e_Sphere s3 = e.CreateSphere(1.0f, 10.0f, 0.f, 2.0f, 128, 0.f, 0.f);
    scene.Add(s3);
    e_Sphere s4 = e.CreateSphere(0.f, 4.0f, 0.f, 1.5f, 128, 128, 128.f);
    scene.Add(s4);

    e_Box box = e.CreateBox(
        5.0f, 7.f, 5.0f,
        2.f, 2.f, 4.f,
        0.f, 0.f,
        0.f, 0.f, 128.f);

    e_Box box2 = e.CreateBox(
        -3.f, 5.f, 5.0f,
        2.f, 1.f, 1.f,
        0.f, 0.f,
        128.f, 128, 0.f);

    e_Box box3 = e.CreateBox(
        -5.0f, 10.f, 5.0f,
        2.f, 1.f, 1.f,
        0.f, 0.f,
        0.f, 128, 128.f);

    scene.Add(box);
    scene.Add(box2);
    scene.Add(box3);

    e_DirectionalLight light = e.CreateDirectionalLight(0, 1.0, 0.3f);
    e_DirectionalLight light2 = e.CreateDirectionalLight(0.707f, 0.707f, 0.707f);
    scene.Add(light);
    scene.Add(light2);

    scene.Add(cam);


    while (e_Window::AllWindowsOpen())
    {
        box.rot_x += 0.6f;
        box.rot_y += 1.0f;

        box2.rot_x += 1.0f;
        box2.rot_y += 0.5f;

        box3.rot_x += 1.0f;
        box3.rot_y += 1.0f;

        win.Render(scene);




    }

}

