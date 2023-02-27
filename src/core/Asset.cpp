#include "Asset.h"

std::unordered_map<std::string, std::shared_ptr<od::Asset>> od::Asset::s_Assets;

od::Asset::Asset(const std::string &path) : m_Path(path) {
}

od::Asset::~Asset() {
}