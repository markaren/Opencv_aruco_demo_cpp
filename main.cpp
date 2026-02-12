
#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

#include <string>

std::string generate_marker(int marker_id, int marker_size) {
    auto aruco_dict = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);

    cv::Mat marker_image = cv::Mat::zeros(marker_size, marker_size, CV_8UC1);
    cv::aruco::generateImageMarker(aruco_dict, marker_id, marker_size, marker_image,1);

    constexpr int padding =20;

    const int padded_size = marker_size +2 * padding;
    cv::Mat padded_image(padded_size, padded_size, CV_8UC1, cv::Scalar(255));

    const int start = padding;
    marker_image.copyTo(padded_image(cv::Rect(start, start, marker_size, marker_size)));

    std::string path = "marker_" + std::to_string(marker_id) + "_" + std::to_string(marker_size) + ".png";
    cv::imwrite(path, padded_image);

    return path;
}

int main() {

    //generate_marker(1, 200);

    cv::VideoCapture cap(0);
    while (true) {
        cv::Mat img;
        cap.read(img);

        cv::Mat gray;
        cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

        auto aruco_dict = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
        auto parameters = cv::aruco::DetectorParameters();
        auto detector = cv::aruco::ArucoDetector(aruco_dict, parameters);

        std::vector<int> ids;
        std::vector<std::vector<cv::Point2f>> corners;
        std::vector<std::vector<cv::Point2f>> rejected;
        detector.detectMarkers(gray, corners, ids, rejected);

        if (ids.size() > 0) {
            cv::aruco::drawDetectedMarkers(img, corners, ids);
        }

        cv::imshow("window", img);

        const auto key = cv::waitKey(10);
        if (key == 'q') {
            break;
        }

    }
}