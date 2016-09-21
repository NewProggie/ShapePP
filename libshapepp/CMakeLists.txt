project(libshapepp VERSION 0.1 LANGUAGES CXX)

add_library(libshapepp
    src/constraint.cpp
    src/ls_solver.cpp
    src/solver.cpp)

add_subdirectory(thirdparty/eigen-2.3.9)

target_include_directories(libshapepp PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE thirdparty/eigen-2.3.9
    PRIVATE src)
target_compile_features(libshapepp
    PUBLIC cxx_auto_type)

# 'make install' to the correct location
install(TARGETS libshapepp EXPORT ShapePPConfig
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)
install(DIRECTORY include/ DESTINATION include)

# Make the project importable
install(EXPORT ShapePPConfig DESTINATION share/ShapePP/cmake)
export(TARGETS libshapepp FILE ShapePPConfig.cmake)
