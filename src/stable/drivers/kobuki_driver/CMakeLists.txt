if (${kobuki_COMPILE})


    include_directories(
        ${INTERFACES_CPP_DIR}
        ${LIBS_DIR}/
        ${CMAKE_CURRENT_SOURCE_DIR}
    )

    add_executable( kobuki_driver  main.cpp kobukimanager.cpp kobukimanager.h thread_control.cpp thread_control.h
                                   actuators/motors.cpp actuators/motors.h
                                   sensors/pose3d.h sensors/pose3d.cpp sensors/quaternion.h
    )
			       
    link_directories(${kobuki_LIBRARIES})
    include_directories(${kobuki_INCLUDE_DIR})
			       
    target_link_libraries(kobuki_driver
        ${CMAKE_THREAD_LIBS_INIT}
        ${kobuki_LIBRARIES}
        JderobotInterfaces
        jderobotutil
        ${ZeroCIce_LIBRARIES}
    )
ENDIF()
