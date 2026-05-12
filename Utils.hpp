#pragma once

#include <vector>
#include "libs/glm/glm.hpp"
#include "libs/glm/gtc/matrix_transform.hpp"
#include "libs/glm/gtc/type_ptr.hpp"


static int BinarySearch(std::vector<uint32_t>& vec, int target) {
	int left = 0;
	int right = vec.size() - 1;
	while (left <= right) {
		int mid = left + (right - left) * 0.5;
		if (vec[mid] == target)
			return mid;
		if (vec[mid] < target)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return -1;
}

inline std::vector<float> Ngonxz(float cx, float cy, float cz, float spx, float spy, float spz, float deg, int itr) {
	std::vector<float> vect;
	vect.push_back(((spx - cx) * cos(glm::radians(deg * itr)) - sin(glm::radians(deg * itr)) * (spz - cz)) + cx);
	vect.push_back(cy);
	vect.push_back(((spz - cz) * cos(glm::radians(deg * itr)) + sin(glm::radians(deg * itr)) * (spx - cx)) + cz);
	return vect;
}

inline std::vector<float> Ngonyz(float cx, float cy, float cz, float spx, float spy, float spz, float deg, int itr) {
	std::vector<float> vect;
	vect.push_back(cx);
	vect.push_back(((spy - cy) * cos(glm::radians(deg * itr)) - sin(glm::radians(deg * itr)) * (spz - cz)) + cy);
	vect.push_back(((spz - cz) * cos(glm::radians(deg * itr)) + sin(glm::radians(deg * itr)) * (spy - cy)) + cz);
	return vect;
}

inline std::vector<float> Ngonxy(float cx, float cy, float cz, float spx, float spy, float spz, float deg, int itr) {
	std::vector<float> vect;
	vect.push_back(((spx - cx) * cos(glm::radians(deg * itr)) - sin(glm::radians(deg * itr)) * (spy - cy)) + cx);
	vect.push_back(((spy - cy) * cos(glm::radians(deg * itr)) + sin(glm::radians(deg * itr)) * (spx - cx)) + cy);
	vect.push_back(cz);
	return vect;
}

//ovals 
inline std::vector<float> Ngonxy(float cx, float cy, float cz, float spxa, float spya, float spza, float spxb, float spyb, float spzb, float deg, int itr) {
	std::vector<float> vect;
	vect.push_back(((spxa - cx) * cos(glm::radians(deg * itr)) - sin(glm::radians(deg * itr)) * (spya - cy)) + cx);
	vect.push_back(((spyb - cy) * cos(glm::radians(deg * itr)) + sin(glm::radians(deg * itr)) * (spxb - cx)) + cy);
	vect.push_back(cz);
	return vect;
}

inline std::vector<float> Ngonxz(float cx, float cy, float cz, float spxa, float spya, float spza, float spxb, float spyb, float spzb, float deg, int itr) {
	std::vector<float> vect;
	vect.push_back(((spxa - cx) * cos(glm::radians(deg * itr)) - sin(glm::radians(deg * itr)) * (spza - cz)) + cx);
	vect.push_back(cy);
	vect.push_back(((spzb - cz) * cos(glm::radians(deg * itr)) + sin(glm::radians(deg * itr)) * (spxb - cx)) + cz);
	return vect;
}