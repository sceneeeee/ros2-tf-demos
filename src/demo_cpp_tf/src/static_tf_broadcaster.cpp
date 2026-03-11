#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp" // 提供消息接口
#include "tf2/LinearMath/Quaternion.h" // 提供tf2::Quaternion类
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp" // 消息类型转换函数
#include "tf2_ros/static_transform_broadcaster.h" // 静态坐标广播器类


class StaticTFBroadcaster: public rclcpp::Node
{
private:
    std::shared_ptr<tf2_ros::StaticTransformBroadcaster> broadcaster_; // 坐标广播器对象指针
public:
    StaticTFBroadcaster() : Node("static_tf_broadcaster")
    {
        broadcaster_ = std::make_shared<tf2_ros::StaticTransformBroadcaster>(this);
        this->publish_tf();
    }

    void publish_tf()
    {
        geometry_msgs::msg::TransformStamped transform;

        transform.header.stamp = this->get_clock()->now(); // 设置时间戳
        transform.header.frame_id = "map"; // 设置父坐标系
        transform.child_frame_id = "target_point"; // 设置子坐标系

        transform.transform.translation.x = 5.0; // 设置平移分量
        transform.transform.translation.y = 3.0; // 设置平移分量
        transform.transform.translation.z = 0.0; // 设置平移分量

        tf2::Quaternion q; // 创建tf2::Quaternion对象
        q.setRPY(0.0, 0.0, 60*M_PI/180); // 设置欧拉角（滚转、俯仰、偏航）
        transform.transform.rotation = tf2::toMsg(q); // 设置旋转分量

        this->broadcaster_->sendTransform(transform); // 发布坐标变换
    }
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv); 
    auto node = std::make_shared<StaticTFBroadcaster>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

