
#include "ros/ros.h"
#include "geometry_msgs/Point.h"
#include "mine.h"
#include "mine_mapping/Mines.h"

std::vector<Mine> mines;

// Parameters
double mine_distance;
std::string frame_id;

ros::Publisher * mine_pub_ptr;

void pointsCallback(const geometry_msgs::Point::ConstPtr& msg)
{
    geometry_msgs::Point new_point = *msg;

    // If the mines vector is empty create a new mine
    if(mines.empty()) mines.push_back(Mine(new_point));
    // Else lets check if the point belongs to an existing mine...
    else
    {
        for(std::vector<Mine>::iterator mine_it = mines.begin() ; mine_it != mines.end() ; ++mine_it)
        {
            // If it belongs to an existing mine return.
            if(mine_it->addPoint(new_point, mine_distance/2.0)) return;
        }
    }

    // Otherwise create a new mine!
    mines.push_back(Mine(new_point));

    // Publish the new set of mines!
    mine_mapping::Mines mines_msg;
    mines_msg.header.stamp = ros::Time::now();
    mines_msg.header.frame_id = frame_id;
    for(std::vector<Mine>::iterator mine_it = mines.begin() ; mine_it != mines.end() ; ++mine_it)
    {
        geometry_msgs::Point p;
        p.x = mine_it->position_.x;
        p.y = mine_it->position_.y;
        mines_msg.mine.push_back(p);
        mines_msg.type.push_back(mine_it->type_);
    }
    mine_pub_ptr->publish(mines_msg);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "mine_mapping_node");

    ros::NodeHandle n;
    ros::NodeHandle pn("~");

    ROS_INFO("Mine mapping node for ROS V0.1");

    ros::Subscriber point_sub = n.subscribe("geo_point_minas", 100, pointsCallback);

    ros::Publisher mine_pub = n.advertise<mine_mapping::Mines>("mines", 1, true);

    mine_pub_ptr = &mine_pub;

    pn.param<std::string>("mines_frame_id", frame_id, "minefield");
    pn.param("min_mine_distance", mine_distance, 0.5);

    ros::spin();

    return 0;
}

// EOF
