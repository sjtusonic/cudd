//#include "$(WHERE)/include/util/util.h"
#include "/home/zz/Downloads/cudd-3.0.0/util/util.h"
#include "cudd.h"
//#define DLOG(x) cout<<"<<#x<<"="<<x<<" @"<<__LINE__<<endl;
#define DLOG(x) printf("%s=%d\n",#x,x); 
#define DEBUG_MARK printf("DEBUG FUNC:%s@LINE:%d\n",__FUNCTION__,__LINE__); 

// main()
// {
// }


void tut1 ()
{
	printf("TEST ZJC: main:\n");
	DdManager *gbm;//  Global BDD manager. 
	char filename[30];
	//DLOG(filename);
	//DLOG(CUDD_UNIQUE_SLOTS);
	//DLOG(CUDD_CACHE_SLOTS);
	gbm = Cudd_Init(0,0,CUDD_UNIQUE_SLOTS,CUDD_CACHE_SLOTS,0);//  Initialize a new BDD manager. 
	DdNode *bdd = Cudd_bddNewVar(gbm);// Create a new BDD variable
	Cudd_Ref(bdd); // Increases the reference count of a node
	print_dd(gbm,bdd,4,14); // zjc debug

	DEBUG_MARK;
	// print static file
	FILE* fh=fopen("./output.rpt","w");
	DEBUG_MARK;
	Cudd_PrintInfo(gbm,fh);
	fclose(fh);
	//
	//  dump dot
	//   extern int Cudd_DumpDot(DdManager *dd, int n, DdNode **f, char const * const *inames, char const * const *onames, FILE *fp);
	//Cudd_DumpDot(gbm);
	write_dd(gbm, bdd, "output.dot");  /*Write the resulting cascade dd to a file*/
	Cudd_Quit(gbm);
}

/*
 * * FILENAME: transfer.c
 * * Overview: BDD tutorial
 * * AUTHOR: David Kebo Houngninou
 * */

#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include "cudd.h"

/*
 * Print a dd summary
 * pr = 0 : prints nothing
 * pr = 1 : prints counts of nodes and minterms
 * pr = 2 : prints counts + disjoint sum of product
 * pr = 3 : prints counts + list of nodes
 * pr > 3 : prints counts + disjoint sum of product + list of nodes
 * @param the dd node
 */
void print_dd (DdManager *gbm, DdNode *dd, int n, int pr ) // dump rpt txt file
{
	printf("[FUNC:%s,LINE:%d]\n",__FUNCTION__,__LINE__);
	printf("gbm=%d\n",gbm);
	printf("dd=%d\n",dd);
	DLOG(n);
	DLOG(pr);
	printf("DdManager nodes: %ld | ", Cudd_ReadNodeCount(gbm)); /*Reports the number of live nodes in BDDs and ADDs*/
	printf("DdManager vars: %d | ", Cudd_ReadSize(gbm) ); /*Returns the number of BDD variables in existence*/
	printf("DdManager reorderings: %d | ", Cudd_ReadReorderings(gbm) ); /*Returns the number of times reordering has occurred*/
	printf("DdManager memory: %ld \n", Cudd_ReadMemoryInUse(gbm) ); /*Returns the memory in use by the manager measured in bytes*/
	DEBUG_MARK;
#if 1
	Cudd_PrintDebug(gbm, dd, n, pr);  // Prints to the standard output a DD and its statistics: number of nodes, number of leaves, number of minterms.
#endif
	DEBUG_MARK;
	printf("[FUNC:%s,LINE:%d]\n",__FUNCTION__,__LINE__);
}


/**
 *  * Writes a dot file representing the argument DDs
 *   * @param the node object
 *    */
void write_dd (DdManager *gbm, DdNode *dd, char* filename) // to dot file
{
	FILE *outfile; // output file pointer for .dot file
	outfile = fopen(filename,"w");
	DdNode **ddnodearray = (DdNode**)malloc(sizeof(DdNode*)); // initialize the function array
	ddnodearray[0] = dd;
	Cudd_DumpDot(gbm, 1, ddnodearray, NULL, NULL, outfile); // dump the function to .dot file
	free(ddnodearray);
	fclose (outfile); // close the file */
}

// This program creates a single BDD variable
void tut ()
{
	DEBUG_MARK;
	DdManager *gbm; /* Global BDD manager. */
	char filename[30];
	DEBUG_MARK;
	gbm = Cudd_Init(0,0,CUDD_UNIQUE_SLOTS,CUDD_CACHE_SLOTS,0); /* Initialize a new BDD manager. */
	DEBUG_MARK;
	DdNode *bdd = Cudd_bddNewVar(gbm); /*Create a new BDD variable*/
	DEBUG_MARK;
	Cudd_Ref(bdd); /*Increases the reference count of a node*/
	DEBUG_MARK;
	bdd = Cudd_BddToAdd(gbm, bdd); /*Convert BDD to ADD for display purpose*/
	DEBUG_MARK;
#if 1
	print_dd (gbm, bdd, 2,4); /*Print the dd to standard output*/
#endif
	DEBUG_MARK;
	sprintf(filename, "./bdd/graph.dot"); /*Write .dot filename to a string*/
	DEBUG_MARK;
	write_dd(gbm, bdd, filename);  /*Write the resulting cascade dd to a file*/
	DEBUG_MARK;
	Cudd_Quit(gbm);
}

