CS 101 PROJECT – BUBBLE TROUBLE


Link to screen recordings- https://drive.google.com/drive/folders/1U1t5cIk4qrtLmrbbZkxIyVOOD4mY0bG0?usp=sharing



I have added all the required features and all the extra features. 
Also, I have made it so that a bubble flashes (changes colour quickly) on being hit by a bullet and then disappears. 
While a bubble is in contact with the shooter, the shooter turns blue.
I have also added a constraint that only a maximum of 5 bullets can be on screen at once. 
There are 3 levels to the game, and you get 3 lives and 60 time units to complete the game. 
There are 3 types of bubbles – the smallest gives you 3 points, medium gives you 5, and the largest gives you 7. 
You can only win by destroying all the bubbles, and you lose when you hit 0 lives or by timeout.


I have made the following major changes in the following files:
#Bullet.h
•       	Added a function to delete bullets (by moving them to an arbitrary coordinate off-screen).
#Bubble.h
•       	Added a variable called g, which acts as constant acceleration and causes the parabolic trajectory of the bubble.
•       	Added a function called change_color, which changes the colour of the bubble into one of 6 colours that I have defined, 
	depending upon the parameter passed.
•       	Also added a function to delete bubbles.
#Shooter.h
•       	Added a function called change_color, which changes the colour of the bubble into one of 2 colours that I have defined, 
	depending upon the parameter passed.
#Main.cpp
•	Added variables to keep track of lives, score, time, level etc.
•       	I added three functions - bubble_split, b_b_collision and b_s_collision, which splits the bubbles into two 
         	and detects a bullet-bubble collision and bubble-shooter collision, respectively.
•       	Used a method called stringstream to display all the text on the screen.
	
The rest of the minor details are commented in these files.


