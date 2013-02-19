#include "adjacency_list.h"

//Prototypes-----------------------------------------
//Adds the passed in member node to the passed in node
//function of convenience and prettiness
void add_member_array(AdjNode *node, Member *member);
void remove_member_array(AdjNode *node1, AdjNode *node2);

//Functions-------------------------------------------
//allocates memory for a new Graph struct, initializes it, and returns it
//Returns a FULLY initialized Graph struct
Graph* create_adj_list() {

	Graph *graph = malloc(sizeof(Graph));
	adj_list_init(graph);
	return graph;
}

//Initialize a Graph represented by an Adjacency list. 
//Create sentinal nodes.
void adj_list_init(Graph *graph) {

	//init sentinal nodes
	graph->head.prev = NULL;
	graph->head.next = &(graph->tail);
	graph->tail.prev = &(graph->head);
	graph->tail.next = NULL;

	graph->head.members = NULL;
	graph->tail.members = NULL;
}

//Takes in a AdjNode struct and initializes its pointers to null
void adj_node_init(AdjNode *node) {

	node->prev = NULL;
	node->next = NULL;
	node->size_members = 10;
	node->num_members = 0;
	node->members = malloc(node->size_members * sizeof(Member*));
}

//Add a node to the end of the adjacency list graph
void add_adj_node(Graph *graph, AdjNode *node) {

	node->next = &(graph->tail);	
	node->prev = graph->tail.prev;

	node->prev->next = node;
	graph->tail.prev = node;
}

//Delete a passed in node from the adjacency list graph (INCLUDING MEMORY FREEING)
//return the AdjNode if its present
//return NULL if it isn't present
AdjNode* delete_adj_node(Graph *graph, AdjNode *node) {

	//Check that node is not head or tail of graph
	if (node != &(graph->head) && node != &(graph->tail)) {
		
		AdjNode *it = graph->head.next;
		//While not on tail
		while (it->next != NULL) {

			//node found! deleteing
			if (node == it) {

				node->prev->next = node->next;
				node->next->prev = node->prev;
				return node;
			}
		}
	}
	else {

		printf("node cannot be the head or tail of the adjacency list!!!");
		return NULL;
	}
	return NULL;
}

//Takes in two nodes (presumably nodes in graph)
//adds them to the ends of each others members list
//Return 1 if unsuccessful (one or more nodes don't exist), 
	//or the nodes are already connected
//Return 0 on success
//O(n) n = number of nodes in node1's member array 
int connect_adj_nodes(Graph *graph, AdjNode *node1, AdjNode *node2) {

	//if the nodes exist in the graph, and they are not ALREADY connected
	if (are_connected(node1, node2) == 1) {
		
		//Create Member nodes
		Member *member1 = malloc(sizeof(Member));
		Member *member2 = malloc(sizeof(Member));

		//Initialize Member nodes to point to nodes
		member1->member = node2;
		member2->member = node1;

		//add member nodes to the lists
		add_member_array(node1, member1);
		add_member_array(node2, member2);

		return 0;
	}

	return 1;
}

//Adds the passed in member node to the passed in node
//function of convenience and prettiness
void add_member_array(AdjNode *node, Member *member) {

	//if array needs reallocating
	if (node->num_members == node->size_members) {

		Member **temp_members;

		//increase members array size by 2
		node->size_members *= 2;
		temp_members = calloc(node->size_members, sizeof(Member*));

		//Copy over members to temp members
		int i = 0;
		for (; i < node->num_members; i++) {

			temp_members[i] = node->members[i];
		}

		//kill old members
		free(node->members);
		node->members = temp_members;
		temp_members = NULL;
	}

	//add new member, increase num_members count
	node->members[node->num_members] = member;
	node->num_members++;
}

//Takes in two AdjNodes and removes the corresponding member nodes from each
	//AdjNode's member list
//Return 0 if successful
//Return 1 if the two aren't connected
int disconnect_adj_nodes(AdjNode *node1, AdjNode *node2) {

	//check if the nodes are indeed connected
	if (are_connected(node1, node2) == 0) {

		//remove each from the array
		remove_member_array(node1, node2);
		remove_member_array(node2, node1);

		return 0;
	}

	return 1;
}

//Removes the member node containing node2 from node1's member list
void remove_member_array(AdjNode *node1, AdjNode *node2) {

	//reference to free memory
	Member* member;

	//decrement member count
	node1->num_members -= 1;

	//Loop over node1's members
	int i = node1->num_members;
	for (; i < node1->num_members; i--) {

		//if member node for node2 found
		if (node1->members[i]->member == node2) {

			member = node1->members[i];
			//if member node is NOT found at the end of the list (IS NOT on first iteration)
			if (i != node1->num_members) {
				
				node1->members[i] = node1->members[i + 1];
			}
			//member IS found at the END (IS on first iteration)
			else {

				node1->members[i] = NULL;
			}
			free(member);
			break;
		}
	}
}

//Takes in a graph and two nodes and checks to see if the two nodes are
	//connected in the passed in graph
//Return 0 if connected
//Return 1 if NOT connected
int are_connected(AdjNode *node1, AdjNode *node2) {

	//loop over all members in node1 looking for node2
	int i = 0;
	for (; i < node1->num_members; i++) {

		//if node2 was found in node1's member list!
		if (node2 == node1->members[i]->member) {

			return 0;
		}
	}

	return 1;
}