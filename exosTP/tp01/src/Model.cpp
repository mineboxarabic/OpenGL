#include "Model.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include "Model.h"

Model::Model(const std::string& filePath) : filePath(filePath) {}

void Model::LoadModel() {
    LoadOBJ(filePath);
}
void calcAverageNormalsx(unsigned int* indeces, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
    unsigned int vLength, unsigned int normalOffset) {
    for (size_t i = 0; i < indiceCount; i += 3) {
        unsigned int in0 = indeces[i] * vLength;
        unsigned int in1 = indeces[i + 1] * vLength;
        unsigned int in2 = indeces[i + 2] * vLength;

        glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
        glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);

        glm::vec3 normal = glm::cross(v1, v2);
        normal = glm::normalize(normal);

        in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;

        vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
        vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;

        vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;







    }


    for (size_t i = 0; i < verticeCount / vLength; i++) {
        unsigned int nOffset = i * vLength + normalOffset;
        glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
        vec = glm::normalize(vec);
        vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
    }
}
void Model::LoadOBJ(const std::string& fileName) {
    // Open the file
    std::ifstream file(fileName);
    std::string line;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> textures;
    std::vector<glm::vec3> normals;
    std::vector<unsigned int> indices;


    std::unordered_map<std::string, GLuint> vertexToIndexMap;
    std::vector<float> expandedVertices;
    std::vector<GLuint> meshIndices;
    GLuint currentIndex = 0;

    if (!file.is_open()) {
        std::cerr << "Failed to load OBJ file: " << fileName << std::endl;
        return;
    }
    std::cout << "Loading OBJ file: " << fileName << std::endl;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string prefix;
        ss >> prefix;
            if (prefix == "v") {
                //If it's a vertex
                glm::vec3 vertex = glm::vec3(0.0f, 0.0f, 0.0f);
               
                ss >> vertex.x >> vertex.y >> vertex.z;
                vertices.push_back(vertex);
            }
            else if (prefix == "vt") {
                //If it's a texture
                glm::vec2 texture = glm::vec2(0.0f, 0.0f);
                ss >> texture.x >> texture.y;
                textures.push_back(texture);
            }
            else if (prefix == "vn") {
                //If it's a normal
                glm::vec3 normal = glm::vec3(0.0f, 0.0f, 0.0f);
                ss >> normal.x >> normal.y >> normal.z;
                normals.push_back(normal);
            }
            else if (prefix == "f") {
                
                std::vector<std::string> faceVertices;
                std::string vertexIndex;
                while (ss >> vertexIndex) {
                    faceVertices.push_back(vertexIndex);
                }

                for (const std::string& viStr : faceVertices) {
                    unsigned int vi = std::stoi(viStr);
                    if (vi == 0 || vi > vertices.size()) {
                        std::cerr << "Error: Face references an invalid vertex index: " << vi << std::endl;
                        continue; 
                    }
                    vi--; 
     

                    std::string vertexKey = std::to_string(vi);
                    if (vertexToIndexMap.find(vertexKey) == vertexToIndexMap.end()) {

                        glm::vec3 pos = vertices[vi]; 

                        expandedVertices.push_back(pos.x);  // x
                        expandedVertices.push_back(pos.y);  // y
                        expandedVertices.push_back(pos.z);  // z

                     
                        expandedVertices.push_back(0.0f); // r
                        expandedVertices.push_back(0.0f); // g
                        expandedVertices.push_back(0.0f); // b


                        expandedVertices.push_back(0.0f); // u
                        expandedVertices.push_back(0.0f); // v
                            
                      
                        vertexToIndexMap[vertexKey] = currentIndex;
                        meshIndices.push_back(currentIndex);
                        currentIndex++;
                    }
                    else {
                        meshIndices.push_back(vertexToIndexMap[vertexKey]);
                    }
                }
            }


    
    }

    std::cout << "done" << std::endl;

    // After processing all faces
    if (!expandedVertices.empty() && !meshIndices.empty()) {
        // Assuming you have a way to associate this mesh data with a specific Mesh object


        calcAverageNormalsx(meshIndices.data(), meshIndices.size(), expandedVertices.data(), expandedVertices.size(), 8, 5);



        Mesh* mesh = new Mesh();
        mesh->CreateMesh(expandedVertices, meshIndices);
        meshList.push_back(mesh);
    }

    // After parsing, construct your mesh(es) from the collected data
    // This could involve creating a Mesh object and adding it to meshList
}

void Model::RenderModel() {
    for (Mesh* mesh : meshList) {
        mesh->Draw();
    }
}

Mesh* Model::GetMesh(int index)
{
    

    return meshList[index];
}



Model::~Model() {
    // Properly delete any dynamically allocated Mesh objects in meshList
}
