#include "dog.h"
#include "singleton.h"

void dog::moung()
{
	singleton::getInstance()->LogPrint("멍멍");

}
