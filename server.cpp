#include "server.hpp"

#include <iostream>

Server::Server(const std::string& name) : name_(name)
{
}

std::string Server::getName() const
{
    return name_;
}

void Server::put(const std::string& key, const std::string& value)
{
    cache_[key] = value;
}

std::string Server::get(const std::string& key) const
{
    auto item = cache_.find(key);

    if (item == cache_.end())
    {
        return "";
    }

    return item->second;
}

bool Server::remove(const std::string& key)
{
    std::size_t removed = cache_.erase(key);

    return removed > 0;
}


std::size_t Server::getKeyCount() const
{
    return cache_.size();
}

void Server::showContents() const
{
    std::cout
        << name_
        << " - "
        << cache_.size()
        << " keys\n";

    for (const auto& [key, value] : cache_)
    {
        std::cout
            << " "
            << key
            << " -> "
            << value
            << "\n";
    }
}

const std::unordered_map<std::string, std::string>& Server::getContents() const
{
    return cache_;
}