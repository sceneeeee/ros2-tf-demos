import rclpy
from rclpy.node import Node
from tf2_ros import StaticTransformBroadcaster # 静态坐标变换广播器
from geometry_msgs.msg import TransformStamped # 消息接口
from tf_transformations import quaternion_from_euler # 欧拉角转四元数
import math # 角度转弧度

class StaticTFBroadcaster(Node):
    
    def __init__(self):
        super().__init__("static_tf_broadcaster")
        self.static_broadcaster_ = StaticTransformBroadcaster(self) # 创建静态坐标变换广播器
        self.publish_static_tf() # 发布静态坐标变换


    def publish_static_tf(self):
        """
        发布静态TF变换, 从base_link到camera_link
        """
        transform = TransformStamped() # 创建坐标变换消息
        transform.header.frame_id = "base_link" # 父坐标系
        transform.child_frame_id = "camera_link" # 子坐标系
        transform.header.stamp = self.get_clock().now().to_msg() # 时间戳

        transform.transform.translation.x = 0.5 # 平移
        transform.transform.translation.y = 0.3
        transform.transform.translation.z = 0.6

        # 欧拉角转四元数 q = x, y, z, w
        q = quaternion_from_euler(math.radians(180), 0, 0) # 角度转弧度
        # 设置旋转
        transform.transform.rotation.x = q[0]
        transform.transform.rotation.y = q[1]
        transform.transform.rotation.z = q[2]
        transform.transform.rotation.w = q[3]
        # 发布静态坐标变换
        self.static_broadcaster_.sendTransform(transform)
        self.get_logger().info(f"Published static transform {transform}")


def main():
    rclpy.init()
    node = StaticTFBroadcaster()
    rclpy.spin(node)
    rclpy.shutdown()