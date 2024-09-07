#include "textObject.h"
#include "functions.h"
#include "map"
#include "Board.h"




int main() {

    // get data from config
    vector<int> gameData = readConfigFile("files/config.cfg");

    if (gameData.size() == 0){
        cout << "Program failed to get data from config" << endl;
        return 1;
    }

    int numRows = gameData[1];
    int numCols = gameData[0];
    int numTotalMine = gameData[2];

    // create data for our welcomeWindow
    int height = numRows * 32 + 100;
    int width = numCols * 32;

    // create texture and set position for our buttons
    sf::Texture texture_debug;
    if (!texture_debug.loadFromFile("files/images/debug.png"))
    {
        cout << "Error loading texture." << endl;
    }
    sf::Sprite sprite_debug;
    sprite_debug.setTexture(texture_debug);
    sprite_debug.setPosition(numCols * 32 - 304, 32 * (numRows + 0.5));

    // create texture for each individual digit for the displayer
    map<int, sf::Texture> texture_digits_displayer;
    for (int i = 0; i <= 9; i++){
        sf::Texture texture_digit;
        int start_x = 21 * i;
        int end_x = 21 * (i+1);
        if (!texture_digit.loadFromFile("files/images/digits.png", sf::IntRect(start_x, 0, end_x, 32)))
        {
            cout << "Error loading digit texture." << endl;
        }
        texture_digits_displayer[i] = texture_digit;
    }

    sf::Texture negative_sign;
    if (!negative_sign.loadFromFile("files/images/digits.png", sf::IntRect(210, 0, 231, 32)))
    {
        cout << "Error loading digit texture." << endl;
    }
    texture_digits_displayer['-'] = negative_sign;


    // create sprite for timer
    sf::Sprite sprite_min_tens_digit;
    sprite_min_tens_digit.setTexture(texture_digits_displayer[0]);
    sprite_min_tens_digit.setPosition(numCols * 32 - 97, 32 * (numRows + 0.5) + 16);

    sf::Sprite sprite_min_digit;
    sprite_min_digit.setTexture(texture_digits_displayer[0]);
    sprite_min_digit.setPosition(numCols * 32 - 76, 32 * (numRows + 0.5) + 16);

    sf::Sprite sprite_sec_tens_digit;
    sprite_sec_tens_digit.setTexture(texture_digits_displayer[0]);
    sprite_sec_tens_digit.setPosition(numCols * 32 - 54, 32 * (numRows + 0.5) + 16);

    sf::Sprite sprite_sec_digit;
    sprite_sec_digit.setTexture(texture_digits_displayer[0]);
    sprite_sec_digit.setPosition(numCols * 32 - 33, 32 * (numRows + 0.5) + 16);

    // create sprite for counter

    sf::Sprite sprite_counter_negative_sign;
    sprite_counter_negative_sign.setTexture(texture_digits_displayer['-']);
    sprite_counter_negative_sign.setPosition(12, 32 * (numRows + 0.5) + 16);

    sf::Sprite sprite_counter_hundreds_digit;
    sprite_counter_hundreds_digit.setTexture(texture_digits_displayer[0]);
    sprite_counter_hundreds_digit.setPosition(33, 32 * (numRows + 0.5) + 16);

    sf::Sprite sprite_counter_tens_digit;
    sprite_counter_tens_digit.setTexture(texture_digits_displayer[0]);
    sprite_counter_tens_digit.setPosition(54, 32 * (numRows + 0.5) + 16);

    sf::Sprite sprite_counter_digit;
    sprite_counter_digit.setTexture(texture_digits_displayer[0]);
    sprite_counter_digit.setPosition(75, 32 * (numRows + 0.5) + 16);

    sf::Texture texture_face_happy;
    if (!texture_face_happy.loadFromFile("files/images/face_happy.png"))
    {
        cout << "Error loading texture." << endl;
    }
    sf::Sprite sprite_face;
    sprite_face.setTexture(texture_face_happy);
    sprite_face.setPosition((numCols / 2.0) * 32 - 32, 32 * (numRows + 0.5));

    sf::Texture texture_face_lose;
    if (!texture_face_lose.loadFromFile("files/images/face_lose.png"))
    {
        cout << "Error loading texture." << endl;
    }
    sf::Sprite sprite_face_lose;
    sprite_face_lose.setTexture(texture_face_lose);

    sf::Texture texture_face_win;
    if (!texture_face_win.loadFromFile("files/images/face_win.png"))
    {
        cout << "Error loading texture." << endl;
    }
    sf::Sprite sprite_face_win;
    sprite_face_win.setTexture(texture_face_win);

    sf::Texture texture_flag;
    if (!texture_flag.loadFromFile("files/images/flag.png"))
    {
        cout << "Error loading texture." << endl;
    }
    sf::Sprite sprite_flag;
    sprite_flag.setTexture(texture_flag);

    sf::Texture texture_leaderboard;
    if (!texture_leaderboard.loadFromFile("files/images/leaderboard.png"))
    {
        cout << "Error loading texture." << endl;
    }
    sf::Sprite sprite_leaderboard;
    sprite_leaderboard.setTexture(texture_leaderboard);
    sprite_leaderboard.setPosition(numCols * 32 - 176, 32 * (numRows + 0.5));

    sf::Texture texture_mine;
    if (!texture_mine.loadFromFile("files/images/mine.png"))
    {
        cout << "Error loading texture." << endl;
    }

    sf::Texture texture_pause;
    if (!texture_pause.loadFromFile("files/images/pause.png"))
    {
        cout << "Error loading texture." << endl;
    }
    sf::Sprite sprite_play_pause;
    sprite_play_pause.setTexture(texture_pause);
    sprite_play_pause.setPosition(numCols * 32 - 240, 32 * (numRows + 0.5));

    sf::Texture texture_play;
    if (!texture_play.loadFromFile("files/images/play.png"))
    {
        cout << "Error loading texture." << endl;
    }


    // create texture for our tiles objects
    sf::Texture texture_tile_hidden;
    if (!texture_tile_hidden.loadFromFile("files/images/tile_hidden.png"))
    {
        cout << "Error loading texture." << endl;
    }

    sf::Sprite sprite_tile_hidden;
    sprite_tile_hidden.setTexture(texture_tile_hidden);

    sf::Texture texture_tile_revealed;
    if (!texture_tile_revealed.loadFromFile("files/images/tile_revealed.png"))
    {
        cout << "Error loading texture." << endl;
    }

    // create texture for each individual digit for the tiles
    map<int, sf::Texture> texture_digits_tiles;
    for (int i = 1; i <= 8; i++){
        sf::Texture texture_digit;
        string filename = "files/images/number_" + std::to_string(i) + ".png";
        if (!texture_digit.loadFromFile(filename))
        {
            cout << "Error loading digit texture." << endl;
        }
        texture_digits_tiles[i] = texture_digit;
    }


    //
    // Section 1: Welcome Window
    //

    sf::RenderWindow welcomeWindow(sf::VideoMode(width, height), "Welcome Window", sf::Style::Close);
    bool openGameWindow = true;

    // read font
    sf::Font font;
    if (!font.loadFromFile("files/font.ttf"))
    {
        cout << "Loading font failed." << endl;
        return 1;
    }

    // create the text object for the titleTextObject
    sf::Text titleTextObject;
    titleTextObject.setFont(font);
    titleTextObject.setString("WELCOME TO MINESWEEPER!");
    titleTextObject.setCharacterSize(24);
    titleTextObject.setFillColor(sf::Color::White);
    titleTextObject.setStyle(sf::Text::Bold | sf::Text::Underlined);
    setText(titleTextObject, width / 2, height / 2 - 150);

    // create text object for "Enter your nameTextObject:"
    sf::Text subtitleTextObject;
    subtitleTextObject.setFont(font);
    subtitleTextObject.setString("Enter your name:");
    subtitleTextObject.setCharacterSize(20);
    subtitleTextObject.setFillColor(sf::Color::White);
    subtitleTextObject.setStyle(sf::Text::Bold);
    setText(subtitleTextObject, width / 2, height / 2 - 75);

    // create text object for the username
    string userName = "|";
    sf::Text nameTextObject;
    nameTextObject.setFont(font);
    nameTextObject.setCharacterSize(18);
    nameTextObject.setString(userName);
    nameTextObject.setFillColor(sf::Color::Yellow);
    nameTextObject.setStyle(sf::Text::Bold);
    setText(nameTextObject, width / 2, height / 2 - 45);

    while(welcomeWindow.isOpen()) {
        sf::Event event;

        while(welcomeWindow.pollEvent(event)) {
            if(event.type == sf::Event::Closed){
                welcomeWindow.close();
                openGameWindow = false;
                break;
            }

            if (event.type == sf::Event::TextEntered){
                if (userName.size() <= 10){
                    if ((65 <= event.text.unicode && event.text.unicode <= 90) || (97 <= event.text.unicode && event.text.unicode <= 122)){
                        char input = static_cast<char>(event.text.unicode);
                        if (userName.size() == 1){
                            input = (char)toupper(input);
                            userName.insert(0,1,input);
                        }
                        else{
                            input = (char)tolower(input);
                            userName.insert(userName.size() - 1, 1, input);
                        }
                    }
                }

                // check if the key entered is the delete key
                if (event.text.unicode == 8 && userName.size() > 1){
                    userName = userName.substr(0, userName.size() - 2) + "|";
                }

                nameTextObject.setString(userName);
                setText(nameTextObject, width / 2, height / 2 - 45);
            }


        }

        // check if "Enter" is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            if (userName.size() > 1){
                welcomeWindow.close();
            }
        }

        // clear the welcomeWindow with black color
        welcomeWindow.clear(sf::Color::Blue);
        welcomeWindow.draw(titleTextObject);
        welcomeWindow.draw(subtitleTextObject);
        welcomeWindow.draw(nameTextObject);
        welcomeWindow.display();
    }

    userName = userName.substr(0, userName.size() - 1);

    //
    // Section 2: Game Window and Leaderboard Window
    //

    // check if the user closed the window previously
    if (openGameWindow){


        sf::RenderWindow gameWindow(sf::VideoMode(width, height), "Game Window", sf::Style::Close);

        // ----- Relevant Parameters for my Game -----

        Board gameBoard = Board(numRows, numCols, numTotalMine);

        // read leaderboard information
        map<string,string> map_leaderboard = readTxtFile("files/leaderboard.txt");


        // create sprites for bottom_layer tiles
        vector<vector<sf::Sprite>> vec_sprite_bottom_tiles(numRows, vector<sf::Sprite>(numCols));
        for (int i = 0; i < numRows; i++){
            for (int j = 0; j < numCols; j++){
                vec_sprite_bottom_tiles[i][j] = sf::Sprite();
                // calculate coordinate
                int x = j * 32;
                int y = i * 32;
                vec_sprite_bottom_tiles[i][j].setPosition(x, y);
                vec_sprite_bottom_tiles[i][j].setTexture(texture_tile_hidden);
            }
        }

        // create sprites for top_layer tiles
        vector<vector<sf::Sprite>> vec_sprite_top_tiles(numRows, vector<sf::Sprite>(numCols));
        for (int i = 0; i < numRows; i++){
            for (int j = 0; j < numCols; j++){
                vec_sprite_top_tiles[i][j] = sf::Sprite();
                // calculate coordinate
                int x = j * 32;
                int y = i * 32;
                vec_sprite_top_tiles[i][j].setPosition(x, y);
            }
        }


        // timer parameters
        sf::Clock clock;
        sf::Time savedTime = sf::Time::Zero;
        sf::Time display_time = sf::Time::Zero;
        sf::Time userTime;

        while(gameWindow.isOpen()){

            if (gameBoard.getGameProgressing() && !gameBoard.getGameWin() && !gameBoard.getGameLose()){
                display_time = clock.getElapsedTime() + savedTime;
            }
            else{
                savedTime = display_time;
            }


            int game_time_as_sec = static_cast<int>(display_time.asSeconds());
            int min = game_time_as_sec / 60;
            int sec = game_time_as_sec % 60;

            // calculate what the digits should be on timer specifically
            int min_tens_digit = min / 10;
            int min_digit = min % 10;
            int sec_tens_digit = sec / 10;
            int sec_digit = sec % 10;

            // apply digit texture on our timer sprite
            sprite_min_tens_digit.setTexture(texture_digits_displayer[min_tens_digit]);
            sprite_min_digit.setTexture(texture_digits_displayer[min_digit]);
            sprite_sec_tens_digit.setTexture(texture_digits_displayer[sec_tens_digit]);
            sprite_sec_digit.setTexture(texture_digits_displayer[sec_digit]);

            // calculate what the digits should be on counter specifically
            int counter_hundreds_digit = abs(gameBoard.getRemainingMineForUser() / 100);
            int counter_tens_digit = abs(gameBoard.getRemainingMineForUser() / 10 % 10);
            int counter_digit = abs(gameBoard.getRemainingMineForUser() % 10);

            // apply digit texture on our counter sprite
            sprite_counter_hundreds_digit.setTexture(texture_digits_displayer[counter_hundreds_digit]);
            sprite_counter_tens_digit.setTexture(texture_digits_displayer[counter_tens_digit]);
            sprite_counter_digit.setTexture(texture_digits_displayer[counter_digit]);

            // apply tile reveal/hidden texture


            if (gameBoard.getGameProgressing()){
                for (int i = 0; i < numRows; i++){
                    for (int j = 0; j < numCols; j++){
                        if (gameBoard.getIsRevealed(i,j)){
                            int numAdjMines = gameBoard.getNumAdjMines(i,j);
                            vec_sprite_bottom_tiles[i][j].setTexture(texture_tile_revealed);
                            if (gameBoard.getIsMine(i,j)){
                                vec_sprite_top_tiles[i][j].setTexture(texture_mine);
                            }
                            else if (numAdjMines != 0){
                                vec_sprite_top_tiles[i][j].setTexture(texture_digits_tiles[numAdjMines]);
                            }
                            else{
                                vec_sprite_top_tiles[i][j].setTexture(texture_tile_revealed);
                            }
                        }
                        else{
                            vec_sprite_bottom_tiles[i][j].setTexture(texture_tile_hidden);
                            if (gameBoard.getIsMine(i,j) && gameBoard.getDebugMode()){
                                vec_sprite_top_tiles[i][j].setTexture(texture_mine);
                            }
                            else if (gameBoard.getIsFlagged(i,j)){
                                vec_sprite_top_tiles[i][j].setTexture(texture_flag);
                            }
                            else{
                                vec_sprite_top_tiles[i][j].setTexture(texture_tile_hidden);
                            }
                        }
                    }
                }
            }
            else{
                for (int i = 0; i < numRows; i++) {
                    for (int j = 0; j < numCols; j++) {
                        vec_sprite_bottom_tiles[i][j].setTexture(texture_tile_revealed);
                        vec_sprite_top_tiles[i][j].setTexture(texture_tile_revealed);

                    }
                }

            }

            sf::Event event;

            while(gameWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    gameWindow.close();
                    break;
                }

                // check if a button is clicked
                if (event.type == sf::Event::MouseButtonPressed){

                    sf::Mouse mouse;
                    int mouse_x = mouse.getPosition(gameWindow).x;
                    int mouse_y = mouse.getPosition(gameWindow).y;

                    // check if debug button is clicked
                    if (sprite_debug.getGlobalBounds().contains(mouse_x, mouse_y)){
                        if (!gameBoard.getGameWin() && !gameBoard.getGameLose()){
                            gameBoard.setDebugMode();
                        }
                    }

                    // check if play/pause button is clicked
                    if (sprite_play_pause.getGlobalBounds().contains(mouse_x, mouse_y) && !gameBoard.getGameWin() && !gameBoard.getGameLose()){
                        if (gameBoard.getGameProgressing()){
                            sprite_play_pause.setTexture(texture_play);
                        }
                        else{
                            sprite_play_pause.setTexture(texture_pause);
                            clock.restart();
                        }
                        gameBoard.setGameProgressing();
                    }

                    // check if leaderboard button is clicked
                    if (sprite_leaderboard.getGlobalBounds().contains(mouse_x,mouse_y)){

                        // create text object for leaderboard title
                        sf::Text leaderboardTitleObject;
                        leaderboardTitleObject.setFont(font);
                        leaderboardTitleObject.setString("LEADERBOARD");
                        leaderboardTitleObject.setCharacterSize(20);
                        leaderboardTitleObject.setFillColor(sf::Color::White);
                        leaderboardTitleObject.setStyle(sf::Text::Bold | sf::Text::Underlined);
                        setText(leaderboardTitleObject, width/4, height/4 - 120);

                        // create text object for the content of the leaderboard
                        sf::Text leaderboardContentObject;
                        string content_leaderboard = "";
                        int index = 1;

                        for (auto pair : map_leaderboard){
                            content_leaderboard += to_string(index) + ".\t" + pair.second + "\t" + pair.first;
                            if (pair.first == userName){
                                content_leaderboard += '*';
                            }
                            content_leaderboard += "\n\n";
                            index += 1;
                        }

                        leaderboardContentObject.setFont(font);
                        leaderboardContentObject.setString(content_leaderboard);
                        leaderboardContentObject.setCharacterSize(18);
                        leaderboardContentObject.setFillColor(sf::Color::White);
                        leaderboardContentObject.setStyle(sf::Text::Bold);
                        setText(leaderboardContentObject, width/4, height/4 + 20);

                        // set game progressing to false
                        gameBoard.setGameProgressing();
                        savedTime = display_time;
                        // create our leaderboard window
                        sf::RenderWindow leaderboardWindow(sf::VideoMode(width/2, height/2), "Leaderboard Window", sf::Style::Close);
                        while(leaderboardWindow.isOpen()){
                            // our leaderboard window events
                            sf::Event leaderEvent;
                            while(leaderboardWindow.pollEvent(leaderEvent)){
                                if(leaderEvent.type == sf::Event::Closed){
                                    leaderboardWindow.close();
                                    clock.restart();
                                    gameBoard.setGameProgressing();
                                    break;
                                }

                            }
                            leaderboardWindow.clear(sf::Color::Blue);
                            leaderboardWindow.draw(leaderboardTitleObject);
                            leaderboardWindow.draw(leaderboardContentObject);
                            leaderboardWindow.display();

                        }
                    }

                    // check if happy face is clicked
                    if (sprite_face.getGlobalBounds().contains(mouse_x, mouse_y)){

                        sprite_face.setTexture(texture_face_happy);

                        // create a new board
                        gameBoard = Board(numRows, numCols, numTotalMine);

                        // reset parameters
                        clock.restart();
                        savedTime = sf::Time::Zero;
                        display_time = sf::Time::Zero;

                        // reset the texture for play/pause button
                        sprite_play_pause.setTexture(texture_pause);
                    }

                    // check if tiles are being clicked
                    if ((mouse_x <= numCols * 32) && (mouse_y <= numRows * 32) && !gameBoard.getGameLose() && !gameBoard.getGameWin()){
                        int row = (mouse_y / 32);
                        int col = (mouse_x / 32);

                        // check if it is left_clicked
                        if (event.mouseButton.button == sf::Mouse::Left){

                            if (!gameBoard.getIsFlagged(row, col)){

                                // if the tile is a mine
                                if (gameBoard.getIsMine(row,col)){
                                    for (int i = 0; i < numRows; i++){
                                        for (int j = 0; j < numCols; j++){
                                            if (gameBoard.getIsMine(i,j)){
                                                gameBoard.revealTile(i,j);
                                            }
                                        }
                                    }
                                    sprite_face.setTexture(texture_face_lose);
                                    gameBoard.setGameLose();
                                }
                                else{
                                    gameBoard.revealNeighbours(row, col);

                                    // check if the user wins the game
                                    if (gameBoard.getNumRevealedTiles() == numRows * numCols - numTotalMine){
                                        sprite_face.setTexture(texture_face_win);
                                        gameBoard.setGameWin();

                                        // get user time
                                        int timer_as_int = display_time.asSeconds();
                                        int user_minute_int = timer_as_int / 60;
                                        int user_second_int = timer_as_int % 60;

                                        // create string for min and sec
                                        string user_minute_str;
                                        string user_second_str;
                                        if (user_minute_int < 10){
                                            user_minute_str = '0' + to_string(user_minute_int);
                                        }
                                        else{
                                            user_minute_str = to_string(user_minute_int);
                                        }
                                        if (user_second_int < 10){
                                            user_second_str = '0' + to_string(user_second_int);
                                        }
                                        else{
                                            user_second_str = to_string(user_second_int);
                                        }

                                        // create string for map
                                        string user_time_string = user_minute_str + ':' + user_second_str;

                                        map_leaderboard[userName] = user_time_string;
                                        writeTxtFile("files/leaderboard.txt", map_leaderboard);
                                        map_leaderboard = readTxtFile("files/leaderboard.txt");

                                    }
                                }
                            }

                        }

                            // check if it is right_clicked
                        else if (event.mouseButton.button == sf::Mouse::Right){
                            if (!gameBoard.getIsRevealed(row,col)){

                                if (!gameBoard.getIsFlagged(row, col)){
                                    // set the tile to flagged
                                    gameBoard.flagTile(row, col);
                                    gameBoard.setRemainingMineForUser(-1);
                                }
                                else{
                                    gameBoard.removeFlag(row, col);
                                    gameBoard.setRemainingMineForUser(1);
                                }
                            }


                        }

                    }

                }
            }

            gameWindow.clear(sf::Color::White);
            gameWindow.draw(sprite_face);
            gameWindow.draw(sprite_debug);
            gameWindow.draw(sprite_leaderboard);
            gameWindow.draw(sprite_play_pause);

            // Draw timer
            gameWindow.draw(sprite_min_tens_digit);
            gameWindow.draw(sprite_min_digit);
            gameWindow.draw(sprite_sec_tens_digit);
            gameWindow.draw(sprite_sec_digit);

            // Draw counter
            gameWindow.draw(sprite_counter_hundreds_digit);
            gameWindow.draw(sprite_counter_tens_digit);
            gameWindow.draw(sprite_counter_digit);

            if (gameBoard.getRemainingMineForUser() < 0){
                gameWindow.draw(sprite_counter_negative_sign);
            }

            // Draw tiles for my game

            for (int i = 0; i < numRows; i++){
                for (int j = 0; j < numCols; j++){

                    gameWindow.draw(vec_sprite_bottom_tiles[i][j]);

                }
            }

            for (int i = 0; i < numRows; i++){
                for (int j = 0; j < numCols; j++){

                    gameWindow.draw(vec_sprite_top_tiles[i][j]);

                }
            }


            gameWindow.display();


        }
    }


    return 0;
}