#pragma once

#include <vector>
#include "EntityAttribute.hpp"
#include "Entity.hpp"
#include "libs/glm/glm.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"
#include "libs/glm/gtc/type_ptr.hpp"

class e_Window; class e_Scene; class Engine; class e_Window;

class e_DirectionalLight : public Entity {

	friend class EntityAttribute<e_DirectionalLight>;
	friend class Entity;
	friend class e_Window;
	friend class e_Scene;
	friend class Engine;

	inline constexpr static unsigned int EntitySize = 3, VectorPos = 2;
	inline static constexpr float near_plane = 0.05f, far_plane = 100.f;
	unsigned int DepthMapFBO;
	unsigned int DepthMap;

	unsigned int SHADOW_WIDTH = 4096, SHADOW_HEIGHT = 4096;

	

	static void UpdateBuffer(e_Window* win, e_Scene* scene);

	void PerFrame(e_Window* win, e_Scene* scene);

	glm::mat4 lightSpaceMatrix;

	void CreateShadowMap();


	unsigned int Index = 0;
	unsigned int ID;

	glm::vec3 LightPos;

	

	inline static constexpr float orthosize = 100.0f;

	static void Initialize();

	e_DirectionalLight(float dir_x, float dir_y, float dir_z);

	void AddData(e_Scene& scene, float dir_x, float dir_y, float dir_z);

public:
	EntityAttribute<e_DirectionalLight> dir_x{ 0, this };
	EntityAttribute<e_DirectionalLight> dir_y{ 1, this };
	EntityAttribute<e_DirectionalLight> dir_z{ 2, this };


	//void PerFrame(Entity::Camera& RenderCamera);
};