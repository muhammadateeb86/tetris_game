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
#include<iostream>
#include<fstream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
#include <sstream>
using namespace std;
using namespace sf;

int main(){

// Muhammad Ateeb i220888 Sec C

/************/
srand(time(0));   // for random time
/************/
    
 /***************************************************/   
RenderWindow window(VideoMode(500, 480), title);         // Main game window
 /***************************************************/
  
  /**********************/  
    Font bebas;                                           // it is font file used for text in game
    bebas.loadFromFile("Text_file/Bebas-Regular.ttf");   // location of font file
 /************************/
 
 /***********************************************/
 
int level=1;                             // these are levels
int score=0;                             // score to be shown 
int score_count=0;                       // this is used in calculating score according to the formula
int n0_lines_cleared=0;                  // this is for no of lines cleared 
int count_figure=1;                      // this count no of figured fall 
//int highScore=0;//[10]={0};            // high score array
 
 bool bomb=false,pause=false;            // pause the game and bomb is for bomb detection 
 bool hard_drop=false;                   // from making bomb fall instantly     
 bool exit=false;                        // this is when user press exit


 int row_position=0;                         // it is used for calculating the bomb row postiton
 int colunm_position=0;                     // it is used for calculating the bomb colunm postiton
   
  /*************************************************/
  
  
        /**********************************************************/
                 /*###################################*/
    /*
        Load "frames.png","tiles.png" and "background.png" for Texture objects
        */
        
        Texture obj1, obj2, obj3,obj4,obj5,obj6;        // making of texture objects filled with colours
        obj1.loadFromFile("img/tiles.png");
        obj2.loadFromFile("img/background.png");
        obj3.loadFromFile("img/frame.png");
        obj4.loadFromFile("img/ba.png");
        obj5.loadFromFile("img/shadow1.png");
        obj6.loadFromFile("img/tetris.png");
                
        Music music;                                                          // music 
        music.openFromFile("music/Mission-Impossible.ogg");                   // loaction
        music.setPosition(0,1,10);                                            // postioning 
        music.setVolume(50);                                                  // volume
        music.setLoop(true);                                                  // to play continuously
        music.play();                                                         // play
 
  
    Text my_text,my_text1,my_text2;        // Text type objects    
     // score board
    my_text.setFont(bebas);
    my_text.setString("Score Board");
    my_text.setPosition(325,40);
    my_text.setFillColor(Color::Green);
    my_text.setCharacterSize(20);
    // level
    my_text1.setFont(bebas);
    my_text1.setString("Level");
    my_text1.setPosition(325,80);
    my_text1.setFillColor(Color::Green);
    my_text1.setCharacterSize(20);
    // No. of line cleared
    my_text2.setFont(bebas);
    my_text2.setString("Lines Cleared");
    my_text2.setPosition(325,120);
    my_text2.setFillColor(Color::Green);
    my_text2.setCharacterSize(20);

   
                    /*###################################*/
       /**************************************************************/ 
 
 /*********************************************************************************/       
    Sprite sprite(obj1), background(obj2), frame(obj3),back(obj4),ghost(obj5),block(obj6);  // objects that displays everything
 /*********************************************************************************/       
 
 /*****************************************/
    int delta_x=0, colorNum=1;                 // x axis and color values
    float timer=0, delay=0.3;                 // timer for the game and delay
    bool rotate=0,game_over=false;             // rotate and gameover
    Clock clock;                               // its Clock
    float time_lvl=0;                          // game level time 
/****************************************/ 

/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/  
  
    while (window.isOpen()){                                            //******Main Game window*********//
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;
        time_lvl+=time;
        if(time_lvl>=300)
        level=2;                          // increasing level after 5 min 
        //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e)){                    //Event is occurring - until the game is in running state
            if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
                window.close();                            //Opened window disposes
            if (e.type == Event::KeyPressed) {             //If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Up)            //Check if the other key pressed is UP key
                    rotate = true;                         //Rotation gets on
                else if (e.key.code == Keyboard::Left)     //Check if the other key pressed is LEFT key
                    delta_x = -1;                          //Change in X-Axis - Negative
                else if (e.key.code == Keyboard::Right)    //Check if the other key pressed is RIGHT key
                    delta_x = 1;                           //Change in X-Axis - Positive
                else if (e.key.code == Keyboard::P)       // check if paused
                    pause=true; 
                else if (e.key.code == Keyboard::Space)   // check if hard drop 
                hard_drop=true;
            }
        }
                
        /*************************/
        
        if(bomb==false)                                // in case of bomb i want this to be not functional
        if (Keyboard::isKeyPressed(Keyboard::Down))   //Just another way to detect key presses without event listener
            delay=0.05;                               //If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05
       /*************************/     
   
   /*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
                                              
        if(pause==true || game_over==true){                 // new winndow in case paused and game over
        RenderWindow window(VideoMode(300, 200), "Menue");  // menue window
       
       /**********************************************/   // loading for the new menue window
        Text my_text3,my_text4,my_text5,my_text6;
        // display new game
        my_text3.setFont(bebas);
        my_text3.setString("1.Start a new game");
        my_text3.setPosition(100,40);
        my_text3.setFillColor(Color::Blue);
        my_text3.setCharacterSize(20);
        //See high-scores
        my_text4.setFont(bebas);
        my_text4.setString("2.See high-scores");
        my_text4.setPosition(100,80);
        my_text4.setFillColor(Color::Blue);
        my_text4.setCharacterSize(20);
        //Help
        my_text5.setFont(bebas);
        my_text5.setString("3.Help");
        my_text5.setPosition(100,120);
        my_text5.setFillColor(Color::Blue);
        my_text5.setCharacterSize(20);           //text.setCharacterSize(24);
        //Exit
        my_text6.setFont(bebas);
        my_text6.setString("4.Exit");
        my_text6.setPosition(100,160);
        my_text6.setFillColor(Color::Blue);
        my_text6.setCharacterSize(20);
    /**********************************************/
        
    /*###########################################*/

         while (window.isOpen()){
         Event event;
         while (window.pollEvent(event)) {                   //Event is occurring - until the game is in running state
            if (event.type == Event::Closed){                   //If cross/close is clicked/pressed
                window.close();
                pause=false;                                // if we close it previous window
                game_over=false;                            // we reverse values for pasue and game over so that game works again
                break;                             
                }
         /**********************************************/       
           else if (event.key.code == Keyboard::Num1){   // press 1 to start new game
            //if(anamoly)
             for(int i=0;i<M;i++)
             for(int j=0;j<N;j++)
             gameGrid[i][j]=0;
             window.close();
             
             game_over=false; count_figure=1; score=0;  // reseting everything
             pause=false; n0_lines_cleared=0; level=1;
             score_count=0;
             break;
             }
         /**********************************************/
             
            //else if (event.key.code == Keyboard::Num2)
             //high score;
         /**********************************************/
         
         /**********************************************/
           else if (event.key.code == Keyboard::Num3){                   // help window
          
            RenderWindow window(VideoMode(300, 250), "Menue");
            
         /**********************************************/
         Text left,right,down,up,shut;
        // move left
        left.setFont(bebas);                                   // loading for the help window
        left.setString("Press Left Arroy Key: Left");
        left.setPosition(30,20);
        left.setFillColor(Color::Blue);
        left.setCharacterSize(20);
        // move right
        right.setFont(bebas);
        right.setString("Press Right Arroy Key: Right");
        right.setPosition(30,60);
        right.setFillColor(Color::Blue);
        right.setCharacterSize(20);
        // move down
        down.setFont(bebas);
        down.setString("Press Down Arroy Key: Down\n\t\t decrease delay");
        down.setPosition(30,100);
        down.setFillColor(Color::Blue);
        down.setCharacterSize(20);
        // move up
        up.setFont(bebas);
        up.setString("Press Up Arroy Key: Up");
        up.setPosition(30,160);
        up.setFillColor(Color::Blue);
        up.setCharacterSize(20);
        // close
        shut.setFont(bebas);
        shut.setString("Press C Key: Continue");
        shut.setPosition(30,180);
        shut.setFillColor(Color::Blue);
        shut.setCharacterSize(20);
         /**********************************************/
         
         
 /*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/  
          
            while (window.isOpen()){
            Event event;
             while (window.pollEvent(event)) {
               if (event.type == Event::Closed){                   //If cross/close is clicked/pressed
                window.close();
                break;                             
                }
                else if (event.key.code == Keyboard::C)           // press C in help menue to continue
                window.close();
                break;
               }
           /********************************/    
               window.clear(Color::Black);
               window.clear(Color::Black);
               window.draw(left);
               window.draw(right);                 // drawing everything
               window.draw(down);
               window.draw(up);
               window.draw(shut);
               window.display();
          /********************************/         
             }
             break;
            }
             else if (event.key.code == Keyboard::Num4){   //press exit to close complete game
             window.close();
             exit=true;
             break;
             }
               }
         /********************************/        
         window.clear(Color::Black);      
         window.draw(my_text3);
         window.draw(my_text4);                  // drawing everything
         window.draw(my_text5);
         window.draw(my_text6);      
         window.display();
         /********************************/  
         }
          /*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/   // help window exits here         
           
           /*###########################################*/                  // menue events ends
        }
      /*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/  // menue window ends
      
      
        if(exit==true)               // if true then close game window also
        window.close();
        
        ///////////////////////////////////////////////
        ///*** START CALLING YOUR FUNCTIONS HERE ***///
       
       
        if(bomb==false)   // if bomb then no move function
        Move(delta_x);    // move function
        Rotate(rotate);   // rotate function
        if(pause==false && game_over==false)          // if game over & pause is false then falls otherwise not
        fallingPiece(timer, delay,colorNum,bomb,count_figure,row_position,colunm_position);  //Example: fallingPiece() function is called here
        
        line_clearing(n0_lines_cleared,score_count);  // line clearing function
        scoring(score,level,score_count);             // scoring function
        if(bomb==false)                               // if bomb no hard drop
        fall_ins(hard_drop);                          // hard drop function
        Game_Over(game_over);                        // game over function

      
        ///*** YOUR CALLING STATEMENTS END HERE ***///
        //////////////////////////////////////////////

