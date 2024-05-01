#include <bits/stdc++.h>
#define SDL_MAIN_HANDLED
#include <ctime>
#include <SDL_image.h>

using namespace std;

//******************/
const int NUM_BUTTOMS = 26;
const string wordList[] = {"firefox", "rockstar","eyelid", "blackmail",
"brainstorm", "brokenheart", "carwash", "cocktail", "countdown",
"deadline", "fastfood", "firefly", "fullmoon", "honeymoon", "hourglass",
"keyboard", "kidnap", "pineapple", "popcorn", "rainbow", "rainforest",
"redbull", "seafood", "secondhand", "starfish", "sunflower", "waterfall",
"watermelon"};
const int wordCount = sizeof(wordList) / sizeof(string);
const int maxScore = 3;
const int maxCharacter = 15;

void displayStartGame();
void showGame();
string chooseWord();
void printTrue();
void printFalse();
bool playGame(int &userScore, string systemWord);
int computeNumber(int x, int y);
int playerChoose();
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
void printOption();
void printOptionQuestion(int userScore);
void printInputToPlayAgain(int userScore, string ans);
string inputToPlayAgain(int userScore, string systemWord);
string playAgain(int userScore, string systemWord);
void printWin();
void printVictory(int userScore);

//******************/
const string WINDOW_TITLE = "Catch The Word";
const int SCREEN_WIDTH = 1103;// ;
const int SCREEN_HEIGHT = 631; //;
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture *background;
SDL_Texture *exactly, *lose, *not_correct, *suggest, *play_again, *win, *play_continue;
SDL_Texture *numberScore[maxScore+1];
SDL_Texture *numberButtoms[NUM_BUTTOMS+1];
SDL_Texture *numberCharacter[maxCharacter+1];
SDL_Texture *numberImg[wordCount+1];

void load_SDL_and_Images();
void unload_SDL_and_Images();
void showGame();
void pause();

//************ SDL functions *************/
void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
void waitUntilKeyPressed();
SDL_Texture *loadTexture(const char *filename, SDL_Renderer* renderer);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h);
//***************************************/


int main(){
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
            if(userScore > 0){
                printVictory(userScore);
            }
            break;
        }
    }
    waitUntilKeyPressed();
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
	int randomIndex = rand() % wordCount;
    return wordList[randomIndex];
}

