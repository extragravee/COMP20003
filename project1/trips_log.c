/*
Defines the structure and functions for the trip log records provided in
the input file.
Function declerations abstracted to header file "trips_log.h"
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct trip{
	int vendor_id; //Code to indicate the vendor which produced the record
	int passenger_count; //Number of passengers
	float trip_distance; //Length of the trip in miles
	float rate_code_ID; //Code to represent the fare rate for the trip
	bool store_and_fwd_flag; //Indicates whether trip records were stored locally
	int pu_location_id; //TLC Taxi Zone where passengers were picked up
	int do_location_id; //TLC Taxi Zone where passengers were dropped off
	int payment_type; //Code to indicate payment type (e.g., cash)
	float fare_amount; //Fare for the trip in USD
	float extra; //Extra charges in USD
	float mta_tax; //MTA tax in USD
	float tip_amount; //Tip in USD
	float tolls_amount; //Tolls in USD
	float improvement_surcharge; //Improvement surcharge in USD
	float total_amount; //Total cost of the trip in USD
	char *pu_datetime; //Date/time passengers were picked up
	char *do_datetime; //Date/time passengers were dropped off
	int trip_duration; //Duration of the trip in minutes

};

