add_executable(egt_newsfeed newsfeed.cpp)

target_include_directories(egt_newsfeed PRIVATE ${LIBEGT_INCLUDE_DIRS})
target_compile_options(egt_newsfeed PRIVATE ${LIBEGT_CFLAGS_OTHER})
target_link_directories(egt_newsfeed PRIVATE ${LIBEGT_LIBRARY_DIRS})
target_link_libraries(egt_newsfeed PRIVATE ${LIBEGT_LIBRARIES})
target_link_options(egt_newsfeed PRIVATE ${LIBEGT_LDFLAGS_OTHER})

target_include_directories(egt_newsfeed PRIVATE ${CMAKE_SOURCE_DIR}/rapidxml)

install(TARGETS egt_newsfeed RUNTIME)
install(DIRECTORY ./
        DESTINATION ${CMAKE_INSTALL_DATADIR}/egt/samples/newsfeed
        FILES_MATCHING
        PATTERN *.xml
)