void printFalse(){
    renderTexture(not_correct, renderer, 480, 200);
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
            userScore = currentScore(userScore, true);
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
                userScore = currentScore(userScore, flag);
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
    while (number<=0 || number>30) {
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

void printType(string ans){
    int x0=256, y0=425;
    for(int i=0; i<ans.length();i++){
        char c = ans[i];
        int index = c-'a';
        renderTexture(numberButtoms[index], renderer, x0+48*(i+1),y0);
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
    renderTexture(suggest, renderer, 60, 180);
    renderTexture(numberCharacter[systemWord_length], renderer, 155, 180);
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
    int index = findIndexOfWord(wordList, wordCount, systemWord);
    renderTexture(numberImg[index], renderer, 410, 95);
    SDL_RenderPresent(renderer);
}

void printScore(int userScore){
    renderTexture(numberScore[userScore], renderer, 938, 150);
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
    renderTexture(exactly, renderer, 480, 200);
    SDL_RenderPresent(renderer);
}

bool checkWord(string systemWord, string userWord){
    if (userWord.length() == systemWord.length() && userWord == systemWord){
        return true;
    }
    return false;
}

void printLose(){
    renderTexture(lose, renderer, 438, 200);
    SDL_RenderPresent(renderer);
}

void printOption(int userScore){
    if(userScore<=0){
        renderTexture(play_again, renderer, 480, 200);
        SDL_RenderPresent(renderer);
    } else {
        renderTexture(play_continue, renderer, 480, 200);
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
    renderTexture(win, renderer, 390, 75);
    SDL_RenderPresent(renderer);
}

void printVictory(int userScore){
    showGame();
    currentScore(userScore, true);
    printWin();
}

//****************************************************
void unload_SDL_and_Images()
{
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(exactly);
    SDL_DestroyTexture(lose);
    SDL_DestroyTexture(not_correct);
    SDL_DestroyTexture(suggest);
    SDL_DestroyTexture(play_again);
    SDL_DestroyTexture(win);
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
    quitSDL(window, renderer);
}

void load_SDL_and_Images()
{
    initSDL(window, renderer);

    background = loadTexture("images/background.png", renderer);
    exactly = loadTexture("images/exactly.png", renderer);
    lose = loadTexture("images/lose.png", renderer);
    not_correct = loadTexture("images/not_correct.png", renderer);
    suggest = loadTexture("images/suggest.png", renderer);
    play_again = loadTexture("images/play_again.png", renderer);
    play_continue = loadTexture("images/play_continue.png", renderer);
    win = loadTexture("images/win.png", renderer);
    bool is_load_buttom_failed = false;
    bool is_load_score_failed = false;
    bool is_load_character_failed = false;
    bool is_load_questionImg_failed = false;
    for (int i=0; i<NUM_BUTTOMS; i++) {
        string character = "";
        character+=char(i+65);
        string filename = "images/" + character + ".png";
        const char* filename_cstr = filename.c_str();
        numberButtoms[i] = loadTexture(filename_cstr, renderer);
        if (numberButtoms[i] == nullptr) {
            is_load_buttom_failed = true;
            break;
        }
    }
    for (int i=0; i<=maxScore; i++) {
        string filename = "images/" +to_string(i*10) + ".png";
        const char* filename_cstr = filename.c_str();
        numberScore[i] = loadTexture(filename_cstr, renderer);
        if (numberScore[i] == nullptr) {
            is_load_score_failed = true;
            break;
        }
    }
    for (int i=2; i<=maxCharacter; i++) {
        string filename = "images/s" +to_string(i) + ".png";
        const char* filename_cstr = filename.c_str();
        numberCharacter[i] = loadTexture(filename_cstr, renderer);
        if (numberCharacter[i] == nullptr) {
            is_load_character_failed = true;
            break;
        }
    }
    for (int i=0; i<wordCount; i++) {
        string filename = "images/" +wordList[i] + ".png";
        const char* filename_cstr = filename.c_str();
        numberImg[i] = loadTexture(filename_cstr, renderer);
        if (numberImg[i] == nullptr) {
            is_load_questionImg_failed = true;
            break;
        }
    }
    if (background == nullptr  || exactly == nullptr || lose == nullptr
        || not_correct == nullptr  || suggest == nullptr || play_again == nullptr
        || win == nullptr || is_load_buttom_failed || is_load_character_failed || is_load_score_failed || is_load_questionImg_failed){
        unload_SDL_and_Images();
        exit(1);
    }
}

void showGame()
{
    SDL_RenderClear(renderer);
    renderTexture(background, renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderPresent(renderer);
}

void pause()
{
    int delayTime = 1500;
    do {
        SDL_Delay(10);
        delayTime-= 10;

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if ((e.type == SDL_QUIT) || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)) {
                unload_SDL_and_Images();
                exit(1);
            }
        }
    } while (delayTime > 0);
}










//*****************************************************
// Các hàm chung về khởi tạo và huỷ SDL
void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    //window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
    //   SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true);


    //Khi thông thường chạy với môi trường bình thường ở nhà
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

/**
* Nạp một ảnh bitmap (BMP) vào một texture trên thiết bị hiện thị (rendering device)
* @param file: đường dẫn và tên file ảnh BMP
* @param ren: renderer để nạp texture lên
* @return trả về texture đã nạp, hoặc nullptr nếu có lỗi.
*/
SDL_Texture *loadTexture(const char *filename, SDL_Renderer* renderer)
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
	if (texture == NULL)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

	return texture;
}

/**
* Vẽ một SDL_Texture lên một SDL_Renderer tại toạ độ (x, y), trong khi
* giữ nguyên chiều rộng và cao của ảnh
* @param tex: texture nguồn chúng ta muốn vẽ ra
* @param ren: thiết bị renderer chúng ta muốn vẽ vào
* @param x: hoành độ
* @param y: tung độ
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
	//Thiết lập hình chữ nhật đích mà chúng ta muốn vẽ ảnh vào trong
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	//Truy vẫn texture để lấy chiều rộng và cao (vào chiều rộng và cao tương ứng của hình chữ nhật đích)
	SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    //Đưa toàn bộ ảnh trong texture vào hình chữ nhật đích
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

/**
* Vẽ một SDL_Texture lên một SDL_Renderer tại toạ độ (x, y), với
* chiều rộng và cao mới
* @param tex: texture nguồn chúng ta muốn vẽ ra
* @param ren: thiết bị renderer chúng ta muốn vẽ vào
* @param x: hoành độ
* @param y: tung độ
* @param w: chiều rộng (mới)
* @param h: độ cao (mới)
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
{
	//Thiết lập hình chữ nhật đích mà chúng ta muốn vẽ ảnh vào trong
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
    dst.w = w;
    dst.h = h;
    //Đưa toàn bộ ảnh trong texture vào hình chữ nhật đích
    //(ảnh sẽ co dãn cho khớp với kích cỡ mới)
	SDL_RenderCopy(ren, tex, NULL, &dst);
}
//**************************************************************

