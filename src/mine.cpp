#include "mine.h"

Mine::Mine()
{

}

Mine::Mine(geometry_msgs::Point & new_point)
{
    points_.push_back(new_point);
    position_.x = new_point.x;
    position_.y = new_point.y;
}

bool Mine::addPoint(geometry_msgs::Point & new_point, double minimum_distance)
{
    // Check if the new point is within range of this mine
    double distance = sqrt(pow(new_point.x - position_.x, 2) + pow(new_point.y - position_.y, 2));
    if(distance < minimum_distance)
    {
        // If so add it to the points list
        points_.push_back(new_point);

        // And re-calculate the position of the mine
        double x = 0.0;
        double y = 0.0;
        for(std::vector<geometry_msgs::Point>::iterator point_it = points_.begin() ; point_it != points_.end() ; ++point_it)
        {
            x += point_it->x;
            y += point_it->y;
        }
        position_.x = x/points_.size();
        position_.y = y/points_.size();

        // Return true if point was added
        return true;
    }

    // Return false if the point was not added
    return false;
}

// EOF
