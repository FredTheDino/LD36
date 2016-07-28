file(GLOB SRC_FILES "*.cpp" "*.h")

add_executable(game ${SRC_FILES})

include_directories(game "${CMAKE_SOURCE_DIR}/jampieengine")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	INCLUDE_DIRECTORIES(game "${CMAKE_SOURCE_DIR}/jampieengine/.WindowsBS/")
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	find_package(Threads)
	target_link_libraries(game ${CMAKE_THREAD_LIBS_INIT})
endif()

target_link_libraries(game jampieengine)
