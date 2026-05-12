#include "Window.hpp"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "glew.h"
#include "Engine.hpp"
#include "DirectionalLight.hpp"

bool previous = false;

e_Window::e_Window(std::string WindowTitle, unsigned int ScreenWidth, unsigned int ScreenHeight, float Red, float Green, float Blue) {

    WindowPool.push_back(this);

    this->Red = Red;
    this->Green = Green;
    this->Blue = Blue;

    this->ScreenWidth = ScreenWidth;
    this->ScreenHeight = ScreenHeight;

    VirtualX = ScreenWidth / 2.0f;
    VirtualY = ScreenHeight / 2.0f;

    WindowObject = SDL_CreateWindow(WindowTitle.c_str(), ScreenWidth, ScreenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (!WindowObject) {
        std::cerr << "[ENGINE][ERROR] SDL_CreateWindow failed: " << SDL_GetError() << "\n";
        SDL_Quit();
        return;
    }

    glContext = SDL_GL_CreateContext(WindowObject);
    if (!glContext) {
        std::cerr << "[ENGINE][ERROR] SDL_GL_CreateContext failed: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(WindowObject);
        SDL_Quit();
        return;
    }

    SDL_GL_MakeCurrent(WindowObject, glContext);

    if (WindowPool.size() == 1) {
        glewInit();
    }
    
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_CULL_FACE);


    SDL_GL_SetSwapInterval(1);

    glGenVertexArrays(1, &u_VAO);

    glBindVertexArray(u_VAO);

    //sphere
    ElementBuffers.push_back(OpenGL_ElementBuffer());

    ElementBuffers[0].CreateBuffer(e_Scene::IndicesData[0].size() * sizeof(float));
    ElementBuffers[0].SetData(e_Scene::IndicesData[0]);

    VertexBuffers.push_back(OpenGL_VertexBuffer());

    VertexBuffers[0].CreateBuffer(e_Scene::VertexData[0].size() * sizeof(float), std::vector<std::pair<unsigned char, uint32_t>>{
        {OpenGLType::Vec3, 0},
        { OpenGLType::Vec2, 13 }
    });

    VertexBuffers[0].SetData(e_Scene::VertexData[0]);

    InstanceBuffers.push_back(OpenGL_InstanceBuffer());

    InstanceBuffers[0].CreateBuffer(4 * 400 * sizeof(float), std::vector<std::pair<unsigned char, uint32_t>>{
        {OpenGLType::Vec3, 1},
        { OpenGLType::Float, 2 },
        { OpenGLType::Float, 3 }
    });

    Shader.push_back(OpenGL_Shader());

    Shader[0].SetFiles("sphere.vert", "sphere.frag");
    //DepthShader.SetFiles("depthshader_sphere.vert", "depthshader.frag");
    Shader[0].Use();


    //floor 
    glGenBuffers(1, &FloorVBO);
    glBindBuffer(GL_ARRAY_BUFFER, FloorVBO);
    glBufferData(GL_ARRAY_BUFFER, FloorVertices.size() * sizeof(float), &FloorVertices.front(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(11, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0 * sizeof(float)));
    glEnableVertexAttribArray(11);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    FloorShader.SetFiles("FloorShader.vert", "FloorShader.frag");

    FloorShader.Use();

    uloc_view = FloorShader.GetUniformLocation("view");
    uloc_projection = FloorShader.GetUniformLocation("projection");
    uloc_cam_pos = FloorShader.GetUniformLocation("cam_pos");
    uloc_col1 = FloorShader.GetUniformLocation("col1");
    uloc_col2 = FloorShader.GetUniformLocation("col2");

    glGenBuffers(1, &SSBO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, SSBO);
    glBufferData(GL_SHADER_STORAGE_BUFFER, 65536, nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, SSBO);

    glGenBuffers(1, &GlobalUniforms_SSBO);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, GlobalUniforms_SSBO);
    glBufferData(GL_SHADER_STORAGE_BUFFER, 5000, nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, GlobalUniforms_SSBO);


    FloorShader.Use();
    FloorShader.SetInt(FloorShader.GetUniformLocation("shadowMaps[0]"), 5);

    FloorShader.SetVec3(uloc_col1, 0.1, 0.1, 0.1);
    FloorShader.SetVec3(uloc_col2, 0.2, 0.2, 0.2);

    FloorDepthShader.SetFiles("floorshader_depth.vert", "depthshader.frag");

    FloorShader.Use();
    FloorShader.SetInt(FloorShader.GetUniformLocation("shadowMaps[0]"), 5);

    FloorShader.SetVec3(uloc_col1, 0.1, 0.1, 0.1);
    FloorShader.SetVec3(uloc_col2, 0.2, 0.2, 0.2);

    DepthShader.push_back(OpenGL_Shader());

    DepthShader[0].SetFiles("depthshader_sphere.vert", "depthshader.frag");

    //box

   
    ElementBuffers.push_back(OpenGL_ElementBuffer());

    ElementBuffers[1].CreateBuffer(e_Scene::IndicesData[1].size() * sizeof(float));
    ElementBuffers[1].SetData(e_Scene::IndicesData[1]);

    VertexBuffers.push_back(OpenGL_VertexBuffer());

    VertexBuffers[1].CreateBuffer(e_Scene::VertexData[1].size() * sizeof(float), std::vector<std::pair<unsigned char, uint32_t>>{
        {OpenGLType::Vec3, 8},
    });

    VertexBuffers[1].SetData(e_Scene::VertexData[1]);


    InstanceBuffers.push_back(OpenGL_InstanceBuffer());

    InstanceBuffers[1].CreateBuffer(4 * 400 * sizeof(float), std::vector<std::pair<unsigned char, uint32_t>>{
        {OpenGLType::Vec3, 4},//pos
        { OpenGLType::Vec3, 5 },//dimensions
        { OpenGLType::Vec2, 6 }, //rotation
        { OpenGLType::Float, 7 } // colour;
    });

    Shader.push_back(OpenGL_Shader());
    
    Shader[1].SetFiles("box.vert", "box.frag");
    //DepthShader.SetFiles("depthshader_sphere.vert", "depthshader.frag");
    Shader[1].Use();

 

    VirtualX = ScreenHeight / 2.0f;
    VirtualY = ScreenWidth / 2.0f;

}

