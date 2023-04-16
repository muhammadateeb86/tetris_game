/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */

// Muhammad Ateeb i220888 Sec C

/************************************************/
void ghost_rotate(bool rotate);                             //  shadow rotate
void  ghost_move(int delta_x);                              //  these are funtions used in this file
void ghost_piece();                                         // shadow move
void  distruction(bool bomb,int row_position,int colunm_position); // bomb functionality

/**************************************************/
//---Piece Starts to Fall When Game Starts---//

/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
void fallingPiece(float &timer, float &delay,int &colorNum,bool &bomb,int &count_figure,int &row_position,int &colunm_position){
             
    if ((timer>delay)) {   
          ghost_piece();                  // instantly falls down :shadow                
      for (int i=0;i<4;i++){ 
            point_2[i][0]=point_1[i][0];  // saving previous cordinates
            point_2[i][1]=point_1[i][1];
            point_1[i][1]+=1;             //How much units downward
            
           }
       if(bomb==true)
         row_position++;                // calculating that bomb will be in which row

        if (!anamoly()){
        
        if(bomb==false){
        row_position=0;     // incase bomb gone reset values of indixes
        colunm_position=0;
        }
        for (int i=0;i<4;i++)
        gameGrid[point_2[i][1]][point_2[i][0]]=colorNum;  // applying color to the figure
        
       if(bomb==true)                                     // incase bomb implement bomb funtionalities
       distruction(bomb,row_position,colunm_position);
 
        count_figure++  ;                            // increse counter for bomb                                  
        bomb=false;                                 // make bomb false so we can control other blocks      
       colorNum=1+rand()%7;                         // random color
       int n=rand()%7;                              // random shapes                                         
  
  
           if((count_figure%15)==0){                       // bomb will fall after 15 figures 
           n=7;
            bomb=true;                                
          }
            //--- Un-Comment this Part When You Make BLOCKS array---//
           
                for (int i=0;i<4;i++){
                
                    point_1[i][0] = BLOCKS[n][i] % 2;          //chosing figures 
                    point_1[i][1] = BLOCKS[n][i] / 2;
                }
                                              
                 for (int i=0;i<4;i++){
                                                    // this is done for the shadow making purpose
                 point_3[i][0]=point_1[i][0];        // shadow have the same shape
                 point_3[i][1]=point_1[i][1];
                 
                 }
                                 
            if(bomb==true){          // incase bomb 
             int r=rand()%10;       // randow x axis for the bomb before falling
                  colunm_position=r;
                  for (int i=0;i<4;i++)
                  point_1[i][0]+=r;    // x axis for the bomb
                    
        }

      }  
        timer=0;      
    }
}

/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///
/*****************************************************/

void Move(int &delta_x){
for(int i=0;i<4;i++){
            point_2[i][0]=point_1[i][0];
            point_2[i][1]=point_1[i][1];            // implemented the falling logic 
            point_1[i][0]+=delta_x;                 // just altered the x axis according to key pressed left or right
                      
   }
   ghost_move(delta_x);                            // same time ghost movement
   if (!anamoly()){
   for(int i=0;i<4;i++){
   point_1[i][0]=point_2[i][0];                    // anamoly condition
   point_1[i][1]=point_2[i][1];
     }
   }

}
/*************************************************************/  // original figure rotation
void Rotate(bool rotate){

ghost_rotate(rotate);                                            // at the same time shadow roation

if(rotate){
// point_1[1][1] on this position lies the center of rotation 
for(int i=0;i<4;i++){

int centre_x_axis=point_1[i][1]-point_1[1][1]; //  minus the y cordinated of pivot from the y of the block in i row, store in x
int centre_y_axis=point_1[i][0]-point_1[1][0]; //  minus the x cordinated of pivot from the x of the block in i row, store in y

point_1[i][0]=point_1[1][0]-centre_x_axis;    //  minus x from the pivot x cordinate, replace with the x of the block in i row
point_1[i][1]=point_1[1][1]+centre_y_axis;    //  plus y in the pivot y cordinate, replace with the y of the block in i row

         }                       /****with this algebra at the end of loop we get such cordinated which rotate the piece 90 degree****/
         
   if (!anamoly()){
   for(int i=0;i<4;i++){
                                      // anamoly condition
   point_1[i][0]= point_2[i][0];
   point_1[i][1]=point_2[i][1];
     }
   }

}
 
}

/*************************************************************/
// line clearing 
/*************************************************************/

