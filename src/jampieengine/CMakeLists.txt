FILE(GLOB SOURCE_FILES "*.cpp" "*.h" "*.c")

ADD_LIBRARY(jampieengine ${SOURCE_FILES})

INCLUDE_DIRECTORIES(jampieengine "/include")
INCLUDE_DIRECTORIES(jampieengine "/glm" "/glm/gtc" "/glm/gtc" "/glm/detail")

#INCLUDE(FindPkgConfig)
#PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)


#OpenGL
find_package("OpenGL" REQUIRED)
if(${OPENGL_FOUND})
	include_directories(jampieengine ${OPENGL_INCLUDE_DIR})
	target_link_libraries(jampieengine ${OPENGL_LIBRARIES})
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	INCLUDE_DIRECTORIES(jampieengine ".WindowsBS/")

	MESSAGE(${CMAKE_SOURCE_DIR})

	FILE(GLOB LIBRARIES "${CMAKE_SOURCE_DIR}/jampieengine/.WindowsBS/include/*.lib")

	target_link_libraries(jampieengine ${LIBRARIES})

else()
	INCLUDE(FindPkgConfig)

	PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
	PKG_SEARCH_MODULE(GLEW REQUIRED glew)

	INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
	TARGET_LINK_LIBRARIES(jampieengine ${SDL2_LIBRARIES} ${GLEW_LIBRARIES})
endif()
