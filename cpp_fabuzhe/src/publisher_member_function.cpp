/* 实现：以某个固定频率发送文本“hello world!”，文本后缀编号，每发送一条消
息，编号递增 1。 */
// 1.包含头文件；
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
// 方便时间的表示
using namespace std::chrono_literals;
// 3.定义节点类； 继承 rclcpp::node 创建节点类
class MinimalPublisher : public rclcpp::Node
{
public:
    // 公共构造函数将节点命名，并初始化参数
    MinimalPublisher()
        : Node("minimal_publisher"), count_(0)
    {
        // 3-1.创建发布方；
        publisher_ =
            this->create_publisher<std_msgs::msg::String>("topic", 10);
        // 3-2.创建定时器；
        timer_ = this->create_wall_timer(500ms,
                                         std::bind(&MinimalPublisher::timer_callback, this));
    }

private:
    // 定义定时器回调函数
    void timer_callback()
    {
        // 3-3.组织消息并发布。
        auto message = std_msgs::msg::String();
        message.data = "Hello, world! " + std::to_string(count_++);
        RCLCPP_INFO(this->get_logger(), "发布的消息：'%s'",
                    message.data.c_str());
        publisher_->publish(message);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    size_t count_;
};
int main(int argc, char *argv[])
{
    // 2.初始化 ROS2 客户端；
    rclcpp::init(argc, argv);
    // 4.调用 spin 函数，并传入节点对象指针。
    rclcpp::spin(std::make_shared<MinimalPublisher>());
    // 5.释放资源；
    rclcpp::shutdown();
    return 0;
}