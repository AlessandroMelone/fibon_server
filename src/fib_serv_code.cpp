#include "ros/ros.h"
#include "fibon_serv/fib_serv.h" //forse ci vuole fib_serv invece di service
#include <iostream>
//#include <sstream>

using namespace std;


void print_fib(const std::vector<int>& seq){
	std::cout << "Sequence contains:";
	for (auto i: seq)
    		std::cout << ' ' << i;
  	std::cout << '\n';
}



bool fib_comp(const int& index, const int& lenght, std::vector<int>& out){	
	if(lenght<1||index<1) return false;

	out.resize(lenght+(index-1));
	out[0] = 1;

	if(lenght==1) return true;
	
	out[1] = 1;
	
	if(lenght==2) return true;
	
	for(int i=2;i<out.size();i++){
		out[i]=out[i-1]+out[i-2];		
	}
	cout<<endl;
	return true;
}


//http://www.cplusplus.com/reference/vector/vector/begin/
//the output of srv file is of type: std::vector<int>

bool service_callback( fibon_serv::fib_serv::Request &req , fibon_serv::fib_serv::Response &res) { 	

	fib_comp(req.index,req.lenght,res.sequence);
	res.sequence = std::vector<int>(res.sequence.begin()+req.index, res.sequence.end());      
      ROS_INFO("Client: index: [%d],  lenght: [% d] ", req.index, req.lenght);
	print_fib(res.sequence);
	return true ;
}

 
int main( int argc, char ** argv){

//	if(argc!=3){
//		ROS_INFO("[USAGE ] : rosrun fibonacci srv server INDEX LENGTH");
//	}
//		return 1 ;
//	
//	if(atoi(argv[1])<0||atoi(argv[2])<1){
//		ROS_INFO("[USAGE ] : rosrun fibonacci srv server WRONG INPUT");
//		return 1;
//	}

	ros::init(argc, argv, "fib_service");
	ros::NodeHandle n;
	ros::ServiceServer service = n.advertiseService("fibonacci_server", service_callback); 
	ROS_INFO("Ready to receive from client.");
	ros::spin();
	return 0;
}






