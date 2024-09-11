#include <stdio.h>
#include <time.h>
#include <locale.h>
#include <fcntl.h>


//proto's
int moon_phase(int year, int month, int day);



int main(){

	//set local for unicode characters
	//setlocale(LC_CTYPE, "");

	//time variables
	time_t now;
	struct tm *clock;
	int hour;

	//Moon phases
	char *phase[8] = {
			"\U0001f312", //waxing crescent
			"\U0001f313", //first quarter
			"\U0001f314", //waxing gibbous
			"\0001f315", //full
			"\0001f316", //waning gibbous
			"\0001f317", //last quarter
			"\0001f318", //waning crescent
			"\U0001f311"  //new
			};

	//fetching the current time
	time(&now);
	clock = localtime(&now);
	hour = clock->tm_hour;


	//Display greeting and moon phase
	printf("Good ");
	if (hour < 12)
		printf("Morning ");
	else if (hour < 17)
		printf("Afternoon ");
	else
		printf("Evening ");
	if (hour > 24 && hour < 5)
		printf("another late one ");
	printf("John!");

	//setmode(_fileno(stdout), _O_U16TEXT);
 	int mp = moon_phase((clock->tm_year + 1900), (clock->tm_mon), clock->tm_mday);
	printf(" %s\n", phase[mp]);



	return 0;
}




//function declarations
int moon_phase(int year, int month, int day)
{
	int d, g, e;

	d = day;
	if (month == 2)
		d += 31;
	else if (month > 2)
		d += 59 + (month - 3) * 30.6 + 0.5;
	
	g = (year - 1900) % 19;
	e = (11 * g + 29) % 30;

	if (e == 25 || e == 24)
		++e;

	return ((((e + d) * 6 + 5) % 177) / 22 & 7);
}
