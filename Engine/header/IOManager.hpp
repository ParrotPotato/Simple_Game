#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <string>
#include <vector>

#define GLM_ENABLE_EXPERIMENTAL

namespace Engine{

class IOManager{
    public:
        static bool readFiletoBuffer(std::string filePath,std::vector<unsigned char> &buffer);
};

}

#endif