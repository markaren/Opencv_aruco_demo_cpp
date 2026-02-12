
add_library(aruco
    src/aruco.cpp
    src/aruco_calib.cpp
    src/charuco.cpp
)
target_include_directories(aruco PUBLIC include)
target_link_libraries(aruco ${OpenCV_LIBS})
