#ifndef __ENV_PARSER_HPP__
#define __ENV_PARSER_HPP__

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <optional>

const std::string delimiter = ",";

class EnvParse
{
public:
    std::map<std::string, std::string> env;
    
    EnvParse(const std::string &env_str) {
        this->env = get_env(env_str);
    }

    std::map<std::string, std::string> get_env(const std::string &env_str)
    {
        std::map<std::string, std::string> env;
        char *env_cstr = std::getenv(env_str.c_str());
        if (env_cstr != nullptr)
        {
            std::string env_str(env_cstr);
            std::istringstream ss(env_str);
            std::string token;
            while (std::getline(ss, token, delimiter[0]))
            {
                std::istringstream ss2(token);
                std::string key, value;
                std::getline(ss2, key, '=');
                std::getline(ss2, value, '=');
                env[key] = value;
            }
        }
        return env;
    }

    template <typename T>
    std::optional<T> get(const std::string &key)
    {
        if (this->env.find(key) != this->env.end())
        {
            return get_as<T>(this->env[key]);
        }
        else
        {
            return std::nullopt;
        }
    }
private:
    template <typename T>
    std::optional<T> get_as(const std::string &value)
    {
        std::istringstream ss(value);
        T t;
        if (ss >> t)
        {
            return t;
        }
        else
        {
            return std::nullopt;
        }
    }
};



#endif // __ENV_PARSER_HPP__