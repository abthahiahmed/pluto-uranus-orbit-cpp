#include <iostream>
#include <vector>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;
// Random number generator
float random(float low, float high){
	return low + static_cast<float>(rand()) * static_cast<float>(high - low) / RAND_MAX;
}
// Window creation
SDL_Window *win = SDL_CreateWindow("Pluto Uranus | Abthahi & Programming", 10,10,700,600, 0);
// Render Creation
SDL_Renderer *ren = SDL_CreateRenderer(win, -1, 0);
// Event object declaring
SDL_Event event;

// Function to draw circle
void drawCircle(int size, int x, int y){
    float px = x + size * cos(0);
    float py = y + size * sin(0);    

    for (float i = 0.01; i < 2 * 3.1416; i+=0.01){
        float cx = x + size * cos(i);
        float cy = y + size * sin(i);
        
        SDL_RenderDrawLine(ren, px, py, cx, cy);
        
        
        px = x + size * cos(i);
        py = y + size * sin(i);  
    }
}
// Function to draw Planet and return the position of planet
vector<float> drawPlanet(float x, float y, int orbitRadius, float deg){
    float a = x + orbitRadius * cos(deg);
    float b = y + orbitRadius * sin(deg);
    drawCircle(10, a, b);
    return {a, b};
}
// Class for the lines
class Line{
    
private : 
    float x1, y1, x2, y2;
public :
    Line(float x1, float y1, float x2, float y2){
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
    }
    void draw(){
        SDL_RenderDrawLine(ren, this->x1, this->y1, this->x2, this->y2);
    }
    
};

int main(int argc, char *argv[]){
    // Set Blend mode of Graphics
    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
    
    bool isRunning = true;
    
    float plutoA = 10, uranusA = 0;
    
    vector<Line> lines;
    
    int t = 0;
	
    while (isRunning){
        SDL_SetRenderDrawColor(ren, 0,0,0,255);
        SDL_RenderClear(ren);
        
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 200);
        
        
        // Orbit Uranus
        drawCircle(100, 300, 300);
        // Orbit Pluto
        drawCircle(260, 370, 300);
    
    
        
        // Pluto
        vector<float> plutoPos = drawPlanet(370, 300, 260, plutoA);
        plutoA -= 0.012;
        
        // Uranus
        vector<float> uranusPos = drawPlanet(300, 300, 100, uranusA);
        uranusA -= 0.039;
        
        if (t > 1){
            lines.push_back(Line(uranusPos[0], uranusPos[1], plutoPos[0], plutoPos[1]));
            t = 0;
        }
        
        
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 80);
        for (auto l : lines){
            l.draw();
        }      
        
        SDL_RenderPresent(ren);
        
        if (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                isRunning = false;
            }
        }
        
        SDL_Delay(1000/60);
        // Reset
        if (lines.size() > 1300){
            lines.clear();
            t = 0;
            uranusA = 0;
            plutoA = 10;
        }
        
        t++;
//        pt++;
//        ut++;
    }
    
    return 0;
} 
