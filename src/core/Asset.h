#pragma once

#include "Libs.h"
#include "Log.h"
#include <unordered_map>

namespace od {
	class Asset {
	public:
		virtual ~Asset();

		inline const std::string GetPath() const { return m_Path; }
		
		template<typename T, typename... Args>
		static std::shared_ptr<T> Load(std::string_view path, Args &&...args) {
			static_assert(std::is_base_of<od::Asset, T>(), "od::Asset::Load<T>: T isn't derived from od::Asset");

			std::shared_ptr<T> asset = std::make_shared<T>(args...);
			asset->m_Path = path;

			if(asset->OnLoad())
				OD_LOG_INFO("Asset '" << path << "' has been loaded");
			else
				OD_LOG_ERROR("Failed to load asset '" << path << "'");

			s_Assets.insert({std::string(path), asset});

			return asset;
		}

		template<typename T>
		inline static std::shared_ptr<T> GetAsset(std::string_view path) {
			static_assert(std::is_base_of<od::Asset, T>(), "od::Asset::GetAsset<T>: T isn't derived from od::Asset");

			std::unordered_map<std::string, std::shared_ptr<od::Asset>>::iterator it = s_Assets.find(std::string(path));

			if(it != s_Assets.end())
				return static_pointer_cast<T>(it->second);

			return nullptr;
		}

	protected:
		virtual bool OnLoad();

	protected:
		static std::unordered_map<std::string, std::shared_ptr<od::Asset>> s_Assets;
		std::string m_Path;
	};
}
