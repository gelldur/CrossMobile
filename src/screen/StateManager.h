//
// Created by Dawid Drozd aka Gelldur on 5/24/16.
//

#pragma once

class Screen;

namespace StateManager
{

bool onEnter(Screen* screen);

bool onExit(Screen* screen);

bool onCreate(Screen* screen);

bool onResume(Screen* screen);
bool willResume(Screen* screen);

bool onPause(Screen* screen);

bool onDestroy(Screen* screen);

}


