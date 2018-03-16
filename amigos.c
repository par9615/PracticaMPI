#include <stdio.h>
#include "mpi.h"
#include <sys/time.h>

#define SERVER 0

int divisors_sum(int);
int find_friend_numbers();
void assign_tasks();

int rank, nprocs;
int left, right;
long long start_ts;
long long stop_ts;
float elapsed_time;
struct timeval ts;

int main(int argc, char *argv[])
{
	int left, right;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);	

	MPI_Barrier(MPI_COMM_WORLD);

	assign_tasks();
	find_friend_numbers();

	MPI_Barrier(MPI_COMM_WORLD);

	MPI_Finalize();


	if (rank == SERVER) {
		gettimeofday(&ts, NULL);
		stop_ts = ts.tv_sec * 1000000 + ts.tv_usec; // Tiempo final

		elapsed_time = (float) (stop_ts - start_ts)/1000000.0;

		printf("Tiempo %1.2f segundos\n",elapsed_time);
	}

	return 0;
}

void assign_tasks()
{
	int msg[2];	


	if(rank == SERVER)
	{
		printf("Ingresa el rango en el que deseas buscar\n");
		scanf("%d %d", &left, &right);
		gettimeofday(&ts, NULL);
		start_ts = ts.tv_sec * 1000000 + ts.tv_usec; // Tiempo inicial
		msg[0] = left;
		msg[1] = right;

		for(int i = 0; i < nprocs; i++)
			if(i != rank)
				MPI_Send(msg, 2, MPI_INT, i, 0, MPI_COMM_WORLD);	
	}

	else
	{
		MPI_Recv(msg, 2, MPI_INT, SERVER, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		left = msg[0] + rank;
		right = msg[1];


	}
}

int find_friend_numbers()
{
	printf("%d está en ejecución\n", rank);
	for(int i = left; i <= right; i+=nprocs)
	{
		int a = divisors_sum(i);

		for(int j = i+1; j <= right; j++)
		{
			int b = divisors_sum(j);
			if(i != j && a == j && b == i)
			{
				printf("%d y %d son amigos\n", i, j);
				printf("%d y %d son amigos\n", j, i);
			}
		}
	}

}


int divisors_sum(int n)
{
	int sum = 0;
	for(int i = 1; i < n; i++)
		if(n%i == 0)
			sum+=i;

	return sum;
}
