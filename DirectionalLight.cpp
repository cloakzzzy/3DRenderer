#include <glew.h>
#include "DirectionalLight.hpp"
#include "Entity.hpp"
#include "Window.hpp"
#include "EntityAttribute.hpp"


void e_DirectionalLight::Initialize() {}

void e_DirectionalLight::CreateShadowMap() {
    glGenFramebuffers(1, &DepthMapFBO);

    // create depth texture
    glGenTextures(1, &DepthMap);
    glBindTexture(GL_TEXTURE_2D, DepthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    // attach depth texture as FBO's depth buffer
    glBindFramebuffer(GL_FRAMEBUFFER, DepthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, DepthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

   

}

void e_DirectionalLight::PerFrame(e_Window* win, e_Scene* scene) {
    glm::mat4 LightView = glm::lookAt(LightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 LightProjection = glm::ortho(-orthosize, orthosize, -orthosize, orthosize, near_plane, far_plane);


    scene->UpdateCameraData(win, LightPos, LightProjection, LightView);

    lightSpaceMatrix = LightProjection * LightView;


    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, DepthMapFBO);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void e_DirectionalLight::UpdateBuffer(e_Window* win, e_Scene* scene) {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, win->GlobalUniforms_SSBO);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, 16 + 2 * sizeof(glm::mat4), sizeof(unsigned int), &scene->Num_DirectionalLights);
    
    glBindBuffer(GL_SHADER_STORAGE_BUFFER,  win->SSBO);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, scene->DataBuffers[e_DirectionalLight::VectorPos].size() * sizeof(float), &scene->DataBuffers[e_DirectionalLight::VectorPos].front());
}
e_DirectionalLight::e_DirectionalLight(float dir_x, float dir_y, float dir_z) {

    this->dir_x.Value = dir_x;
    this->dir_y.Value = dir_y;
    this->dir_z.Value = dir_z;

}

void e_DirectionalLight::AddData(e_Scene& scene, float dir_x, float dir_y, float dir_z) {
    Entity::Generate_ID<e_DirectionalLight>(&scene, ID, Index);

    this->dir_x.Set(&scene);
    this->dir_y.Set(&scene);
    this->dir_z.Set(&scene);

    this->dir_x = this->dir_x;
    this->dir_y = this->dir_y;
    this->dir_z = this->dir_z;

    scene.Num_DirectionalLights++;

    CreateShadowMap();

    LightPos = glm::normalize(glm::vec3(dir_x, dir_y, dir_z)) * 20.f;

    scene.D_Objects.push_back(this);

    scene.DepthMaps.push_back(DepthMap);

   

}
