#pragma once

#include <string>
#include <vector>
#include "Tool.h"

class Inventory
{
private:
    std::vector<Tool> ownedTools;

public:
    bool AddTool(const Tool& tool)
    {
        if (HasTool(tool.GetName()))
        {
            return false;
        }

        ownedTools.push_back(tool);
        return true;
    }

    bool HasTool(const std::string& name) const
    {
        for (const Tool& tool : ownedTools)
        {
            if (tool.GetName() == name)
            {
                return true;
            }
        }

        return false;
    }

    const std::vector<Tool>& GetOwnedTools() const
    {
        return ownedTools;
    }
};
