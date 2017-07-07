/** @file CSS_Compressor.c
 * Keep only mandatory characters in a CSS file to decrease its size.
 * @author Adrien RICCIARDI
 */
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

//-------------------------------------------------------------------------------------------------
// Private variables
//-------------------------------------------------------------------------------------------------
/** The input file file descriptor. */
static int CSS_Compressor_File_Descriptor_Input = -1;
/** The output file file descriptor. */
static int CSS_Compressor_File_Descriptor_Output = -1;

//-------------------------------------------------------------------------------------------------
// Private functions
//-------------------------------------------------------------------------------------------------
/** Close opened files on program exit. */
static void CSSCompressorExitCloseFiles(void)
{
	if (CSS_Compressor_File_Descriptor_Input != -1) close(CSS_Compressor_File_Descriptor_Input);
	if (CSS_Compressor_File_Descriptor_Output != -1) close(CSS_Compressor_File_Descriptor_Output);
}

/** Read a character from the input file.
 * @return The read character.
 * @note The function automatically makes the program exit when the input file end is reached.
 */
static char CSSCompressorInputFileReadCharacter(void)
{
	char Character;

	if (read(CSS_Compressor_File_Descriptor_Input, &Character, 1) != 1) exit(EXIT_SUCCESS); // TODO check for read error
	
	#if CSS_COMPRESSOR_IS_DEBUG_ENABLED
		printf("[%s] \033[32mRead character : 0x%02X (%c).\033[0m\n", __FUNCTION__, Character, Character == '\n' ? ' ' : Character); // Replace new line character by a space to avoid going to new line
	#endif
	return Character;
}

/** Write a character to the output file.
 * @param Character The character to write.
 * @note The function automatically makes the program exit if an error occurred.
 */
static void CSSCompressorOutputFileWriteCharacter(char Character)
{
	if (write(CSS_Compressor_File_Descriptor_Output, &Character, 1) != 1)
	{
		printf("Error : failed to write to output file.\n");
		exit(EXIT_FAILURE);
	}
}

/** Remove comments.
 * @note This function must be called when a '/' character has been read.
 */
static inline void CSSCompressorHandleComment(void)
{
	char Character;
	int Is_Previous_Character_A_Star;
	
	// Get the following character to determine if this is a comment or not
	Character = CSSCompressorInputFileReadCharacter();
	
	// This is a comment, remove it
	if (Character == '*')
	{
		// Read characters until the terminating '*/' combination is found
		while (1)
		{
			Character = CSSCompressorInputFileReadCharacter();
			
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
		CSSCompressorOutputFileWriteCharacter('/');
		CSSCompressorOutputFileWriteCharacter(Character);
	}
}

//-------------------------------------------------------------------------------------------------
// Entry point
//-------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	char *String_Input_File_Name, *String_Output_File_Name;
	unsigned char Character;
	
	// Check parameters
	if (argc != 3)
	{
		printf("Usage : %s Input_File Output_File\n", argv[0]);
		return EXIT_FAILURE;
	}
	String_Input_File_Name = argv[1];
	String_Output_File_Name = argv[2];
	
	atexit(CSSCompressorExitCloseFiles);
	
	// Try to open the files
	// Input file
	CSS_Compressor_File_Descriptor_Input = open(String_Input_File_Name, O_RDONLY);
	if (CSS_Compressor_File_Descriptor_Input == -1)
	{
		printf("Error : failed to open input file '%s' (%s).\n", String_Input_File_Name, strerror(errno));
		return EXIT_FAILURE;
	}
	// Output file
	CSS_Compressor_File_Descriptor_Output = open(String_Output_File_Name, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (CSS_Compressor_File_Descriptor_Output == -1)
	{
		printf("Error : failed to open output file '%s' (%s).\n", String_Output_File_Name, strerror(errno));
		return EXIT_FAILURE;
	}
	
	while (1)
	{
		Character = CSSCompressorInputFileReadCharacter();
		
		switch (Character)
		{
			// Remove new line characters
			case '\n':
				#if CSS_COMPRESSOR_IS_DEBUG_ENABLED
					printf("[%s] Removed new line character.\n", __FUNCTION__);
				#endif
				break;
			
			case '/':
				CSSCompressorHandleComment();
				break;
				
			default:
				CSSCompressorOutputFileWriteCharacter(Character);
				break;
		}
	}
}
