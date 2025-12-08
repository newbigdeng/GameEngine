#pragma once
#include <filesystem>

namespace eng
{
	class FileSystem
	{
	public:
		std::filesystem::path GetExecutableFolder() const;//获取可执行文件路径
		std::filesystem::path GetAssetsFolder() const;//获取资源文件路径
	};
}