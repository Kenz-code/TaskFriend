#include <iostream>
#include <SDL.h>
#undef main
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>
#include <string>
#include <Windows.h>
#include <fstream>
#include <Commdlg.h>

#include "Texture.h"
#include "Render.h"
#include "Buttons.h"

bool doTextInput = false;

Texture Test;

Window window;
SDL_Texture* close_x = window.loadFromFilee("Img/closex.png");
SDL_Texture* task_box = window.loadFromFilee("Img/taskbox.png");
SDL_Texture* plus_add = window.loadFromFilee("Img/plus.png");
SDL_Texture* _delete = window.loadFromFilee("Img/delete.png");
SDL_Texture* save = window.loadFromFilee("Img/save.png");
SDL_Texture* load = window.loadFromFilee("Img/load.png");

TTF_Font* font20 = TTF_OpenFont("Font/Ubuntu.ttf", 20);
TTF_Font* font32 = TTF_OpenFont("Font/Ubuntu.ttf", 32);

Mix_Chunk* leftclick_sfx = Mix_LoadWAV("Sfx/Select.wav");
Mix_Chunk* high_leftclick_sfx = Mix_LoadWAV("Sfx/high_select.wav");
Mix_Chunk* rightclick_sfx = Mix_LoadWAV("Sfx/right click.wav");

OPENFILENAME ofn;
char szFile[100];

std::string inputText[4] = { "  ","  ","  ","  " };

std::vector<int> tasks;

SDL_Color GRAY{ 23,23,23 };
SDL_Color BLACK{ 5,5,5 };




//destroys textures
void close() {

	SDL_DestroyTexture(close_x);
	SDL_DestroyTexture(task_box);
	SDL_DestroyTexture(plus_add);
	//Disable text input
	SDL_StopTextInput();

	TTF_CloseFont(font20);
	font20 = NULL;
	TTF_CloseFont(font32);
	font32 = NULL;
}
//savin progress \/
void save_tasks(std::string filename) {
	//saving the data
	std::ofstream out(filename.c_str());
	out << inputText[0];
	out << "^";
	out << inputText[1];
	out << "~";
	out << inputText[2];
	out << "{";
	out << inputText[3];
	out.close();
}

void load_tasks(std::string filename) {
	//load the data
	std::ifstream filee;
	filee.open(filename);
	std::string x;
	int markers[3] = { 0,0,0 };
	getline(filee, x);
	for (int i = 0; i < x.length(); i++) {
		if (x.at(i) == '^')
			markers[0] = i;
		if (x.at(i) == '~')
			markers[1] = i;
		if (x.at(i) == '{')
			markers[2] = i;
	}
	inputText[0] = x.substr(0, markers[0]);
	inputText[1] = x.substr(markers[0] + 1, markers[1] - markers[0]);
	inputText[2] = x.substr(markers[1] + 1, markers[2] - markers[1]);
	inputText[3] = x.substr(markers[2] + 1, x.size() - markers[2]);
	filee.close();

}

//checks if mouse if colliding with a SDL_Rect
bool checkCollisionMouse(SDL_Rect a, int m_x, int m_y)
{
	//checking the collision using a simple if statement
	if (m_x > a.x and m_y > a.y and m_x < a.w and m_y < a.h) {
		return true;
	}

	//return false if not touching.
    return false;
}

