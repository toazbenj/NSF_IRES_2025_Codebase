#include "waypoint_visualizer.hpp"
#include <math.h>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <nav_msgs/msg/path.hpp>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include "rclcpp/rclcpp.hpp"
#include "visualization_msgs/msg/marker.hpp"
#include "visualization_msgs/msg/marker_array.hpp"
#include "ament_index_cpp/get_package_share_directory.hpp"

WaypointVisualizer::WaypointVisualizer() : Node("waypoint_visualizer_node") {
    this->declare_parameter("waypoints_path", "/src/pure_pursuit/racelines/e7_floor5.csv");
    this->declare_parameter("rviz_waypoints_topic", "/waypoints");
    this->declare_parameter("namespace_str", "/ego_racecar");


    std::string package_share_dir = ament_index_cpp::get_package_share_directory("pure_pursuit");
    waypoints_path = package_share_dir + "/racelines/e7_floor5.csv";

    // waypoints_path = this->get_parameter("waypoints_path").as_string();

    rviz_waypoints_topic = this->get_parameter("rviz_waypoints_topic").as_string();
    namespace_str = this->get_parameter("namespace_str").as_string();

    // Publisher for visualization (MarkerArray)
    vis_path_pub = this->create_publisher<visualization_msgs::msg::MarkerArray>(rviz_waypoints_topic + "_markers", 1000);
    
    // Publisher for path planning (Path)
    path_pub = this->create_publisher<nav_msgs::msg::Path>(namespace_str + rviz_waypoints_topic, 10);
    
    timer_ = this->create_wall_timer(2000ms, std::bind(&WaypointVisualizer::timer_callback, this));

    RCLCPP_INFO(this->get_logger(), "this node has been launched for real");
    RCLCPP_INFO(this->get_logger(), "Loaded waypoints_path: %s", waypoints_path.c_str());

    download_waypoints();
    global_path_publish();
}

void WaypointVisualizer::download_waypoints() {
    csvFile_waypoints.open(waypoints_path, std::ios::in);
    RCLCPP_INFO(this->get_logger(), "%s", (csvFile_waypoints.is_open() ? "fileOpened" : "fileNOTopened"));
    
    std::string line, word, temp;
    while (!csvFile_waypoints.eof()) {
        std::getline(csvFile_waypoints, line, '\n');
        std::stringstream s(line);
        int j = 0;
        while (getline(s, word, ',')) {
            // RCLCPP_INFO(this->get_logger(), "%s", (word.empty() ? "wordempty" : "wordNOTempty"));
            if (!word.empty()) {
                if (j == 0) {
                    double x = std::stod(word);
                    waypoints.X.push_back(x);
                    // RCLCPP_INFO(this->get_logger(), "%f... Xpoint", waypoints.X.back());
                }
                if (j == 1) {
                    waypoints.Y.push_back(std::stod(word));
                    // RCLCPP_INFO(this->get_logger(), "%f... Ypoint", waypoints.Y.back());
                }
            }
            j++;
        }
    }
    csvFile_waypoints.close();
}

void WaypointVisualizer::visualize_points() {
    // Publish MarkerArray for visualization
    auto marker_array = visualization_msgs::msg::MarkerArray();
    auto marker = visualization_msgs::msg::Marker();
    marker.header.frame_id = "map";
    marker.header.stamp = rclcpp::Clock().now();
    marker.type = visualization_msgs::msg::Marker::SPHERE;
    marker.action = visualization_msgs::msg::Marker::ADD;
    marker.scale.x = 0.15;
    marker.scale.y = 0.15;
    marker.scale.z = 0.15;
    marker.color.a = 1.0;
    marker.color.g = 1.0;
    
    for (unsigned int i = 0; i < waypoints.X.size(); ++i) {
        marker.pose.position.x = waypoints.X[i];
        marker.pose.position.y = waypoints.Y[i];
        marker.id = i;
        marker_array.markers.push_back(marker);
    }
    vis_path_pub->publish(marker_array);
}

void WaypointVisualizer::global_path_publish() {

    // Publish Path message for path planning
    auto path_msg = nav_msgs::msg::Path();
    path_msg.header.frame_id = "map";
    path_msg.header.stamp = rclcpp::Clock().now();
    
    for (unsigned int i = 0; i < waypoints.X.size(); ++i) {
        geometry_msgs::msg::PoseStamped pose;
        pose.header.frame_id = "map";
        pose.header.stamp = path_msg.header.stamp;
        pose.pose.position.x = waypoints.X[i];
        pose.pose.position.y = waypoints.Y[i];
        pose.pose.position.z = 0.0;
        pose.pose.orientation.w = 1.0; // Default orientation
        
        path_msg.poses.push_back(pose);
    }
    
    int repeat_cnt = 1;
    for (int i = 0; i < repeat_cnt; i++){
        path_pub->publish(path_msg);
        RCLCPP_INFO(this->get_logger(), "Published path with %zu waypoints", path_msg.poses.size());
    }

}

void WaypointVisualizer::timer_callback() {
    visualize_points();
    // global_path_publish();

}


int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node_ptr = std::make_shared<WaypointVisualizer>();
    rclcpp::spin(node_ptr);
    rclcpp::shutdown();
    return 0;
}