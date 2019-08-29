/*
Header file for btrip_log.c includes trip dictionary structure and functions
Structure
Function declarations
*/

/*
delcares the structure of the trip, all columns as in the csv
*/
struct trip;

/*
returns pointer to a (struct type object) trip based on the row of data provided (buffer)
Uses the once defined field (maxsize 128 char) to temporarily store the cell being copied
*/
struct trip* create_trip_record(char *buffer, char* field);

/*
obtains a pointer, to the pointer that points to the memory being used to store the cell
*/
char** get_struct_member(struct trip* new_trip, int i);

/*
prints all members of the struct
*/
void print_trip(struct trip* new_trip);

/*
frees all the memory allocated for each member in the struct
*/
void free_members_of_struct(struct trip* trip);

/*
prints all members of the struct for inspection and testing
*/
void print_trip(struct trip* new_trip);