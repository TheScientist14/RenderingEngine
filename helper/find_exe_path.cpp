#include "find_exe_path.h"

#include <filesystem>

#if WIN32

#include <Windows.h>

#endif

namespace {
#ifdef WIN32
    char exePath[MAX_PATH + 1] = {0};
#else
    char exePath[512] = { 0 };
#endif

    std::string_view exePathView;
}

std::string_view GetAppPath() {
    if (exePath[0] == 0) {
#ifdef WIN32
        HMODULE exeModule = GetModuleHandleA(nullptr);
        uint32_t length = GetModuleFileNameA(exeModule, exePath, MAX_PATH);

        for (uint32_t i = 0; i < length; ++i) {
            if (exePath[i] == '\\') {
                exePath[i] = '/';
            }
        }
        exePathView = std::string_view(exePath, length);
#else
        ssize_t len = ::readlink("/proc/self/exe", exePath, sizeof(exePath) - 1);
    if (len != -1)
    {
    exePath[len] = '\0';
    char* posBack = strrchr(exePath, '/');
    exePathView = std::string_view(exePath, len);
    chdir(exePathView.begin());
    }
#endif
    }
    return exePathView;
}

std::string_view getRootPath() {

    std::filesystem::path appPath(GetAppPath());
    auto appDir = appPath.parent_path();
    auto shaderPath = appDir / "shaders";
    auto vShaderPath = shaderPath / "defaultVertexShader.glsl";
    auto fShaderPath = shaderPath / "defaultFragmentShader.glsl";
    std::string_view path = GetAppPath();
    char *rootFolder = "/RenderingEngine";
    int pos = path.rfind(rootFolder);
    return path.substr(0, pos + strlen(rootFolder));

}
