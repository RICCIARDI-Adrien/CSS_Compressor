/** @file Step_Unify_Spaces.c
 * @see Steps.h for description.
 * @author Adrien RICCIARDI
 */
#include <stdio.h>
#include <Steps.h>

//-------------------------------------------------------------------------------------------------
// Public functions
//-------------------------------------------------------------------------------------------------
void StepUnifySpaces(char *Pointer_Input_Buffer, int Input_Buffer_Size, char *Pointer_Output_Buffer, int *Pointer_Output_Buffer_Size)
{
	char Character;
	int Output_Size = 0;
	
	while (Input_Buffer_Size > 0)
	{
		// Get a character
		Character = *Pointer_Input_Buffer;
		Pointer_Input_Buffer++;
		Input_Buffer_Size--;
		
		// Replace tab by space
		if (Character == '\t')
		{
			Character = ' ';
			#if CSS_COMPRESSOR_IS_DEBUG_ENABLED
				printf("[%s] Replaces tab character by space character.\n", __FUNCTION__);
			#endif
		}
		
		// Write character to the output buffer
		*Pointer_Output_Buffer = Character;
		Pointer_Output_Buffer++;
		Output_Size++;
	}
	
	*Pointer_Output_Buffer_Size = Output_Size;
}
