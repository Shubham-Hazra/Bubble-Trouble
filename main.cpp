#include <simplecpp>
#include "shooter.h"
#include "bubble.h"
#include <vector>
#include <string>

/* Simulation Vars */
const double STEP_TIME = 0.02;

/* Game Vars */
const int PLAY_Y_HEIGHT = 450;
const int LEFT_MARGIN = 70;
const int TOP_MARGIN = 20;
const int BOTTOM_MARGIN = (PLAY_Y_HEIGHT+TOP_MARGIN);
int life = 3;          // Declaring variables
int time = 0;          // which keep track of
int level = 1;         // lives , time
int score = 0;         // level and score respectively
int level1 = 0;        // declaring level1 which acts as a progression check in the game


void bubble_split(vector<Bubble> &bubbles,int i,double factor);                      // Prototype of the bubble_split function

bool b_b_collision(int i,int j,vector<Bubble> &bubbles,vector<Bullet> &bullets);     // Prototype of the b_b_collision function

bool b_s_collision(int i,vector<Bubble> &bubbles,Shooter &shooter);                  // Prototype of the b_s_collision function

void move_bullets(vector<Bullet> &bullets){
    // move all bullets
    for(unsigned int i=0; i<bullets.size(); i++){
        if(!bullets[i].nextStep(STEP_TIME)){
            bullets.erase(bullets.begin()+i);
        }
    }
}

void move_bubbles(vector<Bubble> &bubbles){
    // move all bubbles
    for (unsigned int i=0; i < bubbles.size(); i++)
    {
        bubbles[i].nextStep(STEP_TIME);
    }
}

vector<Bubble> create_bubbles()
{
    // create initial bubbles in the game
    vector<Bubble> bubbles;
    bubbles.push_back(Bubble(WINDOW_X/2.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS, -BUBBLE_DEFAULT_VX, 30, COLOR(255,105,180)));  //changed vy
    bubbles.push_back(Bubble(WINDOW_X/4.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS, BUBBLE_DEFAULT_VX, 30, COLOR(255,105,180)));   //from 0 to 30
    return bubbles;
}


