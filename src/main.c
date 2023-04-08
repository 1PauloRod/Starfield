#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define WINDOW_WIDTH 1028
#define WINDOW_HEIGHT 700

SDL_Window* window;
SDL_Renderer* renderer;



struct star{
    float x;
    float y;
    float z; 
    float speed;
}; typedef struct star Star;


void updateStars(Star** stars){
    
    for (int i = 0; i < 1000; i++){
        
        stars[i]->x = (stars[i]->x - WINDOW_WIDTH/2) * stars[i]->speed + WINDOW_WIDTH/2;
        stars[i]->y = (stars[i]->y - WINDOW_HEIGHT/2 )* stars[i]->speed + WINDOW_HEIGHT/2;

        if (stars[i]->x > WINDOW_WIDTH || stars[i]->x < 0 || stars[i]->y > WINDOW_HEIGHT || stars[i]->y < 0){
            stars[i]->x = rand() % WINDOW_WIDTH;
            stars[i]->y = rand() % WINDOW_HEIGHT;
            
        }
        stars[i]->speed += 0.0001f;
        
        if (stars[i]->speed > 1.1f)
            stars[i]->speed = 1.01f;
        
        
        
    }
}


Star* createStar(){
    Star* star = (Star*)malloc(sizeof(Star));
    star->x = rand() % WINDOW_WIDTH;
    star->y = rand() % WINDOW_HEIGHT;
    star->z = (rand() % 255 - 150 + 1) + 150;
    star->speed = 1.01f;
    return star;
}

void renderStars(Star** stars){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    
    for (int i = 0; i < 1000; i++){
        SDL_SetRenderDrawColor(renderer, stars[i]->z, stars[i]->z, stars[i]->z, 0);
        SDL_RenderDrawPoint(renderer, stars[i]->x, stars[i]->y);
    }

    SDL_RenderPresent(renderer); 

}

void update(Star** stars){
    updateStars(stars);
    renderStars(stars);
}

int main(int argc, char* argv[]){

    srand(time(NULL));
    Star** stars = (Star**)malloc(1000 * sizeof(Star*));
    if (stars == NULL) exit(1);

    for (int i = 0; i < 1000; i++){
        stars[i] = createStar();
    }

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Starfield", 
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
    WINDOW_WIDTH, WINDOW_HEIGHT, 
    SDL_WINDOW_OPENGL);

    if (window == NULL){
        printf("Error create window.\n");
        exit(1);
    }
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

    renderer = SDL_CreateRenderer(window, -1, 0);
    
    if (renderer == NULL){
        printf("Error create renderer.\n");
        exit(1);
    }

    SDL_Event event;
    int isRunning = TRUE;
    while(isRunning){
        while(SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                isRunning = FALSE;
            }
        }
       
        update(stars);
        
       
    }   

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}