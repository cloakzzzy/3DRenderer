#pragma once

#include <vector>
#include "OpenGLBuffer.hpp"
#include "OpenGLBuffers.hpp"
#include "OpenGLShader.hpp"
#include "Utils.hpp"
#include "Scene.hpp"
#include "Window.hpp"

class e_Sphere; class e_Scene; class e_DirectionalLight; class e_Window;

class Entity {

	friend class e_Sphere;
	friend class e_DirectionalLight;
	friend class e_Window;

protected:
	Entity(){}


	/*
	inline static std::vector<float> DataBuffer;
	inline static std::vector<unsigned int> ObjectIDs;
	inline static std::vector<float> VertexData;
	inline static std::vector<unsigned int> IndicesData;

	unsigned int ID;
	unsigned int Index = 0;

	inline static OpenGL_InstanceBuffer GPU_InstanceBuffer;
	inline static OpenGL_VertexBuffer GPU_VertexBuffer;
	inline static OpenGL_ElementBuffer GPU_ElementBuffer;


	inline static OpenGL_Shader Shader;
	inline static OpenGL_Shader DepthShader;

	*/
	template <typename T>
	static void DataBuffer_Add(e_Scene* scene, std::vector<float>& Payload, unsigned int& ID, unsigned int& Index) {
		if (scene->ObjectIDs[T::VectorPos].size() == 0) { ID = 1; }
		else { ID = scene->ObjectIDs[T::VectorPos].back() + 1; }

		scene->ObjectIDs[T::VectorPos].push_back(ID);

		//Inserts the torus vector to the end of the InstanceBuffer
		scene->DataBuffers[T::VectorPos].insert(T::DataBuffer.end(), Payload.begin(), Payload.end());

		//The objects Index is the end TorusIndicesex
		scene->ObjectIDs[T::VectorPos].size() - 1;
	}

	template<typename T>
	static void Generate_ID(e_Scene* scene, unsigned int& ID, unsigned int& Index) {

		for (int i = 0; i < T::EntitySize; i++) { scene->DataBuffers[T::VectorPos].push_back(NULL); }

		if (scene->ObjectIDs[T::VectorPos].size() == 0) { ID = 1; }
		else { ID = scene->ObjectIDs[T::VectorPos].back() + 1; }

		scene->ObjectIDs[T::VectorPos].push_back(ID);

		Index = scene->ObjectIDs[T::VectorPos].size() - 1;
	}

	template<typename T>
	static void DataBuffer_Remove(e_Scene* scene, unsigned int& Index) {
		
		//subtracts every sphere index, that was in front of deleted sphere by one.
		

		//removes info from instance buffer, stop rendering the torus.
		scene->DataBuffers[T::VectorPos].erase(scene->DataBuffers[T::VectorPos].begin() + Index * T::EntitySize,
			scene->DataBuffers[T::VectorPos].begin() + Index * T::EntitySize + T::EntitySize);

		//remoe pointer to objet

		if constexpr (std::is_same_v<T, e_Sphere>) { scene->Spheres.erase(scene->Spheres.begin() + Index);}
		if constexpr (std::is_same_v<T, e_Box>) { scene->Boxes.erase(scene->Boxes.begin() + Index);}

	}

	
	template<typename Primitive, typename T>
	static void Render(e_Window* win, e_Scene* scene, std::vector<T*> D_Objects) {
		unsigned int NumInstances;

		if constexpr (std::is_same_v<Primitive, e_Sphere>){NumInstances = scene->Spheres.size();}
		if constexpr (std::is_same_v<Primitive, e_Box>) { NumInstances = scene->Boxes.size(); }


		win->Shader[Primitive::VectorPos].Use();

		win->VertexBuffers[Primitive::VectorPos].Bind();
		win->ElementBuffers[Primitive::VectorPos].Bind();

		
	

		//puts instance data from scene object into IBO belonging to window object
		win->InstanceBuffers[Primitive::VectorPos].Bind();
		win->InstanceBuffers[Primitive::VectorPos].SetData(scene->DataBuffers[Primitive::VectorPos]);


		glDrawElementsInstanced(GL_TRIANGLES, scene->IndicesData[Primitive::VectorPos].size(), GL_UNSIGNED_INT, 0, NumInstances);

		
	}

	template<typename Primitive>
	static void Render_UsingDepthShader(e_Window* win, e_Scene& scene) {
		unsigned int NumInstances = scene.ObjectIDs[Primitive::VectorPos].size();

		//
		//std::cout << "fdgd" << " " << NumInstances << '\n';

		win->DepthShader[Primitive::VectorPos].Use();

		win->VertexBuffers[Primitive::VectorPos].Bind();
		win->ElementBuffers[Primitive::VectorPos].Bind();

		//puts instance data into IBO
		win->InstanceBuffers[Primitive::VectorPos].Bind();
		win->InstanceBuffers[Primitive::VectorPos].SetData(scene.DataBuffers[Primitive::VectorPos]);

		//Primitive::Shader.Use();

		glDrawElementsInstanced(GL_TRIANGLES, scene.IndicesData[Primitive::VectorPos].size(), GL_UNSIGNED_INT, 0, NumInstances);
	}

	
};