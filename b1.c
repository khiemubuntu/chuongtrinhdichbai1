#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


typedef struct {
  char word[20];
  int count;
  char line[30];

}element;

typedef struct Node{
  element key;
  struct Node*left,*right;
  
}NodeType;
typedef struct Node *TreeType;
void MakeNullTree(TreeType*T){
  (*T)=NULL;
}
int EmptyTree(TreeType T){
  return T==NULL;
}



NodeType*create_node(element newdata){
  NodeType*N;
  N=(NodeType*)malloc(sizeof(NodeType));
  if(N!=NULL)
    {
      N->left=NULL;
      N->right=NULL;
      N->key=newdata;
    }
  return N;
}

void InsertNode(char *word,int line,TreeType*Root){
  char buff[10];
    sprintf(buff,"%d",line);
  if(*Root==NULL){
    *Root=(NodeType*)malloc(sizeof(NodeType));
    ((*Root)->key).count=1;
    strcpy(((*Root)->key).word,word);
    strcat(((*Root)->key).line,buff);
    (*Root)->left=NULL;
    (*Root)->right=NULL;
  }
  else if(strcmp(((*Root)->key).word,word)>0) InsertNode(word,line,&(*Root)->left);
  else if(strcmp(((*Root)->key).word,word)<0) InsertNode(word,line,&(*Root)->right);
  else if(strcmp(((*Root)->key).word,word)==0) {((*Root)->key).count+=1; strcat(((*Root)->key).line,' ');; strcat(((*Root)->key).line,buff);} 
}
int docfileStopW(char *tumoi){
  FILE *f;
  char tu[30];          
  char stopw[30][20];  //manghaichieu de luu cac tu doc tu file stopw;
  int i=0;int n;
  f=fopen("stopw.txt","r");
  while(!feof(f)){
    fscanf(f,"%s\n",tu); //fscanf
  strcpy(stopw[i++],tu);}
  n=i;
  for(int i=0;i<n;i++){
    if(strcmp(stopw[i],tumoi)==0) return 0;
  }
  return 1;
  fclose(f);
}
void docfileVB(TreeType *T){
  FILE*f;
  element x;
  f=fopen("vanban.txt","r");
  char word[20];
  char c;
  int i=0;
  int line=1;
  while(!feof(f)){
    c=fgetc(f);
    if(isalpha(c)){
      word[i++]=c;
    }
    else{
      if(i!=0){
	word[i]='\0';
	if(word[0]>='a'&&word[0]<='z'&&docfileStopW(word)==1)InsertNode(word,line,&(*T));
	
	i=0;
      }
     
      else if(c=='\n') line++;
    }
  }
  fclose(f);
}
void inorderprinttotext(TreeType tree){
  if(tree!=NULL)
    {
      inorderprinttotext(tree->left);
      printf("%s %d |%s\n",(tree->key).word,(tree->key).count,(tree->key).line);
     
      inorderprinttotext(tree->right);
    }
}
void freetree(TreeType tree){
  if(tree!=NULL)
    {
      freetree(tree->left);
      freetree(tree->right);
      free((void*)tree);
    }
}
int main(){
  TreeType T;
  MakeNullTree(&T);
  docfileVB(&T);
  inorderprinttotext(T);
  freetree(T);
  return 0;
}

