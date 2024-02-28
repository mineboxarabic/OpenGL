#CMakeLists tp01
project(tp01)
cmake_minimum_required(VERSION 3.8.2)

set(RESOURCES_DIRECTORY "${PROJECT_SOURCE_DIR}/resources/")
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(INC_DIR "${PROJECT_SOURCE_DIR}/include/")

#Configure config.hpp.in
configure_file(
	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/config.hpp.in
  ${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/config.hpp @ONLY
)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/include BEFORE)

set(SRC
	${SRC_DIR}/main.cpp
	${SRC_DIR}/Camera.cpp
	${SRC_DIR}/Shader.cpp
	${SRC_DIR}/Texture.cpp
	${SRC_DIR}/Mesh.cpp
	${SRC_DIR}/Model.cpp
	${SRC_DIR}/Light.cpp
	${SRC_DIR}/Window.cpp
	${SRC_DIR}/ImGuiManager.cpp

	${SRC_DIR}/Camera.h
	${SRC_DIR}/Shader.h
	${SRC_DIR}/Texture.h
	${SRC_DIR}/Mesh.h
	${SRC_DIR}/Model.h
	${SRC_DIR}/Light.h
	${SRC_DIR}/Window.h
	${SRC_DIR}/ImGuiManager.h

	${SRC_DIR}/Readme.md
)


set(HEADER
	${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/config.hpp.in
#	${INC_DIR}/${PROJECT_NAME}/myapp.hpp
)

set(RESOURCE_FILES
	${PROJECT_SOURCE_DIR}/resources/shaders/lighting.frag
	${PROJECT_SOURCE_DIR}/resources/shaders/lighting.vert

	${PROJECT_SOURCE_DIR}/resources/images/box2.jpg
	${PROJECT_SOURCE_DIR}/resources/images/box2-diffus.png
	${PROJECT_SOURCE_DIR}/resources/images/box2-diffus-mask.png
	${PROJECT_SOURCE_DIR}/resources/images/box2-specular.png
	${PROJECT_SOURCE_DIR}/resources/images/box2-specular-albedo.png
	${PROJECT_SOURCE_DIR}/resources/images/box2-specular-mask.png

	${PROJECT_SOURCE_DIR}/resources/objects/airboat.obj.txt
	${PROJECT_SOURCE_DIR}/resources/objects/bunny.obj.txt
	${PROJECT_SOURCE_DIR}/resources/objects/Cube.obj.txt
	${PROJECT_SOURCE_DIR}/resources/objects/dragon2_smooth.obj.txt
	${PROJECT_SOURCE_DIR}/resources/objects/dragon2_small.obj.txt
	${PROJECT_SOURCE_DIR}/resources/objects/untitled.obj.txt
	${PROJECT_SOURCE_DIR}/resources/objects/Plan.obj.txt
	${PROJECT_SOURCE_DIR}/resources/objects/Cylindre.obj.txt
	${PROJECT_SOURCE_DIR}/resources/objects/Sphere.obj.txt
	${PROJECT_SOURCE_DIR}/resources/objects/Cone.obj.txt

)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/resources" PREFIX "Resources Files" FILES ${RESOURCE_FILES})

add_executable(${PROJECT_NAME} ${SRC} ${HEADER} ${RESOURCE_FILES})
include_directories(${INC_DIR} AFTER)

#Copy resources
add_custom_command(
	TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/resources
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)

install(
	TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
	DIRECTORY ${PROJECT_SOURCE_DIR}/resources
	DESTINATION ${CMAKE_INSTALL_BINDIR}/${PROJECT_NAME}
)

# Linking
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARY} stbimage glad glfw glm imgui glengine)
