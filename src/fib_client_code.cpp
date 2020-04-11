#include "ros/ros.h"
#include <iostream>
#include "fibon_serv/fib_serv.h"
#include <iostream>
#include <sstream>

using namespace std;


void print_fib(const std::vector<int>& seq);


int main(int argc, char **argv) {
	ros::init( argc, argv, "fibon_client");
	ros::NodeHandle n ;
	//ros::Rate loop_rate(10);
	ros::ServiceClient client = n.serviceClient<fibon_serv::fib_serv>("fibonacci_server");

	if(argc!=3){
		ROS_INFO("[USAGE ] : rosrun fibonacci srv client INDEX LENGTH");
		return 1 ;
	}

	if(atoi(argv[1])<0||atoi(argv[2])<1){
		ROS_INFO("[USAGE ] : rosrun fibonacci srv client WRONG INPUT");
		return 1 ;
	}

	
	
//	while(ros::ok()){
		fibon_serv::fib_serv srv;	
		//define request
		srv.request.index = atoi(argv[1]);
		srv.request.lenght = atoi(argv[2]);


//		std::stringstream ss ;
//		ss<<"Sending from Here";
//		srv.request.in = ss.str();

		if(client.call(srv)){
			cout<<"From Client: index ["<<srv.request.index<<"], lenght ["<<srv.request.lenght<<"]"<<endl;
			print_fib(srv.response.sequence);
		}
		else {
			ROS_ERROR("Failed to call service");
			return 1;
		}	

		ros::spin();
		//ros::spinOnce();
		//loop_rate.sleep();
//	}
	return 0;
}


//void print_server(std::vector<int> seq){
//	std::cout << "Sequence contains:";
//	for (std::vector<int>::iterator it=seq.begin(); it<seq.end(); it++)
//    		std::cout << ' ' << *it;
//  	std::cout << '\n';
//}

void print_fib(const std::vector<int>& seq){
	std::cout << "Sequence contains:";
	for (auto i: seq)
    		std::cout << ' ' << i;
  	std::cout << '\n';
}

