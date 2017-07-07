# CSS Compressor
Pack a CSS file to decrease its weight.

## How it works
Program removes all comments, new lines, useless spaces and useless semi-colons.  
  
1. First step is comments removal.
2. All unused spaces are removed on second step.
3. Third step searches for unneeded semi-colons.
4. Last step is new line characters removal (this is made at last to allow debugging comparison during the previous steps).
