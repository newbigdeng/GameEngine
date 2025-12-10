#pragma once
#include <filesystem>
#include <vector>
#include <string>

namespace eng
{
	class FileSystem
	{
	public:
		std::filesystem::path GetExecutableFolder() const;//获取可执行文件路径
		std::filesystem::path GetAssetsFolder() const;//获取资源文件路径

		std::vector<char> LoadFile(const std::filesystem::path& path);
		std::vector<char> LoadAssetFile(const std::string& relativePath);
		std::string LoadAssetFileText(const std::string& relativePath);
	};
}