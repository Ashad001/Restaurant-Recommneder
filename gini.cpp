#include <iostream>
#include <vector>
#include <string>
using namespace std;

float find_gini(vector<string> &alldata)
{
	// instance will be all reccomendations which is 1 for yes and 0 for no
	// gini is one minus all instances divided by total instances so
	int yes_instances, no_instances, all_instances, y_instances, n_instances;
	yes_instances = no_instances = all_instances = y_instances = n_instances = 0;
	int instance_index = 0;
	float gini[5]; // as we have 5 categories to filter data
	// gain[0] is reccmendations
	// gain[1] is reservations
	// gain[2] is pricing
	// gain[3] is cuisine
	// gain[4] is timing
	// calculating gini for reccomendation
	for (int i = 0; i < alldata.size(); i++)
	{
		while (alldata[i] != "Recommend")
		{ // loop to find where instance starts in a container of generic size
			instance_index++;
		}
		break;
	}
	for (int i = instance_index; i < alldata.size(); i++)
	{
		if (alldata[i] == "1")
		{
			yes_instances++;
			// calculates number of restraunts we reccomend
		}
		else if (alldata[i] == "0")
		{
			no_instances++;
			// calculates number of restraunts we dont reccomend
		}
		all_instances++;
		// calculates number of all restraunts we reccomend or not
	}
	gini[0] = (1 - (sqrt(y_instances / all_instances)) + (sqrt(n_instances / all_instances)));

	instance_index = 0;
	all_instances = 0;
	yes_instances = 0;
	no_instances = 0;
	// calculating gini for reservations
	for (int i = 0; i < alldata.size(); i++)
	{
		while (alldata[i] != "Reservation")
		{ // loop to find where instance starts in a container of generic size
			instance_index++;
		}
		break;
	}
	for (int i = instance_index; i < alldata.size(); i++)
	{
		if (alldata[i] == "yes")
		{
			yes_instances++;
			// calculates number of restraunts with reservations
		}
		else if (alldata[i] == "no")
		{
			no_instances++;
			// calculates number of restraunts without reservations
		}
		all_instances++;
		// calculates number of all restraunts needing reservations or not
	}
	gini[1] = (1 - (sqrt(yes_instances / all_instances)) + (sqrt(no_instances / all_instances)));

	instance_index = 0;
	all_instances = 0;
	yes_instances = 0;
	no_instances = 0;
	// calculating gini for price
	for (int i = 0; i < alldata.size(); i++)
	{
		while (alldata[i] != "Price Range")
		{ // loop to find where instance starts in a container of generic size
			instance_index++;
		}
		break;
	}
	for (int i = instance_index; i < alldata.size(); i++)
	{
		if (alldata[i] == "below 5k")
		{
			yes_instances++;
			// calculates number of restraunts with pricing below 5k
		}
		else if (alldata[i] == "above 5k")
		{
			no_instances++;
			// calculates number of restraunts with pricing above 5k
		}
		all_instances++;
		// calculates number of all restraunts with price ranges
	}
	gini[2] = (1 - (sqrt(yes_instances / all_instances)) + (sqrt(no_instances / all_instances)));

	instance_index = 0;
	all_instances = 0;
	yes_instances = 0;
	no_instances = 0;
	int yes1_instances = 0;
	int no1_instances = 0;
	// calculating gini for cuisine
	for (int i = 0; i < alldata.size(); i++)
	{
		while (alldata[i] != "Cuisine")
		{ // loop to find where instance starts in a container of generic size
			instance_index++;
		}
		break;
	}
	for (int i = instance_index; i < alldata.size(); i++)
	{
		if (alldata[i] == "American")
		{
			yes_instances++;
			// calculates number of restraunts with american cuisine
		}
		else if (alldata[i] == "Desi")
		{
			no_instances++;
			// calculates number of restraunts with desi cuisine
		}
		else if (alldata[i] == "Chinese")
		{
			yes1_instances++;
			// calculates number of restraunts with chinese cuisine
		}
		else if (alldata[i] == "Middle Eastern")
		{
			no1_instances++;
			// calculates number of restraunts with middle eastern cuisine
		}
		all_instances++;
		// calculates number of all cuisines
	}
	gini[3] = (1 - (sqrt(yes_instances / all_instances)) + (sqrt(no_instances / all_instances)) + (sqrt(yes1_instances / all_instances)) + (sqrt(no1_instances / all_instances)));

	instance_index = 0;
	all_instances = 0;
	yes_instances = 0;
	no_instances = 0;
	yes1_instances = 0;
	no1_instances = 0;
	int yes2_instances = 0;
	int no2_instances = 0;
	int yes3_instances = 0;

	// calculating gini for timing
	for (int i = 0; i < alldata.size(); i++)
	{
		while (alldata[i] != "Timing")
		{ // loop to find where instance starts in a container of generic size
			instance_index++;
		}
		break;
	}
	for (int i = instance_index; i < alldata.size(); i++)
	{
		if (alldata[i] == "Breakfast,Lunch,Dinner")
		{
			yes_instances++;
			// calculates number of restraunts with all day service
		}
		else if (alldata[i] == "Breakfast,Lunch")
		{
			no_instances++;
			// calculates number of restraunts with day service
		}
		else if (alldata[i] == "Lunch,Dinner")
		{
			yes1_instances++;
			// calculates number of restraunts with lunch and dinner
		}
		else if (alldata[i] == "Breakfast,Dinner")
		{
			no1_instances++;
		}
		else if (alldata[i] == "Breakfast")
		{
			yes2_instances++;
		}
		else if (alldata[i] == "Lunch")
		{
			no2_instances++;
		}
		else if (alldata[i] == "Dinner")
		{
			yes3_instances++;
		}
		all_instances++;
		// calculates number of all timings
	}
	gini[4] = (1 - (sqrt(yes_instances / all_instances)) + (sqrt(no_instances / all_instances)) + (sqrt(yes1_instances / all_instances)) + (sqrt(no1_instances / all_instances)) + (sqrt(yes2_instances / all_instances)) + (sqrt(no2_instances / all_instances)) + (sqrt(yes3_instances / all_instances)));

	// now we will check for purest gini split
}
int main()
{
}
