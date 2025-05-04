#include <stdio.h>
#include "playerLinklist.h"
#include "teamlinklist.h"
#include "playerBST.h" 

int main() {
	//function testing at early stage
	 printf("Testing each function before integrating the database.\n");
	//Linkedlist model
	test_player_module();
	test_team_module();
	//BST model
	test_player_bst_module();
	test_team_bst_module();
	for (int i = 0; i < 40; i++) {
		printf("*");
	}
	printf("\n\n");

	//final project evaluation with external data resource
	printf("final testng after integrating database.\n");
	test_team_bst_module_from_external();//BST method
	test_team_module_from_external();//Linked List method
	
	return 0;
}