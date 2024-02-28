#define STB_IMAGE_IMPLEMENTATION
//dkjjjjjjj
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "tp01/config.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <string>

#include "./Mesh.h"
#include "./Shader.h"
#include "./Window.h"
#include "./Camera.h"
#include "./Texture.h"
#include "./Light.h"
#include "./Model.h"

#include "./ImGuiManager.h"
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;
Window window;
Camera camera;


Texture boxTexture;

Light mainLight;

float yRotation = 0.0f;
float toRadians = 3.14159265f / 180.0f;


int modelLoc;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

unsigned int currentIndex = 1;

Mesh currentMesh;

void calcAverageNormals(unsigned int* indeces, unsigned int indiceCount,GLfloat* vertices, unsigned int verticeCount,
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

void createShader() {

	std::string pathVertexShader = std::string(_resources_directory).append("shaders/lighting.vert");
	std::string pathFragmentShader = std::string(_resources_directory).append("shaders/lighting.frag");

	Shader* shader = new Shader();
	shader->CreateFromFiles(pathVertexShader, pathFragmentShader);
	shaderList.push_back(*shader);

	Shader* shader2 = new Shader();
	shader2->CreateFromFiles(pathVertexShader, pathFragmentShader);
	shaderList.push_back(*shader2);





}

void createCube() {
	/*std::vector<float> vertices = {
		// Front face (red)
		-0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f, // Bottom-left   // 0
		 0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f, // bottom-right  // 1
		 0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f, // top-right    // 2
		 0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f, // top-right   // 3
		-0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f, // top-left   // 4
		-0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f, // bottom-left  // 5

		// Back face (green)
		-0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f, // bottom-left  // 6
		 0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f, // bottom-right  // 7
		 0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f, // top-right  // 8
		 0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f, // top-right  // 9
		-0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0f, // top-left  // 10
		-0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f, // bottom-left  // 11

		// Left face (blue)
		-0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f, // top-right  // 12
		-0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f, // top-left  // 13
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f, // bottom-left  
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f, // bottom-left
		-0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f, // bottom-right
		-0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f, // top-right

		// Right face (yellow)
		 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f, // top-left
		 0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f, // top-right 
		 0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f, // bottom-right
		 0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f, // bottom-right
		 0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f, // bottom-left
		 0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f, // top-left

		 // Bottom face (cyan)
		 -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 1.0f, // top-right
		  0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 1.0f, // top-left
		  0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f, // bottom-left
		  0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f, // bottom-left
		 -0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f, // bottom-right
		 -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 1.0f, // top-right

		 // Top face (magenta)
		 -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 1.0f, // top-left
		  0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 1.0f, // top-right
		  0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 1.0f, // bottom-right
		  0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 1.0f, // bottom-right
		 -0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 1.0f, // bottom-left
		 -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 1.0f  // top-left
	};*/


	std::vector<float> vertices = {
		// Front face
		//x      y      z      u     v
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Bottom-left
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,// Bottom-right
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f,// Top-right
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,// Top-left

		// Back face
		-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,// Bottom-left
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,// Bottom-right
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,// Top-right
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f,// Top-left

		// Left face
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,// Bottom-left
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,// Bottom-right
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f,// Top-right
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,// Top-left

		// Right face
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,// Bottom-left
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,// Bottom-right
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f,// Top-right
		 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,// Top-left

		 // Bottom face
		 -0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f,// Top-right
		  0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,// Top-left
		  0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,// Bottom-left
		 -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,// Bottom-right

		 // Top face
		 -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,// Top-left
		  0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f,// Top-right
		  0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,// Bottom-right
		 -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 0.0f,// Bottom-left
	};


	std::vector<GLuint> indices = {
		// Front face
		0, 1, 2,
		2, 3, 0,

		// Right face
		4, 5, 6,
		6, 7, 4,

		// Back face
		8, 9, 10,
		10, 11, 8,

		// Left face
		12, 13, 14,
		14, 15, 12,

		// Bottom face
		16, 17, 18,
		18, 19, 16,

		// Top face
		20, 21, 22,
		22, 23, 20
	};


	calcAverageNormals(indices.data(), indices.size(), vertices.data(), vertices.size(), 8, 5);

	Mesh* cube = new Mesh();
	cube->CreateMesh(vertices, indices);
	meshList.push_back(cube);

	Mesh * cube2 = new Mesh();
	cube2->CreateMesh(vertices, indices);
	meshList.push_back(cube2);

	Mesh* cube3 = new Mesh();
	cube2->CreateMesh(vertices, indices);
	meshList.push_back(cube3);



	createShader();

	


}

void getMeshes() {
	/*	${PROJECT_SOURCE_DIR}/resources/objects/airboat.obj.txt
	${PROJECT_SOURCE_DIR}/resources/objects/bunny.obj.txt
	${PROJECT_SOURCE_DIR}/resources/objects/Cube.obj.txt
	${PROJECT_SOURCE_DIR}/resources/objects/dragon2_smooth.obj.txt
	${PROJECT_SOURCE_DIR}/resources/objects/dragon2_small.obj.txt
	${PROJECT_SOURCE_DIR}/resources/objects/untitled.obj.txt
	${PROJECT_SOURCE_DIR}/resources/objects/Plan.obj.txt
	${PROJECT_SOURCE_DIR}/resources/objects/Cylindre.obj.txt
	${PROJECT_SOURCE_DIR}/resources/objects/Sphere.obj.txt
	${PROJECT_SOURCE_DIR}/resources/objects/Cone.obj.txt*/

	createCube();

	std::string obj = std::string(_resources_directory).append("objects/airboat.obj.txt");

	Model dragon(obj);
	dragon.LoadModel();
	meshList.push_back(dragon.GetMesh(0));

	std::string obj2 = std::string(_resources_directory).append("objects/bunny.obj.txt");
	
	Model bunny(obj2);
	bunny.LoadModel();
	meshList.push_back(bunny.GetMesh(0));

	std::string obj3 = std::string(_resources_directory).append("objects/Cube.obj.txt");
	Model cube(obj3);
	cube.LoadModel();

	meshList.push_back(cube.GetMesh(0));

	std::string obj4 = std::string(_resources_directory).append("objects/dragon2_smooth.obj.txt");
	Model dragon2(obj4);
	dragon2.LoadModel();
	meshList.push_back(dragon2.GetMesh(0));

	std::string obj5 = std::string(_resources_directory).append("objects/dragon2_small.obj.txt");
	Model dragon3(obj5);
	dragon3.LoadModel();
	meshList.push_back(dragon3.GetMesh(0));

	std::string obj6 = std::string(_resources_directory).append("objects/airboat.obj.txt");
	Model airboat(obj6);
	airboat.LoadModel();
	meshList.push_back(airboat.GetMesh(0));

	std::string obj7 = std::string(_resources_directory).append("objects/untitled.obj.txt");
	Model untitled(obj7);
	untitled.LoadModel();
	meshList.push_back(untitled.GetMesh(0));

	std::string obj8 = std::string(_resources_directory).append("objects/Plan.obj.txt");
	Model plan(obj8);
	plan.LoadModel();
	meshList.push_back(plan.GetMesh(0));

	std::string obj9 = std::string(_resources_directory).append("objects/Cylindre.obj.txt");
	Model cylindre(obj9);
	cylindre.LoadModel();
	meshList.push_back(cylindre.GetMesh(0));


	std::string obj10 = std::string(_resources_directory).append("objects/Sphere.obj.txt");
	Model sphere(obj10);
	sphere.LoadModel();
	meshList.push_back(sphere.GetMesh(0));

	std::string obj11 = std::string(_resources_directory).append("objects/Cone.obj.txt");
	Model cone(obj11);
	cone.LoadModel();
	meshList.push_back(cone.GetMesh(0));









}

int main() {


	window = Window();
	window.Initialize(1280, 720, "OpenGL");



	//createCube();


	createShader();

	glEnable(GL_DEPTH_TEST);
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	GLuint uniformModel = 0, uniformProjection = 0, uniformView = 0, uniformAmbientIntensity = 0, uniformAmbientColor = 0
		, uniformDirection = 0, uniformDiffuseIntensity = 0;
	camera = Camera(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f,1.0f,0.0f), -90.0f, 0.0f, 5.0f, 0.5f);

	std::string img = std::string(_resources_directory).append("images/box2.jpg");

	boxTexture = Texture(img);
	boxTexture.LoadTexture();


	boxTexture.UseTexture();
	mainLight = Light(1.0f, 1.0f, 1.0f, 0.5f, 2.0f, -1.0f, -2.0f, 1.0f);


	ImGuiManager imguiManager(window.GetWindow());

	std::string obj = std::string(_resources_directory).append("objects/airboat.obj.txt");

	Model myObjModel(obj);
	myObjModel.LoadModel();
	getMeshes();

	ImVec4 color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	float brightness= 1.0f;

	while (!window.ShouldClose()) {


		imguiManager.NewFrame();
		//imguiManager.DrawGUI();
		imguiManager.DrawButtons(currentIndex, meshList.size(),color, brightness);

		imguiManager.Render();

		

		window.Update();

		//Get the time to mkae delta
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;


		//Get contoles for the camera 
		camera.keyControl(window.GetKeys(), deltaTime);
		//Get mouse controles
		camera.mouseControl(window.GetXChange(), window.GetYChange());


		//We use the shader number 0
		shaderList[0].UseShader();
		//We put the model
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformAmbientIntensity = shaderList[0].GetAmbientIntensityLocation();
		uniformAmbientColor = shaderList[0].GetAmbientColorLocation();
		uniformDirection = shaderList[0].GetDirectionLocation();
		uniformDiffuseIntensity = shaderList[0].GetDiffuseIntensityLocation();

		mainLight = Light(color.x, color.y, color.z, brightness, 2.0f, -1.0f, -2.0f, 1.0f);
		mainLight.UseLight(uniformAmbientIntensity, uniformAmbientColor, uniformDiffuseIntensity, uniformDirection);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
		//model = glm::rotate(model, yRotation * toRadians, glm::vec3(0.0f, 0.5f, 0.0f));
		projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 100.f);
		shaderList[0].setModelInShader(model);
		shaderList[0].setProjectionInShader(projection);
		shaderList[0].setViewInShader(camera.calculateViewMatrix());

			
		boxTexture.UseTexture();

		//myObjModel.RenderModel();
		yRotation += 0.1f;
		float yRotation2 = 0.0f;
		yRotation2 += yRotation + 45.0f;


		meshList[currentIndex - 1]->Draw();




		//meshList[0]->Draw();

		 
		/*
		yRotation += 0.1f;
		float yRotation2 = 0.0f;
		yRotation2 += yRotation + 45.0f;

		boxTexture.UseTexture();
		meshList[0]->Draw();



		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -3.0f));
		model = glm::rotate(model, yRotation2 * toRadians, glm::vec3(0.05f, 1.0f, 0.0f));
		shaderList[1].setModelInShader(model);

		meshList[0]->Draw();
		meshList[1]->Draw();

		yRotation2 += yRotation + 20.0f;
		
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.0f, 1.0f, -1.0f));
		model = glm::rotate(model, yRotation2 * toRadians, glm::vec3(1.05f, 1.0f, 0.0f));
		shaderList[1].setModelInShader(model);

		meshList[1]->Draw();*/


	
	}





}
