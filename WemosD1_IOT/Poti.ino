/**************************************************************************************************
 * Poti.ino
 *
 * Created: 07/06/2020
 * Author: Lars Lindner
 *
 *
***************************************************************************************************/

int actpotval = 0;
int oldpotval = 0;


bool potval_changed()
{
	oldpotval = actpotval;
	actpotval = map(analogRead(A0),0,1024,80,20);

	if (actpotval < (oldpotval - 1) || actpotval > (oldpotval + 1))
	{
		return true;
	}
	else
	{
		return false;
	}
}


int returnPotVal()
{
	return actpotval;
}


int readPot()
{
	actpotval = map(analogRead(A0),0,1024,80,20);	
	return actpotval;
}

