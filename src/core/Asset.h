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
		static T *Load(Args &&...args) {
			static_assert(std::is_base_of<od::Asset, T>(), "od::Asset::Load<T>: T isn't derived from od::Asset");
			
			std::shared_ptr<T> asset = std::make_shared<T>(args...);

			std::unordered_map<std::string, std::shared_ptr<od::Asset>>::iterator it = s_Assets.find(asset->GetPath());
			if(it != s_Assets.end()) {
				OD_LOG_ERROR("od::Asset::Load<T>: Asset with path '" << asset->GetPath() << "' is already loaded!");
				return nullptr;
			}

			s_Assets.insert({asset->GetPath(), asset});
			return asset.get();
		}

		template<typename T>
		inline static T *GetAsset(const std::string_view &path) {
			static_assert(std::is_base_of<od::Asset, T>(), "od::Asset::GetAsset<T>: T isn't derived from od::Asset");

			std::unordered_map<std::string, std::shared_ptr<od::Asset>>::iterator it = s_Assets.find(std::string(path));
			if(it != s_Assets.end())
				return (T*)it->second.get();

			return nullptr;
		}

		template<typename T>
		inline static void UnloadAsset(const std::string_view &path) {
			static_assert(std::is_base_of<od::Asset, T>(), "od::Asset::UnloadAsset<T>: T isn't derived from od::Asset");
			
			std::unordered_map<std::string, std::shared_ptr<od::Asset>>::iterator it = s_Assets.find(std::string(path));
			if(it != s_Assets.end())
				s_Assets.erase(it);
			else 
				OD_LOG_ERROR("Failed to unload asset '" << path << "', the asset isn't present in s_Assets");
		}

	protected:
		static std::unordered_map<std::string, std::shared_ptr<od::Asset>> s_Assets;
		std::string m_Path;
	};
}
