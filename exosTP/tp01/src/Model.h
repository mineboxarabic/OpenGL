#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include "Mesh.h"

class Model {
public:
    Model(const std::string& filePath);
    void LoadModel();
    void RenderModel();
    Mesh *GetMesh(int index);
    ~Model();

private:
    std::vector<Mesh*> meshList;
    std::string filePath;

    void LoadOBJ(const std::string& fileName);
    // Add more helper methods if needed for other file formats or processing.
};

#endif // MODEL_H
