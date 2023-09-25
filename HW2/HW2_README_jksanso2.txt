README
Homework Two, completed by Jayden Sansom, jksanso2


Summary
The code created for this homework, following the instructions given, is divided into four separate directories. Each contains the files needed to show the product of their respective parts.

Instructions
To begin creating and running the executable after unzipping the file, first navigate to the terminal on the Ubuntu environment. Use ‘cd’ commands to reach the directory where the folder contained within the .zip file was stored and change directories to be within it. 

Initialization:
        -'cd' to the working directory of 'HW2'
        -Run the command "make init" to update or install the required course libraries (SFML, etc.)

For Part 1:
        -Enter the command “cd 'Part 1'” to enter the correct directory.
        -Run the command “make clean” in case any fragments of old executables remain or you are attempting to recreate the program.
        -Run the command “make” and look to ensure that "main" and all *.o files were created.
        -Finally, run the command “make run” to start executing the window and see the demonstration of Part 1!
                -Press A or Left to move Left
                -Press D or Right to move Right
                -Press Space, W, or Up to jump

        *The threading was created to run the update methods of the player and moving platform on seperate threads.

For Part 2:
        -Enter the command “cd 'Part 2'” to enter the correct directory.
        -Run the command “make clean” in case any fragments of old executables remain or you are attempting to recreate the program.
        -Run the command “make” and look to ensure that "main" and all *.o files were created.
        -Finally, run the command “make run” to start executing the window and see the demonstration of Part 2!
                -Press A or Left to move Left
                -Press D or Right to move Right
                -Press Space, W, or Up to jump
                -Press P to Pause
                -Press I to decrease tic speed
                -Press O to increase tic speed

For Part 3:
        -Enter the command “cd 'Part 3'” to enter the correct directory.
        -For each directory: Server, Client1, Client2, and Client3:
                -Enter the correct directory using the "cd dirName" command.
                -Run the command “make clean” in case any fragments of old executables remain or you are attempting to recreate the program.
                -Run the command “make” and look to ensure that "main" and all *.o files were created.
                -Finally, run the command “make run” to start executing the server/client and see the demonstration of Part 3!

        *Make sure to begin the server before running the clients

For Part 4:
        -Enter the command “cd 'Part 4'” to enter the correct directory.
        -For each directory: Server, Client1, Client2, and Client3:
                -Enter the correct directory using the "cd dirName" command.
                -Run the command “make clean” in case any fragments of old executables remain or you are attempting to recreate the program.
                -Run the command “make” and look to ensure that "main" and all *.o files were created.
                -Finally, run the command “make run” to start executing the server/client and see the demonstration of Part 4!
                -Focus on a client window and use the following keys to control that client's character 
                        -Press A or Left to move Left
                        -Press D or Right to move Right
                        -Press Space, W, or Up to jump

        *Make sure to begin the server before running the clients