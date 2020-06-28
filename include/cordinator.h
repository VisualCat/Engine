#pragma once

#ifndef __CORDINATOR__
#define  __CORDINATOR__ 1

#include <componentmanager.h>
#include <systemmanager.h>
#include <entitymanager.h>
#include <memory>

using namespace VC;


class Coordinator
{
public:
	void Init()
	{
		componentManager_ = std::make_unique<ComponentManager>();
		entityManager_ = std::make_unique<EntityManager>();
		systemManager_ = std::make_unique<SystemManager>();
	}


	// Entity methods
	u32 CreateEntity()
	{
		return entityManager_->CreateEntity();
	}

	void DestroyEntity(u32 entity)
	{
		entityManager_->DestroyEntity(entity);

		componentManager_->EntityDestroyed(entity);

		systemManager_->EntityDestroyed(entity);
	}


	// Component methods
	template<typename T>
	void RegisterComponent()
	{
		componentManager_->RegisterComponent<T>();
	}

	template<typename T>
	void AddComponent(u32 entity, T component)
	{
		componentManager_->AddComponent<T>(entity, component);

		auto signature = entityManager_->GetSignature(entity);
		signature.set(componentManager_->GetComponentType<T>(), true);
		entityManager_->SetSignature(entity, signature);

		systemManager_->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	void RemoveComponent(u32 entity)
	{
		componentManager_->RemoveComponent<T>(entity);

		auto signature = entityManager_->GetSignature(entity);
		signature.set(componentManager_->GetComponentType<T>(), false);
		entityManager_->SetSignature(entity, signature);

		systemManager_->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	T& GetComponent(u32 entity)
	{
		return componentManager_->GetComponent<T>(entity);
	}

	template<typename T>
	u8 GetComponentType()
	{
		return componentManager_->GetComponentType<T>();
	}


	// System methods
	template<typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		return systemManager_->RegisterSystem<T>();
	}

	template<typename T>
	void SetSystemSignature(Signature signature)
	{
		systemManager_->SetSignature<T>(signature);
	}




private:
	std::unique_ptr<ComponentManager> componentManager_;
	std::unique_ptr<EntityManager> entityManager_;

	std::unique_ptr<SystemManager> systemManager_;

};

#endif
