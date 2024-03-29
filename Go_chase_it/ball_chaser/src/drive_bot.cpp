#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"
//TODO: Include the ball_chaser "DriveToTarget" header file
using namespace std;

// ROS::Publisher motor commands;
ros::Publisher motor_command_publisher;

// TODO: Create a handle_drive_request callback function that executes whenever a drive_bot service is requested
// This function should publish the requested linear x and angular velocities to the robot wheel joints
// After publishing the requested velocities, a message feedback should be returned with the requested wheel velocities


bool handle_drive_request_callback(ball_chaser::DriveToTarget::Request &req, ball_chaser::DriveToTarget::Response &res){




	geometry_msgs::Twist motor_command;
       
        motor_command.linear.x = req.linear_x;

        motor_command.angular.z = req.angular_z;

       
        motor_command_publisher.publish(motor_command);

    res.msg_feedback = "service velocities setted!!";
    ROS_INFO_STREAM(res.msg_feedback);

    return true;




}

int main(int argc, char** argv)
{
    // Initialize a ROS node
    ros::init(argc, argv, "drive_bot");

    // Create a ROS NodeHandle object
    ros::NodeHandle n;


    motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    ros::ServiceServer service =n.advertiseService("/ball_chaser/command_robot",handle_drive_request_callback);



    ros::spin();

    return 0;
}
