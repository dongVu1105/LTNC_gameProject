#include <bits/stdc++.h>
#define SDL_MAIN_HANDLED
#include <ctime>
#include <SDL_image.h>
#include "defs.h"
#include "graphics.h"

using namespace std;

Graphics graphics;
const string wordList[] = {"firefox", "rockstar","eyelid", "blackmail",
"brainstorm", "brokenheart", "carwash", "cocktail", "countdown",
"deadline", "fastfood", "firefly", "fullmoon", "honeymoon", "hourglass",
"keyboard", "kidnap", "pineapple", "popcorn", "rainbow", "rainforest",
"redbull", "seafood", "secondhand", "starfish", "sunflower", "waterfall",
"watermelon"};
const int NUM_BUTTOMS = 26;
const int wordListSize = sizeof(wordList) / sizeof(string);
const int maxScore = 3;
const int maxCharacter = 15;

void load_SDL_and_Images();
void unload_SDL_and_Images();
void showGame();
void pause();
void displayStartGame();
string chooseWord();
void printTrue();
void printFalse();
bool playGame(int &userScore, string systemWord);
int computeNumber(int x, int y);
int playerChoose();
int calcCenter(int ans_length);
void printType(string ans);
void printInput(int userScore, string ans, string systemWord);
string inputFromUser(int userScore, string systemWord);
void printQuestion(string systemWord);
void printWordSize(int systemWord_length);
int findIndexOfWord(const string wordList[],const int n, string word);
void printImg(string systemWord);
void printScore(int userScore);
int currentScore(int userScore, bool flag);
bool checkWord(string systemWord, string userWord);
void printLose();
void printOption(int userScore);
void printOptionQuestion(int userScore);
void printInputToPlayAgain(int userScore, string ans);
string inputToPlayAgain(int userScore, string systemWord);
string playAgain(int userScore, string systemWord);
void printWin();
void printGameOver();
void printEndGame(int userScore);

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture *background;
SDL_Texture *exactly, *lose, *not_correct, *suggest, *play_again, *win, *play_continue, *game_over;
SDL_Texture *numberScore[maxScore+1];
SDL_Texture *numberButtoms[NUM_BUTTOMS+1];
SDL_Texture *numberCharacter[maxCharacter+1];
SDL_Texture *numberImg[wordListSize+1];

int main(int argc, char *argv[]){
    load_SDL_and_Images();
    while (1){
        displayStartGame();
        srand(time(0));
        string systemWord = chooseWord();
        int userScore = currentScore(maxScore, true);
        printQuestion(systemWord);
        playGame(userScore, systemWord);
        string option = playAgain(userScore, systemWord);
        if(option == "n"){
            printEndGame(userScore);
            break;
        }
    }
    graphics.waitUntilKeyPressed();
    unload_SDL_and_Images();
    return 0;
}

void displayStartGame() {
    showGame();
}

void printQuestion(string systemWord){
    printWordSize(systemWord.length());
    printImg(systemWord);
}

string chooseWord()
{
	int randomIndex = rand() % wordListSize;
    return wordList[randomIndex];
}

void printFalse(){
    graphics.renderTexture(not_correct, renderer, 463, 200);
    SDL_RenderPresent(renderer);
}

bool playGame(int &userScore, string systemWord){
    string userWord;
    bool flag = false;
    while(1){
        userWord = inputFromUser(userScore, systemWord);
        if (checkWord(systemWord, userWord)){
            flag = true;
            showGame();
            printTrue();
            userScore = currentScore(userScore, flag);
            pause();
            return true;
        } else {
            flag = false;
            showGame();
            printFalse();
            userScore = currentScore(userScore, flag);
            pause();
            if(userScore <= 0){
                showGame();
                printLose();
                userScore = currentScore(userScore, true);
                pause();
                return false;
            }
            printQuestion(systemWord);
            userScore = currentScore(userScore, true);
        }
    }
}

int computeNumber(int x, int y)
{
    int tableX0 = 223, tableY0=481, tableX1=896, tableY1= 591;
    if (x<tableX0 || x>tableX1 || y<tableY0 || y>tableY1) return -1;
    int col = (x-tableX0)*10/(tableX1-tableX0), row=(y-tableY0)*3/(tableY1-tableY0);
    return (row*10 + col + 1);
}

