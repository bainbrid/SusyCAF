#include <cassert>
#include <string>
#include "TTree.h"

#define LEAF(leaf)							\
  leaf = 0;								\
  assert(TTREE_FOREACH_ENTRY_tree->FindBranch( #leaf ) != 0 );		\
  TTREE_FOREACH_ENTRY_activateBranch(#leaf,TTREE_FOREACH_ENTRY_tree);	\
  TTREE_FOREACH_ENTRY_tree->SetBranchAddress( #leaf , &(leaf));		\
  
#define RENAMED_LEAF(var, leafname)					\
  var = 0;								\
  { /*scope to evaluate leafname no more than once*/			\
    const char* name = leafname ;					\
    assert(TTREE_FOREACH_ENTRY_tree->FindBranch( name ) != 0);		\
    TTREE_FOREACH_ENTRY_activateBranch(name,TTREE_FOREACH_ENTRY_tree);	\
    TTREE_FOREACH_ENTRY_tree->SetBranchAddress( name , &(var));		\
  }									\
  
#define TTREE_FOREACH_ENTRY(tree, leaves)				\
  TTree* TTREE_FOREACH_ENTRY_tree = tree;				\
  TTREE_FOREACH_ENTRY_tree->SetBranchStatus("*",0);			\
  leaves								\
  for ( Long64_t							\
	  TTREE_FOREACH_ENTRY_index=0,					\
	  TTREE_FOREACH_ENTRY_local=0,					\
	  TTREE_FOREACH_ENTRY_total=TTREE_FOREACH_ENTRY_tree->GetEntries(); \
	TTREE_FOREACH_ENTRY_index < TTREE_FOREACH_ENTRY_total		\
	  && (0 < TTREE_FOREACH_ENTRY_local				\
	      || -1 < TTREE_FOREACH_ENTRY_tree->LoadTree(TTREE_FOREACH_ENTRY_index) \
	      && -1 < (TTREE_FOREACH_ENTRY_local = TTREE_FOREACH_ENTRY_tree->GetTree()->GetEntries()) ) \
	  && -1 < TTREE_FOREACH_ENTRY_tree->GetEntry(TTREE_FOREACH_ENTRY_index); \
	TTREE_FOREACH_ENTRY_index++, TTREE_FOREACH_ENTRY_local-- )	\
    

void TTREE_FOREACH_ENTRY_activateBranch(const char* leaf, TTree* tree) {
  tree->SetBranchStatus( (leaf +std::string("*")).c_str() , 1); 
  TBranch* branch = tree->FindBranch( leaf );
  for(int i = 0; i < branch->GetListOfBranches()->GetEntries(); i++) {								
    TBranch* subBranch =(TBranch*)(branch->GetListOfBranches()->At(i)); 
    std::string sBname = subBranch->GetName();				
    if( subBranch->GetListOfBranches()->GetEntries() ) sBname+="*";	
    tree->SetBranchStatus( sBname.c_str(), 1);	
  }									
}
