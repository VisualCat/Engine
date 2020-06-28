#pragma once

#ifndef __ENTITY_MANAGER__
#define  __ENTITY_MANAGER__ 1

#define kMAX_ENTITIES 500000

#include <array>
#include <queue>

namespace VC {
	class EntityManager
	{
	public:
		EntityManager()
		{
			for (u32 entity = 0; entity < kMAX_ENTITIES; ++entity)
			{
				avaliableEntities_.push(entity);
			}
		}

		u32 CreateEntity()
		{


			u32 id = avaliableEntities_.front();
			avaliableEntities_.pop();
			++activeEntityCount_;

			return id;
		}

		void DestroyEntity(u32 entity)
		{


			signatures_[entity].reset();
			avaliableEntities_.push(entity);
			--activeEntityCount_;
		}

		void SetSignature(u32 entity, Signature signature)
		{


			signatures_[entity] = signature;
		}

		Signature GetSignature(u32 entity)
		{


			return signatures_[entity];
		}

	private:
		std::queue<u32> avaliableEntities_{};
		std::array<Signature, kMAX_ENTITIES> signatures_{};
		uint32_t activeEntityCount_{};
	};
}
#endif