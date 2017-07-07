/** @file Step_Remove_Line_Feeds.c
 * @see Steps.h for description.
 * @author Adrien RICCIARDI
 */
#include <stdio.h>
#include <Steps.h>

//-------------------------------------------------------------------------------------------------
// Public functions
//-------------------------------------------------------------------------------------------------
void StepRemoveLineFeeds(char *Pointer_Input_Buffer, int Input_Buffer_Size, char *Pointer_Output_Buffer, int *Pointer_Output_Buffer_Size)
{
	char Character;
	int Output_Size = 0;
	
	while (Input_Buffer_Size > 0)
	{
		// Get a character
		Character = *Pointer_Input_Buffer;
		Pointer_Input_Buffer++;
		Input_Buffer_Size--;
		
		// Write it only if it is not a new line
		if (Character == '\n')
		{
			#if CSS_COMPRESSOR_IS_DEBUG_ENABLED
				printf("[%s] Removed line feed.\n", __FUNCTION__);
			#endif
		}
		else
		{
			*Pointer_Output_Buffer = Character;
			Pointer_Output_Buffer++;
			Output_Size++;
		}
	}
	
	*Pointer_Output_Buffer_Size = Output_Size;
}
