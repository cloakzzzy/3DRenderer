#pragma once


#include "Camera.hpp"
#include "EntityAttribute.hpp"


class e_Window;
class e_Sphere;
class Entity;
class Engine;
class e_DirectionalLight;
class e_Camera;
class e_Box;


class e_Scene {
	friend class e_Window;
	friend class e_Sphere;
	friend class e_DirectionalLight;
	friend class Entity;
	friend class Engine;
	friend class e_Camera;
	friend class e_Box;

	friend class EntityAttribute<e_Sphere>;
	friend class EntityAttribute_Packed<e_Sphere>;
	friend class EntityAttribute<e_Box>;
	friend class EntityAttribute_Packed<e_Box>;
	friend class EntityAttribute<e_DirectionalLight>;

	std::vector<std::vector<float>> DataBuffers;
	std::vector<std::vector<unsigned int>> ObjectIDs;
	inline static std::vector<std::vector<float>> VertexData;
	inline static std::vector<std::vector<unsigned int>> IndicesData;

	inline static uint32_t Num_DirectionalLights = 0;

	inline static std::vector<e_DirectionalLight*> D_Objects;

	inline static std::vector<unsigned int> DepthMaps;

	inline static std::vector<unsigned int> i{ 0, 1, 2 };
	std::vector<float> v{ -0.5f,-0.5f, 0.5f,-0.5f, 0.0f, 0.5f };
	inline static std::vector<e_Scene> Scenes;

	e_Camera camera;

	e_Scene();

	void UpdateCameraData(e_Window* win, glm::vec3 CameraPosition, glm::mat4 CameraProjection, glm::mat4 CameraView);

	static void CreateObject();

	void RenderAndSetBuffers(e_Window* scene);
public:
	void Render(float red, float green, float blue);

	void Add(e_Sphere& sphere);

	void Add(e_Camera& camera);

	void Add(e_Box& box);

	void Add(e_DirectionalLight& directionallight);

	void Remove(e_Sphere& sphere);


};
