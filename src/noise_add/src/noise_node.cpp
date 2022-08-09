#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <stdlib.h>

#define PI 3.1415926536

double AWGN_generator()
{/* Generates additive white Gaussian Noise samples with zero mean and a standard deviation of 1. */
 
  double temp1;
  double temp2;
  double result;
  int p;

  p = 1;

  while( p > 0 )
  {
	temp2 = ( rand() / ( (double)RAND_MAX ) ); /*  rand() function generates an
                                                       integer between 0 and  RAND_MAX,
                                                       which is defined in stdlib.h.
                                                   */

    if ( temp2 == 0 )
    {// temp2 is >= (RAND_MAX / 2)
      p = 1;
    }// end if
    else
    {// temp2 is < (RAND_MAX / 2)
       p = -1;
    }// end else

  }// end while()

  temp1 = cos( ( 2.0 * (double)PI ) * rand() / ( (double)RAND_MAX ) );
  result = sqrt( -2.0 * log( temp2 ) ) * temp1;

  return result;	// return the generated random sample to the caller
}

void writeMsg(const geometry_msgs::Twist& msg){
    ROS_INFO_STREAM("Subscriber velocities:"<<" linear="<<msg.linear.x+AWGN_generator()<<" angular="<<msg.angular.z+AWGN_generator()<<"\n");
}

int main(int argc, char**argv){
ros::init(argc, argv, "publish_velocity");
ros::NodeHandle nh;

ros::Subscriber topic_sub= nh.subscribe("/cmd_vel", 1000,writeMsg);

    ros::spin();
    return 0;
}
