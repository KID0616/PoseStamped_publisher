// ros/ros.h　ROSに関する基本的なAPIのためのヘッダ
#include "ros/ros.h"

#include <geometry_msgs/PoseStamped.h>

int main(int argc, char **argv)
{
  // 初期化のためのAPI
  // このノードは"para_in"という名前であるという意味
  ros::init(argc, argv, "para_in");

  // ノードハンドラの宣言
  ros::NodeHandle n;

  //Publisherとしての定義
  // n.advertise<comp_tutorial::adder>("para_input", 1000);
  // comp_tutorial::adder型のメッセージをpara_inputというトピックへ配信する
  //"1000"はトピックキューの最大値
  ros::Publisher para_pub = n.advertise<geometry_msgs::PoseStamped>("Pose_Stamped", 1000);

  //1秒間に1つのメッセージをPublishする
  ros::Rate loop_rate(10);

  //comp_tutrial::adder型のオブジェクトを定義
  //adder.msgで定義したa,bはメンバ変数としてアクセスできる
  geometry_msgs::PoseStamped msg;

  double count = 0;
  while (ros::ok())//ノードが実行中は基本的にros::ok()=1
  {
    msg.pose.position.x = count;
    msg.pose.position.y = count;
    msg.header.frame_id = "Unity";
    msg.header.stamp =  ros::Time::now();
    para_pub.publish(msg);//PublishのAPI
    printf("a = %f b = %f \n",msg.pose.position.x  ,msg.pose.position.y );
    ros::spinOnce();
    loop_rate.sleep();
    count++;
  }
  return 0;
}
