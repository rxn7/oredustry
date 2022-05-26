#include "Asset.h"

std::unordered_map<std::string, std::shared_ptr<od::Asset>> od::Asset::s_Assets;

od::Asset::~Asset() {
}

bool od::Asset::OnLoad() {
	return true;
}