/****************************/
    hard_drop=false;
    delta_x=0;
     delay=0.3;                       //reseting everyting  
     rotate=0; 
     score_count=0;
/****************************/

        window.clear(Color::Black);
        window.draw(background);          // game background
        
        for (int i=0; i<M; i++){
            for (int j=0; j<N; j++){
                 if (gameGrid[i][j]==0)
                  {                                                        // this is done to make the grid lines 
                back.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
                back.setPosition(j*18,i*18);
                back.move(28,31); //offset
                window.draw(back);
                 }
                 else{ 
                sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
                sprite.setPosition(j*18,i*18);
                sprite.move(28,31); //offset
                window.draw(sprite);
              }  
            }
        }
                                               // shadow drawing 
    /*********************************/
    if(bomb==false)                            // dont want to draw shadow of bomb
             for (int i=0; i<4; i++){
            ghost.setTextureRect(IntRect(colorNum*18,0,18,18));
            ghost.setPosition(point_3[i][0]*18,point_3[i][1]*18);
            ghost.move(28,31);
            window.draw(ghost);
          }    
/***************************************/ 

       for (int i=0; i<4; i++){
            sprite.setTextureRect(IntRect(colorNum*18,0,18,18));       // main figures drawing
            sprite.setPosition(point_1[i][0]*18,point_1[i][1]*18);
            sprite.move(28,31);
            window.draw(sprite);
          }
              
            block.setPosition(325,300);  // showing tetris logo
            window.draw(block);  
    
 /******************************************/
          
      //storing high score in the array

