# Parser and Router

## Installing

You need to install OpenCV on your machine.

## How to interface with the code

First Initialize the Map class

```
rapidxml::file<> xmlFile("heavy.osm");
Map MyMap(xmlFile);
```

Then retrieve the User Nodes. This is where the users can be guided to

```
std::vector<tuple<string, double>> MyVectorOfUserDestination = MyMap.GetTupleOfDestinations();
```

The car should now be placed on a node (or as close as possible) in order to start driving.
Our car can therefore start from anywhere on the map. This is done by asking the MyMap instance.

```
double CurrentClosestNode = MyMap.GetClosestNode()->GetId();
```

In order to go somewhere we need to tell the car where about. therefore you need to
send the node id corresponding to the destination from the vector of tuples.
