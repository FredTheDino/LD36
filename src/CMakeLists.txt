CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

PROJECT(LD36 C CXX)

#Sets which kind of windows target you want.
#x32 or x64 for the different architectures.
#e.g SET(WINDOWS_TARGET "x32")
SET(WINDOWS_TARGET "x64")


ADD_SUBDIRECTORY("Box2D")
ADD_SUBDIRECTORY("jampieengine")
ADD_SUBDIRECTORY("game")

set_property(TARGET Box2D jampieengine game PROPERTY CXX_STANDARD 14)