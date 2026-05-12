#pragma once
#include "Utils.hpp"

class e_Scene; class e_DirectionalLight; 

template <typename T>
class EntityAttribute {
	friend T;

public:
	T* p_EntityObject = nullptr;
	float Value;
	unsigned char Offset;
	e_Scene* scene = nullptr;

private:
	__forceinline void Set(e_Scene* scene) {
		this->scene = scene;
	}
	EntityAttribute() {};
	EntityAttribute(unsigned char Offset, T* p_EntityObject) : Offset(Offset), p_EntityObject(p_EntityObject) {}

public:
	__forceinline operator float() const { return Value; }

	__forceinline EntityAttribute& operator=(const float NewValue) {
		unsigned int& Index = p_EntityObject->Index;
		unsigned int& ID = p_EntityObject->ID;
		if (Index >= scene->ObjectIDs[T::VectorPos].size() or scene->ObjectIDs[T::VectorPos][Index] != ID) {
			Index = BinarySearch(scene->ObjectIDs[T::VectorPos], ID);
			if (Index == 4294967295) return *this;
		}
		scene->DataBuffers[T::VectorPos][Index * T::EntitySize + Offset] = NewValue;
		Value = NewValue;
		return *this;
	}

	__forceinline EntityAttribute& operator=(const EntityAttribute& OtherObj) {
		unsigned int& Index = p_EntityObject->Index;
		unsigned int& ID = p_EntityObject->ID;
		float NewValue = OtherObj.Value;
		if (Index >= scene->ObjectIDs[T::VectorPos].size() or scene->ObjectIDs[T::VectorPos][Index] != ID) {
			Index = BinarySearch(scene->ObjectIDs[T::VectorPos], ID);
			if (Index == 4294967295) return *this;
		}
		scene->DataBuffers[T::VectorPos][Index * T::EntitySize + Offset] = NewValue;
		Value = NewValue;
		return *this;
	}

	__forceinline EntityAttribute& operator+=(const float OtherValue) {
		unsigned int& Index = p_EntityObject->Index;
		unsigned int& ID = p_EntityObject->ID;
		if (Index >= scene->ObjectIDs[T::VectorPos].size() or scene->ObjectIDs[T::VectorPos][Index] != ID) {
			Index = BinarySearch(scene->ObjectIDs[T::VectorPos], ID);
			if (Index == 4294967295) return *this;
		}
		Value += OtherValue;
		scene->DataBuffers[T::VectorPos][Index * T::EntitySize + Offset] = Value;
		return *this;
	}

	__forceinline EntityAttribute& operator-=(const float OtherValue) {
		unsigned int& Index = p_EntityObject->Index;
		unsigned int& ID = p_EntityObject->ID;
		if (Index >= scene->ObjectIDs[T::VectorPos].size() or scene->ObjectIDs[T::VectorPos][Index] != ID) {
			Index = BinarySearch(scene->ObjectIDs[T::VectorPos], ID);
			if (Index == 4294967295) return *this;
		}
		Value -= OtherValue;
		scene->DataBuffers[T::VectorPos][Index * T::EntitySize + Offset] = Value;
		return *this;
	}

	__forceinline EntityAttribute& operator*=(const float OtherValue) {
		unsigned int& Index = p_EntityObject->Index;
		unsigned int& ID = p_EntityObject->ID;
		if (Index >= scene->ObjectIDs[T::VectorPos].size() or scene->ObjectIDs[T::VectorPos][Index] != ID) {
			Index = BinarySearch(scene->ObjectIDs[T::VectorPos], ID);
			if (Index == 4294967295) return *this;
		}
		Value *= OtherValue;
		scene->DataBuffers[T::VectorPos][Index * T::EntitySize + Offset] = Value;
		return *this;
	}

	__forceinline EntityAttribute& operator/=(const float OtherValue) {
		unsigned int& Index = p_EntityObject->Index;
		unsigned int& ID = p_EntityObject->ID;
		if (Index >= scene->ObjectIDs[T::VectorPos].size() or scene->ObjectIDs[T::VectorPos][Index] != ID) {
			Index = BinarySearch(scene->ObjectIDs[T::VectorPos], ID);
			if (Index == 4294967295) return *this;
		}
		Value *= OtherValue;
		scene->DataBuffers[T::VectorPos][Index * T::EntitySize + Offset] = Value;
		return *this;
	}

};

template <typename T>
class EntityAttribute_Packed {
	friend T;

public:
	T* p_EntityObject = nullptr;
	unsigned char Offset;
	unsigned char BitOffset;
	unsigned char Value;
	e_Scene* scene;

private:
	__forceinline void Set(e_Scene* scene) {
		this->scene = scene;
	}
	EntityAttribute_Packed() {};

	EntityAttribute_Packed(unsigned char Offset, unsigned char BitOffset, T* p_EntityObject) : Offset(Offset), BitOffset(BitOffset), p_EntityObject(p_EntityObject) {}

public:
	inline operator float() const { return Value; }

