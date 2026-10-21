#pragma once

#include <filesystem>
#include <string>
#include <vector>

// ====================================
// SavedUserManager Class
//
// Handles saved-user file discovery,
// filename validation, and profile labels.
//
// SaveManager remains responsible for
// saving and restoring progress.
// ====================================

class SavedUserManager
{
public:
    static bool HasSupportedSaveFormat(
        const std::filesystem::path& path);

    static std::vector<std::filesystem::path> FindSaveFiles(
        bool supportedOnly);

    static std::string SavedUserLabel(
        const std::filesystem::path& path);

    static std::string SaveFilenameFor(
        const std::string& name);
};