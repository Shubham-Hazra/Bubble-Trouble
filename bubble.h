#include <simplecpp>

/* Bubble Vars */
const int BUBBLE_START_X = 250;
const int BUBBLE_START_Y = 50;
const int BUBBLE_DEFAULT_RADIUS = 10;
const int BUBBLE_RADIUS_THRESHOLD = 10;
const int BUBBLE_DEFAULT_VX = 100;
const int BUBBLE_DEFAULT_VY = 0;
const int g = 1.25;

class Bubble
{
private:
    Circle circle;  // the circle representing the bubble
    double vx, vy;  // velocity in x and y direction
    Color color;    // color of the bubble

public:
    Bubble(double cx, double cy, double r, double vx_=BUBBLE_DEFAULT_VX, double vy_=BUBBLE_DEFAULT_VY, Color color_=COLOR(0, 0, 255))
    {
        // Bubble constructor
        color = color_;
        circle = Circle(cx, cy, r);
        circle.setColor(color);
        circle.setFill(true);

        vx = vx_;
        vy = vy_;
    }

    void nextStep(double t)
    {
        // move the bubble
        double new_x = circle.getX() + vx*t;
        double new_y = circle.getY() + vy*t;

        if ((vx < 0 && new_x < (0 + circle.getRadius())) // bounce along X direction at left border
            ||
            (vx > 0 && new_x > (WINDOW_X - circle.getRadius()))) // bounce along X direction at right border
        {

            vx = -vx;
            new_x = circle.getX() + vx*t;

        }
        if ((vy > 0 && new_y > (450 - circle.getRadius()))      // bounce along Y direction at play height
             ||(vy < 0 && new_y < (0 + circle.getRadius())))    // bounce along Y direction at top border
        {
          vy=-vy;
          new_y = circle.getY() + vy*t;
        }
        vy+=g;

        circle.moveTo(new_x, new_y);
    }

    double get_radius()
    {
        // return the radius of the bubble
        return circle.getRadius();
    }

    double get_center_x()
    {
        // return the x coordinate of the center of the bubble
        return circle.getX();
    }

    double get_center_y()
    {
        // return the y coordinate of the center of the bubble
        return circle.getY();
    }

    double get_vx()
    {
        // return the x velocity of the bubble
        return vx;
    }
    double get_vy()
    {
        // return the y velocity of the bubble
        return vy;
    }

    Color get_color()
    {
        // return the color of the bubble
        return color;
    }
        // To change the color of the bubble
    void change_color(int n)
    {
      if(n==1)
      {
        Color color1=COLOR(255, 0, 0);
        color = color1;
        circle.setColor(color);
        circle.setFill(true);
      }
      if(n==2)
      {
        Color color1=COLOR(0, 255, 0);
        color = color1;
        circle.setColor(color);
        circle.setFill(true);
      }
      if(n==3)
      {
        Color color1=COLOR(0, 0, 255);
        color = color1;
        circle.setColor(color);
        circle.setFill(true);
      }
      if(n==4)
      {
        Color color1=COLOR(255,105,180);
        color = color1;
        circle.setColor(color);
        circle.setFill(true);
      }
      if(n==5)
      {
        Color color1=COLOR(204,51,255);
        color = color1;
        circle.setColor(color);
        circle.setFill(true);
      }
      if(n==6)
      {
        Color color1=COLOR(255,153,0);
        color = color1;
        circle.setColor(color);
        circle.setFill(true);
      }

    }
        // To remove or delete the bubble
    void del()
    {
      circle.moveTo(-10000, -10000);
    }
};
