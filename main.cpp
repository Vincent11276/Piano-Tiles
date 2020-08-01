#include<TGUI/TGUI.hpp>
#include<iostream>
#include<vector>
#include<cstdlib>
using namespace std;

class Tile : public sf::Drawable {
    public:
        Tile(sf::Vector2f size) {
            pTileShape.setSize(size);
        }
        void setPosition(int x, int y) {
            pTileShape.setPosition(x, y);
        }
        sf::Vector2i getPosition() {
            return sf::Vector2i(pTileShape.getPosition().x, pTileShape.getPosition().y);
        }
        void setFillColor(sf::Color color) {
            pTileShape.setFillColor(color);
        }
        void move(int x, int y) {
            pTileShape.move(x, y);
        }
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
            target.draw(pTileShape, states);
        }
     private:
        sf::RectangleShape pTileShape;
};


int main() {

    sf::RenderWindow window(sf::VideoMode(400, 800), "Piano Tiles");
    window.setFramerateLimit(60);

    std::vector<Tile> tileVec;

    Tile newTile(sf::Vector2f(100, 200));
    newTile.setPosition(0, -200);
    tileVec.push_back(newTile);

    sf::Font arialCE;
    if(!arialCE.loadFromFile("fonts/arial sv/arial_ce.ttf")) system("pause");

    float tileMoveSpeed = 500;
    int tileMoveCounter = 0;
    int lastTileCounter = 0;
    int tileLost = 0;
    int tileWin = 0;

    sf::Clock clock;

    while(window.isOpen()) {

        float deltaTime = clock.restart().asSeconds();


        sf::Event event;
        while(window.pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                        if(tileVec[lastTileCounter].getPosition().x == 0) {
                            tileVec[lastTileCounter].setFillColor(sf::Color(0, 255, 0));
                            tileWin++;
                        }                  
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                        if(tileVec[lastTileCounter].getPosition().x == 100) {
                            tileVec[lastTileCounter].setFillColor(sf::Color(0, 255, 0));
                            tileWin++;
                        }                  
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                        if(tileVec[lastTileCounter].getPosition().x == 200) {
                            tileVec[lastTileCounter].setFillColor(sf::Color(0, 255, 0));
                            tileWin++;
                        }                  
                    }
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                        if(tileVec[lastTileCounter].getPosition().x == 300) {
                            tileVec[lastTileCounter].setFillColor(sf::Color(0, 255, 0));
                            tileWin++;
                        }                  
                    }
                    lastTileCounter = tileWin + tileLost;
            }
        }
        

        if(tileVec[lastTileCounter].getPosition().y >= 600) {
            tileVec[lastTileCounter].setFillColor(sf::Color(255, 0, 0));
            tileLost++;
            lastTileCounter = tileWin + tileLost;
        }

        if(tileMoveCounter >= 200) {         
            Tile newTile(sf::Vector2f(100, 200));
            newTile.setFillColor(sf::Color(120,120, 0));
            newTile.setPosition((rand()%4) * 100, -200);
            tileVec.push_back(newTile);
            tileMoveCounter = 0;
        } 

        window.clear();

        for(int i = 0; i < tileVec.size(); i++) {
            window.draw(tileVec[i]);
            tileVec[i].move(0, (float)deltaTime * (float)tileMoveSpeed);      
        }
        
        tileMoveCounter += (float)deltaTime * (float)tileMoveSpeed;
        cout << "tile count = " << tileVec.size() << ", deltaTime = " << deltaTime << ", FPS = " << 1/deltaTime << endl;

        window.display();
    }

    return 0;
}
