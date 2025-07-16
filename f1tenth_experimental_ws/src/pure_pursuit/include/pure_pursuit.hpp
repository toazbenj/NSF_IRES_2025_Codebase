/*
Pure Pursuit Implementation in C++. Includes features such as dynamic lookahead. Does not have waypoint
interpolation yet.
*/
#include <math.h>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>

#include <Eigen/Eigen>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "ackermann_msgs/msg/ackermann_drive_stamped.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "rclcpp/rclcpp.hpp"
#include "visualization_msgs/msg/marker.hpp"
#include "visualization_msgs/msg/marker_array.hpp"

#define _USE_MATH_DEFINES
using std::placeholders::_1;
using namespace std::chrono_literals;


//new stuff

#include "nav_msgs/msg/path.hpp"
#include "std_msgs/msg/float64.hpp"
#include "std_msgs/msg/bool.hpp"


class PurePursuit : public rclcpp::Node {
   public:
    PurePursuit();

   private:
    // global static (to be shared by all objects) and dynamic variables (each instance gets its own copy -> managed on the stack)
    struct csvFileData {
        std::vector<double> X;
        std::vector<double> Y;
        std::vector<double> V;

        int index;
        int velocity_index;

        Eigen::Vector3d lookahead_point_world;  // from world reference frame (usually `map`)
        Eigen::Vector3d lookahead_point_car;    // from car reference frame
        Eigen::Vector3d current_point_world;    // Locks on to the closest waypoint, which gives a velocity profile
    };

    Eigen::Matrix3d rotation_m;

    double x_car_world;
    double y_car_world;
    bool paused_ = false;

    std::string odom_topic;
    std::string car_refFrame;
    std::string drive_topic;
    std::string global_refFrame;
    std::string rviz_current_waypoint_topic;
    std::string rviz_lookahead_waypoint_topic;
    std::string waypoints_path;
    double K_p;
    double min_lookahead;
    double max_lookahead;
    double lookahead_ratio;
    double steering_limit;
    double velocity_percentage;
    double curr_velocity = 0.0;

    bool emergency_breaking = false;
    std::string lane_number = "left";  // left or right lane

    // file object
    std::fstream csvFile_waypoints;

    // struct initialisation
    csvFileData waypoints;
    int num_waypoints;

    // Timer initialisation
    rclcpp::TimerBase::SharedPtr timer_;

    // declare subscriber sharedpointer obj
    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr subscription_odom;
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr pause_sub_;

    // declare publisher sharedpointer obj
    rclcpp::Publisher<ackermann_msgs::msg::AckermannDriveStamped>::SharedPtr publisher_drive;

    rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr vis_current_point_pub;
    rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr vis_lookahead_point_pub;

    // declare tf shared pointers
    std::shared_ptr<tf2_ros::TransformListener> transform_listener_{nullptr};
    std::unique_ptr<tf2_ros::Buffer> tf_buffer_;

    // private functions
    double to_radians(double degrees);
    double to_degrees(double radians);
    double p2pdist(double &x1, double &x2, double &y1, double &y2);

    void load_waypoints();

    void visualize_lookahead_point(Eigen::Vector3d &point);
    void visualize_current_point(Eigen::Vector3d &point);

    void get_waypoint();

    void quat_to_rot(double q0, double q1, double q2, double q3);

    void transformandinterp_waypoint();

    double p_controller();

    double get_velocity(double steering_angle);

    void publish_message(double steering_angle);

    void odom_callback(const nav_msgs::msg::Odometry::ConstSharedPtr odom_submsgObj);

    void timer_callback();

    //new stuff
    double commanded_speed;
    double yaw_car;
    
    rclcpp::Subscription<nav_msgs::msg::Path>::SharedPtr selected_waypoints_sub_;
    rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr speed_command_sub_;

    void selected_waypoints_callback(const nav_msgs::msg::Path::SharedPtr path_msg);
    void speed_command_callback(const std_msgs::msg::Float64::ConstSharedPtr msg);
    void pause_callback(std_msgs::msg::Bool::SharedPtr msg);

    
};
