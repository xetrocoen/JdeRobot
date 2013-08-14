SET(SOURCE_FILES recorder.cpp recordergui.cpp poolWriteImages.cpp poolWritePose3dEncoders.cpp poolWriteLasers.cpp poolWritePointCloud.cpp poolWriteEncoders.cpp)

add_definitions(-DGLADE_DIR="${gladedir}")

set( CMAKE_CXX_FLAGS "-Wno-deprecated" ) # Opciones para el compilador-lgsl -lgslcblas -lGL -lGLU -lglut -lgazebo

include_directories(
    ${INTERFACES_CPP_DIR}
    ${LIBS_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/cameras
)

add_executable (recorder ${SOURCE_FILES})


TARGET_LINK_LIBRARIES(recorder
    ${CMAKE_THREAD_LIBS_INIT} 
	${GLUT_LIBRARIES}
   	${OpenCV_LIBRARIES}
   	${gtkmm_LIBRARIES}
    ${libglademm_LIBRARIES}
    ${gtkglextmm_LIBRARIES}
    ${LIBS_DIR}/colorspaces/libcolorspacesmm.so
    ${INTERFACES_CPP_DIR}/jderobot/libJderobotInterfaces.so
    ${LIBS_DIR}/jderobotutil/libjderobotutil.so
    ${gsl_LIBRARIES}
    ${ZeroCIce_LIBRARIES}
)