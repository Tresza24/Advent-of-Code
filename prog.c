#include <stdio.h>
#include <string.h>

int rc(int i, int j, int matrix[][102], char marked[][102]){
 int count;
 count = 0;
 if( marked[i][j] == 'X' || marked[i][j] == 'O' )
	{return 0;
	}
 else if(marked[i][j] == '-')
	{ count++;
	 marked[i][j] = 'O';
	 count = count + rc(i-1, j, matrix, marked);
	 count = count + rc(i+1, j, matrix, marked);
	 count = count + rc(i, j-1, matrix, marked);
	 count = count + rc(i, j+1, matrix, marked);
	 return count;
	}
 }

int main(){
 FILE* in;
 int matrix[102][102];
 int i, j;
 char marked[102][102];
 int q;
 int sum;
 int max1, max2, max3;
 int temp;
 max1 = 0;
 max2 = 0;
 max3 = 0;
 in = fopen("file.txt", "r");
 if(in)
	{while(!feof(in))
		{for(i=1; i<101; i++)
			{for(j=1; j<101; j++)
				{fscanf(in, "%1d ", &matrix[i][j]);
				}
			}
		}
	 for(i=0; i<102; i++)
		{matrix[0][i] = 9;
		 matrix[101][i] = 9;
		 matrix[i][0] = 9;
		 matrix[i][101] = 9;
		}
	for(i=0; i<102; i++)
                {for(j=0; j<102; j++)
                        {if(matrix[i][j] == 9)
				{marked[i][j] = 'X';
				}
			 else
				{marked[i][j] = '-';
				}
			}
		}



	q=0;
	sum = 0;
	for(i=0; i<102; i++)
                {for(j=0; j<102; j++)
                        {if	( (matrix[i][j] < matrix[i][j-1] ) && (matrix[i][j] < matrix[i][j+1]) &&
				  (matrix[i][j] < matrix[i-1][j] ) && (matrix[i][j] < matrix[i+1][j])  )
					{q++;
					 sum = sum + 1 + matrix[i][j];
					 temp = rc(i, j, matrix, marked);
					 if(temp > max1)
				                {max3 = max2;
				                 max2 = max1;
				                 max1 = temp;
				                }
				         else if(temp > max2)
				                {max3 = max2;
				                 max2 = temp;
				                }
				         else if(temp > max3)
				                {max3 = temp;
				                }
			  		}
			}
		}

	for(i=0; i<102; i++)
		{for(j=0; j<102; j++)
	        	{printf("%c", marked[i][j]);
			}
		 printf("\n");
		}
	}
 printf("NUMBER OF BASINS:%d\n", q);
 printf("TOTAL RISK LEVEL:%d\n", sum);
 printf("MAX 1:%d MAX 2:%d MAX 3:%d\n", max1, max2, max3);
 printf("FINAL RESULT:%d\n", max1*max2*max3);
 fclose(in);
 return 0;
 }
