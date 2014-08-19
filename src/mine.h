#include "geometry_msgs/Point.h"

typedef enum _MineType
{
   ANTI_PERSONAL = 1,
   ANTI_TANK = 2

} MineType;

class Mine
{
public:
    Mine();
    Mine(geometry_msgs::Point & new_point);

    bool addPoint(geometry_msgs::Point & new_point, double minimum_distance);

    MineType type_;
    geometry_msgs::Point position_;

private:
    std::vector<geometry_msgs::Point> points_;

};

// EOF
