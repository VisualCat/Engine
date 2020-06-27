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
		mComponentManager = std::make_unique<ComponentManager>();
		mEntityManager = std::make_unique<EntityManager>();
		mSystemManager = std::make_unique<SystemManager>();
	}


	// Entity methods
	u32 CreateEntity()
	{
		return mEntityManager->CreateEntity();
	}

	void DestroyEntity(u32 entity)
	{
		mEntityManager->DestroyEntity(entity);

		mComponentManager->EntityDestroyed(entity);

		mSystemManager->EntityDestroyed(entity);
	}


	// Component methods
	template<typename T>
	void RegisterComponent()
	{
		mComponentManager->RegisterComponent<T>();
	}

	template<typename T>
	void AddComponent(u32 entity, T component)
	{
		mComponentManager->AddComponent<T>(entity, component);

		auto signature = mEntityManager->GetSignature(entity);
		signature.set(mComponentManager->GetComponentType<T>(), true);
		mEntityManager->SetSignature(entity, signature);

		mSystemManager->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	void RemoveComponent(u32 entity)
	{
		mComponentManager->RemoveComponent<T>(entity);

		auto signature = mEntityManager->GetSignature(entity);
		signature.set(mComponentManager->GetComponentType<T>(), false);
		mEntityManager->SetSignature(entity, signature);

		mSystemManager->EntitySignatureChanged(entity, signature);
	}

	template<typename T>
	T& GetComponent(u32 entity)
	{
		return mComponentManager->GetComponent<T>(entity);
	}

	template<typename T>
	u8 GetComponentType()
	{
		return mComponentManager->GetComponentType<T>();
	}


	// System methods
	template<typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		return mSystemManager->RegisterSystem<T>();
	}

	template<typename T>
	void SetSystemSignature(Signature signature)
	{
		mSystemManager->SetSignature<T>(signature);
	}




private:
	std::unique_ptr<ComponentManager> mComponentManager;
	std::unique_ptr<EntityManager> mEntityManager;

	std::unique_ptr<SystemManager> mSystemManager;

};

#endif
