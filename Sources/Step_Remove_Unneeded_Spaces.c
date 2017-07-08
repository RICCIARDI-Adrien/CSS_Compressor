/** @file Step_Remove_Unneeded_Spaces.c
 * @see Steps.h for description.
 * @author Adrien RICCIARDI
 */
#include <stdio.h>
#include <Steps.h>

//-------------------------------------------------------------------------------------------------
// Public functions
//-------------------------------------------------------------------------------------------------
void StepRemoveUnneededSpaces(char *Pointer_Input_Buffer, int Input_Buffer_Size, char *Pointer_Output_Buffer, int *Pointer_Output_Buffer_Size)
{
	char Character;
	int Output_Size = 0, Is_Previous_Token_Present;
	
	while (Input_Buffer_Size > 0)
	{
		// Remove spaces between block selectors (words that precede '{')
		Is_Previous_Token_Present = 0;
		while (Input_Buffer_Size > 0)
		{
			// Remove block leading spaces
			while (Input_Buffer_Size > 0)
			{
				// Get a character
				Character = *Pointer_Input_Buffer;
				Pointer_Input_Buffer++;
				Input_Buffer_Size--;
				
				// Stop if a token was found
				if (Character != ' ') break;
			}
			if (Input_Buffer_Size == 0) goto Exit;
			
			// Stop when the block beginning as been found
			if (Character == '{')
			{
				*Pointer_Output_Buffer = '{';
				Pointer_Output_Buffer++;
				Output_Size++;
				break;
			}
			
			// Write a single separating space if there is a token before this one (i.e. there are multiple space-separated words on the line preceding '{')
			if (Is_Previous_Token_Present)
			{
				*Pointer_Output_Buffer = ' ';
				Pointer_Output_Buffer++;
				Output_Size++;
			}
			Is_Previous_Token_Present = 1;
			
			// Write the token
			while (Input_Buffer_Size > 0)
			{
				// Write the character
				*Pointer_Output_Buffer = Character;
				Pointer_Output_Buffer++;
				Output_Size++;
				
				// Get next character
				Character = *Pointer_Input_Buffer;
				Pointer_Input_Buffer++;
				Input_Buffer_Size--;
				
				// Stop if a space (i.e. a separator) was found
				if (Character == ' ') break;
				
				// Stop if the block beginning has been found
				if (Character == '{')
				{
					*Pointer_Output_Buffer = '{';
					Pointer_Output_Buffer++;
					Output_Size++;
					break;
				}
			}
			if (Input_Buffer_Size == 0) goto Exit;
		}
	}
	
Exit:
	*Pointer_Output_Buffer_Size = Output_Size;
}