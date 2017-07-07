# CSS Compressor
Pack a CSS file to decrease its weight.

## How it works
Program removes all comments, new lines, useless spaces and useless semicolons.  
  
1. Remove comments (remove them at first because they can be everywhere and would make all other steps more complicated if they have to handle them).
3. Remove unneeded semicolons.
2. Remove all unused spaces.
4. Remove new line characters (this is made at last to allow debugging comparison during the previous steps).