//adds task
void addTask() {
	int size = tasks.size();

	if (size >= 4) {
		std::cout << "\nMaximum number of tasks reached!!\n";
		return;
	}
	else {
		tasks.push_back(1);
		return;
	}
}
//deletes task
void deleteTask() {
	int size = tasks.size();

	if (size <= 0) {
		std::cout << "\nMinimum number of tasks reached!!\n";
		return;
	}
	else {
		tasks.pop_back();
		return;
	}
}
//renders task boxes to the screen based on how many ints are in the tasks vector	
void renderTaskBoxes(std::vector<int> v) {
	int size = v.size();
	if (size == 1) {
		window.render(task_box, 77, 90, 256, 144, NULL);
	}
	else if (size == 2) {
		window.render(task_box, 77, 90, 256, 144, NULL);
		window.render(task_box, 367, 90, 256, 144, NULL);
	}
	else if (size == 3) {
		window.render(task_box, 77, 90, 256, 144, NULL);
		window.render(task_box, 367, 90, 256, 144, NULL);
		window.render(task_box, 657, 90, 256, 144, NULL);
	}
	else if (size == 4) {
		window.render(task_box, 77, 90, 256, 144, NULL);
		window.render(task_box, 367, 90, 256, 144, NULL);
		window.render(task_box, 657, 90, 256, 144, NULL);
		window.render(task_box, 947, 90, 256, 144, NULL);
	}
}
//renders text onto boxes based on a int which is 0-3,etc
void renderTextToBox(SDL_Rect* box, int type, std::string text) {
	//sees which rect to do
	if (type == 0) {
		if (text.size() <= 25) {
			window.renderText(83, 117, text.c_str(), font20, GRAY);
		}
		else if (text.size() > 25 and text.size() <= 50) {
			std::string str1 = text.substr(0, 25);
			std::string str2 = text.substr(25, 25);
			window.renderText(83, 117, str1.c_str(), font20, GRAY);
			window.renderText(83, 157, str2.c_str(), font20, GRAY);
		}
		else if (text.size() > 50 and text.size() <= 75) {
			std::string str1 = text.substr(0, 25);
			std::string str2 = text.substr(25, 25);
			std::string str3 = text.substr(50, 25);
			window.renderText(83, 117, str1.c_str(), font20, GRAY);
			window.renderText(83, 157, str2.c_str(), font20, GRAY);
			window.renderText(83, 197, str3.c_str(), font20, GRAY);
		}
		else if (text.size() > 75) {
			std::string str1 = text.substr(0, 25);
			std::string str2 = text.substr(25, 25);
			std::string str3 = text.substr(50, 25);
			window.renderText(83, 117, str1.c_str(), font20, GRAY);
			window.renderText(83, 157, str2.c_str(), font20, GRAY);
			window.renderText(83, 197, str3.c_str(), font20, GRAY);
		}
		
	}
	//sees which rect to do
	if (type == 1) {
		if (text.size() <= 25) {
			window.renderText(373, 117, text.c_str(), font20, GRAY);
		}
		else if (text.size() > 25 and text.size() <= 50) {
			std::string str1 = text.substr(0, 25);
			std::string str2 = text.substr(25, 25);
			window.renderText(373, 117, str1.c_str(), font20, GRAY);
			window.renderText(373, 157, str2.c_str(), font20, GRAY);
		}
		else if (text.size() > 50 and text.size() <= 75) {
			std::string str1 = text.substr(0, 25);
			std::string str2 = text.substr(25, 25);
			std::string str3 = text.substr(50, 25);
			window.renderText(373, 117, str1.c_str(), font20, GRAY);
			window.renderText(373, 157, str2.c_str(), font20, GRAY);
			window.renderText(373, 197, str3.c_str(), font20, GRAY);
		}
		else if (text.size() > 75) {
			std::string str1 = text.substr(0, 25);
			std::string str2 = text.substr(25, 25);
			std::string str3 = text.substr(50, 25);
			window.renderText(373, 117, str1.c_str(), font20, GRAY);
			window.renderText(373, 157, str2.c_str(), font20, GRAY);
			window.renderText(373, 197, str3.c_str(), font20, GRAY);
		}
	}
	//sees which rect to do
	if (type == 2) {
		if (text.size() <= 25) {
			window.renderText(663, 117, text.c_str(), font20, GRAY);
		}
		else if (text.size() > 25 and text.size() <= 50) {
			std::string str1 = text.substr(0, 25);
			std::string str2 = text.substr(25, 25);
			window.renderText(663, 117, str1.c_str(), font20, GRAY);
			window.renderText(663, 157, str2.c_str(), font20, GRAY);
		}
		else if (text.size() > 50 and text.size() <= 75) {
			std::string str1 = text.substr(0, 25);
			std::string str2 = text.substr(25, 25);
			std::string str3 = text.substr(50, 25);
			window.renderText(663, 117, str1.c_str(), font20, GRAY);
			window.renderText(663, 157, str2.c_str(), font20, GRAY);
			window.renderText(663, 197, str3.c_str(), font20, GRAY);
		}
		else if (text.size() > 75) {
			std::string str1 = text.substr(0, 25);
			std::string str2 = text.substr(25, 25);
			std::string str3 = text.substr(50, 25);
			window.renderText(663, 117, str1.c_str(), font20, GRAY);
			window.renderText(663, 157, str2.c_str(), font20, GRAY);
			window.renderText(663, 197, str3.c_str(), font20, GRAY);
		}
	}
	//sees which rect to do
	if (type == 3) {
		if (text.size() <= 25) {
			window.renderText(953, 117, text.c_str(), font20, GRAY);
		}
		else if (text.size() > 25 and text.size() <= 50) {
			std::string str1 = text.substr(0, 25);
			std::string str2 = text.substr(25, 25);
			window.renderText(953, 117, str1.c_str(), font20, GRAY);
			window.renderText(953, 157, str2.c_str(), font20, GRAY);
		}
		else if (text.size() > 50 and text.size() <= 75) {
			std::string str1 = text.substr(0, 25);
			std::string str2 = text.substr(25, 25);
			std::string str3 = text.substr(50, 25);
			window.renderText(953, 117, str1.c_str(), font20, GRAY);
			window.renderText(953, 157, str2.c_str(), font20, GRAY);
			window.renderText(953, 197, str3.c_str(), font20, GRAY);
		}
		else if (text.size() > 75) {
			std::string str1 = text.substr(0, 25);
			std::string str2 = text.substr(25, 25);
			std::string str3 = text.substr(50, 25);
			window.renderText(953, 117, str1.c_str(), font20, GRAY);
			window.renderText(953, 157, str2.c_str(), font20, GRAY);
			window.renderText(953, 197, str3.c_str(), font20, GRAY);
		}
	}
}

