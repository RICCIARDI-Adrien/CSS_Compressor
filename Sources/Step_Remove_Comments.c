/** @file Step_Remove_Comments.c
 * @see Steps.h for description.
 * @author Adrien RICCIARDI
 */
#include <stdio.h>
#include <Steps.h>

//-------------------------------------------------------------------------------------------------
// Public functions
//-------------------------------------------------------------------------------------------------
void StepRemoveComments(char *Pointer_Input_Buffer, int Input_Buffer_Size, char *Pointer_Output_Buffer, int *Pointer_Output_Buffer_Size)
{
	char Character;
	int Is_Previous_Character_A_Star = 0, Output_Size = 0;
	
	while (Input_Buffer_Size > 0)
	{
		// Search for a starting '/'
		while (Input_Buffer_Size > 0)
		{
			// Get a character
			Character = *Pointer_Input_Buffer;
			Pointer_Input_Buffer++;
			Input_Buffer_Size--;
			
			// Stop writing when a slash has been found
			if (Character == '/') break;
			
			// Write it to the output buffer
			*Pointer_Output_Buffer = Character;
			Pointer_Output_Buffer++;
			Output_Size++;
		}
		
		// Get the following character to determine if this is a comment or not
		if (Input_Buffer_Size == 0) break;
		Character = *Pointer_Input_Buffer;
		Pointer_Input_Buffer++;
		Input_Buffer_Size--;
		
		// This is a comment, remove it
		if (Character == '*')
		{
			// Read characters until the terminating '*/' combination is found
			while (Input_Buffer_Size > 0)
			{
				Character = *Pointer_Input_Buffer;
				Pointer_Input_Buffer++;
				Input_Buffer_Size--;
				
				// Is it a comment termination ?
				if (Is_Previous_Character_A_Star && (Character == '/'))
				{
					#if CSS_COMPRESSOR_IS_DEBUG_ENABLED
						printf("[%s] Removed comment.\n", __FUNCTION__);
					#endif
					
					break;
				}
				
				// Keep information about previous character now that the potential slash has been checked, or Is_Previous_Character_A_Star would have been false due to the slash and would be useless
				if (Character == '*') Is_Previous_Character_A_Star = 1;
				else Is_Previous_Character_A_Star = 0;
			}
		}
		// This is a regular slash
		else
		{
			// Write the slash and the following character
			*Pointer_Output_Buffer = '/';
			Pointer_Output_Buffer++;
			*Pointer_Output_Buffer = Character;
			Pointer_Output_Buffer++;
			Output_Size += 2;
		}
	}
	
	*Pointer_Output_Buffer_Size = Output_Size;
}
