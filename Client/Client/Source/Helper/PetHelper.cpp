#include "Helper/PetHelper.h"
#include "PlayerRole.h"

bool IsValidPet(const SPetItem &pet_)
{
	return pet_.baseInfo.petId != InvalidLogicNumber;
}
