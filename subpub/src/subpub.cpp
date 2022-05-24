#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int64.hpp"
using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
      : Node("subpub")
  {
    subscription_ = this->create_subscription<std_msgs::msg::Int64>(
        "topic", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
    publisher_ = this->create_publisher<std_msgs::msg::Int64>("topic2", 10);
  }

private:
  void topic_callback(const std_msgs::msg::Int64 & msg) const
  {
//    RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
          std_msgs::msg::Int64 new_value;
          new_value.data = msg.data - 5;
          publisher_->publish(new_value);
  }
  rclcpp::Subscription<std_msgs::msg::Int64>::SharedPtr subscription_;
  rclcpp::Publisher<std_msgs::msg::Int64>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}