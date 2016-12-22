#include "EnrollmentSystem.h"
#include "Menu.h"

#define MAX_CREDITS 75

int run()
{
	EnrollmentSystem sys(MAX_CREDITS);

	sys.addMeetingHandler();
	sys.removeMeetingHandler();

	//mainMenu(sys);	

	return 0;
}

int main()
{
	run();

	return 0;
}