#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp" // 提供消息接口
#include "tf2/LinearMath/Quaternion.h" // 提供tf2::Quaternion类
#include "tf2_geometry_msgs/tf2_geometry_msgs.hpp" // 消息类型转换函数
#include "tf2_ros/transform_listener.h" // 坐标监听器类
#include "tf2_ros/buffer.h" 
#include "tf2/utils.h" // 提供四元数转欧拉角函数
#include "chrono" // 提供时间相关函数

using namespace std::chrono_literals; // 使用时间字面量


class TFListener: public rclcpp::Node
{
private:
    std::shared_ptr<tf2_ros::TransformListener> listener_; // 坐标监听器对象指针
    rclcpp::TimerBase::SharedPtr timer_; // 定时器对象指针
    std::shared_ptr<tf2_ros::Buffer> buffer_; // 坐标变换缓存对象指针

public:
    TFListener() : Node("tf_listener")
    {
        this->buffer_ = std::make_shared<tf2_ros::Buffer>(this->get_clock());
        this->listener_ = std::make_shared<tf2_ros::TransformListener>(*buffer_, this);
        timer_ = this->create_wall_timer(
            1s,
            std::bind(&TFListener::getTransform, this)
        );
    }

    void getTransform()
    {
        // 去buffer_中查询坐标变换
        try
        {
            // 查询从"base_link"坐标系到"target_point"坐标系的变换，时间戳为当前时间
            const auto transform = buffer_->lookupTransform(
                "base_link", 
                "target_point", 
                this->get_clock()->now(), 
                1s
            );

            // 输出查询到的坐标变换信息
            auto translation = transform.transform.translation; // 获取平移分量
            auto rotation = transform.transform.rotation; // 获取旋转分量

            double roll, pitch, yaw;
            tf2::getEulerYPR(rotation, roll, pitch, yaw); // 获取欧拉角（滚转、俯仰、偏航） 

            RCLCPP_INFO(this->get_logger(), "Transform : translation (%.2f, %.2f, %.2f), rotation (roll: %.2f, pitch: %.2f, yaw: %.2f)", 
                translation.x, translation.y, translation.z, 
                roll, pitch, yaw
            );
        }
        catch(const std::exception& e)
        {
            RCLCPP_WARN(this->get_logger(), "Could not get transform: %s", e.what());
        }
        
    };
};
int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv); 
    auto node = std::make_shared<TFListener>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

