
int Front;

float WhichFrontAndDistance(float angle){
    if (angle < 0){     // RIGHT TURN
        if (angle > -30){                 // angle btw -30 and 0
            Front = 16;
            return (-angle*2/30);
        } else if (angle > -65){          // angle btw -65 and -30
            Front = 20;
            return (-angle*2/65);
        } else {                          // angle above -65
            Front = 24;
            return ((-angle)-65)/8.4;
        }
    } else {            // LEFT TURN
        if (angle < 20){
            Front = 8;
            return (angle/11);
        } else if (angle < 40){
            Front = 2;
            return (angle/40);
        } else {
            Front = 0;
            return (angle-40.5)/16.5;
        }
    }
}
