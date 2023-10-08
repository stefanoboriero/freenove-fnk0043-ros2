#include <rclcpp/rclcpp.hpp>
#include <rclcpp/executors.hpp>

class MyNode: public rclcpp::Node
{
public:
    MyNode(): Node("cpp_test")
    {
        RCLCPP_INFO(this->get_logger(), "Hello in cpp");
        counter_ = 0;
        timer_ = this->create_wall_timer(std::chrono::seconds(1), std::bind(&MyNode::timer_callback, this));
    }
private:
    void timer_callback()
    {
        counter_++;
        RCLCPP_INFO(this->get_logger(), "Hello %d", counter_);
    }

    rclcpp::TimerBase::SharedPtr timer_;
    int counter_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}