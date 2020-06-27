#pragma once
#ifndef __SYSTEM_MANAGER__
#define  __SYSTEM_MANAGER__ 1

#include <memory>
#include <unordered_map>
#include <bitset>
#include <system.h>
namespace VC{

	using Signature = std::bitset<32>;

	class SystemManager
	{
	public:
		template<typename T>
		std::shared_ptr<T> RegisterSystem()
		{
			const char* typeName = typeid(T).name();

			assert(mSystems.find(typeName) == mSystems.end() && "Registering system more than once.");

			auto system = std::make_shared<T>();
			mSystems.insert({ typeName, system });
			return system;
		}

		template<typename T>
		void SetSignature(Signature signature)
		{
			const char* typeName = typeid(T).name();

			assert(mSystems.find(typeName) != mSystems.end() && "System used before registered.");

			mSignatures.insert({ typeName, signature });
		}

		void EntityDestroyed(u32 entity)
		{
			for (auto const& pair : mSystems)
			{
				auto const& system = pair.second;


				system->entities_.erase(entity);
			}
		}

		void EntitySignatureChanged(u32 entity, Signature entitySignature)
		{
			for (auto const& pair : mSystems)
			{
				auto const& type = pair.first;
				auto const& system = pair.second;
				auto const& systemSignature = mSignatures[type];

				if ((entitySignature & systemSignature) == systemSignature)
				{
					system->entities_.insert(entity);
				}
				else
				{
					system->entities_.erase(entity);
				}
			}
		}

	private:
		std::unordered_map<const char*, Signature> mSignatures{};
		std::unordered_map<const char*, std::shared_ptr<System>> mSystems{};
	};

}

#endif