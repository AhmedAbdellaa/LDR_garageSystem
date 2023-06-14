#include "STD_TYPES_H.h"
#include "MAP.h"

sint32 MAP(sint32 copy_s32InputRangeMin, sint32 copy_s32InputRangeMax,
           sint32 copy_s32OutputRangeMin, sint32 copy_s32OutputRangeMax, sint32 copy_s32InputValue)
{
    sint32 Local_s32YDiff,Local_s32XDiff;
    Local_s32XDiff = copy_s32InputRangeMax - copy_s32OutputRangeMin;
    Local_s32YDiff = copy_s32OutputRangeMax - copy_s32InputRangeMin;

    return (sint32)((copy_s32InputValue*Local_s32YDiff)/Local_s32XDiff);
}
