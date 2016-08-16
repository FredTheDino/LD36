FILE(GLOB SOURCE_FILES "*.cpp" "*.h" "*.c")

ADD_LIBRARY(jampieengine ${SOURCE_FILES})

INCLUDE_DIRECTORIES(jampieengine "/include")
INCLUDE_DIRECTORIES(jampieengine "/glm" "/glm/gtc" "/glm/gtc" "/glm/detail" "../impl/entity.cpp")


#OpenGL
find_package("OpenGL" REQUIRED)
if(${OPENGL_FOUND})
	include_directories(jampieengine ${OPENGL_INCLUDE_DIR})
	target_link_libraries(jampieengine ${OPENGL_LIBRARIES})
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    INCLUDE_DIRECTORIES(jampieengine ".WindowsBS/")

    MESSAGE(${CMAKE_SOURCE_DIR})

    FILE(GLOB SDL_LIBRARIES "${CMAKE_SOURCE_DIR}/jampieengine/.WindowsBS/SDL2/*.lib")

    FILE(GLOB GLEW_LIBRARIES "${CMAKE_SOURCE_DIR}/jampieengine/.WindowsBS/GL/*.lib")

    if(${WINDOWS_TARGET} STREQUAL "x64")
        FILE(GLOB OpenAL_LIBRARIES "${CMAKE_SOURCE_DIR}/jampieengine/.WindowsBS/AL/Win64/*.lib")
    else()
        FILE(GLOB OpenAL_LIBRARIES "${CMAKE_SOURCE_DIR}/jampieengine/.WindowsBS/AL/Win32/*.lib")
    endif()

    target_link_libraries(jampieengine ${SDL_LIBRARIES} ${OpenAL_LIBRARIES} ${GLEW_LIBRARIES})

else()
	INCLUDE(FindPkgConfig)

	PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
	if (${SDL2_FOUND})
		INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
		TARGET_LINK_LIBRARIES(jampieengine ${SDL2_LIBRARIES})
	endif()

	PKG_SEARCH_MODULE(GLEW REQUIRED glew)
	if (${GLEW_FOUND})
		INCLUDE_DIRECTORIES(${GLEW_INCLUDE_DIRS})
		TARGET_LINK_LIBRARIES(jampieengine ${GLEW_LIBRARIES})
	endif()

	Find_Package(OpenAL REQUIRED)
	INCLUDE_DIRECTORIES(${OPENAL_INCLUDE_DIRS})
	TARGET_LINK_LIBRARIES(jampieengine ${OPENAL_LIBRARY})
endif()
