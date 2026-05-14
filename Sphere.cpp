#include "Sphere.hpp"
#include "Scene.hpp"
#include <vector>
#include "Window.hpp"

//void e_Sphere::CreateBuffers(e_Scene scene, e_Window window) {}

void e_Sphere::GenerateModel(int acc) {
	std::vector<float> vert;
	float cx = 0.0f;
	float cy = 0.0f;
	float cz = 0.0f;
	float r = 1.0f;
	uint32_t j = 0;
	int layers = int(ceil(float(acc) / 2));

	float th = 360.0f / float(acc);
	for (int i = 0; i < layers; i++) {
		std::vector<float> a = Ngonyz(cx, cy, cz, cx, cy + r, cz, th, i);
		float rada = abs(cz - a[2]);
		for (int j = 0; j < acc; j++) {
			std::vector<float> pa = Ngonxz(cx, a[1], cz, cx, a[1], cz + rada, th, j);
			vert.push_back(pa[0]); vert.push_back(pa[1]); vert.push_back(pa[2]);
		}
	}

	vert.push_back(cx);
	vert.push_back(cy - r);
	vert.push_back(cz);


	e_Scene::VertexData.push_back(std::vector<float>());

	for (int32_t i = 0; i < vert.size(); i += 3) {
		e_Scene::VertexData[0].push_back(vert[i + 2]); // 3
		e_Scene::VertexData[0].push_back(vert[i + 1]); //2 
		e_Scene::VertexData[0].push_back(vert[i]); // 1

		float layer = floor((i / 3) / acc);
		float v = (i / 3) % (int)acc;

		e_Scene::VertexData[0].push_back(v / acc);
		e_Scene::VertexData[0].push_back(layer / layers);
	}

	int size = vert.size() / 3;

	e_Scene::IndicesData.push_back(std::vector<unsigned int>());

	for (int i = 0; i < size - 1; i++) {
		if (i > (size - acc * 1) - 1 and (i % acc != 0)) {

			if (i + 1 != size - 1) {

				e_Scene::IndicesData[0].push_back(size - 1);
				e_Scene::IndicesData[0].push_back(i + 1);
				e_Scene::IndicesData[0].push_back(i);

			}

		}
		else {

			e_Scene::IndicesData[0].push_back(i); // 1
			e_Scene::IndicesData[0].push_back(i + acc); // 3
			e_Scene::IndicesData[0].push_back(i + 1); // 2


			e_Scene::IndicesData[0].push_back(i + 1);
			e_Scene::IndicesData[0].push_back(i + acc);

			if ((i + acc + 1) != size) {
				e_Scene::IndicesData[0].push_back(i + acc + 1);
			}
			else {
				e_Scene::IndicesData[0].push_back(size - 1);
			}
		}
	}
}



e_Sphere::e_Sphere(float pos_x, float pos_y, float pos_z, float radius, uint8_t red, uint8_t green, uint8_t blue) {

	this->pos_x.Value = pos_x;
	this->pos_y.Value = pos_y;
	this->pos_z.Value = pos_z;

	this->radius.Value = radius;

	this->red.Value = red;
	this->green.Value = green;
	this->blue.Value = blue;
}

void e_Sphere::AddData(e_Scene& scene, float pos_x, float pos_y, float pos_z, float radius, unsigned char red, unsigned char green, unsigned char blue) {

	for (int i = 0; i < EntitySize; i++) {
		scene.DataBuffers[VectorPos].push_back(0);
	}

	this->pos_x.Set(&scene);

	this->pos_y.Set(&scene);

	this->pos_z.Set(&scene);

	this->radius.Set(&scene);

	this->red.Set(&scene);

	this->green.Set(&scene);

	this->blue.Set(&scene);

	Index = scene.Spheres.size();

	scene.Spheres.push_back(this);
	
	this->pos_x = this->pos_x;
	this->pos_y = this->pos_y;
	this->pos_z = this->pos_z;

	this->radius = this->radius;

	this->red = this->red;
    this->green = this->green;
   this->blue = this->blue;


}

void e_Sphere::Remove(e_Scene& scene) {

	for (int i = Index + 1; i < scene.Spheres.size(); i++) {scene.Spheres[i]->Index -= 1;}

	Entity::DataBuffer_Remove<e_Sphere>(&scene, Index);

	
}


