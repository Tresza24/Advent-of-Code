#include <stdio.h>
#include <string.h>
#include <math.h>
typedef struct{
	char top;
	char mid;
	char bot;
	char ltop;
	char rtop;
	char lbot;
	char rbot;
	}seg_t;

int main(){
 FILE* in;
 seg_t x;
 char s[10];
 int countlet[7];
 int len;
 int i,j;
 int stupidsum;
 char one[2+1];
 char four[4+1];
 char seven[3+1];
 int ris;
 int sums = 0;
 int sumris;
 sumris = 0;
 for(i=0; i<7; i++)
	{countlet[i] = 0;
	}
 in = fopen("filen.txt", "r");
 if(in)
	{while(!feof(in))
		{for(i=0; i<11; i++)
			{fscanf(in, "%s ", s);
			 len = strlen(s);
			 switch(len)
			 	{case 2:
					strcpy(one, s);
					break;
				 case 3:
					strcpy(seven, s);
					break;
				 case 4:
					strcpy(four, s);
					break;
				 default:
					break;
				} //this checks the lenght of the input, 1, 4 and 7 have a unique lenght
			 for(j=0; j<len; j++)
				{switch(s[j])
					{case 'a':
						countlet[0]++;
						break;
					 case 'b':
						countlet[1]++;
						break;
					 case 'c':
						countlet[2]++;
						break;
                                         case 'd':
                                                countlet[3]++;
                                                break;
                                         case 'e':
                                                countlet[4]++;
                                                break;
                                         case 'f':
                                                countlet[5]++;
                                                break;
                                         case 'g':
                                                countlet[6]++;
                                                break;
					 default:
						break;
					} //counting how many times a letter is repeated
				}
			}
	 	 for(i=0; i<7; i++)
        		{//printf("%d   ", countlet[i]);
			 switch(countlet[i])
				{case 6:
					x.ltop = 'a' + i;
					break; //there a 6 numbers which have a left-top segment
				 case 4:
					x.lbot = 'a' + i;
				 	break; //same but with lower bottom
				 case 9:
					x.rbot = 'a' + i;
					break; //right bottom
				 default:
					break;
        			}
			}
		for(i=0; i<7; i++)
                        {countlet[i] = 0;
			} //for the next cycle
		 //printf("%s   %s    %s", one, four, seven);
		 //printf("LT:%c  LB: %c    RB: %c           ", x.ltop, x.lbot, x.rbot);
 //RICERCA DI RTOP TRAMITE CODIFICA DI 1
		for(i=0; i<2; i++)
			{if(one[i] != x.rbot)
				{x.rtop = one[i];
				}
			} //knowing one of the 2 segments of 1 (right-bottom), i can find right-top
		//printf("%c", x.rtop);
 //RICERCA TOP TRAMITE CODIFICA DI 7
		for(i=0; i<3; i++)
                        {if(seven[i] != x.rbot && seven[i] != x.rtop)
                                {x.top = seven[i];
                                }
                        } //knowing 2 of the 3 segments of 7 (right-bottom and right-top), i can find top
//RICERCA DI MID TRAMITE CODIFICA DI 4
		for(i=0; i<4; i++)
                        {if(four[i] != x.rbot && four[i] != x.rtop && four[i] != x.ltop)
                                {x.mid = four[i];
                                } //same process, find mid
                        }
		stupidsum = x.top + x.mid + x.rtop + x.ltop + x.rbot + x.lbot - 6 * ('a');
		//printf("\nss: %d", stupidsum);
		x.bot = 'a' + (21 - stupidsum); //this one is for finding bottom
		printf("TOP:%c     MID:%c     BOT:%c      LTOP:%c       RTOP:%c       LBOT:%c       RBOT:%c\n", x.top, x.mid, x.bot, x.ltop, x.rtop, x.lbot, x.rbot);

//PARTE 2: DECODIFICA OUTPUT
		ris = 0;
		for(i=0; i<4; i++)
			 {fscanf(in, "%s ", s);
			  len = strlen(s);
			  switch(len)
                                {case 2:
                                        ris = ris + 1 * (pow(10, 3-i));
                                        break;
                                 case 3:
                                        ris = ris + 7 * (pow(10, 3-i));
                                        break;
                                 case 4:
                                        ris = ris + 4 * (pow(10, 3-i));
                                        break;
				 case 7:
					ris = ris + 8 * (pow(10, 3-i));
					break;
				//1, 4, 7 and 8 have a unique lenght, so i don't have to check their segments, just the lenght
				//for the other numbers, i checked their ascii character encoding (as I did when finding bottom)
				 case 6:
					stupidsum = 0;
					for(j=0; j<6; j++)
						{stupidsum += s[j];
						}
					if(stupidsum - x.top - x.bot - x.ltop - x.rbot == x.lbot + x.rtop)
						{ris = ris + 0 * (pow(10, 3-i));
                                        	 break;
						}
					else if(stupidsum - x.top - x.bot - x.ltop - x.rbot == x.lbot + x.mid)
                                                {ris = ris + 6 * (pow(10, 3-i));
                                                 break;
                                                }
					else
						{ris = ris + 9 * (pow(10, 3-i));
                                                 break;
                                                }
				 case 5:
                                        stupidsum = 0;
                                        for(j=0; j<5; j++)
                                                {stupidsum += s[j];
                                                }
                                        if(stupidsum - x.top - x.bot - x.mid == x.lbot + x.rtop)
                                                {ris = ris + 2 * (pow(10, 3-i));
                                                 break;
                                                }
                                        else if(stupidsum - x.top - x.bot -x.mid == x.ltop + x.rbot)
                                                {ris = ris + 5 * (pow(10, 3-i));
                                                 break;
                                                }
                                        else
                                                {ris = ris + 3 * (pow(10, 3-i));
                                                 break;
                                                }
                                 default:
					break;
				} 
			}
			sums++;
			printf("RIS:%d\n" , ris);
			sumris = sumris + ris;
			printf("SOMMA TEMP:%d\n", sumris);
			x.top = 0;
			x.mid = 0;
			x.bot = 0;
			x.ltop = 0;
			x.rtop = 0;
			x.lbot = 0;
			x.rbot = 0;
		}
	}
 printf("SUMS:%d\n", sums);
 printf("RISULTATO:%d\n" , sumris);
 return 0;
}
