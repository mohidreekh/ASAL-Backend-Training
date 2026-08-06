#pragma once
#include <iostream>
using namespace std;

//class MoviePlayer
//{
//public:
//    void watchMovie()
//    {
//        Amplifier amp;
//        DVD dvd;
//        Projector projector;
//        Lights lights;
//        lights.dim();
//        amp.on();
//        projector.start();
//        dvd.play();
//    }
//};

//PROBLEM : Client knows too many subsystem details
// 
//SOLUTION : Using Facade to hide unnecessary details 


class MovieFacade {
public:
    void watch() {
        Amplifier amp;
        DVD dvd;
        Projector projector;
        Lights lights;
        lights.dim();
        amp.on();
        projector.start();
        dvd.play();
    }
};

class MoviePlayer
{
public:

    void watchMovie()
    {
        MovieFacade* watcher = new MovieFacade();
        watcher->watch();
    }
};


