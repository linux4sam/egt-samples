add_executable(egt_weather weather.cpp)

target_include_directories(egt_weather PRIVATE ${LIBEGT_INCLUDE_DIRS})
target_compile_options(egt_weather PRIVATE ${LIBEGT_CFLAGS_OTHER})
target_link_directories(egt_weather PRIVATE ${LIBEGT_LIBRARY_DIRS})
target_link_libraries(egt_weather PRIVATE ${LIBEGT_LIBRARIES})
target_link_options(egt_weather PRIVATE ${LIBEGT_LDFLAGS_OTHER})

target_include_directories(egt_weather PRIVATE ${JSONCPP_INCLUDE_DIRS})
target_compile_options(egt_weather PRIVATE ${JSONCPP_CFLAGS_OTHER})
target_link_directories(egt_weather PRIVATE ${JSONCPP_LIBRARY_DIRS})
target_link_libraries(egt_weather PRIVATE ${JSONCPP_LIBRARIES})
target_link_options(egt_weather PRIVATE ${JSONCPP_LDFLAGS_OTHER})

install(TARGETS egt_weather RUNTIME)
install(DIRECTORY ./
        DESTINATION ${CMAKE_INSTALL_DATADIR}/egt/samples/weather
        FILES_MATCHING
        PATTERN *.jpg
)
