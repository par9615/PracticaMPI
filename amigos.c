#include <stdio.h>

int divisors_sum(int n)
{
	int sum = 0;
	for(int i = 1; i < n; i++)
		if(n%i == 0)
			sum+=i;

	return sum;
}

int main()
{
	int l, r;
	scanf("%d %d", &l, &r);

	

	for(int i = l; i <= r; i++)
	{
		int a = divisors_sum(i);

		for(int j = i+1; j <= r; j++)
		{
			int b = divisors_sum(j);
			if(i != j && a == j && b == i)
			{
				printf("%d y %d son amigos\n", i, j);
				printf("%d y %d son amigos\n", j, i);
			}
		}
	}
	return 0;
}