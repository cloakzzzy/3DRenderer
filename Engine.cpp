#include "Engine.hpp"
#include "Window.hpp"
#include "Sphere.hpp"
#include "Box.hpp"

void Engine::Initialize() {

    if (Created) {
        std::cerr << "[RUNTIME ERROR] An Instance Of Engine Has Already Been Initialized" << '\n';
        throw std::runtime_error("An Instance Of Engine Has Already Been Initialized");
    }

    Created = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "[ENGINE][ERROR]SDL_Init failed: " << SDL_GetError() << "\n";
        throw std::runtime_error("[ENGINE][ERROR]SDL_Init failed: ");
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    e_Sphere::GenerateModel(70);
    e_Box::GenerateModel();

}

e_Window Engine::CreateWindow(std::string WindowTitle, unsigned int ScreenWidth, unsigned int ScreenHeight, float Red, float Green, float Blue) {
    return e_Window(WindowTitle, ScreenWidth, ScreenHeight, Red, Green, Blue);
}

e_Sphere Engine::CreateSphere(float pos_x, float pos_y, float pos_z, float radius, unsigned char red, unsigned char green, unsigned char blue) {
    return e_Sphere(pos_x, pos_y, pos_z, radius, red, green, blue);
}

e_Box Engine::CreateBox(float pos_x, float pos_y, float pos_z, float length, float width, float height, float rot_x, float rot_y, unsigned char red, unsigned char green, unsigned char blue) {
    return e_Box(pos_x, pos_y, pos_z, length, width, height, rot_x, rot_y, red, green, blue);
}

e_Camera Engine::CreateCamera(float CameraSpeed, float Sensitivity, float Fov, float Aspect, float Near, float Far) {
    return e_Camera(Sensitivity, CameraSpeed, Fov, Aspect, Near, Far);
}

e_DirectionalLight Engine::CreateDirectionalLight(float dir_x, float dir_y, float dir_z) {
    return e_DirectionalLight(dir_x, dir_y, dir_z);
}

e_Scene Engine::CreateScene() {

    return e_Scene();
}