/************************************************/      
   
/****************************************************/   // displaying game windows values          
// displaying score
Text text3;
text3.setFont(bebas);
text3.setString(to_string(score));
text3.setPosition(325,60);                            // dispay at the end as these are dynamic values
text3.setCharacterSize(20);  
// displaying lines 
Text text4;
text4.setFont(bebas);
text4.setString(to_string(n0_lines_cleared));
text4.setPosition(325,140);  
text4.setCharacterSize(20);
// displaying level
Text text5;
text5.setFont(bebas);
text5.setString(to_string(level));
text5.setPosition(325,100); 
text5.setCharacterSize(20);
// bomb row positon
Text text6;
text6.setFont(bebas);
text6.setString("Bomb row position");
text6.setPosition(325,160); 
text6.setCharacterSize(20);

Text text7;
text7.setFont(bebas);
text7.setString(to_string(row_position));
text7.setPosition(325,180); 
text7.setCharacterSize(20);

Text text8;
text8.setFont(bebas);
text8.setString("Bomb colunm position");
text8.setPosition(325,200); 
text8.setCharacterSize(20);

Text text9;
text9.setFont(bebas);
text9.setString(to_string(colunm_position));
text9.setPosition(325,220); 
text9.setCharacterSize(20);
/************************************************/

        //---The Final on Which Everything is Drawn Over is Loaded---//
        window.draw(frame);
        /********************/
        window.draw(my_text);
        window.draw(my_text1);     // help window content
        window.draw(my_text2);
        window.draw(text3);
       /*************************/
        window.draw(text4);
        window.draw(text5);
        window.draw(text6);       // game window content
        window.draw(text7);
        window.draw(text8);
        window.draw(text9);
        //---The Window that now Contains the Frame is Displayed---//
        window.display();
        
     
    }
    
   /*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/  // game window exits here
    
    return 0;
}

