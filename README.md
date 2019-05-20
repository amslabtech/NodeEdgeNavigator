# node_edge_navigator

[![Build Status](https://travis-ci.org/amslabtech/node_edge_navigator.svg?branch=master)](https://travis-ci.org/amslabtech/node_edge_navigator)

## node_edge_navigator
### Published topics
- /direction/relative (geometry_msgs/PoseStamped)

### Subscribed topics
- /node_edge_map/map (amsl_navigation_msgs/NodeEdgeMap)
- /global_path (std_msgs/Int32Array)
- /estimated_pose/edge (amsl_navigation_msgs/Edge)
- /estimated_pose/pose (nav_msgs/Odometry)

## local_goal_creator
### Published topics
- /local_goal (geometry_msgs/PoseStamped)

### Subscribed topics
- /direction/relative (geometry_msgs/PoseStamped)
- /local_map (nav_msgs/OccupancyGrid)