std::string doC_B(std::string inputText, SDL_Event e) {
	//Handle backspace
	if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0)
	{
		//lop off character
		inputText.pop_back();
	}
	//Handle copy
	else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
	{
		SDL_SetClipboardText(inputText.c_str());
	}
	//Handle paste
	else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
	{
		inputText = SDL_GetClipboardText();
	}
	return inputText;
}

std::string doKeyboard(std::string inputText, SDL_Event e) {
	//Not copy or pasting
	if (!(SDL_GetModState() & KMOD_CTRL && (e.text.text[0] == 'c' || e.text.text[0] == 'C' || e.text.text[0] == 'v' || e.text.text[0] == 'V')))
	{
		//Append character
		inputText += e.text.text;
	}
	return inputText;
}

std::string mthdTextToBox(std::string inputText, int type) {
	if (type == 0) {
		if (tasks.size() >= 1) {
			renderTextToBox(&btasks0, 0, inputText);
		}
		else {
			inputText = "  ";
		}
	}
	if (type == 1) {
		if (tasks.size() >= 2) {
			renderTextToBox(&btasks1, 1, inputText);
		}
		else {
			inputText = "  ";
		}
	}
	if (type == 2) {
		if (tasks.size() >= 3) {
			renderTextToBox(&btasks1, 2, inputText);
		}
		else {
			inputText = "  ";
		}
	}
	if (type == 3) {
		if (tasks.size() >= 4) {
			renderTextToBox(&btasks1, 3, inputText);
		}
		else {
			inputText = "  ";
		}
	}
	return inputText;
}