bool e_Window::AllWindowsOpen() {
    if (SDL_WaitEventTimeout(&WindowEvents, 10)) {
        if (WindowEvents.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
            for (e_Window* win : WindowPool) {
                if (win->WindowObject && WindowEvents.window.windowID == SDL_GetWindowID(win->WindowObject))
                {
                    SDL_DestroyWindow(win->WindowObject);
                    win->WindowObject = nullptr;
                    win->IsRunning_ = false;
                }
            }
        }

        bool IsAllClosed = true;
        for (e_Window* win : WindowPool) {
            if (win->WindowObject) {
                IsAllClosed = false;
            }
        }

        if (IsAllClosed)
            return false;
        else
            return true;


    }

}

e_Window e_Window::Create(std::string WindowTitle, unsigned int ScreenWidth, unsigned int ScreenHeight, float Red, float Green, float Blue) {
    return e_Window(WindowTitle, ScreenWidth, ScreenHeight, Red, Green, Blue);
}


void e_Window::DrawCalls_SetBuffers(e_Scene* scene) {
    
   // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    scene->UpdateCameraData(this, scene->camera.position, scene->camera.GetProjection(), scene->camera.GetView());
    e_DirectionalLight::UpdateBuffer(this, scene);

    Entity::Render<e_Sphere, e_DirectionalLight>(this, scene, scene->D_Objects);

    //glDisable(GL_CULL_FACE);

    Entity::Render<e_Box, e_DirectionalLight>(this, scene, scene->D_Objects);

    e_Window::FloorShader.Use();
    glBindBuffer(GL_ARRAY_BUFFER, FloorVBO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void e_Window::Render(e_Scene& scene) {
    SDL_GL_MakeCurrent(WindowObject, glContext);
    glBindVertexArray(u_VAO);

    glClearColor(Red, Green, Blue, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    last = now;
    now = SDL_GetPerformanceCounter();
    DeltaTime = (double)(now - last) / freq;
    freq = (double)SDL_GetPerformanceFrequency();

    glViewport(0, 0, 800, 600);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    {

        if (SDL_WaitEventTimeout(&WindowEvents, 4)) {
            // We got at least one event — process it
            do {
                if (WindowEvents.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                    if (WindowEvents.button.button == SDL_BUTTON_RIGHT) {
                        monob += 0.00000000;
                        if (monob == 0.000000001) {
                            toggleb = !toggleb;
                            if (toggleb == false) {
                                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            }
                            else {
                                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            }
                        }
                    }
                }
                if (WindowEvents.type == SDL_EVENT_MOUSE_BUTTON_UP) {
                    if (WindowEvents.button.button == SDL_BUTTON_RIGHT) {
                        monob = 0;
                    }
                }
                if (WindowEvents.type == SDL_EVENT_MOUSE_MOTION) {
                    VirtualX += (float)WindowEvents.motion.xrel;
                    VirtualY += (float)WindowEvents.motion.yrel;
                    scene.camera.Mouse_SetLookAt(VirtualX, VirtualY, ScreenWidth, ScreenHeight);
                }


            } while (SDL_PollEvent(&WindowEvents));
        }

        const bool* keys = SDL_GetKeyboardState(NULL);

        bool currentW = keys[SDL_SCANCODE_ESCAPE];


        //float cameraSpeed = static_cast<float>(5.0f) * DeltaTime;
        float cameraSpeed = 5.0f * DeltaTime;

        {
            // pressed THIS frame only
            if (!previous && currentW)
            {
                toggle = !toggle;
                if (toggle == false) {
                    SDL_SetWindowRelativeMouseMode(WindowObject, true);
                    SDL_HideCursor();
                }
                else {
                    SDL_SetWindowRelativeMouseMode(WindowObject, false);
                    SDL_ShowCursor();
                }
            }
            previous = currentW;

            scene.camera.HandleMovement(keys[SDL_SCANCODE_W], keys[SDL_SCANCODE_S],
                keys[SDL_SCANCODE_A], keys[SDL_SCANCODE_D], keys[SDL_SCANCODE_SPACE], keys[SDL_SCANCODE_LSHIFT], DeltaTime);


        }

    }


    DrawCalls_SetBuffers(&scene);


    SDL_GL_SwapWindow(WindowObject);
}


