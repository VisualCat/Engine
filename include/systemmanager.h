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

			assert(systems_.find(typeName) == systems_.end() && "Registering system more than once.");

			auto system = std::make_shared<T>();
			systems_.insert({ typeName, system });
			return system;
		}

		template<typename T>
		void SetSignature(Signature signature)
		{
			const char* typeName = typeid(T).name();

			assert(systems_.find(typeName) != systems_.end() && "System used before registered.");

			signatures_.insert({ typeName, signature });
		}

		void EntityDestroyed(u32 entity)
		{
			for (auto const& pair : systems_)
			{
				auto const& system = pair.second;


				system->entities_.erase(entity);
			}
		}

		void EntitySignatureChanged(u32 entity, Signature entitySignature)
		{
			for (auto const& pair : systems_)
			{
				auto const& type = pair.first;
				auto const& system = pair.second;
				auto const& systemSignature = signatures_[type];

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
		std::unordered_map<const char*, Signature> signatures_{};
		std::unordered_map<const char*, std::shared_ptr<System>> systems_{};
	};

}

#endif