file(GLOB BOX2D_SOURCE_FILES 
    "*.h"
    "Collision/*.h"
    "Collision/*.cpp"
    "Collision/Shapes/*.h"
    "Collision/Shapes/*.cpp"
    "Common/*.h"
    "Common/*.cpp"
    "Dynamics/*.h"
    "Dynamics/*.cpp"
    "Dynamics/Contacts/*.h"
    "Dynamics/Contacts/*.cpp"
    "Dynamics/Joints/*.h"
    "Dynamics/Joints/*.cpp"
    "Rope/*.h"
    "Rope/*.cpp"
    )

include_directories(Box2D ${CMAKE_SOURCE_DIR})
add_library(Box2D ${BOX2D_SOURCE_FILES})