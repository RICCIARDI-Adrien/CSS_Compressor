/** @file Step_Remove_Last_Semicolon.c
 * @see Steps.h for description.
 * @author Adrien RICCIARDI
 */
#include <stdio.h>
#include <Steps.h>

//-------------------------------------------------------------------------------------------------
// Public functions
//-------------------------------------------------------------------------------------------------
void StepRemoveLastSemicolon(char *Pointer_Input_Buffer, int Input_Buffer_Size, char *Pointer_Output_Buffer, int *Pointer_Output_Buffer_Size)
{
	char Character;
	int Output_Size = 0;
	
	while (Input_Buffer_Size > 0)
	{
		// Get a character
		Character = *Pointer_Input_Buffer;
		Pointer_Input_Buffer++;
		Input_Buffer_Size--;
		
		// Search for a semicolon
		if (Character == ';')
		{
			// Discard all following spaces until a token is discovered
			while (Input_Buffer_Size > 0)
			{
				Character = *Pointer_Input_Buffer;
				if ((Character != ' ') && (Character != '\n')) break; // Also ignore new lines in case the line feeds removal step has not been done yet
				Pointer_Input_Buffer++;
				Input_Buffer_Size--;
			}
			
			// Is the next character a block termination ('}') ?
			if (Input_Buffer_Size == 0) break;
			Character = *Pointer_Input_Buffer;
			Pointer_Input_Buffer++;
			Input_Buffer_Size--;
			
			// This is the block end, write nothing to remove the semicolon ('}' will be automatically written by the remaining code)
			if (Character == '}')
			{
				#if CSS_COMPRESSOR_IS_DEBUG_ENABLED
					printf("[%s] Removed unneeded semicolon.\n", __FUNCTION__);
				#endif
			}
			// This is not the block end, write the semicolon and the following character
			else
			{
				*Pointer_Output_Buffer = ';';
				Pointer_Output_Buffer++;
				Output_Size++;
			}
		}
		
		// Write the character to the output buffer
		*Pointer_Output_Buffer = Character;
		Pointer_Output_Buffer++;
		Output_Size++;
	}
	
	*Pointer_Output_Buffer_Size = Output_Size;
}
