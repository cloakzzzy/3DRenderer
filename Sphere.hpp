#pragma once
#include "Entity.hpp"
#include "EntityAttribute.hpp"

class Engine;  class e_Scene;
class e_Window;

class e_Sphere : public Entity {

	friend class EntityAttribute<e_Sphere>;
	friend class EntityAttribute_Packed<e_Sphere>;
	friend class Engine;
	friend class Entity;
	friend class e_Window;

	friend class e_Scene;

	inline static constexpr unsigned int VectorPos = 0;
	
	//static void CreateBuffers(e_Scene *scene, e_Window *window);

	static void GenerateModel(int acc);

	static void Initialize(e_Scene& scene);

	void AddData(e_Scene& scene, float pos_x, float pos_y, float pos_z, float radius, unsigned char red, unsigned char green, unsigned char blue);

	e_Sphere(float pos_x, float pos_y, float pos_z, float radius, unsigned char red, unsigned char green, unsigned char blue);

	void Remove(e_Scene& scene);

	inline constexpr static unsigned int EntitySize = 5;
	unsigned int ID;
	unsigned int Index = 0;

public:

	

	EntityAttribute<e_Sphere> pos_x{ 0,this };
	EntityAttribute<e_Sphere> pos_y{ 1, this };
	EntityAttribute<e_Sphere> pos_z{ 2, this };
	EntityAttribute<e_Sphere> radius{ 3, this };
	EntityAttribute_Packed<e_Sphere> red{ 4, 0, this };
	EntityAttribute_Packed<e_Sphere> green{ 4, 8, this };
	EntityAttribute_Packed<e_Sphere> blue{ 4, 16, this };

	
	
};
