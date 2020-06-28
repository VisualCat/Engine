#pragma once

#ifndef __COMPONENT_ARRAY__
#define  __COMPONENT_ARRAY__ 1
#define kMAX_ENTITIES 500000

#include <array>
#include <unordered_map>

namespace VC {

	class IComponentArray
	{
	public:
		virtual ~IComponentArray() = default;
		virtual void EntityDestroyed(u32 entity) = 0;
	};

	template<typename T>
	class ComponentArray : public IComponentArray
	{
	public:
		void InsertData(u32 entity, T component)
		{
		
			// Put new entry at end
			size_t newIndex = size_;
			entityToIndexMap_[entity] = newIndex;
			indexToEntityMap_[newIndex] = entity;
			componentArray_[newIndex] = component;
			++size_;
		}

		void RemoveData(u32 entity)
		{
		

			// Copy element at end into deleted element's place to maintain density
			size_t indexOfRemovedEntity = entityToIndexMap_[entity];
			size_t indexOfLastElement = size_ - 1;
			componentArray_[indexOfRemovedEntity] = componentArray_[indexOfLastElement];

			// Update map to point to moved spot
			u32 entityOfLastElement = indexToEntityMap_[indexOfLastElement];
			entityToIndexMap_[entityOfLastElement] = indexOfRemovedEntity;
			indexToEntityMap_[indexOfRemovedEntity] = entityOfLastElement;

			entityToIndexMap_.erase(entity);
			indexToEntityMap_.erase(indexOfLastElement);

			--size_;
		}

		T& GetData(u32 entity)
		{


			return componentArray_[entityToIndexMap_[entity]];
		}

		void EntityDestroyed(u32 entity) override
		{
			if (entityToIndexMap_.find(entity) != entityToIndexMap_.end())
			{
				RemoveData(entity);
			}
		}

	private:
		std::array<T, kMAX_ENTITIES> componentArray_{};
		std::unordered_map<u32, size_t> entityToIndexMap_{};
		std::unordered_map<size_t, u32> indexToEntityMap_{};
		size_t size_{};
	};


}

#endif