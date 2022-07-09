#pragma once

#include "Libs.h"
#include "Log.h"
#include <vector>

namespace od {
	class Entity {
	public:
		Entity(const glm::f32vec2 &position = {0,0});

		inline glm::f32vec2 GetPosition() const { return m_Position; }
		inline bool IsQueuedForDestruction() const { return m_IsQueuedForDestruction; }
		inline void Destroy() { m_IsQueuedForDestruction = true; }
		
		template<typename T>
		static void DeleteDestroyedEntities(std::vector<T> &ents) {
			static_assert(std::is_base_of<od::Entity, T>(), "DeleteDestroyedEntities: T isn't derived from od::Entity!");

			typename std::vector<T>::iterator it = ents.begin();
			while(it != ents.end()) {
				od::Entity *ent = static_cast<od::Entity*>(&*it);

				if(ent->IsQueuedForDestruction())
					it = ents.erase(it);
				else
					++it;
			}
		}

		virtual void Awake() {}
		virtual void Update(uint32_t deltaTime) {}
		virtual void Render() {}

	protected:
		bool m_IsQueuedForDestruction = false;
		glm::f32vec2 m_Position;
	};
}
