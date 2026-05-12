#include "Box.hpp"
#include "Scene.hpp"
#include <vector>
#include "Window.hpp"

//void e_Sphere::CreateBuffers(e_Scene scene, e_Window window) {}

void e_Box::GenerateModel() {

	e_Scene::VertexData.push_back(std::vector<float>());

	e_Scene::VertexData[1].insert(e_Scene::VertexData[1].end(),
		{ 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f , -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f });

	e_Scene::IndicesData.push_back(std::vector<unsigned int>());
	
	e_Scene::IndicesData[1].insert(e_Scene::IndicesData[1].end(),
		{ 0,1,3,
		  3, 2, 0,

		  0, 5, 4 ,
		 0, 4, 1,

		  1, 4, 6,
	      1, 6, 3,
	      
		 4, 7, 6,
		 7, 4, 5,

		0, 2, 7,
		5, 0, 7,

		2, 6, 7,
		2, 3, 6,
		    
		});

}



e_Box::e_Box(float pos_x, float pos_y, float pos_z, float length, float width, float height, float rot_x, float rot_y, unsigned char red, unsigned char green, unsigned char blue){
	this->pos_x.Value = pos_x;
	this->pos_y.Value = pos_y;
	this->pos_z.Value = pos_z;

	this->length.Value = length;
	this->width.Value = width;
	this->height.Value = height;

	this->rot_x.Value = rot_x;
	this->rot_y.Value = rot_x;

	this->red.Value = red;
	this->green.Value = green;
	this->blue.Value = blue;
}

void e_Box::AddData(e_Scene& scene) {

	this->pos_x.Set(&scene);

	this->pos_y.Set(&scene);

	this->pos_z.Set(&scene);

	this->rot_x.Set(&scene);
	
	this->length.Set(&scene);
	this->width.Set(&scene);
	this->height.Set(&scene);

	this->rot_x.Set(&scene);
	this->rot_y.Set(&scene);

	this->red.Set(&scene);

	this->green.Set(&scene);

	this->blue.Set(&scene);

	Entity::Generate_ID<e_Box>(&scene, ID, Index);

	//this code sets the code in the data buffer to the starting val of the attributes, using the equals operator overload.

	this->pos_x = this->pos_x;
	this->pos_y = this->pos_y;
	this->pos_z= this->pos_z;

	this->length = this->length;
	this->width = this->width;
	this->height = this->height;

	this->rot_x = this->rot_x;
	this->rot_y = this->rot_x;

	this->red = this->red;
	this->green = this->green;
	this->blue = this->blue;


}

void e_Box::Remove(e_Scene& scene) {
	Entity::DataBuffer_Remove<e_Box>(&scene, ID, Index);
}

