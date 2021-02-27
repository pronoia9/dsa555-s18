unsigned int factorial (unsigned int n)
{
	if (n <= 1) { return 1; } // 0! and 1! = 1
	return n * factorial(n - 1);;
}

double power (double base, unsigned int n)
{
	if (n == 0) { return 1; }
	return base * power(base, n-1);
}

/* CHALLENGE: Can you think of a way to write the power function so that its run time is 
better (ie different big-O better...not just different constant better) than the run time 
of the iterative version of Power. */
double power2 (double base, unsigned int n)
{
	// O(log n) is the only possible option
	// n = even: base ^ (n/2) * base ^ (n/2)
	// n = odd : base ^ (n/2) * base ^ (n/2) * base
	if (n == 0) { return 1; }
	double x = power2(base, n/2) * power2(base, n/2);
	return (n % 2) ? (x *= base) : (x);
}

unsigned int fibonacci (unsigned int n)
{
	if (n < 2) { return n; }
	return fibonacci(n - 1) + fibonacci(n - 2);
}