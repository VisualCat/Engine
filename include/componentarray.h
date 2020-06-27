#pragma once

#ifndef __COMPONENT_ARRAY__
#define  __COMPONENT_ARRAY__ 1
#define kMAX_ENTITIES 5000

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
			size_t newIndex = mSize;
			mEntityToIndexMap[entity] = newIndex;
			mIndexToEntityMap[newIndex] = entity;
			mComponentArray[newIndex] = component;
			++mSize;
		}

		void RemoveData(u32 entity)
		{
		

			// Copy element at end into deleted element's place to maintain density
			size_t indexOfRemovedEntity = mEntityToIndexMap[entity];
			size_t indexOfLastElement = mSize - 1;
			mComponentArray[indexOfRemovedEntity] = mComponentArray[indexOfLastElement];

			// Update map to point to moved spot
			u32 entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
			mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
			mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

			mEntityToIndexMap.erase(entity);
			mIndexToEntityMap.erase(indexOfLastElement);

			--mSize;
		}

		T& GetData(u32 entity)
		{


			return mComponentArray[mEntityToIndexMap[entity]];
		}

		void EntityDestroyed(u32 entity) override
		{
			if (mEntityToIndexMap.find(entity) != mEntityToIndexMap.end())
			{
				RemoveData(entity);
			}
		}

	private:
		std::array<T, kMAX_ENTITIES> mComponentArray{};
		std::unordered_map<u32, size_t> mEntityToIndexMap{};
		std::unordered_map<size_t, u32> mIndexToEntityMap{};
		size_t mSize{};
	};


}

#endif