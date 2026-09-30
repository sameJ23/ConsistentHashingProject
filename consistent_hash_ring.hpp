#pragma once

#include <cstddef>
#include <map>
#include <string>

class ConsistentHashRing
{
    public:
        void addServer(const std::string& serverName);

        bool removeServer(const std::string& serverName);

        std::string getServer(const std::string& key) const;

        void showRing() const;

    private:
        std::size_t hashValue(const std::string& value) const;

        std::map<std::size_t, std::string> ring_;
};