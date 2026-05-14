#include "Scene.hpp"
#include <SDL3/SDL.h>
#include <GL/glew.h>
#include "Window.hpp"
#include "OpenGLBuffer.hpp"
#include "OpenGLBuffers.hpp"
#include "DirectionalLight.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"
#include "Box.hpp"
#include "Entity.hpp"

e_Scene::e_Scene() {
	
	//camera.Set(WinPtr->ScreenWidth, WinPtr->ScreenHeight, 90, float(800) / float(600), 0.2, 100);
	

	
	ObjectIDs.push_back(std::vector<unsigned int>());
	ObjectIDs.push_back(std::vector<unsigned int>());
	ObjectIDs.push_back(std::vector<unsigned int>());

	DataBuffers.push_back(std::vector<float>());
	DataBuffers.push_back(std::vector<float>());
	DataBuffers.push_back(std::vector<float>());
	


}
/*
void e_Scene::Render(float red, float green, float blue) {

	SDL_GL_MakeCurrent(Win->WindowObject, Win->glContext);
	//glBindVertexArray(u_VAO);

	if (SDL_WaitEventTimeout(&e_Window::WindowEvents, 10)) {
		if (e_Window::WindowEvents.type == SDL_EVENT_MOUSE_MOTION) {
			VirtualX += (float)e_Window::WindowEvents.motion.xrel;
			VirtualY += (float)e_Window::WindowEvents.motion.yrel;
			camera.Mouse_SetLookAt(VirtualX, VirtualY, 10);
		}
	}
	Shader[e_Sphere::VectorPos].Use();
	GLint pos = Shader[e_Sphere::VectorPos].GetUniformLocation("CameraPosition");
	GLint proj = Shader[e_Sphere::VectorPos].GetUniformLocation("CameraProjection");
	GLint view = Shader[e_Sphere::VectorPos].GetUniformLocation("CameraView");

	Shader[e_Sphere::VectorPos].SetVec3(pos, camera.position.x, camera.position.y, camera.position.z);
	Shader[e_Sphere::VectorPos].SetMat4(proj, glm::value_ptr(camera.GetProjection()));
	Shader[e_Sphere::VectorPos].SetMat4(view, glm::value_ptr(camera.GetView()));


	unsigned int NumInstances = ObjectIDs[e_Sphere::VectorPos].size();
	
	glViewport(0, 0, Win->ScreenWidth , Win->ScreenHeight);

	glClearColor(Win->Red, Win->Green, Win->Blue, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	
	VertexBuffers[e_Sphere::VectorPos].Bind();
	ElementBuffers[e_Sphere::VectorPos].Bind();
	
	//puts instance data into IBO
	InstanceBuffers[e_Sphere::VectorPos].Bind();
	InstanceBuffers[e_Sphere::VectorPos].SetData(DataBuffers[e_Sphere::VectorPos]);
	
	

	glDrawElementsInstanced(GL_TRIANGLES, IndicesData[e_Sphere::VectorPos].size(), GL_UNSIGNED_INT, 0, NumInstances);
	
	SDL_GL_SwapWindow(Win->WindowObject);
	
}
*/

void e_Scene::Add(e_DirectionalLight& directionallight) {
	directionallight.AddData(*this, directionallight.dir_x, directionallight.dir_y, directionallight.dir_z);
}

void e_Scene::Add(e_Sphere& sphere) {
	sphere.AddData(*this, sphere.pos_x, sphere.pos_y, sphere.pos_z, sphere.radius, sphere.red, sphere.green, sphere.blue);
}

void e_Scene::Add(e_Camera& camera) {
	this->camera = camera;
}

void e_Scene::Add(e_Box& box) {
	box.AddData(*this);
}

void e_Scene::UpdateCameraData(e_Window* win, glm::vec3 CameraPosition, glm::mat4 CameraProjection, glm::mat4 CameraView) {
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, win->GlobalUniforms_SSBO);
	glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(glm::vec3), glm::value_ptr(CameraPosition));
	glBufferSubData(GL_SHADER_STORAGE_BUFFER, 16, sizeof(glm::mat4), glm::value_ptr(CameraProjection));
	glBufferSubData(GL_SHADER_STORAGE_BUFFER, 16 + sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(CameraView));
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void e_Scene::Remove(e_Sphere& sphere) {
	sphere.Remove(*this);
}

void e_Scene::Remove(e_Box& box) {
	box.Remove(*this);
}


