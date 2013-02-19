#ifndef ADJACENCY_LIST_H_
#define ADJACENCY_LIST_H_

#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

//Preprocessor macro which converts a AdjNode to the structure the AdjNode is IN (Duct tape style!)
#define ADJ_LIST_ENTRY(NODE, STRUCT, MEMBER) 				\
	((STRUCT *)((uint8_t*)(NODE) - offsetof(STRUCT, MEMBER)))

//Forward Declarations------------------------------------------
struct adjacency_list_node;

//Struct definitions------------------------------------------
//structure of a node in a member array of an adjacency_list
struct member_node {

	struct adjacency_list_node *member;
};

//structure of a node of an adjacency list
struct adjacency_list_node {

	//previous node in the adjacency list
	struct adjacency_list_node *prev;
	//Next node in the adjacency list
	struct adjacency_list_node *next;
	//number of members in the members array
	int num_members;
	//current size of the members array
	int size_members;
	//array of member_node ptrs
	struct member_node **members;
};

//structure of a linked list for an adjacency list
struct adjacency_list {

	//head of the adjacency list
	struct adjacency_list_node head;
	//tail of the adjacency list
	struct adjacency_list_node tail;
};

//TypeDefs------------------------------
typedef struct member_node Member;
typedef struct adjacency_list_node AdjNode;
typedef struct adjacency_list Graph;

//Prototypes---------------------------------------
Graph* create_adj_list();
void adj_list_init(Graph *graph);
void adj_node_init(AdjNode *node);
void destroy_adj_list();

void add_adj_node(Graph *graph, AdjNode *node);
AdjNode* delete_adj_node(Graph *graph, AdjNode *node);

int connect_adj_nodes(Graph *graph, AdjNode *node1, AdjNode *node2);
int disconnect_adj_nodes(AdjNode *node1, AdjNode *node2);

int are_connected(AdjNode *node1, AdjNode *node2);

#endif