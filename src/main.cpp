#include <ncurses.h>
#include "Train.h"
#include <format>
#include <iostream>
#include <print>
#include <curses.h>
#include <signal.h>
#include <unistd.h>
#include <args.hxx>
#include "consts.h"
#include <cstring>
#include <string>
#include <random>
#include "prompts.h"
/*
Basic structure:
    The train is drawn using a for loop which loops through reverse of x.
        The reason for that is to make the train go towards the LEFT side of the screen. Since x-1 is going towards the left If we are
        Starting at the most highest COL in the terminal.

*/

constexpr int TRAIN_TRACKS_HEIGHT = 1;
constexpr int MESSAGE_HEIGHT = 7;
int main(int argc, char** argv){
    std::random_device rd;  // Hardware entropy source
    std::mt19937 gen(rd()); // Seed the engine once
    std::uniform_int_distribution<int> swi(0, 5);
    std::uniform_int_distribution<int> swi_rare(0, 100);

    if (swi_rare(gen) == swi_rare(gen)){
        system("ls"); // idk how much chance this has tbh?
        return 0;
    }

    args::ArgumentParser parser("Train animation in terminal using ncurses", "Sometimes may print current directory. Who knows?");
    args::ValueFlag<int> speedArg(parser, "speed", "Speed of the train animation. Lower is faster. Default is 2", {'s', "speed"}, 2);
    args::ValueFlag<int> offsetArg(parser, "offset", "Offset of each cart. Default is 0", {'w', "offset"}, 0);
    args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
    args::ValueFlag<int> framespeedArg(parser, "framespeed", "Time spent between each frame (in microseconds). Default is 20000", {'f', "framespeed"}, 20000);
    
    args::Flag loopArg(parser, "loop", "Loop forever?", {'l', "loop"});
    args::Flag adjustableArg(parser, "adjust", "Adjust to live terminal size?", {'a', "adjust"});
    args::Flag eraseArg(parser, "erase", "Erase terminal? Recommended to use with [adjust]", {'e', "erase"});
    args::Flag signalArg(parser, "signal", "Disable default-behaviour 'Ignore INT signal' Not recommended!", {'i', "signal"});
    args::Flag trainArg(parser, "traintracks", "Disable default-behaviour 'Show train tracks'",{'t', "traintracks"} );
    args::Flag drawArg(parser, "drawextended", "Draw extended train?",{'d', "drawextended"} );

    args::ValueFlag loopforArg(parser, "loopfor", "Loop until. Default is 0", {'u', "loopfor"}, 0);
    
    try {
        parser.ParseCLI(argc, argv);
    }
    catch (args::Help) {
        std::cout << parser;
        return 0;
    }
    catch (args::ParseError e) {
        std::cerr << "Invalid flag: " << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }
    catch (args::ValidationError e) {
        std::cerr <<"Invalid value: " << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }




    initscr();
    if (!signalArg.Get()){
        signal(SIGINT, SIG_IGN);
    }
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    leaveok(stdscr, TRUE);
    scrollok(stdscr, FALSE);

    int i = 0;
    
    Layout func;
    TerminalSize curSize {
        .line = LINES,
        .col = COLS
    };
        

    if (curSize < TerminalSize{
        .line=LOGOHEIGHT + TRAIN_TRACKS_HEIGHT + MESSAGE_HEIGHT,
        .col=LOGOLENGTH 
    }) {
        endwin();
        std::cerr << "Error: " << std::format("Terminal size too small. Minimum size is {}x{}", LOGOLENGTH, LOGOHEIGHT + TRAIN_TRACKS_HEIGHT + MESSAGE_HEIGHT);
        return 1;
    }
    auto longest = std::max_element(
        healthy_messages.begin(),
        healthy_messages.end(),
        [](const char* a, const char* b) {
            return strlen(a) < strlen(b);
        }
    );
    func.getXPos = [&]() {
        if (adjustableArg.Get()){
            return COLS;
        }
        return curSize.col;
    };
    func.getYPos = [&]() {
        if (adjustableArg.Get()){
            return  LINES;
        }
        return curSize.line;
    };
    TrainParameters params = TrainParameters::NON;
    Train t(func, params);
    TrainDrawingInformation info {
        .wheels_speed = speedArg.Get(),
        .tile_drawing_offset = offsetArg.Get(),
    };

    int speed = framespeedArg.Get();
    int time_spent = 0;

    std::uniform_int_distribution<int> dist(0, healthy_messages.size() - 1);

    do {

        info.draw_tracks = !(trainArg.Get() || (swi(gen) == swi(gen)));
        info.draw_extended = drawArg.Get() || swi(gen) == swi(gen);
        int index = dist(gen);
        while (true){
            if (t.Draw(i,std::format("Train number: {}\n{}",time_spent+1, healthy_messages[index]).c_str(), info) == ERR) {i=0;break;};
            refresh();
            getch();
            usleep(speed);
            if (eraseArg.Get()){
                erase();
            }

            i++;
        }
        time_spent++;
    }
    while (loopArg.Get() || (time_spent < loopforArg.Get()));

    endwin();
}