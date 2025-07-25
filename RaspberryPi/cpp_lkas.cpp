#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <cmath>

using namespace cv;
using namespace std;

// 하얀 차선 검출 (HLS 색공간)
Mat filter_white_lanes(const Mat &image) {
    Mat hls, mask;
    cvtColor(image, hls, COLOR_BGR2HLS);
    Scalar lower_white(0, 200, 0);
    Scalar upper_white(255, 255, 255);
    inRange(hls, lower_white, upper_white, mask);
    return mask;
}

// ROI 적용
Mat region_of_interest(const Mat& edges, const vector<Point>& vertices) {
    Mat mask = Mat::zeros(edges.size(), edges.type());
    vector<vector<Point>> pts = {vertices};
    fillPoly(mask, pts, Scalar(255));
    Mat masked;
    bitwise_and(edges, mask, masked);
    return masked;
}

// 사다리꼴 ROI 시각화
void draw_ROI_polygon(Mat& img, const vector<Point>& vertices, Scalar color = Scalar(0,255,255), int thickness = 2) {
    for (size_t i = 0; i < vertices.size(); ++i) {
        line(img, vertices[i], vertices[(i+1) % vertices.size()], color, thickness);
    }
}

// 평균 기울기와 절편을 이용해 차선 좌표 생성
Vec4i make_coordinates(const Mat& image, double slope, double intercept) {
    int y1 = image.rows;
    int y2 = static_cast<int>(y1 * 0.6);
    int x1 = static_cast<int>((y1 - intercept) / slope);
    int x2 = static_cast<int>((y2 - intercept) / slope);
    return Vec4i(x1, y1, x2, y2);
}

// 좌/우 차선 평균화
vector<Vec4i> average_slope_intercept(const Mat& image, const vector<Vec4i>& lines) {
    vector<pair<double, double>> left_fit, right_fit;
    for (const auto& l : lines) {
        int x1 = l[0], y1 = l[1], x2 = l[2], y2 = l[3];
        if (x1 == x2) continue; // 수직 라인 제외
        double slope = static_cast<double>(y2 - y1) / (x2 - x1);
        double intercept = y1 - slope * x1;
        if (slope < 0)
            left_fit.emplace_back(slope, intercept);
        else
            right_fit.emplace_back(slope, intercept);
    }
    vector<Vec4i> out(2, Vec4i());
    if (!left_fit.empty()) {
        double ls = 0, li = 0;
        for (const auto& q : left_fit) { ls += q.first; li += q.second; }
        ls /= left_fit.size(); li /= left_fit.size();
        out[0] = make_coordinates(image, ls, li);
    }
    if (!right_fit.empty()) {
        double rs = 0, ri = 0;
        for (const auto& q : right_fit) { rs += q.first; ri += q.second; }
        rs /= right_fit.size(); ri /= right_fit.size();
        out[1] = make_coordinates(image, rs, ri);
    }
    return out;
}

// 차선 직선 그리기
Mat draw_lines(const Mat &image, const vector<Vec4i> &lines, Scalar color = Scalar(0,0,255), int thickness = 5) {
    Mat line_image = Mat::zeros(image.size(), image.type());
    for (const auto &ln : lines) {
        if (ln != Vec4i()) {
            cv::line(line_image, Point(ln[0], ln[1]), Point(ln[2], ln[3]), color, thickness);
        }
    }
    return line_image;
}

// 차량 위치 오프셋 계산
int get_vehicle_position(int frame_width, const Vec4i& left_line, const Vec4i& right_line) {
    int car_center = frame_width / 2;
    int lane_center;
    if (left_line != Vec4i() && right_line != Vec4i()) {
        int left_x = left_line[0], right_x = right_line[0];
        lane_center = (left_x + right_x) / 2;
    } else if (left_line != Vec4i()) {
        lane_center = left_line[0] + 200;
    } else if (right_line != Vec4i()) {
        lane_center = right_line[0] - 200;
    } else {
        lane_center = car_center;
    }
    return car_center - lane_center;
}

