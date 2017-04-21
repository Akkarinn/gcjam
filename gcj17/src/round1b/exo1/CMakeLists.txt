
set(SOURCE_FILES main.cpp)

include_directories(${CMAKE_INCLUDE_DIR})
add_executable(r1b_exo1 ${SOURCE_FILES})

set_target_properties(r1b_exo1 PROPERTIES FOLDER ${V_FOLDER})
