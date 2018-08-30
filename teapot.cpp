#include <SDL2/SDL.h>
#include <emscripten.h>
#include <cstdlib>
#include <GL/gl.h>                      /* for glVertex3f, GLfloat, etc */
#include <GL/glu.h>                     /* for gluLookAt, gluOrtho2D, etc */
#include <GL/glut.h>                    /* for glutSolidTeapot */

struct context
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    int iteration;
};

/* light information */
struct light_t {
	GLfloat position[4];
	GLfloat spotDirection[3];
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat spotCutoff;
	GLfloat spotExponent;
	GLfloat spotAttenuation[3];  /*  [0] = constant, [1] = linear, [2] = quadratic  */
};
struct light_t light = {
	{ 1.0, 1.0, -2.0, 1.0	},
	{ -1.0, -1.0, 2.0		},
	{ 0.0, 0.0, 0.0, 1.0	},
	{ 1.0, 1.0, 1.0, 1.0	},
	{ 1.0, 1.0, 1.0, 1.0	},
	180.0, 0.0,
	{ 1.0, 0.0, 0.0			}
};

/* material information */
struct material_t {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat emission[4];
	GLfloat shininess;
};
struct material_t red_plastic = {
	{ 0.3, 0.0, 0.0, 1.0 },
	{ 0.3, 0.0, 0.0, 1.0 },
	{ 0.8, 0.6, 0.6, 1.0 },
	{ 0.0, 0.0, 0.0, 1.0 },
	32.0
};

void update_light(GLenum l, struct light_t* lptr) {
	glLightfv(l, GL_POSITION, lptr->position);
	glLightfv(l, GL_DIFFUSE, lptr->diffuse);
	glLightfv(l, GL_SPECULAR, lptr->specular);
	glLightfv(l, GL_AMBIENT, lptr->ambient);
	glLightfv(l, GL_SPOT_DIRECTION, lptr->spotDirection);
	glLightf(l, GL_SPOT_CUTOFF, lptr->spotCutoff);
	glLightf(l, GL_SPOT_EXPONENT, lptr->spotExponent);
	glLightf(l, GL_CONSTANT_ATTENUATION, lptr->spotAttenuation[0]);
	glLightf(l, GL_LINEAR_ATTENUATION, lptr->spotAttenuation[1]);
	glLightf(l, GL_QUADRATIC_ATTENUATION, lptr->spotAttenuation[2]);
}


void set_material(struct material_t* mptr) {
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mptr->ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mptr->diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mptr->specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, mptr->shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mptr->emission);
}

void mainloop(void *arg)
{
    context *ctx = static_cast<context*>(arg);
    SDL_Window *window = ctx->window;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    /* draw the teapot */
    gluLookAt(0.0, 0.0, -5.0,
                0.0, 0.0, 0.0,
                0.0, 1.0, 0.0);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    update_light(GL_LIGHT0, &light);
    set_material(&red_plastic);

    glRotatef(0.5f, 0.0f, 0.0f, 1.0f);
    glRotatef(0.5f, 1.0f, 0.0f, 0.0f);


    glutSolidTeapot(1);

    SDL_GL_SwapWindow(window);

    /*
    context *ctx = static_cast<context*>(arg);
    SDL_Renderer *renderer = ctx->renderer;

    // example: draw a moving rectangle

    // red background
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    // moving blue rectangle
    SDL_Rect r;
    r.x = ctx->iteration % 255;
    r.y = 50;
    r.w = 50;
    r.h = 50;
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255 );
    SDL_RenderFillRect(renderer, &r );

    SDL_RenderPresent(renderer);

    ctx->iteration++;
    */
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_CreateWindowAndRenderer(255, 255, 0, &window, &renderer);
    SDL_GLContext Context = SDL_GL_CreateContext(window);

    context ctx;
    ctx.renderer = renderer;
    ctx.window = window;
    ctx.iteration = 0;

    const int simulate_infinite_loop = 1; // call the function repeatedly
    const int fps = -1; // call the function as fast as the browser wants to render (typically 60fps)
    emscripten_set_main_loop_arg(mainloop, &ctx, fps, simulate_infinite_loop);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}