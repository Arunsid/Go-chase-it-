#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

ros::ServiceClient client;

void drive_bot(float lin_x,float ang_z)
{
	ball_chaser::DriveToTarget srv;
	srv.request.linear_x=lin_x;
	srv.request.angular_z=ang_z;

	if(!client.call(srv))
	{
	ROS_ERROR("Failed to call service ball_chaser");
	}
}

void process_image_callback(const sensor_msgs::Image img)
{


bool col_flag=false;
int col_value=0;

for(int i=0;i<img.height;i++)
{


int offset=img.step*i;

	for(int j=0;j<img.step;j+=3)
	{

		if(img.data[offset+j] == 255 && img.data[offset+j+1] == 255  && img.data[offset+j+2] == 255 )
		{
			col_flag=true;
			col_value=j/3;
	                break;
 		}
		

	}
	if(col_flag==true)break;

}


if(!col_flag){
		drive_bot(0.0,0.0);
		return;
	     }

if(col_value<(img.width/3))
		{	drive_bot(0.5,0.5);
			return;
		}

if(col_value>(img.width/3)*2)
		{
			drive_bot(0.5,-0.5);
			return;
		}
drive_bot(0.5,0.0);

}







int main(int argc,char **argv)
{
ros::init(argc,argv,"process_image");
ros::NodeHandle(nh);

client=nh.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");
ros::Subscriber sub1=nh.subscribe("camera/rgb/image_raw",10,process_image_callback);
ros::spin();
return 0;
}
