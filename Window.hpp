#pragma once
#include <string>
#include <iostream>
#include <SDL3/SDL.h>
#include <glew.h>
#include <vector>
#include "OpenGLBuffer.hpp"
#include "OpenGLBuffers.hpp"
#include "OpenGLShader.hpp"

class e_Scene; class Engine; class e_Camera; class e_Sphere; class e_DirectionalLight; class Entity;

class e_Window {

	friend class e_Scene;
	friend class Engine;
	friend class e_Sphere;
	friend class e_DirectionalLight;
	friend class Entity;

	inline static SDL_Event WindowEvents;
	inline static std::vector<e_Window*> WindowPool;

	inline static std::vector<OpenGL_Shader> DepthShader;

	std::vector<OpenGL_InstanceBuffer> InstanceBuffers;
	std::vector<OpenGL_VertexBuffer> VertexBuffers;
	std::vector<OpenGL_ElementBuffer> ElementBuffers;
	std::vector<OpenGL_Shader> Shader;
	std::vector<OpenGL_Shader> DepthShaders;

	inline static OpenGL_Shader FloorShader;
	inline static OpenGL_Shader FloorDepthShader;

	unsigned int FloorVBO;

	inline static unsigned int SSBO;

	unsigned int GlobalUniforms_SSBO;

	inline static unsigned int uloc_view;
	inline static unsigned int uloc_projection;
	inline static unsigned int uloc_cam_pos;
	inline static unsigned int uloc_col1;
	inline static unsigned int uloc_col2;

	inline static std::vector<float> FloorVertices{
		10000.0f, 0.f, 10000.f,
		-10000.0f, 0.f, -10000.f,
		-10000.0f, 0.f, 10000.f,

		10000.0f, 0.f, -10000.f,
		-10000.0f, 0.f, -10000.f,

		10000.0f, 0.f, 10000.f,
	};

	unsigned int u_VAO;


	double now;
	double last;
	double freq;

	int a = 234;

	SDL_Window* WindowObject;
	SDL_GLContext glContext;
	e_Scene* Scene;


	float VirtualX, VirtualY;

	double DeltaTime = 0.0;

	double monoa = 0;
	bool toggle = true;
	double monob = 0;
	double toggleb = false;

	bool IsRunning_ = true;

	float Red; float Green; float Blue;
	unsigned int ScreenWidth, ScreenHeight;

	e_Window() {};
	e_Window(std::string WindowTitle, unsigned int ScreenWidth, unsigned int ScreenHeight, float Red, float Green, float Blue);

	void DrawCalls_SetBuffers(e_Scene* scene);

public:

	static e_Window Create(std::string WindowTitle, unsigned int ScreenWidth, unsigned int ScreenHeight, float Red, float Green, float Blue);

	static bool AllWindowsOpen();

	float GetAspect() { return float(ScreenWidth) / float(ScreenHeight); }

	void Render(e_Scene& scene);

	bool IsRunning() {
		return IsRunning_;
	}

};
