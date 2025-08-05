#include "draw.h"

void draw_traffic_signals(cv::Mat& frame, const std::vector<cv::Vec3f>& detected_circles, TrafficSignal signal) {
    for (const auto& c : detected_circles) {
        cv::Point center(cvRound(c[0]), cvRound(c[1]));
        int radius = cvRound(c[2]);
        cv::Scalar color = cv::Scalar(200,200,200); // 기본 옅은 회색
        int thick = 3;
	std::string signal_str;
        if (signal != TrafficSignal::NONE) {
            if (signal == TrafficSignal::RED){
	        color = cv::Scalar(0,0,255);
		signal_str = "RED";
cv::circle(frame, center, radius, color, thick);
		cv::putText(frame, signal_str, cv::Point(200, 40), cv::FONT_HERSHEY_SIMPLEX, 0.7, color, 2);
	    }
	    else if (signal == TrafficSignal::YELLOW){
	        color = cv::Scalar(0,255,255);
		signal_str = "YELLOW";
cv::circle(frame, center, radius, color, thick);
		cv::putText(frame, signal_str, cv::Point(200, 40), cv::FONT_HERSHEY_SIMPLEX, 0.7, color, 2);
	    }
 	    else if (signal == TrafficSignal::GREEN){
	        color = cv::Scalar(0,255,0);
		signal_str = "GREEN";
		cv::putText(frame, signal_str, cv::Point(200, 40), cv::FONT_HERSHEY_SIMPLEX, 0.7, color, 2);
cv::circle(frame, center, radius, color, thick);
	    }            
        }
        
    }    
}

void draw_lane_and_roi(cv::Mat& frame,
                       const std::vector<cv::Point>& left_curve, const std::vector<cv::Point>& right_curve,
                       const cv::Vec3f& left_poly, const cv::Vec3f& right_poly,
                       const std::vector<cv::Point>& roi_verts, const cv::Mat& roi_mask,
                       int Width) {
    if (left_curve.size() > 5 && right_curve.size() > 5)
        fill_lane_area(frame, left_curve, right_curve, cv::Scalar(0,255,0), roi_mask);

    draw_roi(frame, roi_verts, cv::Scalar(0,255,255), 2);

    if (!left_curve.empty())
        draw_curve_in_roi(frame, left_poly, roi_mask, cv::Scalar(255,0,0), 3);
    if (!right_curve.empty())
        draw_curve_in_roi(frame, right_poly, roi_mask, cv::Scalar(0,255,0), 3);
}

void draw_lkas_info(cv::Mat& frame, const LKASCommand& lkas, bool intervention, int x, int y0, int line_gap, char direction, int offset) {
    if (intervention) {
        cv::putText(frame, "LKAS ACTIVE", cv::Point(x,y0), cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(100,255,100), 2);
        char angle_buf[64], speed_buf[64];
	char direction_buf[32], offset_buf[32];
	if(direction == 'R') cv::putText(frame, "<-", cv::Point(120, 140), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255,200,200), 2);
	if(direction == 'L') cv::putText(frame, "->", cv::Point(180, 120), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255,200,200), 2);
    	sprintf(angle_buf, "%.1f deg", lkas.steering_angle);
        sprintf(speed_buf, "L: %.1f R: %.1f", lkas.left_speed, lkas.right_speed);
        cv::putText(frame, angle_buf, cv::Point(120, 110), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,165,255), 2);
        cv::putText(frame, speed_buf, cv::Point(x,y0+line_gap), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255,191,0), 1.5);
    } else {
        //cv::putText(frame, "LKAS INACTIVE", cv::Point(x,y0), cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(128, 128, 128), 2);
    }
}

void draw_fps_info(cv::Mat& frame, double fps, int height) {
    char fps_text[32];
    sprintf(fps_text, "FPS: %.2f", fps);
    cv::putText(frame, fps_text, cv::Point(210,220), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(200,200,200), 1);
}