int playerChoose(){
    int number=-1;
    SDL_Event e;
    while (number<=0) {
        SDL_Delay(10);
        if ( SDL_WaitEvent(&e) == 0) continue;
        if ((e.type == SDL_QUIT) || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
            unload_SDL_and_Images();
            exit(1);
        }

        if (e.type == SDL_MOUSEBUTTONDOWN) {
            number = computeNumber(e.button.x, e.button.y);
        }
    }
    return number;
}

int calcCenter(int ans_length) {
    int center = ((SCREEN_WIDTH - ans_length * 48) / 2)-30;
    return center;
}

void printType(string ans){
    int x0=calcCenter(ans.length()), y0=434;
    for(int i=0; i<ans.length();i++){
        char c = ans[i];
        int index = c-'a';
        graphics.renderTexture(numberButtoms[index], renderer, x0+48*(i+1),y0);
        SDL_RenderPresent(renderer);
    }
}

void printInput(int userScore, string ans, string systemWord){
    showGame();
    printQuestion(systemWord);
    currentScore(userScore, true);
    printType(ans);
}

string inputFromUser(int userScore, string systemWord){
    int numberOfButton;
    char button;
    string ans="";
    while (1){
        numberOfButton = playerChoose();
        if(numberOfButton == 29 || numberOfButton == 30){
            break;
        } else if (numberOfButton ==27 || numberOfButton == 28){
            string temp = ans;
            int tempLength = temp.length();
            ans=temp.substr(0, tempLength-1);
            printInput(userScore, ans, systemWord);
        } else {
            button = numberOfButton+96;
            ans+=button;
            printInput(userScore, ans, systemWord);
        }
    }
    return ans;
}

void printWordSize(int systemWord_length){
    graphics.renderTexture(suggest, renderer, 60, 180);
    graphics.renderTexture(numberCharacter[systemWord_length], renderer, 155, 180);
    SDL_RenderPresent(renderer);
}

int findIndexOfWord(const string wordList[],const int n, string word) {
    auto it = find(wordList, wordList + n, word);
    if (it != wordList + n) {
        return distance(wordList, it);
    }
    return -1;
}

void printImg(string systemWord){
    int index = findIndexOfWord(wordList, wordListSize, systemWord);
    graphics.renderTexture(numberImg[index], renderer, 410, 110);
    SDL_RenderPresent(renderer);
}

void printScore(int userScore){
    graphics.renderTexture(numberScore[userScore], renderer, 938, 150);
    SDL_RenderPresent(renderer);
}

int currentScore(int userScore, bool flag){
    if(flag == false){
        userScore-=1;
    }
    printScore(userScore);
    return userScore;
}

void printTrue(){
    graphics.renderTexture(exactly, renderer, 495, 200);
    SDL_RenderPresent(renderer);
}

bool checkWord(string systemWord, string userWord){
    if (userWord == systemWord){
        return true;
    }
    return false;
}

void printLose(){
    graphics.renderTexture(lose, renderer, 438, 200);
    SDL_RenderPresent(renderer);
}

void printOption(int userScore){
    if(userScore<=0){
        graphics.renderTexture(play_again, renderer, 480, 200);
        SDL_RenderPresent(renderer);
    } else {
        graphics.renderTexture(play_continue, renderer, 480, 200);
        SDL_RenderPresent(renderer);
    }

}

void printOptionQuestion(int userScore){
    showGame();
    currentScore(userScore, true);
    printOption(userScore);
}

void printInputToPlayAgain(int userScore, string ans){
    showGame();
    printOption(userScore);
    currentScore(userScore, true);
    printType(ans);
}

string inputToPlayAgain(int userScore, string systemWord){
    int numberOfButton;
    char button;
    string ans="";
    while (1){
        numberOfButton = playerChoose();
        if(numberOfButton == 29 || numberOfButton == 30){
            break;
        } else if (numberOfButton ==27 || numberOfButton == 28){
            ans="";
            printInputToPlayAgain(userScore, ans);
        } else {
            button = numberOfButton+96;
            ans+=button;
            printInputToPlayAgain(userScore, ans);
        }
    }
    return ans;
}

string playAgain(int userScore, string systemWord){
    string option;
    printOptionQuestion(userScore);
    option = inputToPlayAgain(userScore, systemWord);
    return option;
}

