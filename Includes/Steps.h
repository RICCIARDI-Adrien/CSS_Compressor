/** @file Steps.h
 * Gather all needed steps to compress a CSS file.
 * @author Adrien RICCIARDI
 */
#ifndef H_STEPS_H
#define H_STEPS_H

//-------------------------------------------------------------------------------------------------
// Functions
//-------------------------------------------------------------------------------------------------
/** Remove all blocks starting with '/''*' and ending with '*''/'.
 * @param Pointer_Input_Buffer The buffer containing the CSS data with comments.
 * @param Input_Buffer_Size Input buffer size in bytes.
 * @param Pointer_Output_Buffer On output, contain the CSS data without comments.
 * @param Pointer_Output_Buffer_Size On output, contain the output buffer size in bytes.
 */
void StepRemoveComments(char *Pointer_Input_Buffer, int Input_Buffer_Size, char *Pointer_Output_Buffer, int *Pointer_Output_Buffer_Size);

#endif
