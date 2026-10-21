#include "../include/SavedUserManager.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <stdexcept>

// ====================================
// Validate Save File Format
// ====================================

bool SavedUserManager::HasSupportedSaveFormat(
    const std::filesystem::path& path)
{
    std::ifstream file(path);
    std::string version;

    return std::getline(file, version) &&
        (version == "BBT_SAVE_V2" ||
         version == "BBT_SAVE_V3" ||
         version == "BBT_SAVE_V4" ||
         version == "BBT_SAVE_V5" ||
         version == "BBT_SAVE_V6");
}

// ====================================
// Find Saved Users
// ====================================

std::vector<std::filesystem::path>
SavedUserManager::FindSaveFiles(bool supportedOnly)
{
    const std::string prefix = "researcher_save_";
    const std::string suffix = ".txt";

    std::vector<std::filesystem::path> saveFiles;

    std::error_code error;
    std::filesystem::directory_iterator entry(".", error);
    const std::filesystem::directory_iterator end;

    while (!error && entry != end)
    {
        const std::filesystem::path path = entry->path();

        if (entry->is_regular_file(error) &&
            !entry->is_symlink(error))
        {
            const std::string filename = path.filename().string();

            const bool isLegacySave =
                filename == "researcher_save.txt";

            const bool hasValidFilename =
                filename.rfind(prefix, 0) == 0 &&
                filename.size() > prefix.size() + suffix.size() &&
                filename.compare(
                    filename.size() - suffix.size(),
                    suffix.size(),
                    suffix) == 0;

            bool hasValidUsername = false;

            if (hasValidFilename)
            {
                const std::string username = filename.substr(
                    prefix.size(),
                    filename.size() - prefix.size() - suffix.size());

                hasValidUsername =
                    !username.empty() &&
                    std::all_of(
                        username.begin(),
                        username.end(),
                        [](unsigned char ch)
                        {
                            return std::isalnum(ch) ||
                                   ch == '-' ||
                                   ch == '_';
                        });
            }

            const bool isUserSave =
                hasValidFilename && hasValidUsername;

            if ((isLegacySave || isUserSave) &&
                (!supportedOnly || HasSupportedSaveFormat(path)))
            {
                saveFiles.push_back(path);
            }
        }

        if (!error)
        {
            entry.increment(error);
        }
    }

    if (error)
    {
        throw std::runtime_error(
            "Unable to read the saved-user folder.");
    }

    std::sort(saveFiles.begin(), saveFiles.end());

    return saveFiles;
}

// ====================================
// Get Saved User Label
// ====================================

std::string SavedUserManager::SavedUserLabel(
    const std::filesystem::path& path)
{
    std::ifstream file(path);

    std::string version;
    std::string name;

    if (std::getline(file, version) &&
        (version == "BBT_SAVE_V2" ||
         version == "BBT_SAVE_V3" ||
         version == "BBT_SAVE_V4" ||
         version == "BBT_SAVE_V5" ||
         version == "BBT_SAVE_V6") &&
        std::getline(file, name) &&
        !name.empty())
    {
        return name;
    }

    return path.filename().string() +
        " [unsupported or unreadable]";
}

// ====================================
// Generate Safe Save Filename
// ====================================

std::string SavedUserManager::SaveFilenameFor(
    const std::string& name)
{
    std::string safeName;

    for (unsigned char ch : name)
    {
        if (std::isalnum(ch) || ch == '-' || ch == '_')
        {
            safeName += static_cast<char>(ch);
        }
        else if (safeName.empty() || safeName.back() != '_')
        {
            safeName += '_';
        }
    }

    while (!safeName.empty() &&
           safeName.back() == '_')
    {
        safeName.pop_back();
    }

    if (safeName.empty())
    {
        safeName = "Researcher";
    }

    return "researcher_save_" + safeName + ".txt";
}