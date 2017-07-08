# CSS Compressor
Pack a CSS file to decrease its weight.

## How it works
Program removes all comments, new lines, useless spaces and useless semicolons.  
  
1. Remove comments (remove them at first because they can be everywhere and would make all other steps more complicated if they have to handle them).
2. Remove new line characters so they do not have to be taken into account by the next steps.
3. Remove unneeded semicolons.
4. Remove all unused spaces.
