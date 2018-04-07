
set(SOURCE_FILES main.cpp)

include_directories(${CMAKE_INCLUDE_DIR})
add_executable(2017_r1b_exo2 ${SOURCE_FILES})

set_target_properties(2017_r1b_exo2 PROPERTIES FOLDER ${V_FOLDER})
