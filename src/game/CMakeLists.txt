file(GLOB GAME_SOURCE_FILES "*.cpp" "*.h")

add_executable(game ${GAME_SOURCE_FILES})

include_directories(game "${CMAKE_SOURCE_DIR}/jampieengine")
include_directories(game ${CMAKE_SOURCE_DIR})

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	INCLUDE_DIRECTORIES(game "${CMAKE_SOURCE_DIR}/jampieengine/.WindowsBS/")
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	find_package(Threads)
	target_link_libraries(game ${CMAKE_THREAD_LIBS_INIT})
endif()

target_link_libraries(game jampieengine)
target_link_libraries(game Box2D)
