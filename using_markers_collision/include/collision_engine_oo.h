#ifndef __COLIISION_ENGINE_OO_H__
#define __COLIISION_ENGINE_OO_H__

#include <ros/ros.h>
#include <visualization_msgs/MarkerArray.h>
#include <geometry_msgs/PoseStamped.h>

class CE_OO{
public:    
    CE_OO(ros::NodeHandle*);
    bool run();
protected:
    ros::NodeHandle *n;
    ros::Publisher c_r_c_pub;
    ros::Publisher c_g_c_pub;
    ros::Subscriber sub_c_r_c; //Cube, red, collision
    ros::Subscriber sub_c_g_c; //Cube, green, collision
    visualization_msgs::MarkerArray marker_array_msg;
    geometry_msgs::PoseStamped pose, c_r_c_msg, c_g_c_msg;
    void positionCallbackR(const geometry_msgs::PoseStamped::ConstPtr &msg);
    void positionCallbackG(const geometry_msgs::PoseStamped::ConstPtr &msg);
    void initialize_stuff();
};
#endif
