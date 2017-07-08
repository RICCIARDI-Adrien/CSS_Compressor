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
	int Output_Size = 0, Is_Previous_Token_Present, Is_Colon_Found;
	
Handle_Next_Block:
	#if CSS_COMPRESSOR_IS_DEBUG_ENABLED
		printf("[%s] Cleaning block selector(s) from unneeded spaces.\n", __FUNCTION__);
	#endif
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
			
			#if CSS_COMPRESSOR_IS_DEBUG_ENABLED
				printf("[%s] Block selector found.\n", __FUNCTION__);
			#endif
			
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
					goto Handle_Next_Property;
				}
			}
		}
		
		// Block scope has been reached, discard spaces in it
Handle_Next_Property:
		#if CSS_COMPRESSOR_IS_DEBUG_ENABLED
			printf("[%s] Cleaning block property from unneeded spaces.\n", __FUNCTION__);
		#endif
		while (Input_Buffer_Size > 0)
		{
			// Remove spaces until a property is found
			while (Input_Buffer_Size > 0)
			{
				// Get a character
				Character = *Pointer_Input_Buffer;
				Pointer_Input_Buffer++;
				Input_Buffer_Size--;
				
				// Stop if a token was found
				if (Character != ' ') break;
			}
			
			// Write the property
			Is_Colon_Found = 0;
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
				
				// Stop when the ':' separator is found
				if (Character == ':')
				{
					*Pointer_Output_Buffer = ':';
					Pointer_Output_Buffer++;
					Output_Size++;
					Is_Colon_Found = 1;
					break;
				}
			}
			
			// Discard spaces that separate the property from the colon (if needed)
			if (!Is_Colon_Found)
			{
				while (Input_Buffer_Size > 0)
				{
					// Get a character
					Character = *Pointer_Input_Buffer;
					Pointer_Input_Buffer++;
					Input_Buffer_Size--;
					
					// Stop if the colon was found (assume the CSS file is working)
					if (Character == ':')
					{
						*Pointer_Output_Buffer = ':';
						Pointer_Output_Buffer++;
						Output_Size++;
						break;
					}
				}
			}
			
			// Discard the spaces separating the colon from the property value
			while (Input_Buffer_Size > 0)
			{
				// Get a character
				Character = *Pointer_Input_Buffer;
				Pointer_Input_Buffer++;
				Input_Buffer_Size--;
				
				// Stop if a token was found
				if (Character != ' ') break;
			}
			
			// Write the value
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
				
				// Stop when the terminating semicolon has been found
				if (Character == ';')
				{
					*Pointer_Output_Buffer = ';';
					Pointer_Output_Buffer++;
					Output_Size++;
					goto Handle_Next_Property;
				}
				
				// Stop if the block end has been found
				if (Character == '}')
				{
					*Pointer_Output_Buffer = '}';
					Pointer_Output_Buffer++;
					Output_Size++;
					goto Handle_Next_Block;
				}
			}
		}
	}
	
	*Pointer_Output_Buffer_Size = Output_Size;
}
