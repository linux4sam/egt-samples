add_executable(egt_layout layout.cpp)

target_include_directories(egt_layout PRIVATE ${LIBEGT_INCLUDE_DIRS})
target_compile_options(egt_layout PRIVATE ${LIBEGT_CFLAGS_OTHER})
target_link_directories(egt_layout PRIVATE ${LIBEGT_LIBRARY_DIRS})
target_link_libraries(egt_layout PRIVATE ${LIBEGT_LIBRARIES})
target_link_options(egt_layout PRIVATE ${LIBEGT_LDFLAGS_OTHER})

install(TARGETS egt_layout RUNTIME)
install(DIRECTORY icons
        DESTINATION ${CMAKE_INSTALL_DATADIR}/egt/samples/layout
        FILES_MATCHING
        PATTERN icons/*.png
)
