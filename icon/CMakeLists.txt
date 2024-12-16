add_executable(egt_icon icon.cpp)

target_include_directories(egt_icon PRIVATE ${LIBEGT_INCLUDE_DIRS})
target_compile_options(egt_icon PRIVATE ${LIBEGT_CFLAGS_OTHER})
target_link_directories(egt_icon PRIVATE ${LIBEGT_LIBRARY_DIRS})
target_link_libraries(egt_icon PRIVATE ${LIBEGT_LIBRARIES})
target_link_options(egt_icon PRIVATE ${LIBEGT_LDFLAGS_OTHER})

install(TARGETS egt_icon RUNTIME)
install(DIRECTORY ./
        DESTINATION ${CMAKE_INSTALL_DATADIR}/egt/samples/icon/icons
        FILES_MATCHING
        PATTERN *.png
)
