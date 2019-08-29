/*
Header file for btrip_log.c includes trip dictionary structure and functions
Structure
Function declarations
*/

/*

*/
struct trip;


/*
Returns pointer to a (struct type object) trip based on the row of data provided (buffer)
*/
struct trip* create_trip_record(char *buffer);