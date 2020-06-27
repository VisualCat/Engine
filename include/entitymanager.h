#pragma once

#ifndef __ENTITY_MANAGER__
#define  __ENTITY_MANAGER__ 1

#define kMAX_ENTITIES 5000

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
				mAvailableEntities.push(entity);
			}
		}

		u32 CreateEntity()
		{


			u32 id = mAvailableEntities.front();
			mAvailableEntities.pop();
			++mLivingEntityCount;

			return id;
		}

		void DestroyEntity(u32 entity)
		{


			mSignatures[entity].reset();
			mAvailableEntities.push(entity);
			--mLivingEntityCount;
		}

		void SetSignature(u32 entity, Signature signature)
		{


			mSignatures[entity] = signature;
		}

		Signature GetSignature(u32 entity)
		{


			return mSignatures[entity];
		}

	private:
		std::queue<u32> mAvailableEntities{};
		std::array<Signature, kMAX_ENTITIES> mSignatures{};
		uint32_t mLivingEntityCount{};
	};
}
#endif