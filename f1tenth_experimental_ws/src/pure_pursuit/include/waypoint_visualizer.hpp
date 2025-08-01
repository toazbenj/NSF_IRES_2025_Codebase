#include <math.h>

#include <chrono>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "rclcpp/rclcpp.hpp"
#include "visualization_msgs/msg/marker.hpp"
#include "visualization_msgs/msg/marker_array.hpp"

#include <nav_msgs/msg/path.hpp>

// other macros
#define _USE_MATH_DEFINES

using std::placeholders::_1;
using namespace std::chrono_literals;

class WaypointVisualizer : public rclcpp::Node {
   public:
    WaypointVisualizer();

   private:
    struct csvFileData {
        std::vector<double> X;
        std::vector<double> Y;
    };

    // topic names
    std::string waypoints_path;
    std::string rviz_waypoints_topic;
    std::string namespace_str;
    // file object
    std::fstream csvFile_waypoints;

    // struct initialisation
    csvFileData waypoints;

    // Publisher initialisation
    rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr vis_path_pub;
    rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr path_pub;
    
    // Timer initialisation
    rclcpp::TimerBase::SharedPtr timer_;

    // private functions

    void download_waypoints();
    void global_path_publish();
    void visualize_points();
    void timer_callback();
};