
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>

#include <GL/glut.h>  // GLUT, includes glu.h and gl.h

#include "plot/Color/HSV.hpp"
#include "plot/Heatmap/Heatmap.hpp"

using namespace plt;

static const std::size_t window_width = 360,
                         window_height = 320;

static const std::size_t w = 320,
                         h = 320,
                         p = 100000;

// This creates two normal random distributions which will give us random points.
std::random_device rd;
std::mt19937 prng(rd());
std::normal_distribution<float>
    x_distr(0.5f*w, 0.5f*w),
    y_distr(0.5f*h, 0.25f*h);

plt::Heatmap<float> hm(w, h);

unsigned char *image;

void display() {
    hm.render(image);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, window_width, window_height, 0.0);

    static color::hsv<float> low(240.0f, 1.0f, 0.5529f);
    static color::hsv<float> mid(125.95f, 0.5137f, 1.0f);
    static color::hsv<float> high(358.5f, 0.9677f, 1.0f);

    for (std::size_t m = 0; m < h; m++) {
        for (std::size_t n = 0; n < w; n++) {
            unsigned char *color = image + (m * w * 4 + (n * 4));

            glBegin(GL_POINTS);
                glColor3f((float)color[0] / 255.0f,
                          (float)color[1] / 255.0f,
                          (float)color[2] / 255.0f);
                glVertex2i(n, m);
            glEnd();
        }

        for (std::size_t n = 0; n < 40; ++n) {
            float step = (float)m / (float)h;

            color::rgb<float> color = color::get::cast_rgb(
                color::hsv<float>(240.0f - (240.0f * step), 1.0f, 1.0f));

            glBegin(GL_POINTS);
            glColor3f(color::get::red(color),
                      color::get::green(color),
                      color::get::blue(color));
                glVertex2i(w + n, m);
            glEnd();
        }
    }

    glFlush();  // Render now
    glutPostRedisplay();
}

void onMouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        hm.point(x, y, 1.0f);
    }
}

int main(int argc, char *argv[]) {

    std::cout << "[" << hm.min() << ", " << hm.max() << "]" << std::endl;

    for (int m = 0; m < p; m++) {
        hm.point(x_distr(prng), y_distr(prng), 0.5f);
    }

    std::cout << "[" << hm.min() << ", " << hm.max() << "]" << std::endl;

    image = hm.render();

    glutInit(&argc, argv);
    glutCreateWindow("heatmap");
    glutReshapeWindow(window_width, window_height);
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(50, 50);
    glutDisplayFunc(display);
    glutMouseFunc(onMouseClick);
    glutMainLoop();

    return 0;
}
