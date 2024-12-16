add_executable(egt_gallery gallery.cpp)

target_include_directories(egt_gallery PRIVATE ${LIBEGT_INCLUDE_DIRS})
target_compile_options(egt_gallery PRIVATE ${LIBEGT_CFLAGS_OTHER})
target_link_directories(egt_gallery PRIVATE ${LIBEGT_LIBRARY_DIRS})
target_link_libraries(egt_gallery PRIVATE ${LIBEGT_LIBRARIES})
target_link_options(egt_gallery PRIVATE ${LIBEGT_LDFLAGS_OTHER})

install(TARGETS egt_gallery RUNTIME)
install(DIRECTORY ./
        DESTINATION ${CMAKE_INSTALL_DATADIR}/egt/samples/gallery
        FILES_MATCHING
        PATTERN *.png
        PATTERN movies/*.png
        PATTERN movies/*.jpg
)
