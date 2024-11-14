/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You don't need to change anything in the driver code/main function except the part(s) where instructed.
 * You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 * The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 * Load the images into the textures objects from img directory.
 * Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 * SUGGESTION: If you want to make changes in "utils.h", do it once you complete rest of the functionalities.
 * TIP: You can study SFML for drawing scenes, sprites and window.
 * */


// Affan Ahmad          22i-0916               Project
#include <SFML/Graphics.hpp>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
#include <sstream>
#include<fstream>
#include<iostream>
#include<string>
using namespace std;
using namespace sf;

int main(){
    srand(time(0));
    RenderWindow window(VideoMode(320, 480), title);
    Texture obj1, obj2, obj3 , object4,object5 , object6 , object7 , object8;
    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/background.png");
    obj3.loadFromFile("img/frame.png");
    ////////////////////////////////////////////////////
    //Following code is creation of objects for menu///
    
    object4.loadFromFile("img/start.png"); 
    object5.loadFromFile("img/help.png");
    object6.loadFromFile("img/highscores.png");
    object7.loadFromFile("img/pause.png");
    object8.loadFromFile("img/gameover.png");
    
    /////////////////////////////////////////////////////
    Sprite sprite(obj1), background(obj2), frame(obj3) , start(object4),help(object5) , highscores(object6), pause(object7), gameover(object8);
     
    bool menu = true,highscore_menu=false , help_menu=false , pause_=false , gameover_ = false; // every boolean for the further menus is initally set to false except the main menu beacuse it is to be dispalyed unitally
    int delta_x=0, colorNum = 1 , score = 0 , level =1;
    float timer=0, delay=0.3;
    bool rotate=0 , top = false;
    string level_ = " ";         // variable to store and display the current level of the game onto the main background object
    Clock clock;
    Clock clock2;
    while (window.isOpen() && top == false){  // top boolean checks if the blocks had reached to the very top >>> ends the game and shows the game over screen 
    	level_ = "Level 1"; // initally the game level is 1
    	

	if ( level == 2)
		grid_shorten();
    
	while(menu)
         {
         	window.draw(start);  // 
         	window.display();    //draws and displays the menu object onto the screen
         	if(Keyboard::isKeyPressed(Keyboard::Num1))  // if num1 key is pressed the menu boolean becomes true and the menu exits and the game begins
         		menu=false;
         	else if(Keyboard::isKeyPressed(Keyboard::Num3))  // if num1 key is pressed the help_menu boolean becomes true 
         	{
         		help_menu=true;
         		while(help_menu)
         		{
         			window.draw(help); 
         			window.display();  // object for help menu is drawn and displayed
         			
         			if(Keyboard::isKeyPressed(Keyboard::Num0)){ // if num0 key is pressed the help menu is exited and the user come backs to the main menu
					help_menu = false;
				}
         		}	
         	}
         	
         	else if(Keyboard::isKeyPressed(Keyboard::Num4)){ // if num4 key is pressed the menu boolean becomes false, the main window closes. 
         		menu = false;
         		window.close();
         		update_highscore(score); // scores are updated in the score.txt file using the update_highscore function
         		return 0;
         	}
         	else if(Keyboard::isKeyPressed(Keyboard::Num2)){  // if num2 key is pressed the highscore_menu boolean becomes tru and the highscore object is drawn 
      			highscore_menu = true;
      			while (highscore_menu)
      			{
      				window.draw(highscores);
      				Text text;   
      				Font font;
				if (!font.loadFromFile("vaca.ttf"))
					throw("Could not load font");
      				fstream myFile;  // myFile of data type fstream used in file handling
      				myFile.open("scores.txt", ios::in); // opens file in read mode 
      				int x_ = 80,y_=100; // the offset coordinates for our text to be printed on the screen
				if (myFile.is_open()){   //checks if file is open or closed
					string line;
					while (getline(myFile,line))  // the loop will itterate untill End Of File is reached
					{
						text.setFont(font);              // 
						text.setString(line);            //
						text.setCharacterSize(24);       //   text font , size ,color , style(bold) is set
						text.setFillColor(Color::Yellow);//
						text.setStyle(Text::Bold);       //
						text.setPosition(x_,y_);   
						window.draw(text);      // draws the text object onto the highscore object 
						y_+=30;        // every next line from the file gets printed 30 pxs downwards
					}
					myFile.close();       
				}
				window.display();                               
				if(Keyboard::isKeyPressed(Keyboard::Num0)){     // if num0 key is pressed the help menu is exited and the user come backs to the main menu
					highscore_menu = false;
				}
      			}
			
         	}
         }	
         
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;    
        //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e)){                    //Event is occurring - until the game is in running state
            if (e.type == Event::Closed){                   //If cross/close is clicked/pressed
                window.close();   
                update_highscore(score);      
                return 0;                   //Opened window disposes
            }
            if (e.type == Event::KeyPressed) {             //If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Up)            //Check if the other key pressed is UP key
                {
                    rotate = true;    //Rotation gets on
                    rotation(rotate);
                }
                else if (e.key.code == Keyboard::Left)     //Check if the other key pressed is LEFT key
                {
                    	
                    	delta_x = -1; 
                    	horizontal_movements_left();
                }                         //Change in X-Axis - Negative
                else if (e.key.code == Keyboard::Right)    //Check if the other key pressed is RIGHT key	
                {
                    	delta_x = 1;
                    	horizontal_movements_right();
                }                           //Change in X-Axis - Positive
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))   //Just another way to detect key presses without event listener
            delay=0.05;  				//If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05
         
        else if(Keyboard::isKeyPressed(Keyboard::Space))  
        	hard_drop();
        
        if (Keyboard::isKeyPressed(Keyboard::F))       // If the user pressed 'F' key the pause boolean turns true 
        {
        	pause_ = true;
        	while(pause_)
        	{
        		window.draw(pause);                      // pause object is drawn and displayed
        		window.display();
        		
        		if (Keyboard::isKeyPressed(Keyboard::Num1))
        		{
        			level = 1;   				     // level is set back to 1
        			clock2.restart();                           // as new game has began the clock is resetted back to zero       
        			gridclear();                                // if '1' is pressed the grid is cleared for a new game to be started
        			level_ = "Level 1";
        			score = 0;                                      // score is set back to 0
        			pause_ = false;				  // pause boolean becomes false so the pause menu can be exited
        		}
        		
        		else if (Keyboard::isKeyPressed(Keyboard::Num2))
        		{
        			highscore_menu = true;
	      			while (highscore_menu)
	      			{
	      				window.draw(highscores);
	      				Text text;   
	      				Font font;
					if (!font.loadFromFile("vaca.ttf"))
						throw("Could not load font");
	      				fstream myFile;  // myFile of data type fstream used in file handling
	      				myFile.open("scores.txt", ios::in); // opens file in read mode 
	      				int x_ = 80,y_=100; // the offset coordinates for our text to be printed on the screen
					if (myFile.is_open()){   //checks if file is open or closed
						string line;
						while (getline(myFile,line))  // the loop will itterate untill End Of File is reached
						{
							text.setFont(font);              // 
							text.setString(line);            //
							text.setCharacterSize(24);       //   text font , size ,color , style(bold) is set
							text.setFillColor(Color::Yellow);//
							text.setStyle(Text::Bold);       //
							text.setPosition(x_,y_);   
							window.draw(text);      // draws the text object onto the highscore object 
							y_+=30;        // every next line from the file gets printed 30 pxs downwards
						}
						myFile.close();       
					}
					window.display();                               
					if(Keyboard::isKeyPressed(Keyboard::Num0)){     // if num0 key is pressed the help menu is exited and the user come backs to the main menu
						highscore_menu = false;
					}
	      			}
        		}
        		
        		else if (Keyboard::isKeyPressed(Keyboard::Num3))        // help menu already explained above on line 63
        		{
        			help_menu = true;
        				
        				while(help_menu)
        				{
        					window.draw(help);
        					window.display();
        						if (Keyboard::isKeyPressed(Keyboard::Num0))
        							help_menu = false;
        				}
        		}
        		
        		else if (Keyboard::isKeyPressed(Keyboard::Num4)){     
        			window.close();
        			update_highscore(score);
        			return 0;
        		}		
        			
        		else if (Keyboard::isKeyPressed(Keyboard::Num5)) // if num5 is pressed pause menu exits and the game continues
        			pause_ = false;
        	
        	}
    }
        	
      
   
        ///////////////////////////////////////////////
        ///*** START CALLING YOUR FUNCTIONS HERE ***///
        
        
        
        top = top_check ();  // top_check() checks if the top of grid is reached and returns true if reached else returns false
        if (top == true )    // if top is true means game is over so gameover_ boolean becomes true
         {
         	gameover_ = true;
         	
         	while ( gameover_)
         	{
		 	window.draw(gameover);    // gameover object is drawn and displayed 
			window.display();
			
			if (Keyboard::isKeyPressed(Keyboard::Num1)) // if num1 is pressed the game restarts 
			{
					gridclear();			//the grid is cleared again
					clock2.restart();		// as new game has began the clock is resetted back to zero 
					score = 0;			//score is set back to 0
					level = 1;			// level returned to level 1
					level_="Level 1";		
					top = false;			// top reached becomes false as grid is cleared now
					gameover_=false;		// as new game is started so gameover_ becomes false aswell
			}
			if (Keyboard::isKeyPressed(Keyboard::Num2)) // If num 2 is pressed the games exits 
			{	
					top = true;			
					window.close();
					update_highscore(score);
					return 0;
			}
        	}
         
         
         }
        fallingPiece(timer, delay,colorNum);  // falling piece is called to make the piece stored in point_1 array to fall down
   	delay=0.3;
    	rotate=0;  
   	linebreak(score,level); 		// checkes if the piece fill a horizontal row so it can break it and increase the score based on the current level
        ///*** YOUR CALLING STATEMENTS END HERE ***///
        //////////////////////////////////////////////

 
        window.clear(Color::Black);                
        window.draw(background);
        for (int i=0; i<M; i++){
            for (int j=0; j<N; j++){
                if (gameGrid[i][j]==0)
                    continue;
                sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
                sprite.setPosition(j*18,i*18);
                sprite.move(28,31); //offset
                window.draw(sprite);
            }
        }
       
        for (int i=0; i<4; i++){
            sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
            sprite.setPosition(point_1[i][0]*18,point_1[i][1]*18);
            sprite.move(28,31);
            window.draw(sprite);
     
         } 
        
        float new_time = clock2.getElapsedTime().asSeconds();  // calculates the time elapsed since the start of game and stores it in 'new time' variable
        if(new_time > 60){					 // is time reached the 1 minute mark	
        	level = 2;					// level is switched to level 2
        	level_ = "Level 2";
        	delay = 0.2;					// falling speed increased 
        
        }
         
        //---The Final on Which Everything is Drawn Over is Loaded---//
        window.draw(frame);
        //---The Window that now Contains the Frame is Displayed---//
        
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //// Following code using objects to display text onto the background ///////////////////////////////////////
        //////// Text's font , size ,color , style(bold,underlined) , offset coorindated are set ///////////////////
        Text text,text1;
	Font font;
	if (!font.loadFromFile("vaca.ttf"))
		throw("Could not load font");
	text.setFont(font);
	text.setString("Score");  // stores the string "Score" onto the background object
	text.setCharacterSize(24); 
	text.setFillColor(Color::Red);
	text.setStyle(Text::Bold);
	text.setPosition(230,(window.getSize().y/2) - 30 );
	window.draw(text);
	
	text.setFont(font);
	text.setString(to_string(score));      // stores the current score in te game onto the background object
	text.setCharacterSize(24); 
	text.setFillColor(Color::Yellow);
	text.setStyle(Text::Bold);
	text.setPosition(240,(window.getSize().y/2));
	window.draw(text);
	
	text.setFont(font);
	text.setString(level_);	// stores the current level of the game onto the background object
	text.setCharacterSize(20); 
	text.setFillColor(Color::Yellow);
	text.setStyle(Text::Bold);
	text.setStyle(Text::Underlined);
	text.setPosition(230,(window.getSize().y/2) - 80 );
	window.draw(text);
	
        window.display();
       ////////////////////////////////////////////////////////////////////////////////////
       ////////////////////////////////////////////////////////////////////////////////////
    }
    
    update_highscore(score); // if the window is manually closed highscores are updated in the "score.txt" file
   
    return 0;
}
