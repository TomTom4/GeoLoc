#ifndef TEST_H
#define TEST_H

double ToRadians(double degrees);
double DirectDistance(double lat1, double lng1, double lat2, double lng2);
class Node{
	public :
		int id;
		float latitude;
		float longitude;

		void ToString();
		Node();
		Node(int Node_Id, float lon, float lat);
};

class Road{
	public :
		int id;
		Node begin;
		Node end;
		float a;
		float b;
		int width;

		void ToString();
		Road(int Road_Id, Node b, Node e);
		void Compute();
		double DistanceToCenter(double lon, double lat);
};

Node GetNodeById(int id, std::vector<Node> v);
int WhichRoad(double lon, double lat, std::vector<Road> v);


#endif
