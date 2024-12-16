add_executable(egt_brick brick.cpp)

target_include_directories(egt_brick PRIVATE ${LIBEGT_INCLUDE_DIRS})
target_compile_options(egt_brick PRIVATE ${LIBEGT_CFLAGS_OTHER})
target_link_directories(egt_brick PRIVATE ${LIBEGT_LIBRARY_DIRS})
target_link_libraries(egt_brick PRIVATE ${LIBEGT_LIBRARIES})
target_link_options(egt_brick PRIVATE ${LIBEGT_LDFLAGS_OTHER})

install(TARGETS egt_brick RUNTIME)
install(DIRECTORY ./
        DESTINATION ${CMAKE_INSTALL_DATADIR}/egt/samples/brick
        FILES_MATCHING
        PATTERN *.png
)