int main()
{
    initCanvas("Bubble Trouble", WINDOW_X, WINDOW_Y);

    Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
    b1.setColor(COLOR(0, 0, 255));

    string msg_cmd("Cmd: _");
    Text charPressed(LEFT_MARGIN, BOTTOM_MARGIN, msg_cmd);

    // Intialize the shooter
    Shooter shooter(SHOOTER_START_X, SHOOTER_START_Y, SHOOTER_VX);

    // Initialize the bubbles
    vector<Bubble> bubbles = create_bubbles();

    // Initialize the bullets (empty)
    vector<Bullet> bullets;

    // Initializing all the text outputs
    string msg_cmd1("LEVEL:  /3");
    Text t1(250,470, msg_cmd1);
    string msg_cmd2("SCORE:   ");
    Text t2(430,470, msg_cmd2);
    string msg_cmd3("TIME:  /60");
    Text t3(50, 30, msg_cmd3);
    string msg_cmd4("LIVES: 3/3");
    Text t4(430,30, msg_cmd4);



    XEvent event;

    // Main game loop
    while (true)
    {
      if(level1==0)          // Displaying Level 1 at the start of the game
      {
        level1++;
        Text t(250,250,"LEVEL 1!");
        t.setColor(COLOR(0,0,255));
        Rectangle r(250,250,textWidth("LEVEL 1!")+6,textHeight()+6);
        r.setColor(COLOR("red"));
        wait(2);
        continue;
      }

      if(level1==2)          // Creating Bubbles for level 2
      {
        bubbles.push_back(Bubble(WINDOW_X/4.0, BUBBLE_START_Y, 2*BUBBLE_DEFAULT_RADIUS, -1.5*BUBBLE_DEFAULT_VX, 30, COLOR(204,51,255)));
        bubbles.push_back(Bubble(2*WINDOW_X/4.0, BUBBLE_START_Y, 2*BUBBLE_DEFAULT_RADIUS, 1.75*BUBBLE_DEFAULT_VX, 40, COLOR(204,51,255)));
        bubbles.push_back(Bubble(3*WINDOW_X/4.0, BUBBLE_START_Y, 2*BUBBLE_DEFAULT_RADIUS, 1.25*BUBBLE_DEFAULT_VX, 30, COLOR(204,51,255)));
        level1++;
      }
      else if(level1==4)     // Creating Bubbles for level 3
      {
        bubbles.push_back(Bubble(WINDOW_X/4.0, BUBBLE_START_Y, 3*BUBBLE_DEFAULT_RADIUS, -1.25*BUBBLE_DEFAULT_VX, 30, COLOR(255,153,0)));
        bubbles.push_back(Bubble(2*WINDOW_X/4.0, BUBBLE_START_Y, 3*BUBBLE_DEFAULT_RADIUS, 2*BUBBLE_DEFAULT_VX, 50, COLOR(255,153,0)));
        bubbles.push_back(Bubble(3*WINDOW_X/4.0, BUBBLE_START_Y, 3*BUBBLE_DEFAULT_RADIUS, 1.5*BUBBLE_DEFAULT_VX, 40, COLOR(255,153,0)));
        level1++;
      }


      bool pendingEvent = checkEvent(event);
      if (pendingEvent)
      {
        // Get the key pressed
        char c = charFromEvent(event);
        msg_cmd[msg_cmd.length() - 1] = c;
        charPressed.setMessage(msg_cmd);

        // Update the shooter
        if(c == 'a')
            shooter.move(STEP_TIME, true);
        else if(c == 'd')
            shooter.move(STEP_TIME, false);
        else if(c == 'w'&& bullets.size()<5)              // Only allowing 5 bullets on screen together
            bullets.push_back(shooter.shoot());
        else if(c == 'q')
            return 0;

      }

      // Updating the time
      {
        stringstream ss3;
        ss3<<(time/35);
        string s3;
        ss3>>s3;
        if(time>349)
        {
          msg_cmd3[msg_cmd3.length() - 5] = s3[0];
          msg_cmd3[msg_cmd3.length() - 4] = s3[1];
          t3.setMessage(msg_cmd3);
        }
        else
        {
          msg_cmd3[msg_cmd3.length() - 4] = s3[0];
          t3.setMessage(msg_cmd3);
        }
         time++;
      }

      // Setting the level

      {
        stringstream ss1;
        ss1<<level;
        string s1;
        ss1>>s1;
        msg_cmd1[msg_cmd1.length() - 3] = s1[0];
        t1.setMessage(msg_cmd1);
      }




        // Update the bubbles
        move_bubbles(bubbles);

        // Update the bullets
        move_bullets(bullets);

        // Checking for bubble and bullet collisions

        for (unsigned int i=0; i < bubbles.size(); i++)
        {
           for (unsigned int j=0; j < bullets.size(); j++)
           {
              if(b_b_collision(i,j,bubbles,bullets))
              {
                 // Changing colors rapidly
                 for(int k=0;k<2;k++)
                 {
                   bubbles[i].change_color(2);
                   wait(0.02);
                   bubbles[i].change_color(3);
                   wait(0.02);
                 }

                 bullets[j].del();                     // Deleting bullet
                 bullets.erase(bullets.begin()+j);     // Removing bullet from vector

                 // Checking for the type of bubble(size)

                 if(bubbles[i].get_radius()==10)
                 {
                   bubbles[i].del();                   // Deleting Bubble
                   bubbles.erase(bubbles.begin()+i);   // Removing bubble from vector
                   score+=3;
                 }
                 else if(bubbles[i].get_radius()==20)
                 {
                   bubbles[i].change_color(4);
                   bubble_split(bubbles,i,2.0);        // Splitting larger bubble
                   score+=5;                           // Updating score variable
                 }
                 else if(bubbles[i].get_radius()==30)
                 {
                   bubbles[i].change_color(5);
                   bubble_split(bubbles,i,1.5);        // Splitting larger bubble
                   score+=7;                           // Updating score variable
                 }


                 // Setting the score

                 {
                 stringstream ss2;
                 ss2<<score;
                 string s2;
                 ss2>>s2;
                 if(score>100)
                 {
                   msg_cmd2[msg_cmd2.length() - 3] = s2[0];
                   msg_cmd2[msg_cmd2.length() - 2] = s2[1];
                   msg_cmd2[msg_cmd2.length() - 1] = s2[2];
                   t2.setMessage(msg_cmd2);
                 }
                 else if(score>10)
                 {
                   msg_cmd2[msg_cmd2.length() - 2] = s2[0];
                   msg_cmd2[msg_cmd2.length() - 1] = s2[1];
                   t2.setMessage(msg_cmd2);
                 }
                 else
                 {
                    msg_cmd2[msg_cmd2.length() - 2] = s2[0];
                    t2.setMessage(msg_cmd2);
                 }
                 }
              }
           }

        }

        // Checking for bubble and shooter collisions

        for (unsigned int i=0; i < bubbles.size(); i++)
        {
           if(b_s_collision(i,bubbles,shooter))
              {
                while(b_s_collision(i,bubbles,shooter))
                {
                  shooter.change_color(2);                         // Changing the color of shooter
                  move_bubbles(bubbles);                           // While the bubble passes through
                  b_s_collision(i,bubbles,shooter);

                  // Checking for movements during bubble and shooter collision but not allowing shooting bullets

                  pendingEvent = checkEvent(event);
                  if (pendingEvent)
                  {
                      // Get the key pressed
                      char c = charFromEvent(event);
                      msg_cmd[msg_cmd.length() - 1] = c;
                      charPressed.setMessage(msg_cmd);

                     // Update the shooter
                     if(c == 'a')
                     shooter.move(STEP_TIME, true);
                     else if(c == 'd')
                     shooter.move(STEP_TIME, false);
                     else if(c == 'q')
                     return 0;

                  }
                  wait(STEP_TIME/2.0);
                }

                 shooter.change_color(1);
                 life--;                                // Updating life variable

                 // Setting the lives
                 {
                 stringstream ss4;
                 ss4<<life;
                 string s4;
                 ss4>>s4;
                 msg_cmd4[msg_cmd4.length() - 3] = s4[0];
                 t4.setMessage(msg_cmd4);
                 }
              }
        }

            // Checking for 0 bubbles and level and displaying appropriate messages

            if(bubbles.size()==0)
            {
              if(level1==1)
              {
                level++;
                level1++;

                // Deleting all the bullets after a level

                for (unsigned int j=0; j < bullets.size(); j++)
                {
                  bullets[j].del();
                }
                bullets.clear();

                Text t(250,250,"LEVEL 2!");
                t.setColor(COLOR(0,0,255));
                Rectangle r(250,250,textWidth("LEVEL 2!")+6,textHeight()+6);
                r.setColor(COLOR("red"));
                wait(2);
                continue;
              }
              else if(level1==3)
              {
                level++;
                level1++;

                // Deleting all the bullets after a level

                for (unsigned int j=0; j < bullets.size(); j++)
                {
                  bullets[j].del();
                }
                bullets.clear();

                Text t(250,250,"LEVEL 3!");
                t.setColor(COLOR(0,0,255));
                Rectangle r(250,250,textWidth("LEVEL 3!")+6,textHeight()+6);
                r.setColor(COLOR("red"));
                wait(2);
                continue;
              }
              else if(level1==5)
              {
                level++;
                level1++;

                // Deleting all the bullets after a level

                for (unsigned int j=0; j < bullets.size(); j++)
                {
                  bullets[j].del();
                }
                bullets.clear();

                Text t(250,250,"YOU WIN!");
                t.setColor(COLOR(0,255,0));
                Rectangle r(250,250,textWidth("YOU WIN!")+6,textHeight()+6);
                r.setColor(COLOR("red"));
                wait(3);
                break;
              }
            }

            // Checking for 0 lives and displaying appropriate message

            if(life<=0)
            {

              Text t1(250,250,"YOU LOSE!");
              t1.setColor(COLOR(255,0,0));
              Rectangle r1(250,250,textWidth("YOU LOSE!")+6,textHeight()+6);
              wait(3);
              break;
            }

        wait(STEP_TIME);

        // Checking for time and ending game and displaying appropriate message if time over

        if(time>2100)
        {
          Text t1(250,230,"TIME UP!");
          Rectangle r1(250,230,textWidth("TIME UP!")+6,textHeight()+6);
          t1.setColor(COLOR(255,0,0));
          Text t2(250,260,"YOU LOSE!");
          t2.setColor(COLOR(255,0,0));
          Rectangle r2(250,260,textWidth("YOU LOSE!")+6,textHeight()+6);
          wait(3);
          break;
        }
    }
}



