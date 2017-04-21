
set(SOURCE_FILES main.cpp)

include_directories(${CMAKE_INCLUDE_DIR})
add_executable(exo2 ${SOURCE_FILES})

set_target_properties(exo2 PROPERTIES FOLDER ${V_FOLDER})