int main(int argc, char* argv[]) {
	bool running = true;

	SDL_Event e;

	tasks.push_back(1);
	std::cout << tasks.size();

	//Enable text input
	SDL_StartTextInput();
	//bunch of varibles
	bool doTextForTask[4] = { false,false,false,false };

	while (running) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				running = false;
			}
			if (e.type == SDL_MOUSEBUTTONUP) {
				if (e.button.button == SDL_BUTTON_LEFT) {
					//get mouse state
					int m_x, m_y;
					SDL_GetMouseState(&m_x, &m_y);
					doTextForTask[0] = false;
					doTextForTask[1] = false;
					doTextForTask[2] = false;
					doTextForTask[3] = false;
					//see if they are pressing exit button
					if (checkCollisionMouse(bclose, m_x, m_y) == true) {
						Mix_PlayChannel(-1, high_leftclick_sfx, 0);
						running = false;
					}
					else if (checkCollisionMouse(badd, m_x, m_y) == true) {
						Mix_PlayChannel(-1, high_leftclick_sfx, 0);
						addTask();
					}
					else if (checkCollisionMouse(bsave, m_x, m_y) == true) {
						Mix_PlayChannel(-1, high_leftclick_sfx, 0);
						// open a file name
						ZeroMemory(&ofn, sizeof(ofn));
						ofn.lStructSize = sizeof(ofn);
						ofn.hwndOwner = NULL;
						ofn.lpstrFile = szFile;
						ofn.lpstrFile[0] = '\0';
						ofn.nMaxFile = sizeof(szFile);
						ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
						ofn.nFilterIndex = 1;
						ofn.lpstrFileTitle = NULL;
						ofn.nMaxFileTitle = 0;
						ofn.lpstrInitialDir = NULL;
						ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
						ofn.lpstrTitle = "Save";

						GetOpenFileName(&ofn);

						save_tasks(ofn.lpstrFile);
					}
					else if (checkCollisionMouse(bload, m_x, m_y) == true) {
						Mix_PlayChannel(-1, high_leftclick_sfx, 0);
						// open a file name
						ZeroMemory(&ofn, sizeof(ofn));
						ofn.lStructSize = sizeof(ofn);
						ofn.hwndOwner = NULL;
						ofn.lpstrFile = szFile;
						ofn.lpstrFile[0] = '\0';
						ofn.nMaxFile = sizeof(szFile);
						ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
						ofn.nFilterIndex = 1;
						ofn.lpstrFileTitle = NULL;
						ofn.nMaxFileTitle = 0;
						ofn.lpstrInitialDir = NULL;
						ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
						ofn.lpstrTitle = "Load";

						GetOpenFileName(&ofn);

						load_tasks(ofn.lpstrFile);
					}
					else if (checkCollisionMouse(bdelete, m_x, m_y) == true) {
						Mix_PlayChannel(-1, high_leftclick_sfx, 0);
						deleteTask();
					}
					else if (checkCollisionMouse(btasks0, m_x, m_y) == true and tasks.size() >= 1) {
						Mix_PlayChannel(-1, high_leftclick_sfx, 0);
						doTextForTask[0] = true;
					}
					else if (checkCollisionMouse(btasks1, m_x, m_y) == true and tasks.size() >= 2) {
						Mix_PlayChannel(-1, high_leftclick_sfx, 0);
						doTextForTask[1] = true;
					}
					else if (checkCollisionMouse(btasks2, m_x, m_y) == true and tasks.size() >= 3) {
						Mix_PlayChannel(-1, high_leftclick_sfx, 0);
						doTextForTask[2] = true;
					}
					else if (checkCollisionMouse(btasks3, m_x, m_y) == true and tasks.size() >= 4) {
						Mix_PlayChannel(-1, high_leftclick_sfx, 0);
						doTextForTask[3] = true;
					}
					else { Mix_PlayChannel(-1, leftclick_sfx, 0); }
				}
				else if (e.button.button == SDL_BUTTON_RIGHT) {
					Mix_PlayChannel(-1, rightclick_sfx, 0);
				}
			}

			//Special key input 1
			if (e.type == SDL_KEYDOWN and doTextForTask[0] == true)
			{
				inputText[0] = doC_B(inputText[0], e);
			}
			else if (e.type == SDL_TEXTINPUT and doTextForTask[0] == true)
			{
				inputText[0] = doKeyboard(inputText[0], e);
			}

			//Special key input 2
			if (e.type == SDL_KEYDOWN and doTextForTask[1] == true)
			{
				inputText[1] = doC_B(inputText[1], e);
			}
			else if (e.type == SDL_TEXTINPUT and doTextForTask[1] == true)
			{
				inputText[1] = doKeyboard(inputText[1], e);
			}

			//Special key input 3
			if (e.type == SDL_KEYDOWN and doTextForTask[2] == true)
			{
				inputText[2] = doC_B(inputText[2], e);
			}
			else if (e.type == SDL_TEXTINPUT and doTextForTask[2] == true)
			{
				inputText[2] = doKeyboard(inputText[2], e);
			}

			//Special key input 4
			if (e.type == SDL_KEYDOWN and doTextForTask[3] == true)
			{
				inputText[3] = doC_B(inputText[3], e);
			}
			else if (e.type == SDL_TEXTINPUT and doTextForTask[3] == true)
			{
				inputText[3] = doKeyboard(inputText[3], e);
			}

			
		}
		//clear renderer
		window.clear(&GRAY);
		//renderer textures
		window.render(close_x, 1220, 15, 40, 40, NULL);
		window.render(plus_add, 30, 15, 40, 40, NULL);
		window.render(_delete, 80, 15, 40, 40, NULL);
		window.render(save, 130, 16, 40, 40, NULL);
		window.render(load, 180, 15, 40, 40, NULL);
		renderTaskBoxes(tasks);
		inputText[0] = mthdTextToBox(inputText[0], 0);
		inputText[1] = mthdTextToBox(inputText[1], 1);
		inputText[2] = mthdTextToBox(inputText[2], 2);
		inputText[3] = mthdTextToBox(inputText[3], 3);
		//update renderer
		window.update();
		


	}

	close();

	return 0;
}