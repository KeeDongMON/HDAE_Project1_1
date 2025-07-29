#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

// 신호등 색상 판별 함수 (HSV 원픽셀 기준)
string detect_signal_color(const Vec3b& hsv_pix) {
    int h = hsv_pix[0];
    int s = hsv_pix[1];
    int v = hsv_pix[2];

    if (((h >= 0 && h <= 10) || (h >= 170 && h <= 179)) && s > 100 && v > 100)
        return "Red";
    else if (h >= 15 && h <= 35 && s > 100 && v > 100)
        return "Yellow";
    else if (h >= 40 && h <= 90 && s > 50 && v > 50)
        return "Green";
    else
        return "None";
}

int main() {
    const int Width = 320;
    const int Height = 240;

    VideoCapture cap(0);
    cap.set(CAP_PROP_FRAME_WIDTH, Width);
    cap.set(CAP_PROP_FRAME_HEIGHT, Height);

    if (!cap.isOpened()) {
        cerr << "카메라 열기 실패" << endl;
        return -1;
    }

    double last_time = (double)cv::getTickCount();
    double fps = 0.0;

    while (true) {
        Mat frame;
        if (!cap.read(frame) || frame.empty()) {
            cerr << "프레임 읽기 실패" << endl;
            break;
        }

        // ROI: 프레임 상단 1/3만 (더 좁게, 교통 신호등이 있을 확률 높은 구간)
        int roi_height = frame.rows / 3;
        Rect roi_rect(0, 0, frame.cols, roi_height);
        Mat roi = frame(roi_rect);

        // 그레이스케일 변환 및 블러 (HoughCircles 선행 처리)
        Mat gray;
        cvtColor(roi, gray, COLOR_BGR2GRAY);
        GaussianBlur(gray, gray, Size(9, 9), 2, 2);

        // 원 검출
        vector<Vec3f> circles;
        HoughCircles(gray, circles, HOUGH_GRADIENT, 1, gray.rows / 10, 100, 20, 5, 40);

        // HSV 변환 (ROI만)
        Mat hsv;
        cvtColor(roi, hsv, COLOR_BGR2HSV);

        vector<string> detected_colors;

        for (size_t i = 0; i < circles.size(); i++) {
            Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);

            Mat mask = Mat::zeros(hsv.size(), CV_8U);
            circle(mask, center, radius, Scalar(255), FILLED);

            Scalar mean_hsv = mean(hsv, mask);
            Vec3b pix_val(
                static_cast<uchar>(mean_hsv[0]),
                static_cast<uchar>(mean_hsv[1]),
                static_cast<uchar>(mean_hsv[2])
            );
            string color = detect_signal_color(pix_val);

            if (color != "None") {
                detected_colors.push_back(color);
                Scalar draw_color;
                if (color == "Red") draw_color = Scalar(0, 0, 255);
                else if (color == "Yellow") draw_color = Scalar(0, 255, 255);
                else draw_color = Scalar(0, 255, 0);

                circle(roi, center, radius, draw_color, 2);
                putText(roi, color, Point(center.x - radius, center.y - radius - 10),
                        FONT_HERSHEY_SIMPLEX, 0.5, draw_color, 2);
            }
        }

        // 가장 많이 검출된 색상 출력 (없으면 "No Signal")
        string result = "No Signal";
        if (!detected_colors.empty()) {
            int red_count = count(detected_colors.begin(), detected_colors.end(), "Red");
            int yellow_count = count(detected_colors.begin(), detected_colors.end(), "Yellow");
            int green_count = count(detected_colors.begin(), detected_colors.end(), "Green");

            if (red_count >= yellow_count && red_count >= green_count)
                result = "Red";
            else if (yellow_count >= green_count)
                result = "Yellow";
            else
                result = "Green";
        }

        // fps 계산
        double now = (double)cv::getTickCount();
        fps = cv::getTickFrequency() / (now - last_time);
        last_time = now;

        // 결과, fps 영상에 표기
        putText(roi, "Signal: " + result, Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255, 255, 255), 2);
        char fps_text[32];
        sprintf(fps_text, "FPS: %.2f", fps);
        putText(roi, fps_text, Point(10, 60), FONT_HERSHEY_SIMPLEX, 0.6, Scalar(255, 255, 0), 2);

        imshow("Traffic Light Detection (ROI-top1/3)", roi);
        char key = (char)waitKey(30);
        if (key == 27 || key == 'q') break; // ESC 또는 q 누르면 종료
    }

    cap.release();
    destroyAllWindows();
    return 0;
}
