unsigned int factorial (unsigned int n) 
{
	int x;
	(n == 0) ? (x = 1) : (x = n);
	for (int i = n; i > 1; i--) { x *= i - 1; }
	return x;
}

double power (double base, unsigned int n)
{
	if (n == 0) { return 1; }
	int x = base;
	for (int i = n; i > 1; i--) { x *= base; }
	return x;
}

unsigned int fibonacci (unsigned int n)
{
	if (n < 2) { return n; } // 0 + 1 = 1
                             //     1 + 1 = 2
	int x = 1;               //         1 + 2 = 3
	int y = 1;               //             2 + 3 = 5
	int z;                   //                 3 + 5 = 8 ...

	for (int i = 2; i < n; i++)
	{
		z = x;
		x = z + y;
		y = z;
	}

	return x;
}