void tut2_xor()
{
	DEBUG_MARK;
	char filename[30];
	DdManager *gbm; /* Global BDD manager. */
	gbm = Cudd_Init(0,0,CUDD_UNIQUE_SLOTS,CUDD_CACHE_SLOTS,0); /* Initialize a new BDD manager. */
	DdNode *bdd, *x1, *x2;
	x1 = Cudd_bddNewVar(gbm); /*Create a new BDD variable x1*/
	x2 = Cudd_bddNewVar(gbm); /*Create a new BDD variable x2*/
	bdd = Cudd_bddXor(gbm, x1, x2); /*Perform XOR Boolean operation*/
	Cudd_Ref(bdd);          /*Update the reference count for the node just created.*/
	bdd = Cudd_BddToAdd(gbm, bdd); /*Convert BDD to ADD for display purpose*/
	print_dd (gbm, bdd, 2,4);   /*Print the dd to standard output*/
	sprintf(filename, "./bdd/graph_xor.dot"); /*Write .dot filename to a string*/
	write_dd(gbm, bdd, filename);  /*Write the resulting cascade dd to a file*/
	Cudd_Quit(gbm);
	DEBUG_MARK;
}
void tut2_and()
{
	DEBUG_MARK;
	char filename[30];
	DdManager *gbm; /* Global BDD manager. */
	gbm = Cudd_Init(0,0,CUDD_UNIQUE_SLOTS,CUDD_CACHE_SLOTS,0); /* Initialize a new BDD manager. */
	DdNode *bdd, *x1, *x2;
	x1 = Cudd_bddNewVar(gbm); /*Create a new BDD variable x1*/
	x2 = Cudd_bddNewVar(gbm); /*Create a new BDD variable x2*/
	bdd = Cudd_bddAnd(gbm, x1, x2); /*Perform AND Boolean operation*/
	Cudd_Ref(bdd);          /*Update the reference count for the node just created.*/
	bdd = Cudd_BddToAdd(gbm, bdd); /*Convert BDD to ADD for display purpose*/
	print_dd (gbm, bdd, 2,4);   /*Print the dd to standard output*/
	sprintf(filename, "./bdd/graph_and.dot"); /*Write .dot filename to a string*/
	write_dd(gbm, bdd, filename);  /*Write the resulting cascade dd to a file*/
	Cudd_Quit(gbm);
	DEBUG_MARK;
}
void tut2_nand4()
{
	char filename[30];
	DdManager *gbm; /* Global BDD manager. */
	gbm = Cudd_Init(0,0,CUDD_UNIQUE_SLOTS,CUDD_CACHE_SLOTS,0); /* Initialize a new BDD manager. */
	DdNode *bdd, *var, *tmp_neg, *tmp;
	int i;
	bdd = Cudd_ReadOne(gbm); /*Returns the logic one constant of the manager*/
	Cudd_Ref(bdd); /*Increases the reference count of a node*/

	for (i = 3; i >= 0; i--) {
		var = Cudd_bddIthVar(gbm,i); /*Create a new BDD variable*/
		tmp_neg = Cudd_Not(var); /*Perform NOT Boolean operation*/
		tmp = Cudd_bddAnd(gbm, tmp_neg, bdd); /*Perform AND Boolean operation*/
		Cudd_Ref(tmp);
		Cudd_RecursiveDeref(gbm,bdd);
		bdd = tmp;
	}

	bdd = Cudd_BddToAdd(gbm, bdd); /*Convert BDD to ADD for display purpose*/
	print_dd (gbm, bdd, 2,4); /*Print the dd to standard output*/
	sprintf(filename, "./bdd/graph_nand4.dot"); /*Write .dot filename to a string*/
	write_dd(gbm, bdd, filename);  /*Write the resulting cascade dd to a file*/
	Cudd_Quit(gbm);
}
void tut_ss(){
	DEBUG_MARK;
	char filename[30];
	DdManager *gbm; /* Global BDD manager. */
	gbm = Cudd_Init(0,0,CUDD_UNIQUE_SLOTS,CUDD_CACHE_SLOTS,0); /* Initialize a new BDD manager. */
	DdNode *bdd , *bdd_and1, *bdd_and2,
	*x1, *x2, *x3,
	*bdd_const1;
	bdd_const1 = Cudd_ReadOne(gbm); /*Returns the logic one constant of the manager*/
	x1 = Cudd_bddNewVar(gbm); /*Create a new BDD variable x1*/
	x2 = Cudd_bddNewVar(gbm); /*Create a new BDD variable x2*/
	x3 = Cudd_bddNewVar(gbm); /*Create a new BDD variable x2*/
#if 0
	// Y=x1*x2+x1*x3
	bdd_and1=Cudd_bddAnd(gbm,x1,x2);
	bdd_and2=Cudd_bddAnd(gbm,x1,x3);
	bdd=Cudd_bddOr(gbm,bdd_and1,bdd_and2);
	// bdd=Cudd_bddOr(gbm,bdd_and1,bdd_const1);
#endif

#if 1
	// Y=x1*x2+`x1*x2
	bdd_and1=Cudd_bddAnd(gbm,x1,x2);
	bdd_and2=Cudd_bddAnd(gbm,Cudd_Not(x1),x2);
	bdd=Cudd_bddOr(gbm,bdd_and1,bdd_and2);
#endif

	// bdd = Cudd_bddXor(gbm, x1, x2); /*Perform XOR Boolean operation*/
	Cudd_Ref(bdd);          /*Update the reference count for the node just created.*/
	bdd = Cudd_BddToAdd(gbm, bdd); /*Convert BDD to ADD for display purpose*/

	print_dd (gbm, bdd, 2,4);   /*Print the dd to standard output*/
	sprintf(filename, "./bdd/graph_ss.dot"); /*Write .dot filename to a string*/
	write_dd(gbm, bdd, filename);  /*Write the resulting cascade dd to a file*/
	Cudd_Quit(gbm);
	DEBUG_MARK;
}

int main (int argc, char *argv[])
{
	// tut2_xor();
	// tut2_nand4();	
	tut_ss();
	return 0;
}
