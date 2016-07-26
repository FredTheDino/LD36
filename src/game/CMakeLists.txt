file(GLOB SRC_FILES "*.cpp" "*.h")

add_executable(game ${SRC_FILES})

include_directories(game "${CMAKE_SOURCE_DIR}/jampieengine")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	INCLUDE_DIRECTORIES(game "${CMAKE_SOURCE_DIR}/jampieengine/.WindowsBS/")
endif()

target_link_libraries(game jampieengine)
