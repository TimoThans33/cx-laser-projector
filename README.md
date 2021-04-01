# CX Laser Projector

code used for the laser projector.

## Getting started
```
mkdir build && cd build
```
```
cmake ../ && make -j4
```
```
./app
``` 

## new features
* filemanagement

Reading a csv file and store in the correct format for openGL.

* path scene

This feature includes code for the rendering of the csv file in openGL.

## communication with AS robots

RobotClient:

Trajectory
```
void RobotClient::executeTrajectory(const std::string& msg)
{
    node_.request(tjess::transport::Scope::HOST, pv::CmdLineArgs::getNamespace()+"_robot_manager", "executeTrajectory", msg );
}
```
Deze trajectory kan dus opgevraagd worden met Tjess maar wordt hier gemaakt: robot manager execute trajectory -> motion_planning.cpp
```
bool MotionPlanning::executeTrajectory(const MinimalTrajectory& new_trajectory)

bool MotionPlanning::getFeasibleTrajectory(const MinimalTrajectory& trajectory_in, Trajectory& trajectory_out)

GeneratorOutput out = path_generator_.generatePath(default_generator, gen_input);

for(int i = 0; i<out.x.size(); i++)
{
    TrajectoryPoint tmp_point;
    tmp_point.pose.push_back(out.x.at(i));
    tmp_point.pose.push_back(out.y.at(i));
    tmp_point.pose.push_back(out.theta.at(i));
    tmp_point.velocity = out.vx.at(i);
    tmp_point.acceleration = out.ax.at(i);
    tmp_point.angular_rate = out.psi.at(i);
    tmp_point.lateral_acceleration = out.vx.at(i)*out.psi.at(i);
    tmp_point.curvature = out.psi.at(i)/std::max(out.vx.at(i),0.0000001f);
    tmp_point.time = out.t.at(i) + feasible_path_start_time;       //  temorary solution, time shift will be sent from the rover 
    trajectory_out.points.push_back(tmp_point);
}

FeasiblePathGenerator path_generator_;

-> #include "primevision/mpl/generators/feasible_path_generator.h"

GeneratorOutput FeasiblePathGenerator::generatePath(const std::string& generator, const GeneratorInput& input)

struct GeneratorOutput
{
	std::vector<float>  x;
	std::vector<float>  y;
	std::vector<float>  theta;
	std::vector<float>  vx;
	std::vector<float>  psi;
	std::vector<float>  ax;
	std::vector<float>  t;
    int start;
    int finish;
    bool valid{false};
};

if(publish_corridor_)
{
nlohmann::json cor_msg = nlohmann::json::object();
cor_msg["id"] = pv::CmdLineArgs::getNamespace();
cor_msg["corridor"] = nlohmann::json::array();
for(auto p : safe_corridor)
{
    nlohmann::json line = { p.first, p.second};
    cor_msg["corridor"].push_back(line);
}

triggerEvent_("CORRIDOR_VIZ", cor_msg.dump() );
}

```
Sensor data
```
node_.subscribe(tjess::transport::Scope::HOST, "/" + pv::CmdLineArgs::getNamespace()+"_robot_manager/status", [this](const std::string& req))

nlohmann::json cmd = nlohmann::json::parse(req);
if(cmd.count("odom")==1 && cmd["odom"].is_array())
{
    std::vector<float> odom = cmd["odom"].get<std::vector<float>>();
    position_x = odom.at(0);
    position_y = odom.at(1);
    orientation_z = odom.at(2);
    velocity_x_ = odom.at(3);
    angular_rate_ = odom.at(4);
}
```

tjess gebruiken of eigen functies toevoegen?

mqtt voor sensor data?

Opties trajectory doorgeven?
-> trajectory doorsturen met JSON (gebeurt nu ook al)
    -> naar socket (TCP)
    -> naar udp(?)
-> trajectory schrijven naar file en file serven
    -> MQTT message doorgeven dat robot gaat rijden...

## Resources
* Hands-on Network Programming with C: Learn Socket Programming in C

Learn socket programming in C and write secure and optimized network code.

* openGL SuperBible

Usefull to get some context of graphics and the GPU. Very advanced.
