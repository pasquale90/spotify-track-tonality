#ifndef FIX_PATHS_H
#define FIX_PATHS_H

// TODO1:Requires adjustment tailored to the Eyeharp program
auto getCredentialsAbsPath = [](const std::string& relativePath) -> std::string {
    std::filesystem::path rootDir = std::filesystem::absolute(__FILE__).parent_path();
    std::filesystem::path targetPath = rootDir / relativePath;
    return targetPath.lexically_normal().string();
};
const std::string credentialsFile = getCredentialsAbsPath("../spotify/credentials.json");

#endif