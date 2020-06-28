#pragma once

#ifndef __COMPONENT_MANAGER__
#define  __COMPONENT_MANAGER__ 1

#include <any>
#include <memory>
#include <unordered_map>
#include <platform_types.h>
#include <componentarray.h>

namespace VC {
	class ComponentManager
	{
	public:
		template<typename T>
		void RegisterComponent()
		{
			const char* typeName = typeid(T).name();

			

			componentTypes_.insert({ typeName, nextComponentType_ });
			componentArrays_.insert({ typeName, std::make_shared<ComponentArray<T>>() });

			++nextComponentType_;
		}

		template<typename T>
		u8 GetComponentType()
		{
			const char* typeName = typeid(T).name();

		

			return componentTypes_[typeName];
		}

		template<typename T>
		void AddComponent(u32 entity, T component)
		{
			GetComponentArray<T>()->InsertData(entity, component);
		}

		template<typename T>
		void RemoveComponent(u32 entity)
		{
			GetComponentArray<T>()->RemoveData(entity);
		}

		template<typename T>
		T& GetComponent(u32 entity)
		{
			return GetComponentArray<T>()->GetData(entity);
		}

		void EntityDestroyed(u32 entity)
		{
			for (auto const& pair : componentArrays_)
			{
				auto const& component = pair.second;

				component->EntityDestroyed(entity);
			}
		}

	private:
		std::unordered_map<const char*, u8> componentTypes_{};
		std::unordered_map<const char*, std::shared_ptr<IComponentArray>> componentArrays_{};
		u8 nextComponentType_{};


		template<typename T>
		std::shared_ptr<ComponentArray<T>> GetComponentArray()
		{
			const char* typeName = typeid(T).name();


			return std::static_pointer_cast<ComponentArray<T>>(componentArrays_[typeName]);
		}
	};
}
#endif