// LKAS 상태 판단
string determine_lkas_state(int offset, int threshold) {
    if (abs(offset) < threshold)
        return "OK";
    else if (offset > 0)
        return "left";
    else
        return "right";
}

int main() {
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "Error: Could not open video stream." << endl;
        return -1;
    }
    int offset_threshold = 30;
    double prevTime = static_cast<double>(getTickCount());

    while (true) {
        Mat frame;
        bool ret = cap.read(frame);
        if (!ret) break;

        double curTime = static_cast<double>(getTickCount());
        Mat small_frame;
        resize(frame, small_frame, Size(320, 240));
        Mat white_mask = filter_white_lanes(small_frame);
        Mat edges;
        Canny(white_mask, edges, 30, 100);
        int height = edges.rows, width = edges.cols;

        // 사다리꼴 ROI
        int roi_top = static_cast<int>(height * 0.55);
        int roi_margin = static_cast<int>(width * 0.08);
        vector<Point> roi_vertices = {
            Point(roi_margin, height), // 좌하
            Point(width / 2 - width * 0.18, roi_top), // 좌상
            Point(width / 2 + width * 0.18, roi_top), // 우상
            Point(width - roi_margin, height) // 우하
        };

        Mat roi_edges = region_of_interest(edges, roi_vertices);
        vector<Vec4i> lines;
        HoughLinesP(roi_edges, lines, 1, CV_PI/180, 20, 20, 300);

        Mat combined_image = small_frame.clone();
        string detect_status = "";
        string side_status = "";
        string lkas_state = "";

        if (lines.size() == 0) {
            detect_status = "not detected";
            lkas_state = "not detected";
        } else if (lines.size() == 1) {
            // 선이 1개인 경우
            int x1 = lines[0][0], y1 = lines[0][1], x2 = lines[0][2], y2 = lines[0][3];
            double slope = static_cast<double>(y2 - y1) / (x2 - x1);
            if (slope < 0)
                side_status = "LEFT lane detected";
            else
                side_status = "RIGHT lane detected";
            vector<Vec4i> averaged_lines = average_slope_intercept(small_frame, lines);
            Mat line_image = draw_lines(small_frame, averaged_lines);
            addWeighted(small_frame, 0.8, line_image, 1.0, 0, combined_image);
            lkas_state = side_status;
        } else {
            // 2개 이상일 때 정상 처리
            vector<Vec4i> averaged_lines = average_slope_intercept(small_frame, lines);
            Mat line_image = draw_lines(small_frame, averaged_lines);
            addWeighted(small_frame, 0.8, line_image, 1.0, 0, combined_image);
            int offset = get_vehicle_position(width, averaged_lines[0], averaged_lines[1]);
            lkas_state = determine_lkas_state(offset, offset_threshold);
        }

        // ROI 사다리꼴 표시
        draw_ROI_polygon(combined_image, roi_vertices);

        // FPS 표시
        double sec = (curTime - prevTime) / getTickFrequency();
        prevTime = curTime;
        double fps = 1.0 / sec;
        string fps_str = format("FPS : %.1f", fps);
        putText(combined_image, fps_str, Point(0,100), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,255,0));

        // LKAS 상태 및 감지 정보 표시
        putText(combined_image, "LKAS: " + lkas_state, Point(20,40), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255,255,0), 2);

        if (lines.size() == 0) {
            putText(combined_image, "not detected", Point(20, 200), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,0,255), 2);
        } else if (lines.size() == 1) {
            putText(combined_image, side_status, Point(20, 200), FONT_HERSHEY_SIMPLEX, 1, Scalar(255,0,0), 2);
        }

        imshow("Lane Detection with LKAS", combined_image);

        char key = (char)waitKey(1);
        if (key == 'q')
            break;
    }
    cap.release();
    destroyAllWindows();
    return 0;
}
