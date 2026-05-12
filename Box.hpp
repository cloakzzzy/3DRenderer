#pragma once
#include "Entity.hpp"
#include "EntityAttribute.hpp"

class Engine;  class e_Scene;
class e_Window; 

class e_Box: public Entity {

	friend class EntityAttribute<e_Box>;
	friend class EntityAttribute_Packed<e_Box>;
	friend class Engine;
	friend class Entity;
	friend class e_Window;
	friend class e_Box;

	friend class e_Scene;

	inline static constexpr unsigned int VectorPos = 1;

	//static void CreateBuffers(e_Scene *scene, e_Window *window);

	static void GenerateModel();

	static void Initialize(e_Scene& scene);

	void AddData(e_Scene& scene);

	e_Box(float pos_x, float pos_y, float pos_z, float length, float width, float height, float rot_x, float rot_y, unsigned char red, unsigned char green, unsigned char blue);

	void Remove(e_Scene& scene);

	inline constexpr static unsigned int EntitySize = 9;
	unsigned int ID;
	unsigned int Index = 0;

public:



	EntityAttribute<e_Box> pos_x{ 0,this };
	EntityAttribute<e_Box> pos_y{ 1, this };
	EntityAttribute<e_Box> pos_z{ 2, this };

	EntityAttribute<e_Box> length{ 3, this };
	EntityAttribute<e_Box> width{ 4, this };
	EntityAttribute<e_Box> height{ 5, this };

	EntityAttribute<e_Box> rot_x{ 6, this };
	EntityAttribute<e_Box> rot_y{ 7, this };

	EntityAttribute_Packed<e_Box> red{ 8, 0, this };
	EntityAttribute_Packed<e_Box> green{ 8, 8, this };
	EntityAttribute_Packed<e_Box> blue{ 8, 16, this };



};
