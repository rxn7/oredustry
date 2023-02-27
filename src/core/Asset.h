#pragma once

#include "Libs.h"
#include "Log.h"
#include <unordered_map>

namespace od {
	class Asset {
	public:
		Asset(const std::string &path);
		virtual ~Asset();

		inline const std::string GetPath() const { return m_Path; }
		
		template<typename T, typename... Args>
		static T *Load(const std::string &unique_id, Args &&...args) {
			static_assert(std::is_base_of<od::Asset, T>(), "od::Asset::Load<T>: T isn't derived from od::Asset");
			
			const std::shared_ptr<T> asset = std::make_shared<T>(args...);

			const std::unordered_map<std::string, std::shared_ptr<od::Asset>>::iterator it = s_Assets.find(unique_id);
			if(it != s_Assets.end()) {
				OD_LOG_ERROR("od::Asset::Load<T>: Asset with UID '" << unique_id << "' is already loaded!");
				return nullptr;
			}

			s_Assets.insert({unique_id, asset});
			return asset.get();
		}

		template<typename T>
		inline static T *Get(const std::string &unique_id) {
			static_assert(std::is_base_of<od::Asset, T>(), "od::Asset::Get<T>: T isn't derived from od::Asset");

			const std::unordered_map<std::string, std::shared_ptr<od::Asset>>::iterator it = s_Assets.find(unique_id);
			if(it != s_Assets.end())
				return (T*)it->second.get();

			OD_LOG_ERROR("od::Asset::Get<T>: Failed to find asset with UID '" << unique_id << '\'');
			return nullptr;
		}

		template<typename T>
		inline static void Unload(const std::string &unique_id) {
			static_assert(std::is_base_of<od::Asset, T>(), "od::Asset::Unload<T>: T isn't derived from od::Asset");
			
			const std::unordered_map<std::string, std::shared_ptr<od::Asset>>::iterator it = s_Assets.find(unique_id);
			if(it != s_Assets.end())
				s_Assets.erase(it);
			else 
				OD_LOG_ERROR("Failed to unload asset of UID '" << unique_id << "', the asset isn't present in s_Assets");
		}

	protected:
		static std::unordered_map<std::string, std::shared_ptr<od::Asset>> s_Assets;
		std::string m_Path;
	};
}
