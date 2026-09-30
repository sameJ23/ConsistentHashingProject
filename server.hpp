#pragma once

#include <string>
#include <unordered_map>

class Server
{
public:
    Server(const std::string& name);

    std::string getName() const;

    void put(const std::string& key, const std::string& value);

    std::string get(const std::string& key) const;

    bool remove(const std::string& key);

    std::size_t getKeyCount() const;
    
    void showContents() const;

    const std::unordered_map<std::string, std::string>& getContents() const;

private:
    std::string name_;

    std::unordered_map<std::string, std::string> cache_;
};
