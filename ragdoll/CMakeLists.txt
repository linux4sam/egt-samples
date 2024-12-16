add_executable(egt_ragdoll ragdoll.cpp hooman.cpp)

add_dependencies(egt_ragdoll box2d)

target_include_directories(egt_ragdoll PRIVATE ${LIBEGT_INCLUDE_DIRS})
target_compile_options(egt_ragdoll PRIVATE ${LIBEGT_CFLAGS_OTHER})
target_link_directories(egt_ragdoll PRIVATE ${LIBEGT_LIBRARY_DIRS})
target_link_libraries(egt_ragdoll PRIVATE ${LIBEGT_LIBRARIES})
target_link_options(egt_ragdoll PRIVATE ${LIBEGT_LDFLAGS_OTHER})

target_include_directories(egt_ragdoll PRIVATE ${CMAKE_SOURCE_DIR}/external/Box2D)
target_link_directories(egt_ragdoll PRIVATE ${CMAKE_BINARY_DIR}/external)
target_link_libraries(egt_ragdoll PRIVATE box2d)

install(TARGETS egt_ragdoll RUNTIME)
