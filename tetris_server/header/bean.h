#pragma once
#include <vector>
#include "ButtonManager.h"
#include "Canvas.h"
#include "Scene.h"
#include "SelectScene.h"
#include "BlockBoard.h"

SelectScene* ModeSelectScene();
SelectScene* SingleModeMeneSelectScene();
ButtonManager* ModeSelectSceneButtonManager(vector<string> names);
Canvas* MainSceneCanvas(); 
//PaintBlockBoard* PaintBlockBoard();
