/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */

//---Piece Starts to Fall When Game Starts---//

// Affan Ahmad          22i-0916               Project

#include<iostream>
#include<string>
#include<fstream>
using namespace std;
void fallingPiece(float& timer, float& delay,int& colorNum){
 
    if (timer>delay){
   
    		
    	for (int i=0;i<4;i++){
            point_2[i][0]=point_1[i][0];
            point_2[i][1]=point_1[i][1];
            point_1[i][1]+=1;                   //How much units downward
        }
        if (!anamoly()){
            for(int i=0;i<4;i++)
            	gameGrid[point_2[i][1]][point_2[i][0]] = colorNum;
            	colorNum = 1 + rand()%7;
            int n=rand()%7;
            //--- Un-Comment this Part When You Make BLOCKS array---//
            
                for (int i=0;i<4;i++){
                    point_1[i][0] = BLOCKS[n][i] % 2;
                    point_1[i][1] = BLOCKS[n][i] / 2;
                }
                
            }
        
        timer=0;
        }
  }
 




/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///


void horizontal_movements_left()
{
	
	
	for (int i=0;i<4;i++)   // loop runs for every single sqaure for the piece stored in point_1 array
	{
	 	point_2[i][0]=point_1[i][0];   //x and y coordinates of point_1 array are copied to point_2 like usual to store the previous pos 
	 	point_2[i][1]=point_1[i][1];
	 	point_1[i][0] += -1 ; 		// all the sqaures are shifted one units to the left
	}
	 if (!anamoly()) 			// if no anamoly was found meaning no piece went out of border , no piece over wrote any other piece.
	 {
		 for (int i=0;i<4;i++) 	 
		  point_1[i][0]=point_2[i][0];   // the x coordinates for all the pieces are copied back from point_2 array to point_1 array
	 
	 }
	 return;
			
}

void horizontal_movements_right()      // works in the same fashion as the horizontal_movemnets_left function but instead shifts blocks one unit right
{
	
	

	for (int i=0;i<4;i++)  
	{
		point_2[i][0]=point_1[i][0];
		point_2[i][1]=point_1[i][1]; 
		point_1[i][0] += 1 ; 
	}
	if (!anamoly()) 
	{
		 for (int i=0;i<4;i++) 
		 point_1[i][0]=point_2[i][0];
	}
	return;
}


