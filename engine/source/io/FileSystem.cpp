#include "FileSystem.h"
#include <fstream>

#include "config.h"

#if defined _WIN32
#include <Windows.h>
#elif defined (__APPLE__)
#include <mach-o/dyld.h>
#elif defined (__linux__)
#include <unistd.h>
#include <limits.h>
#endif

namespace eng
{
	std::filesystem::path FileSystem::GetExecutableFolder() const
	{
#if defined _WIN32
		wchar_t buf[MAX_PATH];
		GetModuleFileNameW(NULL, buf, MAX_PATH);
		return std::filesystem::path(buf).remove_filename();
#elif defined (__APPLE__)
		uint32_t size = 0;
		_NSGetExecutablePath(nullptr, &size);
		std::string tmp(size, '\0');
		_NSGetExecutablePath(tmp.data(), &size);
		return std::filesystem::weakly_canonical(std::filesystem::path(tmp)).remove_filename();
#elif defined (__linux__)
		return std::filesystem::weakly_canonical(std::filesystem::read_symlink("/proc/self/exe")).remove_filename();
#else
		return std::filesystem::current_path();
#endif

		return std::filesystem::path();
	}

	std::filesystem::path FileSystem::GetAssetsFolder() const
	{
#if defined (ASSETS_ROOT)
		auto path = std::filesystem::path(std::string(ASSETS_ROOT));
		if (std::filesystem::exists(path))
			return path;
#endif
		return std::filesystem::weakly_canonical(GetExecutableFolder())/"assets";
	}


	std::vector<char> FileSystem::LoadFile(const std::filesystem::path& path)
	{
		std::ifstream file(path, std::ios::binary | std::ios::ate);//以二进制读取，指针读到末尾
		if(!file.is_open())return {};

		auto size = file.tellg();//返回当前读取指针的位置

		file.seekg(0);//将读取指针移动到文件起始位置

		std::vector<char>buffer(size);
		
		if (!file.read(buffer.data(), size))return {};//读取文件内容到缓冲区

		return buffer;
	}

	std::vector<char> FileSystem::LoadAssetFile(const std::string& relativePath)
	{
		return LoadFile(GetAssetsFolder() / relativePath);
	}

	std::string FileSystem::LoadAssetFileText(const std::string& relativePath)
	{
		auto buffer = LoadAssetFile(relativePath);
		return std::string(buffer.begin(),buffer.end());
	}

}