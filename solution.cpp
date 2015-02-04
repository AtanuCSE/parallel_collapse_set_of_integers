// sometest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_TAG	1
#define ARR_SIZE_TAG 2
#define DEFAULT_TAG_2 3

#define BUF_SIZE 5    //input block size


FILE *fp;
char buf[1030];
long long char_read=0;
long long adder=0;
int scanner=0;



int buf_read(char * buf, const char * end)
{
	fp = fopen("999.txt", "r");  //Input file
    int count;
	fseek( fp, char_read, SEEK_SET );  //Seek for next block
    count = fread(buf, 1, BUF_SIZE, fp);     //Read block of input
	char_read=char_read+count;

    if (count > 0 && buf[count - 1] == '\n')
	{
        --count;
    }
	fclose(fp);
    return count;
}

int main (int argc , char **argv)
{
	int myid, numprocs;
	int token = 0;
	int read=0;
	MPI_Status status;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);

	if (numprocs == 1)
	{
		/*Trivial single processor
		*So will be a normal program
		*no parallelism
		******************/

		
		fp = fopen("999.txt", "r");
		
		do 
		{
		  scanner = (int)fgetc(fp);
		  scanner=(int)scanner-48;

		  if(scanner>=0)
		  adder=adder+scanner;


		} while(scanner != EOF && scanner!=-49);

		fclose(fp);

		long long result=0;
		int flag=0;

		while(flag==0)
		{
			result=0;
			while(adder/10!=0)
			{
				int temp=adder%10;
				result=result+temp;
				adder=adder/10;
			}
			result=result+adder%10;
			int checker=result/10;

			if(checker==0) flag=1;
			else adder=result;

			
		}

		printf("Collapse Message Result is = %lld",result);

		
	}
	else
	{
		if(myid==0)
		{
			//Master


			/* read a block of chars to buf */
			read = buf_read(buf, buf + BUF_SIZE);

			/* initial allocation */
			int allocatedJobs = 1;
			
			
			while (read)
			{
				
				int targetSlave=allocatedJobs%(numprocs-1)+1;

				printf("Sending to %d\n",targetSlave);

				/* allocate a job to proc i+1 */
				MPI_Send(&read, 1, MPI_INT, targetSlave, ARR_SIZE_TAG, MPI_COMM_WORLD);    //send array size
				MPI_Send(&buf, read, MPI_INT, targetSlave, DEFAULT_TAG, MPI_COMM_WORLD);   //send array
					
				allocatedJobs++;

				/* read a block, but if the last read was a short item count, don't try to read again */
				/* read a block of chars to buf */
				read = buf_read(buf, buf + BUF_SIZE);

			}

			read=0;
			for(int h=1;h<numprocs;h++)
			{
				MPI_Send(&read, 1, MPI_INT, h, ARR_SIZE_TAG, MPI_COMM_WORLD);    //send array size
			}
				
			

			allocatedJobs--; //minus the last increased one

			/* while there is any job to be allocated or received */
			while(allocatedJobs)
			{
				 printf("Discharging %d\n",allocatedJobs);

				 long long receive=0;
				 int size=1;

				 int comingReceiver=allocatedJobs%(numprocs-1)+1;

				 /*after sending jobs, we open a blocking socket and wait for return*/
				 MPI_Recv(&receive, 1, MPI_INT, comingReceiver, DEFAULT_TAG, MPI_COMM_WORLD, &status);

				 /* status.MPI_SOURCE contains the sending process ID. We obtain the value received, 
					and add them to the result */       
				 int current_received_process=status.MPI_SOURCE;

				 adder=adder+receive;

				 allocatedJobs--;

				
		
			}

			//collapse by the master processor
			long long result=0;
			int flag=0;

			while(flag==0)
			{
				result=0;
				while(adder/10!=0)
				{
					int temp=adder%10;
					result=result+temp;
					adder=adder/10;
				}
				result=result+adder%10;
				int checker=result/10;

				if(checker==0) flag=1;
				else adder=result;

			
			}
			 
			printf("Collapse Message Result is = %lld",result);

			
			 
			 
		}
		else
		{
			while(true)
			{
				//workers
				int receive_size;

				//MPI_Recv(&receive_size, 1, MPI_INT, 0, ARR_SIZE_TAG, MPI_COMM_WORLD, &status);  //receive array size
				MPI_Recv(&receive_size, 1, MPI_INT, 0, ARR_SIZE_TAG, MPI_COMM_WORLD, &status);  //receive array size

				if(receive_size>0)      //check array size for 0
				{

					MPI_Recv(&buf, receive_size, MPI_INT, 0, DEFAULT_TAG, MPI_COMM_WORLD, &status);

					printf("buf= %s and myid=%d\n",buf,myid);

					long long temp_adder=0;

					for(int j=0;j<receive_size;j++)
						temp_adder=temp_adder+buf[j]-48;

					MPI_Send(&temp_adder, 1, MPI_INT, 0, DEFAULT_TAG, MPI_COMM_WORLD);
				}
				else
				{
				
					int blank_adder=0;

					MPI_Send(&blank_adder, 1, MPI_INT, 0, DEFAULT_TAG, MPI_COMM_WORLD);

					break;
				}

			}
			
		}

	}

	

	MPI_Finalize();

	return 0;
}