void linebreak (int &score , int level)   // takes score and level as parameters and takes score by reference because the value of score needs to be update if line(s) break
{
	int line_count=0;     // line_count will count the number of subsequent lines broken
	if ( level == 1)
	{	           
		int count = 0;		           // counts the number of pieces filled in a single row
		for(int i = M-1; i>=0; i--)       // runs for every single row in the game grid array expect the row where piece is spawned
		{
		count = 0;                        // piece filled counter will be set to zero for every new row
			for(int j = 0; j < N; j++) // runs for each column in a single row
			{
				if(gameGrid[i][j])  // if anything other than zero is present on the index i.e a piece is present there
				count++;            // counter is incremented
			}
			
			if(count == N)		    // if the counter equal to the coulumn length --> line is filled with blocks and needs to break
			{
				for(int x = i; x>=0; x--)  // for the row where 'count == N' 
				{
					for(int y = 0; y<N; y++) 
					{
						gameGrid[x][y] = gameGrid[x-1][y]; // for each row every single column is shifted 1 unit downwards 	
					}
				}
			line_count++; // if a line breaks line count increments
			}
		}
	}
	
	else if ( level == 2)                       // condition is seperate for level too because in level '2' the last row becomes locked
	{
		int count = 0;		           // counts the number of pieces filled in a single row
		for(int i = M-2; i>=0; i--)       // runs for every single row in the game grid array expect the row where piece is spawned
		{
		count = 0;                        // piece filled counter will be set to zero for every new row
			for(int j = 0; j < N; j++) // runs for each column in a single row
			{
				if(gameGrid[i][j])  // if anything other than zero is present on the index i.e a piece is present there
				count++;            // counter is incremented
			}
			
			if(count == N)		    // if the counter equal to the coulumn length --> line is filled with blocks and needs to break
			{
				for(int x = i; x>=0; x--)  // for the row where 'count == N' 
				{
					for(int y = 0; y<N; y++) 
					{
						gameGrid[x][y] = gameGrid[x-1][y]; // for each row every single column is shifted 1 unit downwards 	
					}
				}
			line_count++; // if a line breaks line count increments
			}
		}
	}
	
	
	
	///////////////////////////////// the part under is just for calculating score/////////////////////////////////////////
	if ( line_count == 1)   // if '1' cosective lines were destroyed 
		score = score + (10*level);  // score is previous score plus ( 10 * level )
	else if ( line_count == 2)
		score = score + (30*level);
	else if ( line_count == 3)
		score = score + (60*level);
	else if ( line_count == 4)
		score = score + (100*level);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

void rotation(bool rotate) // takes bool rotate as parameter
{
	int x,y;  // x and y are delcared
	if (rotate)  
	{
		
		for (int i=0; i<4; i++) 
		{
			x = point_1[i][1] - point_1[2][1]; 		// point of rotation for x axis will be [2][1] i.e X axis will be rotated with respect to Y coordinate 
			y = point_1[i][0] - point_1[2][0];		// point of rotation for y axis will be [2][0] i.e Y axis will be rotated with respect to X coordinate 
			point_1[i][0] = point_1[2][0] + x;            // as we are rotating counter-clockwise the effect of delta x is added to x 
			point_1[i][1] = point_1[2][1] - y;		// and the effect of delta y is subtracted from y for each block in point_1 array
		}
		
		if( !anamoly() )                                      // explained on line 59
		{	
			for (int i=0;i<4;i++)
	       	{
	       		point_1[i][0]=point_2[i][0];
	       		point_1[i][1]=point_2[i][1];
	       	}
		}
		
	}
	rotate = false;  // after 1 complete 90 degree rotation , rotation is turned back to false again
	return;
}


bool top_check ()  // checks if the piece have fallen and eventually reached the very top of gameGrid matrix
{
	for (int i=0 ; i<M ; i++)       // for the number of rows 
	{
		if( gameGrid[1][N]  !=0) // if any index for the column at the very top of the screen that is M=1 is not 0 ,a piece exists on the index ,the function returns true indicating game over
		return true;
	}
	return false; // if the very top line was all clear with all indexes containing value '0' the ftn returns false indicating that game should continue
}


void hard_drop()  // this ftn instantly drops the piece to the very bottom of the grid or above an existing piece if it's present under the piece currently in play
{
	bool continue_fall = true;    
	int  drop_dis = 0;		// calculates the distance required in Y axis for the piece to reach bottom
	
	while( continue_fall )        
	{
		drop_dis++; // drop distace increments with every continue fall statement becoming true
		for (int i =0 ; i<4 ; i++) 
		{
			if (  drop_dis + point_1[i][1] == 20 )   //if the drop distance calculated plus the piece current coordinate in y axis is equal to 20, the piece must exit the loop and must fall right now
			{
				continue_fall = false;    // fall is no longer needed so continue fall becomes false
				break;  // loop breaks as no further calculations are required as we already have the drop distance required
			}
		
			if ( drop_dis + point_1[i][1] < 0 ) // this means the piece had already fallen into place and presing spacebar would have no effect on it
				continue;
			
			else if ( gameGrid[point_1[i][1] + drop_dis][point_1[i][0]] )      // if there is an existing piece bellow the piece in play the loop termiantes aswell 
			{
				continue_fall = false;
				break;
			}
				
		
		}
	}
	
	for (int i=0 ; i<4 ; i++)
	{
			point_1[i][1] += drop_dis - 1; // drop distance is added to the y coordinated of point_1 array hence making it fall down instantly
	}

	return;


}

void gridclear()
{
	for( int i=0 ; i< M ; i++)    // like the line break ftn discussed above the function scans each and every element of gameGrid array and initializes it back to '0' for a game reset
	{
		for(int j =0 ; j< N ; j++)
			gameGrid[i][j] = 0;
	}
	for(int i=0 ; i< 4 ; i++)  // similarly point_1 array coordinates are reseted too before the start of a new game
	{
		point_1[i][0] = 0; 
		point_1[i][1] = 0;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////
// Following code copies the high scores from the "score.txt" files and stores it in the array
// Then it adds the new score obtained by the user to the last index of the array
// The array is then sorted out in order
// After that the scores are written back to the same "score.txt" file opening the file in write mode along with names stored in names[] array
// For every new score reached by the user if it's greater than the lowest score in the file , the new score gets re written over it 

void update_highscore(int score){
	fstream myFile;
	string deli = " ";
	int scores[6];
	int index = 0,temp;
	string temp1;
	myFile.open("scores.txt", ios::in); // read mode to file
	if (myFile.is_open()){
		string line;
		while (getline(myFile,line))
		{
			string name = line.substr(0,line.find(deli));
			string score = line.substr(line.find(deli)+1);
			scores[index] = stoi(score);
			index++;	
		}
		myFile.close();
	}
	string names[6] = {"User1","User2","User3","User4","User5","NewUser"};
	scores[5] = score;
	for(int i = 0; i<6; i++) {
	   for(int j = i+1; j<6; j++)
	   {
	      if(scores[j] > scores[i]) {
		 temp = scores[i];
		 temp1 = names[i];
		 scores[i] = scores[j];
		 names[i] = names[j];
		 scores[j] = temp;
		 names[j] = temp1;
	      }
	   } 
	}
	string write;
	myFile.open("scores.txt", ios::out);
	if (myFile.is_open()){
		for(int i=0; i<5;i++){
			write = names[i] + " " + to_string(scores[i]) + "\n";
			myFile<<write;
		}
		myFile.close(); 
	}
	myFile.open("scores.txt", ios::in); // read mode to file
	if (myFile.is_open()){
		string line;
		while (getline(myFile,line))
		{
			string name = line.substr(0,line.find(deli));
			string score = line.substr(line.find(deli)+1);	
		}
		myFile.close();
	}

}


void grid_shorten () // activates at level 2
{
	for(int i=0 ; i<N ; i++)
		gameGrid[19][i] = 1 ;  // as soon as the game turns to level 2 the very last grid is locked with red color and remains no longer in play
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	


void cast_shadow ()
{
	bool continue_fall = true;
	int  drop_dis = 0;
	
	
	
	drop_dis++;
	while( continue_fall )
	{
		for (int i =0 ; i<4 ; i++)
		{
			if (  drop_dis + point_1[i][1] == 20 )
			{
				continue_fall = false;
				break;
			}
		
			if ( drop_dis + point_1[i][1] < 0 )
				continue;
			
			else if ( gameGrid[point_1[i][1] + drop_dis][point_1[i][0]] )
			{
				continue_fall = false;
				break;
			}
				
		
		}
	}
	
	
	for (int i=0 ; i<4 ; i++)
	{
			point_1[i][1] += drop_dis - 1;
	}

	return;

}





///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////
