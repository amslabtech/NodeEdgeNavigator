#ifndef __NODE_EDGE_NAVIGATOR_H
#define __NODE_EDGE_NAVIGATOR_H

#include <ros/ros.h>

#include <tf/tf.h>
#include <tf/transform_listener.h>

#include <std_msgs/Empty.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Int32MultiArray.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Odometry.h>

#include "amsl_navigation_msgs/Node.h"
#include "amsl_navigation_msgs/Edge.h"
#include "amsl_navigation_msgs/NodeEdgeMap.h"
#include "amsl_navigation_msgs/UpdateNode.h"
#include "amsl_navigation_msgs/UpdateEdge.h"
#include "amsl_navigation_msgs/Replan.h"
#include "amsl_navigation_managers/node_edge_map_interface.h"

class NodeEdgeNavigator
{
public:
    NodeEdgeNavigator(void);

    void map_callback(const amsl_navigation_msgs::NodeEdgeMapConstPtr&);
    void path_callback(const std_msgs::Int32MultiArrayConstPtr&);
    void pose_callback(const nav_msgs::OdometryConstPtr&);
    void edge_callback(const amsl_navigation_msgs::EdgeConstPtr&);
    void intersection_flag_callback(const std_msgs::BoolConstPtr&);
    void process(void);
    double pi_2_pi(double);
    void request_replanning(void);
    void arrived_at_node(void);
    double get_distance_from_points(const geometry_msgs::Point&, const geometry_msgs::Point&);
    void check_global_path_with_localization(void);
    double calculate_practical_edge_progress(const amsl_navigation_msgs::Edge&, int, int);
    void get_direction_from_positions(const geometry_msgs::Point&, const geometry_msgs::Point&, geometry_msgs::Pose&);
    bool is_ignorable_node(void);

private:
    double HZ;
    double EXCESS_DETECTION_RATIO;
    double GOAL_RADIUS;
    bool ENABLE_REQUESTING_REPLANNING;
    double INTERSECTION_ACCEPTANCE_PROGRESS_RATIO;
    std::string ROBOT_FRAME;
    double GOAL_DISTANCE;
    int GLOBAL_PATH_INDEX_OFFSET;
    double EXCESS_DETECTION_DISTANCE;
    double TIMEOUT;

    ros::NodeHandle nh;
    ros::NodeHandle private_nh;

    ros::Publisher direction_pub;
    ros::Publisher goal_flag_pub;
    ros::Subscriber map_sub;
    ros::Subscriber path_sub;
    ros::Subscriber pose_sub;
    ros::Subscriber edge_sub;
    ros::Subscriber intersection_flag_sub;
    ros::ServiceClient node_client;
    ros::ServiceClient edge_client;
    ros::ServiceClient replan_client;

    tf::TransformListener listener;
    tf::StampedTransform transform;

    amsl_navigation_msgs::NodeEdgeMap map;
    NodeEdgeMapInterface nemi;
    std::vector<int> global_path_ids;
    nav_msgs::Odometry estimated_pose;
    amsl_navigation_msgs::Edge estimated_edge;

    bool map_subscribed;
    bool global_path_subscribed;
    bool pose_updated;
    bool edge_updated;
    std::vector<int> passed_paths;
    bool intersection_flag;
    int last_target_node_id;
    bool first_edge_sub_flag;
    int global_path_index;
    std::vector<int> appended_position_type_node_list;
};

#endif// __NODE_EDGE_NAVIGATOR_H
