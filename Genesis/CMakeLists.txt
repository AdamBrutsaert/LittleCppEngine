file(GLOB FILES CONFIGURE_DEPENDS "include/**/*.h" "src/**/*.cpp")
add_library(Genesis ${FILES})

target_include_directories(Genesis PUBLIC "include")
target_precompile_headers(Genesis PRIVATE include/Precompiled.h src/Precompiled.cpp)

# Macros
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions(Genesis PRIVATE GEN_WINDOWS)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_definitions(Genesis PRIVATE GEN_LINUX)
endif()

# glfw
add_subdirectory(thirdparties/glfw)
add_dependencies(Genesis glfw)

target_link_libraries(Genesis PRIVATE glfw)
target_include_directories(Genesis PRIVATE thirdparties/glfw/include)

# glad
add_subdirectory(thirdparties/glad)
add_dependencies(Genesis glad)

target_link_libraries(Genesis PRIVATE glad)
target_include_directories(Genesis PRIVATE thirdparties/glad/include)

# glm
target_include_directories(Genesis PUBLIC thirdparties/glm)

# stb
add_subdirectory(thirdparties/stb)
add_dependencies(Genesis stb)

target_link_libraries(Genesis PRIVATE stb)
target_include_directories(Genesis PRIVATE thirdparties/stb/include)
