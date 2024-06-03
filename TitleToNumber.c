unsigned long int my_pow(int x, int y)
{
	int i = 0;
	unsigned long mul = 1;
	for (i = 0; i < y; i++)
		mul = mul * x;
	return mul;
}

int my_strlen(char *ch)
{
	int len = 0;
	while (*ch) {
		len++;
		ch++;
	}
	return len;
}


int titleToNumber(char* columnTitle) {

	int len = 0;
	int ans = 0;
	len = my_strlen(columnTitle);
	while (*columnTitle) {
		ans += (my_pow(26, len -1) * (*columnTitle - 'A' + 1));
		len--;
        columnTitle++;
	}
	return ans;
}
