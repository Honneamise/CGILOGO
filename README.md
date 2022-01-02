# CGILOGO

![image](image.png)

This is a very simple Common Gateway Interface written in C .

You can use a subset of the UCB Logo commands to draw images in SVG format.


<b>F INT</b> : advance of INT pixels<br>
<b>R INT</b> : rotate right of INT degrees<br>
<b>L INT</b> : rotate left of INT degrees<br>
<b>H</b> : reset position and direction<br>
<b>M INT INT</b> : move to coordinates X Y<br>
<b>U</b> : pen up<br>
<b>D</b> : pen down<br>
<b>C RGB</b> : set the current pen color<br>
<b>W INT [ INSTRUCTIONS ]</b> : repeat INT times the instructions in the brackets.<br>
<br>
The top left of the drawing area is located at 0,0 and the bottom right at 800,600.<br>
The starting position is at 400,300 and the direction points upwards.<br>
INT must be a positive number in decimal format.<br>
RGB is a color in standard hexadecimal format ( default is #000000 )<br>
Tokens must be separated by one or more blank characters.<br>
The code can be of max 500 characters, including blanks.
\
\
\
Live demo : https://logo.honny.net
