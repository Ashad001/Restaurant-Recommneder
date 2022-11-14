#include <iostream>
#include <vector>
#include <string>
using namespace std;
float gini[5]; // as we have 5 categories to filter data, this is global scoped
string gininame[5] = {"Recommend", "Reservation", "Price Range", "Cuisine", "Timing"};
int find_root_gini(string alldata[], int arrlen)
{
	int indarr[5];
	for (int i = 0; i < arrlen; i++)
	{ // loop to find where instance starts in a container of generic size
		if (alldata[i] == "Recommend")
		{

			indarr[0] = i;
		}
		else if (alldata[i] == "Reservation")
		{
			indarr[1] = i;
		}
		else if (alldata[i] == "Price Range")
		{
			indarr[2] = i;
		}
		else if (alldata[i] == "Cuisine")
		{
			indarr[3] = i;
		}
		else if (alldata[i] == "Timing")
		{
			indarr[4] = i;
		}
	}
	// instance will be all reccomendations which is 1 for yes and 0 for no
	// gini is one minus all instances divided by total instances squared
	float yes_instances = 0, no_instances = 0, all_instances = 0;
	int instance_index = 0, rec_start_instance = 0;

	// gain[0] is reccmendations
	// gain[1] is reservations
	// gain[2] is pricing
	// gain[3] is cuisine
	// gain[4] is timing
	// calculating gini for reccomendation
	for (int i = 0; i < arrlen; i++)
	{
		if (alldata[i] != "Recommend")
		{ // loop to find where instance starts in a container of generic size
			instance_index++;
		}
		rec_start_instance = indarr[0];
	}
	for (int i = indarr[0] + 1; i < indarr[1]; i++)
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

	gini[0] = (1 - pow((yes_instances / all_instances), 2) + pow((no_instances / all_instances), 2));

	instance_index = 0;
	all_instances = -1;
	yes_instances = 0;
	no_instances = 0;
	int rec_count = 0, dontrec_count = 0, rec1_count = 0, dontrec1_count = 0;
	// calculating gini for reservations
	for (int i = 0; i < arrlen; i++)
	{
		if (alldata[i] != "Reservation")
		{ // loop to find where instance starts in a container of generic size
			instance_index++;
		}
		else if (alldata[i] == "Reservation")
		{

			break;
		}
	}
	int j = 0;
	for (int i = indarr[1]; i < indarr[2]; i++)
	{

		if (alldata[i] == "yes")
		{

			yes_instances++;
			// calculates number of restraunts with reservations

			if (alldata[j + rec_start_instance] == "1")
			{ // finding if reservation is yes , is it reccomended or not
				// cout<<gini[0];
				rec_count++;
			}
			else if (alldata[j + rec_start_instance] == "0")
			{

				dontrec_count++;
			}
		}
		else if (alldata[i] == "no")
		{

			no_instances++;
			// calculates number of restraunts without reservations
			if (alldata[j + rec_start_instance] == "1")
			{ // finding if reservation is no , is it reccomended or not

				rec1_count++;
			}
			else if (alldata[j + rec_start_instance] == "0")
			{
				dontrec1_count++;
			}
		}

		all_instances++;
		// calculates number of all restraunts needing reservations or not
		j++;
	}

	// cout<<yes_instances<<no_instances<<all_instances;
	gini[1] = ((yes_instances / all_instances) * (1 - pow((rec_count / (rec_count + dontrec_count)), 2) - pow((dontrec_count / (rec_count + dontrec_count)), 2)) +
			   ((no_instances / all_instances) * (1 - pow((rec1_count / (rec1_count + dontrec1_count)), 2) - pow((dontrec1_count / (rec1_count + dontrec1_count)), 2))));

	j = 0;
	instance_index = 0;
	all_instances = 0;
	yes_instances = 0;
	no_instances = 0;
	rec_count = 0;
	dontrec_count = 0;
	rec1_count = 0;
	dontrec1_count = 0;
	// calculating gini for price range
	for (int i = 0; i < arrlen; i++)
	{
		if (alldata[i] != "Price Range")
		{ // loop to find where instance starts in a container of generic size
			instance_index++;
		}
		else if (alldata[i] == "Price Range")
		{

			break;
		}
	}
	for (int i = indarr[2]; i < indarr[3]; i++)
	{
		if (alldata[i] == "below 5k")
		{
			yes_instances++;
			// calculates number of restraunts with reservations
			if (alldata[j + rec_start_instance] == "1")
			{ // finding if price range is below 5k , is it reccomended or not
				rec_count++;
			}
			else if (alldata[j + rec_start_instance] == "0")
			{
				dontrec_count++;
			}
		}
		else if (alldata[i] == "above 5k")
		{
			no_instances++;
			// calculates number of restraunts with pricing above 5k
			if (alldata[j + rec_start_instance] == "1")
			{ // finding if pricing is above 5k , is it reccomended or not
				rec1_count++;
			}
			else if (alldata[j + rec_start_instance] == "0")
			{
				dontrec1_count++;
			}
		}
		all_instances++;
		j++;
		// calculates number of all restraunts with price range
	}
	gini[2] = ((yes_instances / all_instances) * (1 - pow((rec_count / (rec_count + dontrec_count)), 2) - pow((dontrec_count / (rec_count + dontrec_count)), 2)) +
			   ((no_instances / all_instances) * (1 - pow((rec1_count / (rec1_count + dontrec1_count)), 2) - pow((dontrec1_count / (rec1_count + dontrec1_count)), 2))));

	j = 0;
	instance_index = 0;
	all_instances = 0;
	int y_instances[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int n_instances[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int recount[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int drecount[8] = {0, 0, 0, 0, 0, 0, 0, 0};

	// calculating gini for cuisine
	for (int i = 0; i < arrlen; i++)
	{
		if (alldata[i] != "Cuisine")
		{ // loop to find where instance starts in a container of generic size
			instance_index++;
		}
		else if (alldata[i] == "Cuisine")
		{

			break;
		}
	}
	for (int i = indarr[3]; i < indarr[4]; i++)
	{
		if (alldata[i] == "American")
		{
			y_instances[0]++;

			// calculates number of restraunts with reservations
			if (alldata[j + rec_start_instance] == "1")
			{ // finding if price range is below 5k , is it reccomended or not
				recount[0]++;
			}
			else if (alldata[j + rec_start_instance] == "0")
			{

				drecount[0]++;
			}
		}
		else if (alldata[i] == "Desi")
		{

			n_instances[0]++;
			// calculates number of restraunts with pricing above 5k
			if (alldata[j + rec_start_instance] == "1")
			{ // finding if pricing is above 5k , is it reccomended or not

				recount[1]++;
			}
			else if (alldata[j + rec_start_instance] == "0")
			{

				drecount[1]++;
			}
		}
		else if (alldata[i] == "Chinese")
		{
			y_instances[1]++;

			// calculates number of restraunts with chinese cuisine
			if (alldata[j + rec_start_instance] == "1")
			{ // finding if pricing is above 5k , is it reccomended or not
				recount[2]++;
			}
			else if (alldata[j + rec_start_instance] == "0")
			{
				drecount[2]++;
			}
		}
		else if (alldata[i] == "Middle Eastern")
		{
			n_instances[1]++;
			// calculates number of restraunts with middle eastern cuisine
			if (alldata[j + rec_start_instance] == "1")
			{ // finding if pricing is above 5k , is it reccomended or not
				recount[3]++;
			}
			else if (alldata[j + rec_start_instance] == "0")
			{
				drecount[3]++;
			}
		}

		all_instances++;
		j++;

		// calculates number of all restraunts needing reservations or not
	}
	if (drecount[2] == 0)
		drecount[2] = 1;

	if (drecount[3] == 0)
		drecount[3] = 1;

	gini[3] =
		(((y_instances[0] / all_instances) * (1 - pow(recount[0] / (recount[0] + drecount[0]), 2) - pow((drecount[0] / (recount[0] + drecount[0])), 2))) +
		 ((n_instances[0] / all_instances) * (1 - pow((recount[1] / (recount[1] + drecount[1])), 2) - pow((drecount[1] / (recount[1] + drecount[1])), 2))) +
		 ((y_instances[1] / all_instances) * (1 - pow((recount[2] / (recount[2] + drecount[2])), 2) - pow((drecount[2] / (recount[2] + drecount[2])), 2))) +
		 ((n_instances[1] / all_instances) * (1 - pow((recount[3] / (recount[3] + drecount[3])), 2) - pow((drecount[3] / (recount[3] + drecount[3])), 2))));

	for (int i = 0; i < 8; i++)
	{
		y_instances[i] = n_instances[i] = recount[i] = drecount[i] = 0;
	}
	instance_index = 0;
	all_instances = 0;
	j = 0;
	// calculating gini for timing
	for (int i = 0; i < arrlen; i++)
	{
		if (alldata[i] != "Timing")
		{ // loop to find where instance starts in a container of generic size
			instance_index++;
		}
		else if (alldata[i] == "Timing")
		{

			break;
		}
	}
	for (int i = indarr[4]; i < indarr[5]; i++)
	{
		if (alldata[i] == "Breakfast,Lunch,Dinner")
		{
			y_instances[0]++;
			// calculates number of restraunts with all day service
			if (alldata[j + rec_start_instance] == "1")
			{ // finding if price range is below 5k , is it reccomended or not
				recount[0]++;
			}
			else if (alldata[j + rec_start_instance] == "0")
			{
				drecount[0]++;
			}
		}
		else if (alldata[i] == "Breakfast,Lunch")
		{
			n_instances[0]++;
			// calculates number of restraunts with day service
			if (alldata[j + rec_start_instance] == "1")
			{ // finding if pricing is above 5k , is it reccomended or not
				recount[1]++;
			}
			else if (alldata[j + rec_start_instance] == "0")
			{
				drecount[1]++;
			}
		}
		else if (alldata[i] == "Lunch,Dinner")
		{
			y_instances[1]++;
			// calculates number of restraunts with lunch and dinner
			if (alldata[j + rec_start_instance] == "1")
			{ // finding if pricing is above 5k , is it reccomended or not
				recount[2]++;
			}
			else if (alldata[j + rec_start_instance] == "0")
			{
				drecount[2]++;
			}
		}
		else if (alldata[i] == "Breakfast,Dinner")
		{
			n_instances[1]++;
			if (alldata[j + rec_start_instance] == "1")
			{ // finding if pricing is above 5k , is it reccomended or not
				recount[3]++;
			}
			else if (alldata[j + rec_start_instance] == "0")
			{
				drecount[3]++;
			}
		}
		else if (alldata[i] == "Breakfast")
		{
			y_instances[2]++;
			if (alldata[j + rec_start_instance] == "1")
			{ // finding if pricing is above 5k , is it reccomended or not
				recount[4]++;
			}
			else if (alldata[j + rec_start_instance] == "0")
			{
				drecount[4]++;
			}
		}
		else if (alldata[i] == "Lunch")
		{
			n_instances[2]++;
			if (alldata[j + rec_start_instance] == "1")
			{ // finding if pricing is above 5k , is it reccomended or not
				recount[5]++;
			}
			else if (alldata[j + rec_start_instance] == "0")
			{
				drecount[5]++;
			}
		}
		else if (alldata[i] == "Dinner")
		{
			y_instances[3]++;
			if (alldata[j + rec_start_instance] == "1")
			{ // finding if pricing is above 5k , is it reccomended or not
				recount[6]++;
			}
			else if (alldata[j + rec_start_instance] == "0")
			{
				drecount[6]++;
			}
		}
		j++;
		all_instances++;
		// calculates number of all timings
	}
	if (drecount[2] == 0)
		drecount[2] = 1;

	if (drecount[3] == 0)
		drecount[3] = 1;

	if (drecount[4] == 0)
		drecount[4] = 1;

	if (drecount[5] == 0)
		drecount[5] = 1;

	if (drecount[6] == 0)
		drecount[6] = 1;

	if (drecount[1] == 0)
		drecount[1] = 1;

	if (drecount[0] == 0)
		drecount[0] = 1;

	gini[4] = ((y_instances[0] / all_instances) * (1 - pow((recount[0] / (recount[0] + drecount[0])), 2) - pow((drecount[0] / (recount[0] + drecount[0])), 2)) +
			   ((n_instances[0] / all_instances) * (1 - pow((recount[1] / (recount[1] + drecount[1])), 2) - pow((drecount[1] / (recount[1] + drecount[1])), 2))) + (y_instances[1] / all_instances) * (1 - pow((recount[2] / (recount[2] + drecount[2])), 2) - pow((drecount[2] / (recount[2] + drecount[2])), 2)) +
			   ((n_instances[1] / all_instances) * (1 - pow((recount[3] / (recount[3] + drecount[3])), 2) - pow((drecount[3] / (recount[3] + drecount[3])), 2))) +
			   (y_instances[2] / all_instances) * (1 - pow((recount[4] / (recount[4] + drecount[4])), 2) - pow((drecount[4] / (recount[4] + drecount[4])), 2)) +
			   ((n_instances[2] / all_instances) * (1 - pow((recount[5] / (recount[5] + drecount[5])), 2) - pow((drecount[5] / (recount[5] + drecount[5])), 2))) + (y_instances[3] / all_instances) * (1 - pow((recount[6] / (recount[6] + drecount[6])), 2) - pow((drecount[6] / (recount[6] + drecount[6])), 2)));

	// finding lowest gini and returning it to main, we will be returning index of lowest gini instead
	int min = 1, ind = 0;
	for (int i = 1; i < 5; i++)
	{
		if (gini[i] < min)
		{
			min = gini[i];
			ind = i;
		}
	}

	return ind;
}
int main()
{
	int index = 0;
	string alldata[30] = {"Name", "a", "b", "c", "d", "Recommend", "1", "0", "1", "1", "Reservation", "yes", "no", "yes", "yes", "Price Range", "above 5k", "below 5k", "below 5k", "below 5k", "Cuisine", "American", "American", "Desi", "American", "Timing", "Lunch", "Breakfast", "Breakfast,Lunch", "Breakfast,Lunch,Dinner"};

	index = find_root_gini(alldata, 30);
	cout << "Best root would be " << gininame[index] << " as it has least gini of " << gini[index];
}