// Declaring bubble_split function
// which splits larger bubble into two smaller bubbles

void bubble_split(vector<Bubble> &bubbles,int i,double factor)
{
   double a = bubbles[i].get_center_x();
   double b = bubbles[i].get_center_y();
   double r = bubbles[i].get_radius();
   double vx = bubbles[i].get_vx();
   double vy = bubbles[i].get_vy();
   Color col = bubbles[i].get_color();
   bubbles[i].del();
   bubbles.erase(bubbles.begin()+i);
   bubbles.push_back(Bubble(a-r/factor, b, r/factor, -1.5*vx, 1.25*vy, col));
   bubbles.push_back(Bubble(a+r/factor, b, r/factor, 1.5*vx, 1.5*vy, col));
}

// Declaring b_b_collision function
// which detects collision between bubble and bullets

bool b_b_collision(int i,int j,vector<Bubble> &bubbles,vector<Bullet> &bullets)
{
    bool a = bullets[j].get_center_x()<(bubbles[i].get_center_x()+bubbles[i].get_radius()+(bullets[j].get_width()/2));
    bool b = bullets[j].get_center_x()>(bubbles[i].get_center_x()-bubbles[i].get_radius()-(bullets[j].get_width()/2));
    bool c = bullets[j].get_center_y()>(bubbles[i].get_center_y()-bubbles[i].get_radius()-(bullets[j].get_height()/2));
    bool d = bullets[j].get_center_y()<(bubbles[i].get_center_y()+bubbles[i].get_radius()+(bullets[j].get_height ())/2);

    return (a&&b&&c&&d);
}

