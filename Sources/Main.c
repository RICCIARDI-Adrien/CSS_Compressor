/** @file Main.c
 * Keep only mandatory characters in a CSS file to decrease its size.
 * @author Adrien RICCIARDI
 */
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <Steps.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

//-------------------------------------------------------------------------------------------------
// Private constants
//-------------------------------------------------------------------------------------------------
/** Maximum input file size in bytes. */
#define MAIN_MAXIMUM_INPUT_FILE_SIZE (10 * 1024 * 1024) // 10MB should be enough

//-------------------------------------------------------------------------------------------------
// Private variables
//-------------------------------------------------------------------------------------------------
/** The first buffer used to store the files data and steps results. */
static char Main_Buffer_1[MAIN_MAXIMUM_INPUT_FILE_SIZE];
/** The second buffer used to store the files data and steps results. */
static char Main_Buffer_2[MAIN_MAXIMUM_INPUT_FILE_SIZE];

//-------------------------------------------------------------------------------------------------
// Entry point
//-------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	char *String_Input_File_Name, *String_Output_File_Name;
	int File_Descriptor, Buffer_1_Size, Buffer_2_Size;
	
	// TODO banner
	
	// Check parameters
	if (argc != 3)
	{
		printf("Usage : %s Input_File Output_File\n", argv[0]);
		return EXIT_FAILURE;
	}
	String_Input_File_Name = argv[1];
	String_Output_File_Name = argv[2];
	
	// Try to load the input file
	// Open file
	printf("Loading input file...\n");
	File_Descriptor = open(String_Input_File_Name, O_RDONLY);
	if (File_Descriptor == -1)
	{
		printf("Error : failed to open input file '%s' (%s).\n", String_Input_File_Name, strerror(errno));
		return EXIT_FAILURE;
	}
	// Read whole content
	Buffer_1_Size = read(File_Descriptor, Main_Buffer_1, sizeof(Main_Buffer_1));
	if (Buffer_1_Size == -1)
	{
		printf("Error : failed to read the input file (%s).\n", strerror(errno));
		close(File_Descriptor);
		return EXIT_FAILURE;
	}
	close(File_Descriptor);
	
	// Execute first step : comments removal
	printf("Removing comments...\n");
	StepRemoveComments(Main_Buffer_1, Buffer_1_Size, Main_Buffer_2, &Buffer_2_Size);
	
	// Execute the fourth step : line feeds removal
	StepRemoveLineFeeds(Main_Buffer_2, Buffer_2_Size, Main_Buffer_1, &Buffer_1_Size);
	
	// Remove output file if existing to avoid merging its content with the new one that will be written
	unlink(String_Output_File_Name);
	
	// Store compressed CSS into the output file
	printf("Writing output file...\n");
	File_Descriptor = open(String_Output_File_Name, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (File_Descriptor == -1)
	{
		printf("Error : failed to open output file '%s' (%s).\n", String_Output_File_Name, strerror(errno));
		return EXIT_FAILURE;
	}
	// Write whole content
	if (write(File_Descriptor, Main_Buffer_1, Buffer_1_Size) != Buffer_1_Size)
	{
		printf("Error : failed to write the output file (%s).\n", strerror(errno));
		close(File_Descriptor);
		return EXIT_FAILURE;
	}
	close(File_Descriptor);
	
	printf("CSS compression done.\n");
	return EXIT_SUCCESS;
}
	