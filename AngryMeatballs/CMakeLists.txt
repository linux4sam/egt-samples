add_executable(egt_AngryMeatballs
    main.cpp
    Ball.cpp
    MainWindow.cpp
    RotateImageWidget.cpp)

add_dependencies(egt_AngryMeatballs box2d)

target_compile_definitions(egt_AngryMeatballs PRIVATE ASSETDIR="${CMAKE_INSTALL_FULL_DATADIR}/egt/samples/AngryMeatballs")

target_include_directories(egt_AngryMeatballs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(egt_AngryMeatballs PRIVATE ${LIBEGT_INCLUDE_DIRS})
target_compile_options(egt_AngryMeatballs PRIVATE ${LIBEGT_CFLAGS_OTHER})
target_link_directories(egt_AngryMeatballs PRIVATE ${LIBEGT_LIBRARY_DIRS})
target_link_libraries(egt_AngryMeatballs PRIVATE ${LIBEGT_LIBRARIES})
target_link_options(egt_AngryMeatballs PRIVATE ${LIBEGT_LDFLAGS_OTHER})

target_include_directories(egt_AngryMeatballs PRIVATE ${CMAKE_SOURCE_DIR}/external/Box2D)
target_link_directories(egt_AngryMeatballs PRIVATE ${CMAKE_BINARY_DIR}/external)
target_link_libraries(egt_AngryMeatballs PRIVATE box2d)

install(TARGETS egt_AngryMeatballs RUNTIME)
install(DIRECTORY ./
        DESTINATION ${CMAKE_INSTALL_DATADIR}/egt/samples/AngryMeatballs
        FILES_MATCHING
        PATTERN *.png
        PATTERN AngryMeatballs.xml
)
