add_executable(Sandbox src/Sandbox.cpp src/SandboxScene.cpp include/SandboxScene.h src/SandboxLayer.cpp include/SandboxLayer.h)

target_include_directories(Sandbox PRIVATE "$<TARGET_PROPERTY:Genesis,INTERFACE_INCLUDE_DIRECTORIES>")
target_include_directories(Sandbox PRIVATE include)

target_link_libraries(Sandbox PRIVATE Genesis)

add_dependencies(Sandbox Genesis)