void line_clearing(int &n0_lines_cleared,int &score_count){
int bottom_line=M-1; // as we have 20 rows we start cheking from row 19 and move up if row is not filled 
for(int top_line=M-1;top_line>0;top_line--) // as bottom line is filled we replace it with the top that is unfilled
{
  int count=0;   // it counts the places which are true if all the colunm have blocks its value become 10 and that line is replaced
  
  for(int colunm=0; colunm<N;colunm++){
  
  if(gameGrid[top_line][colunm])
  count++;                                 
  gameGrid[bottom_line][colunm]=gameGrid[top_line][colunm];  // as bottom is filled this command replaces it with top 
  
  }
  
 if (count<N)
 bottom_line--;   //this is the condition that if row is not filled decrement bottom line as we have to chk line on top
 if(count==N){
 n0_lines_cleared++;
 score_count++;    // used in score calculation
 }
 }
} 

/***********************************************************/
  void scoring(int &score,int &level,int &score_count){
  
switch(score_count){
// when 1 line cleared                                 // here score counts equal to no of lines cleared at time
case 1:
score=score+10*level;                                  // level game is level
break;
// when 2 line cleared 
case 2:
score=score+30*level;
break;
// when 3 line cleared 
case 3:
score=score+60*level;
break;
// when 4 line cleared 
case 4:
score=score+100*level;
break;

}

}
/**********************************************************/

 // funciton that halts the game
/**********************************************************/ 
void Game_Over(bool &game_over){  // when game gets over

for(int i=0;i<N;i++)                         
if(gameGrid[1][i]){     // checked that 1st row has any element
   game_over=true;     // if it has then game over
   }  
   
}


/*************************************************/   // hard drop funtion
void fall_ins(bool hard_drop){

if(hard_drop)     // if true key pressed
  while (anamoly()){
    for(int i=0;i<4;i++){
            point_2[i][0]=point_1[i][0];   // implemented the same falling logic
            point_2[i][1]=point_1[i][1];
            point_1[i][1]+=1;             //How much units downward until anamoly
           
           }
          } 
  if (!anamoly()){
   for(int i=0;i<4;i++){
    
   point_1[i][0]= point_2[i][0];           // anamoly condition
   point_1[i][1]=point_2[i][1];
     }
   }
}

/*********************************************/

void ghost_piece(){

    while ((shadow())){                         // concept of hard droping alway on the bottom
    for(int i=0;i<4;i++){
            
           point_4[i][0]=point_3[i][0];         
           point_4[i][1]=point_3[i][1]; 
            
           point_3[i][1]+=1;             //How much units downward until reach anamoly
           
           }
         } 
       if (!shadow()){
   for(int i=0;i<4;i++){
   point_3[i][0]=point_4[i][0];       // anamoly condition
   point_3[i][1]=point_4[i][1];
     }
   }
}
/*************************************************/    // shadow move function

void ghost_move(int delta_x){
   for(int i=0;i<4;i++){
   point_3[i][0]=point_1[i][0];      // copy x axis
   point_3[i][1]=point_1[i][1];      // copy y axis
     }
    ghost_piece();
        if (!shadow()){
for(int i=0;i<4;i++){
         point_3[i][0]=point_4[i][0];   // anamoly condition
         point_3[i][1]=point_4[i][1];
   }
 
}
 
}

/************************************/    // shadow copies the rotation of the origial
void ghost_rotate(bool rotate){

if(rotate){
   for(int i=0;i<4;i++){
   point_3[i][0]=point_1[i][0];       // just copies the points of rotaion  x axis
   point_3[i][1]=point_1[i][1];      // just copies the points of rotaion  y axis
     }
    ghost_piece();                  // call it so that it completesly copy rotaion
        if (!shadow()){              // if anamoly then resists its points
           for(int i=0;i<4;i++){
         point_3[i][0]=point_4[i][0];
         point_3[i][1]=point_4[i][1];
   }
 
}

}
}

/********************************************************************/      // bomb funtionality
void  distruction(bool bomb,int row_position,int colunm_position){

           
          // this checks that if bomb strike another block or below grid
        if ((colunm_position<0 || row_position<0 ||colunm_position>=N || row_position>=M))   // anamoly first condition       
         gameGrid[row_position-1][colunm_position]=0;                                                        // if true then bomb diappears
          else{
        if(gameGrid[row_position-1][colunm_position]==gameGrid[row_position][colunm_position]){ // this checks the color of underneth block
          for(int i=0;i<M;i++)       // everything in grid disappears
           for(int j=0;j<N;j++)
           gameGrid[i][j]=0;
           }
           else{
           // bomb disappears
           gameGrid[row_position-1][colunm_position]=1;
           gameGrid[row_position-1][colunm_position]=0;
          // beneath bomb disappears
           gameGrid[row_position][colunm_position]=0;
          // left one disappears
           gameGrid[row_position][colunm_position-1]=0;
          // right one disappears
           gameGrid[row_position][colunm_position+1]=0;
          // one to right of right disappears
           gameGrid[row_position][colunm_position+2]=0;         
           }
           }
           
        
  
  }
/********************************************************************/
  
///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////



