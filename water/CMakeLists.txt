add_executable(egt_water water.cpp)

target_compile_definitions(egt_water PRIVATE EXAMPLEDATA="${CMAKE_INSTALL_FULL_DATADIR}/egt/samples/water")

target_include_directories(egt_water PRIVATE ${LIBEGT_INCLUDE_DIRS})
target_compile_options(egt_water PRIVATE ${LIBEGT_CFLAGS_OTHER})
target_link_directories(egt_water PRIVATE ${LIBEGT_LIBRARY_DIRS})
target_link_libraries(egt_water PRIVATE ${LIBEGT_LIBRARIES})
target_link_options(egt_water PRIVATE ${LIBEGT_LDFLAGS_OTHER})

install(TARGETS egt_water RUNTIME)
install(DIRECTORY ./
        DESTINATION ${CMAKE_INSTALL_DATADIR}/egt/samples/water
        FILES_MATCHING
        PATTERN *.png
)