// Declaring b_s_collision function
// which detects collision between bubble and shooter

bool b_s_collision(int i,vector<Bubble> &bubbles,Shooter &shooter)
{
   bool a = shooter.get_body_center_x()<(bubbles[i].get_center_x()+BUBBLE_DEFAULT_RADIUS+(shooter.get_body_width()/2));
   bool b = shooter.get_body_center_x()>(bubbles[i].get_center_x()-BUBBLE_DEFAULT_RADIUS-(shooter.get_body_width()/2));
   bool c = shooter.get_body_center_y()>(bubbles[i].get_center_y()-BUBBLE_DEFAULT_RADIUS-(shooter.get_body_height()/2));
   bool d = shooter.get_body_center_y()<(bubbles[i].get_center_y()+BUBBLE_DEFAULT_RADIUS+(shooter.get_body_height())/2);
   bool k = shooter.get_head_center_x()<(bubbles[i].get_center_x()+BUBBLE_DEFAULT_RADIUS+(shooter.get_head_radius()));
   bool l = shooter.get_head_center_x()>(bubbles[i].get_center_x()-BUBBLE_DEFAULT_RADIUS-(shooter.get_head_radius()));
   bool m = shooter.get_head_center_y()>(bubbles[i].get_center_y()-BUBBLE_DEFAULT_RADIUS-(shooter.get_head_radius()));
   bool n = shooter.get_head_center_y()<(bubbles[i].get_center_y()+BUBBLE_DEFAULT_RADIUS+(shooter.get_head_radius()));

   return (a&&b&&c&&d)||(k&&l&&m&&n) ;
}