void printWin(){
    graphics.renderTexture(win, renderer, 388, 75);
    SDL_RenderPresent(renderer);
}

void printGameOver(){
    graphics.renderTexture(game_over, renderer, 420, 110);
    SDL_RenderPresent(renderer);
}


void printEndGame(int userScore){
    showGame();
    currentScore(userScore, true);
    if(userScore>0){
        printWin();
    } else{
        printGameOver();
    }
}

void showGame()
{
    SDL_RenderClear(renderer);
    graphics.renderTexture(background, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderPresent(renderer);
}

void pause()
{
    int delayTime = 1600;
    do {
        SDL_Delay(10);
        delayTime-= 10;
    } while (delayTime > 0);
}

void unload_SDL_and_Images()
{
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(exactly);
    SDL_DestroyTexture(lose);
    SDL_DestroyTexture(not_correct);
    SDL_DestroyTexture(suggest);
    SDL_DestroyTexture(play_again);
    SDL_DestroyTexture(win);
    SDL_DestroyTexture(play_continue);
    SDL_DestroyTexture(game_over);
    for (int i=0; i<NUM_BUTTOMS; i++) {
        SDL_DestroyTexture(numberButtoms[i]);
    }
    for (int i=0; i<maxScore; i++) {
        SDL_DestroyTexture(numberScore[i]);
    }
    for (int i=0; i<maxCharacter; i++) {
        SDL_DestroyTexture(numberCharacter[i]);
    }
    for (int i=0; i<maxCharacter; i++) {
        SDL_DestroyTexture(numberImg[i]);
    }
    graphics.quitSDL(window, renderer);
}

void load_SDL_and_Images()
{
    graphics.initSDL(window, renderer);

    background = graphics.loadTexture("images/background.png", renderer);
    exactly = graphics.loadTexture("images/exactly.png", renderer);
    lose = graphics.loadTexture("images/lose.png", renderer);
    not_correct = graphics.loadTexture("images/not_correct.png", renderer);
    suggest = graphics.loadTexture("images/suggest.png", renderer);
    play_again = graphics.loadTexture("images/play_again.png", renderer);
    play_continue = graphics.loadTexture("images/play_continue.png", renderer);
    win = graphics.loadTexture("images/win.png", renderer);
    game_over = graphics.loadTexture("images/game_over.png", renderer);
    bool is_load_buttom_failed = false;
    bool is_load_score_failed = false;
    bool is_load_character_failed = false;
    bool is_load_questionImg_failed = false;
    for (int i=0; i<NUM_BUTTOMS; i++) {
        string character = "";
        character+=char(i+65);
        string filename = "images/" + character + ".png";
        const char* filename_cstr = filename.c_str();
        numberButtoms[i] = graphics.loadTexture(filename_cstr, renderer);
        if (numberButtoms[i] == nullptr) {
            is_load_buttom_failed = true;
            break;
        }
    }
    for (int i=0; i<=maxScore; i++) {
        string filename = "images/" +to_string(i*10) + ".png";
        const char* filename_cstr = filename.c_str();
        numberScore[i] = graphics.loadTexture(filename_cstr, renderer);
        if (numberScore[i] == nullptr) {
            is_load_score_failed = true;
            break;
        }
    }
    for (int i=2; i<=maxCharacter; i++) {
        string filename = "images/s" +to_string(i) + ".png";
        const char* filename_cstr = filename.c_str();
        numberCharacter[i] = graphics.loadTexture(filename_cstr, renderer);
        if (numberCharacter[i] == nullptr) {
            is_load_character_failed = true;
            break;
        }
    }
    for (int i=0; i<wordListSize; i++) {
        string filename = "images/" +wordList[i] + ".png";
        const char* filename_cstr = filename.c_str();
        numberImg[i] = graphics.loadTexture(filename_cstr, renderer);
        if (numberImg[i] == nullptr) {
            is_load_questionImg_failed = true;
            break;
        }
    }
    if (background == nullptr  || exactly == nullptr || lose == nullptr
        || not_correct == nullptr  || suggest == nullptr || play_again == nullptr
        || win == nullptr || play_continue == nullptr || game_over == nullptr ||
        is_load_buttom_failed || is_load_character_failed || is_load_score_failed ||
        is_load_questionImg_failed){
        unload_SDL_and_Images();
        exit(1);
    }
}


