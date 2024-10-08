#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <assert.h>


#include "ai.h"
#include "utils.h"
#include "priority_queue.h"
#define MIN_LIVES 0
#define INCREM 1
#define DECREM 1
#define NONE 0
#define INITIAL_MOVE_DEPTH 1
#define INITIAL_POSSIBLE_MOVES 4

struct heap h;

float get_reward( node_t* n );

/**
 * Function called by pacman.c
*/
void initialize_ai() {
	heap_init(&h);
}

/**
 * function to copy a src into a dst state
*/
void copy_state(state_t* dst, state_t* src) {
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

//GIVEN - creates initial state node
node_t* create_init_node( state_t* init_state ) {
	node_t * new_n = (node_t *) malloc(sizeof(node_t));
	assert(new_n);
	new_n->parent = NULL;	
	new_n->priority = 0;
	new_n->depth = 0;
	new_n->num_childs = 0;
	copy_state(&(new_n->state), init_state);
	new_n->acc_reward =  0;
	return new_n;
	
}

//GIVEN - Calculates heuristic score
float heuristic( node_t* n ) {
	float h = 0;

	//as these scores are heuristic, they are not magic numbers. Their value
	//is completely arbitrary

	//MODIFIED invincibility, so it not only prefers invincibility,
	//but also prefers to eat ghosts in a row, and get additional fruits
	if(n->parent) {
		if((((n->parent)->state).GhostsInARow) != ((n->state).GhostsInARow)) {
			h+=10;
		}
	}

	//if lost a life, MODIFIED so cost to losing a life is much higher
	if(n->parent) {
		if(((n->parent)->state).Lives > (n->state).Lives) {
			h-=100;
		}
	}

	//if the game is over (lost all lives) MODIFIED to make it a lot more averse to losing all lives
	if((n->state).Lives < MIN_LIVES) {
		h-=1000;
	}

	return h;
}

//GIVEN - calcualtes reward and accumulated reward for a give node
float get_reward ( node_t* n ) {
	float reward = 0;
	
	//FILL IN MISSING CODE
	float parent_score;

	//check if reward is required for the initial node
	if((n->parent)) {
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
bool applyAction(node_t* n, node_t** new_node, move_t action ) {

	bool changed_dir = false;

    //LN 12, applyAction
    (*new_node) = (node_t *) malloc(sizeof(node_t));
    assert(*new_node);

    //applyAction 1
    (*new_node)->parent = n;

    //applyAction 2
    copy_state(&((*new_node)->state), &(n->state));
    changed_dir = execute_move_t( &((*new_node)->state), action );

    //if movement is not valid, rest of the actions not executed
    if(changed_dir) {
    	//applyAction 3
    	(*new_node)->priority = (n->priority) - DECREM;
		(*new_node)->depth = (n->depth) + INCREM;

		//applyAction 4, 5
		//accumulated reward is reward of the own node + parent nodes accumulated reward
		(*new_node)->acc_reward =  get_reward(*new_node) + n->acc_reward;

		//applyAction 6
		(*new_node)->num_childs = NONE;

		//if first action from initial state, record direction of movement,
		//if children node of depth 1 action, then just record what the depth 1
		//parents/granparents move is
		if((*new_node)->depth == INITIAL_MOVE_DEPTH) {
			(*new_node)->move = action;
		} else {
			(*new_node)->move = ((*new_node)->parent)->move;
		}
		n->num_childs += INCREM;

    }

	return changed_dir;

}

/**
 * Checks if a life has been lost in a certain state
 */
bool life_lost(node_t* node) {

	//if lives in current state are less than lives in parent state
	if(node->parent) {
		if(((node->state).Lives)<((node->parent)->state).Lives) {
			return true;
		}
	}
	return false;
}

/**
 * MAX
 * Propogates score back to the first action at depth 1
 */
void propagate_max_score_to_first_action(float* best_action_score, node_t* node) {
	float leaf_reward = node->acc_reward;

	if(leaf_reward > best_action_score[node->move]) {
		best_action_score[node->move] = leaf_reward;
	}

}

/**
 * AVG
 * Propogates score back to the first action at depth 1
 */
void propagate_avg_score_to_first_action(float* best_action_score, node_t* node, int* number_of_descendants) {
	if(best_action_score[node->move]== INT_MIN) {
		best_action_score[node->move] = node->acc_reward;
	} else {
		best_action_score[node->move] += node->acc_reward;
	}
	
	//tracking denominator for averaging
	number_of_descendants[node->move] += INCREM;
}

/**
 * Chooses the best action based on MAX propagation
 */
int choose_best_action(float* best_action_score, int propagation, int* number_of_descendants) {
	int i;
	if(propagation == avg) {
		for(i =left; i<=down; i++) {
			if(number_of_descendants[i] > NONE) {
				best_action_score[i] /= number_of_descendants[i];
			}
		}
	}

	int best_action = left;
	float temp_score = best_action_score[left];

	//tracking indexes of highest scoring actions
	int top_scores[INITIAL_POSSIBLE_MOVES] = {0,0,0,0};
	for (i=right; i<=down; i++) {
		if(best_action_score[i]>temp_score) {
			best_action = i;
			temp_score = best_action_score[i];
		}
	}
	//here we have a definite best action, record all indexes with the
	//same best_action_score (ties)
	int counter = 1;
	top_scores[left] = best_action;

	for (i = left; i<=down; i++) {
		if(i!=best_action) {
			if(best_action_score[i]==temp_score) {
				top_scores[counter++] = i;
			}
		}
	}

	//randomly break ties based on indexes of highest scores
	if(counter==1) {
		return best_action;
	} else {
		return top_scores[rand()%counter];
	}
	
	
}

/**
 * Find best action by building all possible paths up to budget
 * and back propagate using either max or avg
 */

extern int total_generated_nodes ; //
extern int total_expanded_nodes ; //
extern int absolute_max_depth ; //

move_t get_next_move( state_t init_state, int budget, propagation_t propagation, char* stats ) {

	//starting to record time for iterations
	clock_t start= clock(); 
	
	move_t best_action;
	unsigned i;

	// move_t best_action;
	float best_action_score[INITIAL_POSSIBLE_MOVES]; // tracking the current best scores for the first 4 actions
	for(i = left; i <=down; i++)
	    best_action_score[i] = INT_MIN;

	int number_of_descendants[INITIAL_POSSIBLE_MOVES]; //tracking number of descendants for each action
	for( i=left; i<=down; i++) {
		number_of_descendants[i] = NONE;
	}

	unsigned generated_nodes = NONE;
	unsigned expanded_nodes = NONE;
	unsigned max_depth = NONE;

	bool is_valid_move = false;
	
	//LN 2
	//array of explored nodes
	node_t** explored = (node_t**)malloc(sizeof(node_t*) * budget); 
	assert(explored);

	//LN 1
	//Add the initial node
	node_t* n = create_init_node( &init_state );
	generated_nodes++;

	//LN 3
	//Frontier - containing initial node only
	heap_push(&h,n);


	//FILL IN THE GRAPH ALGORITHM
	//LN 4, 5
	//while fronitier =/= empty
	node_t* temp;
	while(h.count>NONE) {

		//LN 6
		n = heap_delete(&h);

		//LN 7
		explored[expanded_nodes++] = n;
		total_expanded_nodes++;

		//LN 8, 9
		if(expanded_nodes<budget) {

			//LN 10, 11
			for (int nextMove=left; nextMove<=down; nextMove ++) {
				
				//LN 12
				is_valid_move = applyAction(n, &temp, nextMove);
				generated_nodes++;
				total_generated_nodes++;

				//if the move is valid, then add the next move to heap
				if (is_valid_move) {

					//LN 13
					if(propagation == max) {
						propagate_max_score_to_first_action(best_action_score, temp);
					} else if (propagation == avg) {
						propagate_avg_score_to_first_action(best_action_score, temp, number_of_descendants);
					}

					//LN 14, 15, 17, 18
					//if life is not lost, keep node
					if(!life_lost(temp)) {
						heap_push(&h, temp);

						//keep track of max_depth
						if((temp)->depth > max_depth) {
							max_depth = temp->depth;
							if(max_depth>absolute_max_depth) {
								absolute_max_depth = max_depth;
							}
						}

					//LN 15, 16
					//if life lost, delete node
					} else{
						free(temp);
					}
				//if move is invalid, discard
				} else {
					free(temp);
				}
				
			}
		//if budged all used up, exit
		} else{
			break;
		}

	}
	

	sprintf(stats, "Max Depth: %d Expanded nodes: %d  Generated nodes: %d\n",max_depth,expanded_nodes,generated_nodes);

	//free heap
	emptyPQ(&h);

	//LN 19, 20
	// free explored array
	for(int i=0; i<expanded_nodes; i++) {
		free(explored[i]);
	}
	free(explored);

	//LN 21
	best_action = choose_best_action(best_action_score, propagation, number_of_descendants);

	if(best_action == left)
		sprintf(stats, "%sSelected action: Left\n",stats);
	if(best_action == right)
		sprintf(stats, "%sSelected action: Right\n",stats);
	if(best_action == up)
		sprintf(stats, "%sSelected action: Up\n",stats);
	if(best_action == down)
		sprintf(stats, "%sSelected action: Down\n",stats);

	sprintf(stats, "%sScore Left %f Right %f Up %f Down %f",stats,best_action_score[left],best_action_score[right],best_action_score[up],best_action_score[down]);


	//LN 22
	return best_action;
}


