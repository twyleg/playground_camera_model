# Copyright (C) 2024 twyleg
set(TARGET_NAME playground_camera_model)


#
# add source files to target
#
add_executable(${TARGET_NAME}
    main.cc
)


#
# set target properties
#
set_target_properties(${TARGET_NAME}
    PROPERTIES
    CXX_STANDARD 17
    INCLUDE_CURRENT_DIR ON
)


#
# link against libs
#
target_link_libraries(${TARGET_NAME}
    playground_camera_model::core
)
