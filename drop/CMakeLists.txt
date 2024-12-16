add_executable(egt_drop drop.cpp shape.cpp)

add_dependencies(egt_drop box2d)

target_include_directories(egt_drop PRIVATE ${LIBEGT_INCLUDE_DIRS})
target_compile_options(egt_drop PRIVATE ${LIBEGT_CFLAGS_OTHER})
target_link_directories(egt_drop PRIVATE ${LIBEGT_LIBRARY_DIRS})
target_link_libraries(egt_drop PRIVATE ${LIBEGT_LIBRARIES})
target_link_options(egt_drop PRIVATE ${LIBEGT_LDFLAGS_OTHER})

target_include_directories(egt_drop PRIVATE ${CMAKE_SOURCE_DIR}/external/Box2D)
target_link_directories(egt_drop PRIVATE ${CMAKE_BINARY_DIR}/external)
target_link_libraries(egt_drop PRIVATE box2d)

install(TARGETS egt_drop RUNTIME)
install(DIRECTORY ./
        DESTINATION ${CMAKE_INSTALL_DATADIR}/egt/samples/drop
        FILES_MATCHING
        PATTERN *.png
        PATTERN drop.xml
)
