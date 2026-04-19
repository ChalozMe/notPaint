#pragma once
#include <string>

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    void use() const;
    ~Shader();

private:
    unsigned int id;
};