	__forceinline EntityAttribute_Packed& operator=(const unsigned char NewValue) {
		unsigned int& Index = p_EntityObject->Index;
		unsigned int& ID = p_EntityObject->ID;
		if (Index >= scene->ObjectIDs[T::VectorPos].size() or scene->ObjectIDs[T::VectorPos][Index] != ID) {
			Index = BinarySearch(scene->ObjectIDs[T::VectorPos], ID);
			if (Index == 4294967295) return *this;
		}
		Value = NewValue;

		union { float f; unsigned int u; } tmp;

		tmp.f = scene->DataBuffers[T::VectorPos][Index * scene->EntitySize + Offset];

		tmp.u &= ~(0xFFu << BitOffset);
		tmp.u |= (static_cast<unsigned int>(Value) << BitOffset);

		scene->DataBuffers[T::VectorPos][Index * T::EntitySize + Offset] = tmp.f;


		return *this;
	}
	__forceinline EntityAttribute_Packed& operator=(const EntityAttribute_Packed& OtherObj) {
		unsigned int& Index = p_EntityObject->Index;
		unsigned int& ID = p_EntityObject->ID;
		if (Index >= scene->ObjectIDs[T::VectorPos].size() or scene->ObjectIDs[T::VectorPos][Index] != ID) {
			Index = BinarySearch(scene->ObjectIDs[T::VectorPos], ID);
			if (Index == 4294967295) return *this;
		}
		Value = OtherObj.Value;

		union { float f; unsigned int u; } tmp;

		tmp.f = scene->DataBuffers[T::VectorPos][Index * T::EntitySize + Offset];

		tmp.u &= ~(0xFFu << BitOffset);
		tmp.u |= (static_cast<unsigned int>(Value) << BitOffset);

		scene->DataBuffers[T::VectorPos][Index * T::EntitySize + Offset] = tmp.f;


		return *this;


	}

	__forceinline EntityAttribute_Packed& operator+=(const unsigned char OtherValue) {
		unsigned int& Index = p_EntityObject->Index;
		unsigned int& ID = p_EntityObject->ID;
		if (Index >= scene->ObjectIDs[T::VectorPos].size() or scene->ObjectIDs[T::VectorPos][Index] != ID) {
			Index = BinarySearch(scene->ObjectIDs[T::VectorPos], ID);
			if (Index == 4294967295) return *this;
		}
		Value += OtherValue;

		union { float f; unsigned int u; } tmp;

		tmp.f = scene->DataBuffers[T::VectorPos][Index * T::EntitySize + Offset];

		tmp.u &= ~(0xFFu << BitOffset);
		tmp.u |= (static_cast<unsigned int>(Value) << BitOffset);

		scene->DataBuffers[T::VectorPos][Index * T::EntitySize + Offset] = tmp.f;


		return *this;
	}

	__forceinline EntityAttribute_Packed& operator-=(const unsigned char OtherValue) {
		unsigned int& Index = p_EntityObject->Index;
		unsigned int& ID = p_EntityObject->ID;
		if (Index >= scene->ObjectIDs[T::VectorPos].size() or scene->ObjectIDs[T::VectorPos][Index] != ID) {
			Index = BinarySearch(scene->ObjectIDs[T::VectorPos], ID);
			if (Index == 4294967295) return *this;
		}
		Value -= OtherValue;

		union { float f; unsigned int u; } tmp;

		tmp.f = scene->DataBuffers[T::VectorPos][Index * T::EntitySize + Offset];

		tmp.u &= ~(0xFFu << BitOffset);
		tmp.u |= (static_cast<unsigned int>(Value) << BitOffset);

		scene->DataBuffers[T::VectorPos][Index * T::EntitySize + Offset] = tmp.f;


		return *this;
	}

	__forceinline EntityAttribute_Packed& operator*=(const unsigned char OtherValue) {
		unsigned int& Index = p_EntityObject->Index;
		unsigned int& ID = p_EntityObject->ID;
		if (Index >= scene->ObjectIDs[T::VectorPos].size() or scene->ObjectIDs[T::VectorPos][Index] != ID) {
			Index = BinarySearch(scene->ObjectIDs[T::VectorPos], ID);
			if (Index == 4294967295) return *this;
		}
		Value *= OtherValue;

		union { float f; unsigned int u; } tmp;

		tmp.f = scene->DataBuffers[T::VectorPos][Index * scene->EntitySize + Offset];

		tmp.u &= ~(0xFFu << BitOffset);
		tmp.u |= (static_cast<unsigned int>(Value) << BitOffset);

		scene->DataBuffers[T::VectorPos][Index * T::EntitySize + Offset] = tmp.f;


		return *this;
	}

	__forceinline EntityAttribute_Packed& operator/=(const unsigned char OtherValue) {
		unsigned int& Index = p_EntityObject->Index;
		unsigned int& ID = p_EntityObject->ID;
		if (Index >= scene->ObjectIDs[T::VectorPos].size() or scene->ObjectIDs[T::VectorPos][Index] != ID) {
			Index = BinarySearch(scene->ObjectIDs[T::VectorPos], ID);
			if (Index == 4294967295) return *this;
		}
		Value /= OtherValue;

		union { float f; unsigned int u; } tmp;

		tmp.f = scene->DataBuffers[T::VectorPos][Index * T::EntitySize + Offset];

		tmp.u &= ~(0xFFu << BitOffset);
		tmp.u |= (static_cast<unsigned int>(Value) << BitOffset);

		scene->DataBuffers[T::VectorPos][Index * T::EntitySize + Offset] = tmp.f;


		return *this;
	}

};
