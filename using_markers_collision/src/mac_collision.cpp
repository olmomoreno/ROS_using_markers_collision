#include "/home/olmo/jade_workspace/src/using_markers_collision/include/mac_collision_oo.h"

MAS_OO::MAS_OO(ros::NodeHandle *nh){
    n=nh;
    marker_pub = n->advertise<visualization_msgs::MarkerArray>("visualization_marker_array", 1000);
    c_r_pub = n->advertise<geometry_msgs::PoseStamped>("feed_pos_c_r_c", 1000);
    c_g_pub = n->advertise<geometry_msgs::PoseStamped>("feed_pos_c_g_c", 1000);
    sub_c_r_c = n->subscribe("set_pos_c_r_c", 1000, &MAS_OO::positionCallbackR, this);
    sub_c_g_c = n->subscribe("set_pos_c_g_c", 1000, &MAS_OO::positionCallbackG, this);
    initialize_stuff();
}

void MAS_OO::initialize_stuff(){
//    visualization_msgs::Marker a;
//    marker_array_msg.markers.push_back(a);
    marker_array_msg.markers.resize(2);//final->width * final->height);
       for( int i = 0; i < 2; i++){
            marker_array_msg.markers[i].header.frame_id = "/base_link";
            marker_array_msg.markers[i].header.stamp = ros::Time();
            marker_array_msg.markers[i].ns = "array_simple";
            marker_array_msg.markers[i].id = i;
            marker_array_msg.markers[i].type = visualization_msgs::Marker::CUBE;
            marker_array_msg.markers[i].action = visualization_msgs::Marker::ADD;
            marker_array_msg.markers[i].pose.position.y = 0.0;
            marker_array_msg.markers[i].pose.position.z = 0.0;
            marker_array_msg.markers[i].pose.orientation.x = 0.0;
            marker_array_msg.markers[i].pose.orientation.y = 0.0;
            marker_array_msg.markers[i].pose.orientation.z = 0.0;
            marker_array_msg.markers[i].pose.orientation.w = 1.0;
            marker_array_msg.markers[i].scale.x = 1.0;
            marker_array_msg.markers[i].scale.y = 1.0;
            marker_array_msg.markers[i].scale.z = 1.0;
            marker_array_msg.markers[i].color.a = 1.0;
            if(i == 0){
                marker_array_msg.markers[i].color.r = 1.0;
                marker_array_msg.markers[i].color.g = 0.0;
                marker_array_msg.markers[i].color.b = 0.0;
            	marker_array_msg.markers[i].pose.position.x = 0.0;
            }
            if(i == 1){
                marker_array_msg.markers[i].color.r = 0.0;
                marker_array_msg.markers[i].color.g = 1.0;
                marker_array_msg.markers[i].color.b = 0.0;
            	marker_array_msg.markers[i].pose.position.x = -5.5;
            }
       }
       marker_pub.publish(marker_array_msg);
}

bool MAS_OO::run(){
    ros::Rate r(30);
    while (marker_pub.getNumSubscribers() < 1)
    {
        ROS_WARN_ONCE("Please create a subscriber to the marker_array");
        sleep(1);
    }
    while (ros::ok())
    {
        ros::spinOnce();
        c_r_c_msg.pose.position.x=marker_array_msg.markers[0].pose.position.x;
        c_g_c_msg.pose.position.x=marker_array_msg.markers[1].pose.position.x;
    	c_r_pub.publish(c_r_c_msg);
        c_g_pub.publish(c_g_c_msg);
        marker_pub.publish(marker_array_msg);
        r.sleep();
    }
}

void MAS_OO::positionCallbackR(const geometry_msgs::PoseStamped::ConstPtr &msg)
{
    pose=*msg;
    marker_array_msg.markers[0].pose.position.x=pose.pose.position.x;
    ROS_INFO("I heard R[%f]:", pose.pose.position.x);
    //marker.pose=msg->pose;
}

void MAS_OO::positionCallbackG(const geometry_msgs::PoseStamped::ConstPtr &msg)
{
    pose=*msg;
    marker_array_msg.markers[1].pose.position.x=pose.pose.position.x;
    //ROS_INFO("I heard R[%f]:", pose.pose.position.x);
    //marker.pose=msg->pose;
}

int main( int argc, char** argv )
{
    ros::init(argc, argv, "marker_array_collision");
    ros::NodeHandle n;
    MAS_OO instance(&n);
    instance.run();
}
