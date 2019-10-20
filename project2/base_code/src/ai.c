#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>


#include "ai.h"
#include "utils.h"
#include "priority_queue.h"


struct heap h;

float get_reward( node_t* n );

/**
 * Function called by pacman.c
*/
void initialize_ai(){
	heap_init(&h);
}

/**
 * function to copy a src into a dst state
*/
void copy_state(state_t* dst, state_t* src){
	//Location of Ghosts and Pacman
	memcpy( dst->Loc, src->Loc, 5*2*sizeof(int) );

    //Direction of Ghosts and Pacman
	memcpy( dst->Dir, src->Dir, 5*2*sizeof(int) );

    //Default location in case Pacman/Ghosts die
	memcpy( dst->StartingPoints, src->StartingPoints, 5*2*sizeof(int) );

    //Check for invincibility
    dst->Invincible = src->Invincible;
    
    //Number of pellets left in level
    dst->Food = src->Food;
    
    //Main level array
	memcpy( dst->Level, src->Level, 29*28*sizeof(int) );

    //What level number are we on?
    dst->LevelNumber = src->LevelNumber;
    
    //Keep track of how many points to give for eating ghosts
    dst->GhostsInARow = src->GhostsInARow;

    //How long left for invincibility
    dst->tleft = src->tleft;

    //Initial points
    dst->Points = src->Points;

    //Remiaining Lives
    dst->Lives = src->Lives;   

}

node_t* create_init_node( state_t* init_state ){
	node_t * new_n = (node_t *) malloc(sizeof(node_t));
	new_n->parent = NULL;	
	new_n->priority = 0;
	new_n->depth = 0;
	new_n->num_childs = 0;
	copy_state(&(new_n->state), init_state);
	new_n->acc_reward =  get_reward( new_n );
	return new_n;
	
}


float heuristic( node_t* n ){
	float h = 0;
	
	//FILL IN MISSING CODE
	//if eaten a fruit
	if((n->state).Invincible == 1){
		if((n->state).tleft == (11-(n->state).LevelNumber)){
			h+=10;
		}
	}

	//if lost a life -10
	if(n->parent){
		if(((n->parent)->state).Lives > (n->state).Lives){
			h-=10;
		}
	}
	

	//if the game is over (lost all lives)
	if((n->state).Lives == 0){
		h-=100;
	}

	return h;
}

float get_reward ( node_t* n ){
	float reward = 0;
	
	//FILL IN MISSING CODE
	float parent_score;

	//check if reward is required for the initial node
	if((n->parent)){
		parent_score = ((n->parent)->state).Points;
	} else {
		parent_score = 0;
	}

	reward = heuristic(n) + (n->state).Points - parent_score;

	float discount = pow(0.99,n->depth);
   	
	return discount * reward;
}

/**
 * Apply an action to node n and return a new node resulting from executing the action
*/
bool applyAction(node_t* n, node_t** new_node, move_t action ){

	bool changed_dir = false;

    //LN 12, applyAction
    (*new_node) = (node_t *) malloc(sizeof(node_t));
    (*new_node)->parent = n;
    copy_state(&((*new_node)->state), &(n->state));

    changed_dir = execute_move_t( &((*new_node)->state), action );	

	(*new_node)->priority = (n->priority) - 1;
	(*new_node)->depth = (n->depth) + 1;

	(*new_node)->acc_reward =  get_reward(*new_node);

	// (*new_node)->num_childs = 0;
	// (*new_node)->move = action;
	// n->num_childs += 1;
    


	return changed_dir;

}


/**
 * Find best action by building all possible paths up to budget
 * and back propagate using either max or avg
 */

move_t get_next_move( state_t init_state, int budget, propagation_t propagation, char* stats ){
	move_t best_action = rand() % 4; // this is taking a random value for the ai's next move

	float best_action_score[4]; // tracking the current best scores for the first 4 actions
	for(unsigned i = 0; i < 4; i++)
	    best_action_score[i] = INT_MIN;

	unsigned generated_nodes = 0;
	unsigned expanded_nodes = 0;
	unsigned max_depth = 0;

	bool is_valid_move = false;
	
	//LN 2
	//array of explored nodes - does this needs to be a dynamic array <<<<<<<<<<<<<<<<<<<<<<< no?
	node_t* explored[budget]; 

	//LN 1
	//Add the initial node
	node_t* n = create_init_node( &init_state );
	
	//LN 3
	//Frontier - containing initial node only
	heap_push(&h,n);
	
	//FILL IN THE GRAPH ALGORITHM
	//LN 4, 5
	//while fronitier =/= empty
	while(h.count>0){

		//LN 6 - initial location y=22 (row) x = 13 (index)
		n = heap_delete(&h);

		//LN 7
		explored[expanded_nodes++] = n;

		//LN 8, 9
		if(expanded_nodes<budget){

			//LN 10, 11
			for (int nextMove=left; nextMove<=down; nextMove ++){
				node_t* temp;

				//calling LN 12
				is_valid_move = applyAction(n, &temp, nextMove);
				break;
			}
			

			// free(temp); //do i need to free what is being pointed to by the parent pointer in the node struct? <<<<<<<<<<<<
		}

	}
	
	sprintf(stats, "Max Depth: %d Expanded nodes: %d  Generated nodes: %d, X: %d, Y: %d\n Size of heap= %d\n",max_depth,expanded_nodes,generated_nodes, 
		(n->state).Loc[4][1], (n->state).Loc[4][0], h.size);
	//need to add sprintf(stats) and each item that is popped from the PQ plus their priorities


	// memory management
	// free explored array
	for(int i=0; i<expanded_nodes; i++){
			free(explored[i]);
	}
	//free heap
	if(h.size>0){
		emptyPQ(&h);
	}



	if(best_action == left)
		sprintf(stats, "%sSelected action: Left\n",stats);
	if(best_action == right)
		sprintf(stats, "%sSelected action: Right\n",stats);
	if(best_action == up)
		sprintf(stats, "%sSelected action: Up\n",stats);
	if(best_action == down)
		sprintf(stats, "%sSelected action: Down\n",stats);

	sprintf(stats, "%sScore Left %f Right %f Up %f Down %f",stats,best_action_score[left],best_action_score[right],best_action_score[up],best_action_score[down]);
	return best_action;
}

