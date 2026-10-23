#pragma once

#include <string>

class Tool
{
private:
    std::string name;
    std::string description;
    int xpCost;

public:
    Tool(const std::string& toolName,
         const std::string& toolDescription,
         int cost)
        : name(toolName),
          description(toolDescription),
          xpCost(cost)
    {
    }

    const std::string& GetName() const
    {
        return name;
    }

    const std::string& GetDescription() const
    {
        return description;
    }

    int GetXPCost() const
    {
        return xpCost;
    }
};
