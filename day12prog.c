#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define DIM 11 //THIS WAS ADDED AFTER RUNNING THE PROGRAM 1 TIME, I HAVE NO BETTER WAY TO PASS THE MATRIX
#define EFL "file.txt"
typedef struct N{
	char s[6];
	struct N *next;
	}nodo_t; //LIST OF NAMES
typedef nodo_t* pnodo; //POINTER TO LIST

int ispresent(pnodo head, char* str){ //FUNCTION TO DETERMINE IF A STRING IS ALREADY PRESENT IN A LIST
 while(head != NULL)
	{if(strcmp(head->s, str) == 0)
		{return 1;
		}
	 else
		{head = head->next;
		}
	}
 return 0;
}

pnodo Listins_head(pnodo l ,char* str){ //NEW NODE IN LIST
 pnodo holder;
 holder = malloc(sizeof(nodo_t));
 if(holder)
        {strcpy(holder->s, str);
         holder->next = l;
         l = holder;
        }
 else
        {printf("Errore malloc\n");
        }
 return l;
}

pnodo Listelim_all(pnodo l){ //FREE LIST
 pnodo holder;
 while(l != NULL)
        {holder = l;
         l = l->next;
         free(holder);
        }
 return NULL;
}

void explore(int graph[][DIM], int backup[][DIM], int V, int col, int* pt){  	//STUPID FUNCTION
 printf("\n");									//GRAPH IS A MATRIX REPRESENTING EACH EDGE: 0 MEANS NO EDGE, 1 IS EDGE FROM SMALL TO BIG, 2 IS EDGE FROM BIG TO SMALL
 int j;										//THE COLUMN REPRESENTS THE STARTING CAVE, THE ROW REPRESENTS THE ARRIVING CAVE
 int k;										//BACKUP IS TO RESTORE THE EDGES AFTER AN EXPLORATION. V = DIM. COL IS THE CURRENT COLUMN. PT IS A POINTER TO A COUNTER IN MAIN
 for(j=0; j<V; j++)								//AN EXPLORATION WORKS LIKE THIS:
        {for(k=0; k<V; k++)
                {printf("%d ", graph[j][k]);
                }
         printf("\n");
        }
 /*int end = 1;
 for(k=0; k<V && end; k++)
	{if(graph[k][col] != 0)
		{end = 0;
		} 
	}*/
 if(col == V-1)									//IF COL IS THE LAST COLUMN; THEN WE HAVE REACHED THE END. THE FUNCTION GOES BACK TO THE PREVIOUS STATE
	{(*pt)++; printf("END\n"); printf("COUNT:%d\n", *pt);
	}
 else										//NOW WE START THE EXPLORATION PROCESS. WE GO DOWN THE COLUMN TO FIND THE CONNECTED CAVES.
	{for(j=0; j<V; j++)							//THERE ARE 3 CASES:
		{switch(graph[j][col])
			{case 0:
				break;						//CASE 0: NO EDGE. NOTHING HAPPENS
			 case 1:						//CASE 1: EDGE FROM SMALL TO BIG. TO AVOID GETTING STUCK IN A LOOP, THE CAVE IS DELETED.
				printf("MOVE: %d -> %d\n", col, j);		//THIS MEANS DELETING ALL THE EDGES CONNECTING THE CAVE TO OTHER CAVES. THIS IS ACHIEVED BY
				for(k=0; k<V; k++)				//ELIMINATING ITS ROW AND COLUMN.
					{graph[k][col] = 0;
					 graph[col][k] = 0;
					}
				explore(graph, backup, V, j, pt);
				for(k=0; k<V; k++)				//AFTER THE EXPLORATION, THE CAVE EDGES ARE RESTORED TO THEIR PREVIOUS STATE
                                        {graph[k][col] = backup[k][col];
                                         graph[col][k] = backup[col][k];
                                        }
				break;
			 case 2:						//CASE 2: EDGE FROM BIG TO SMALL.
				printf("MOVE: %d -> %d\n", col, j);		//NOTHING IS DELETED. WE EXPLORE THE NEW CAVE.
				explore(graph, backup, V, j, pt);		//AFTER EXPLORATION WE RESTORE THE GRAPH
				graph[j][col] = backup[j][col];
                                graph[col][j] = backup[col][j];
				break;
			 default:
				;
			}

		}
	}
 printf("DEAD STOP\n");
 }



int main(){
 pnodo head;
 pnodo cur;
 FILE* in;
 in = fopen(EFL, "r");
 char from[6];
 char to[6];
 int V = 0;
 int i, j, k, l;
 int count = 0;
 head = NULL;
 if(in)
	{while(!feof(in))
		{fscanf(in, " %[^-]- %[^\n] ", from, to);
		 if(! ispresent(head, from) )
			{head = Listins_head(head, from);
			 V++;
			}
		 if(! ispresent(head, to) )
                        {head = Listins_head(head, to);
			 V++;
                        }
		}
	} //FINDING THE NAMES OF THE GRAPH POINTS AND THEIR NUMBER
 else
	{printf("che cazzo");
	 return 0;
	}
 printf("V: %d\n", V);
 int graph[V][V]; //REPRESENTATIVE MATRIX OF GRAPH
 int backup[V][V]; //BACKUP GRAPH
 char nodes[V][6]; //ARRAY WITH THE NAMES OF THE POINTS
 strcpy(nodes[0], "start");
 strcpy(nodes[V-1], "end");
 cur = head;
 i = 1;
 while(cur != NULL)
	{if( strcmp(cur->s, "start") == 0 || strcmp(cur->s, "end") == 0)
		{cur = cur->next;
		}
	 else
		{strcpy(nodes[i], cur->s);
		 i++;
		 cur = cur->next;
		}
	}
 for(i=0; i<V; i++)
	{printf("%d: %s ",i,  nodes[i]);
	} //NAMES ASSIGNED TO ARRAY
 rewind(in);
 for(i=0; i<V; i++)
	{for(j=0; j<V; j++)
		{graph[i][j] = 0;
		}
	} //EMPTY GRAPH

 while(!feof(in))
	{fscanf(in, " %[^-]- %[^\n] ", from, to);
	 for(i=0; strcmp(from, nodes[i]) ; i++);
	 for(j=0; strcmp(to, nodes[j]) ; j++);
	 printf("\n%d %d %s %s", i, j, from, to);
	 if(isupper(from[0]))
		{graph[j][i] = 2;
		 graph[i][j] =1;
		}
	 else if(isupper(to[0]))
		{graph[j][i] = 1;
		 graph[i][j] = 2;
		}
	 else
		{graph[i][j] = 1;
		 graph[j][i] = 1;
		}
	} //REPRESENTATIVE MATRIX HAS BEEN BUILT.
 printf("\n\n\n");
  for(i=0; i<V; i++)
        {for(j=0; j<V; j++)
                {printf("%d ", graph[i][j]);
		}
	 printf("\n");
	}
 for(i=0; i<V; i++)
        {for(j=0; j<V; j++)
                {backup[i][j] = graph[i][j];
		}
	} //BACKUP MATRIX HAS BEEN COPIED FROM ORIGINAL GRAPH

 //EXPLORATION OF COLUMN 0
 explore(graph, backup, V, 0, &count);
 printf("\n\n\n");
  for(i=0; i<V; i++)
        {for(j=0; j<V; j++)
                {printf("%d ", graph[i][j]);
                }
         printf("\n");
	}
 printf("COUNT:%d\n", count);
 head = Listelim_all(head);
 fclose(in);
 return 0; //THIS DOESNT WORK.
 }
