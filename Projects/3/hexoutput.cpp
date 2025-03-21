//
// Created by bob on 11/23/18.
//

#include <fstream>
#include <iostream>
#include "hexpathfinder.h"

using namespace std;
/*
void drawLine(ofstream &outFile,uint32_t r1,uint32_t c1,uint32_t r2,uint32_t c2,uint32_t off1,uint32_t off2) {

    outFile << "newpath\n"
            << c1 * off1 + 54 + off2 << ' ' << 762 - (r1 * off1 + 54 + off2) << " moveto\n"
            << c2 * off1 + 54 + off2 << ' ' << 762 - (r2 * off1 + 54 + off2) << " lineto\n"
            << "stroke\n";
}
*/
void drawLine(ofstream &outFile,uint32_t x1,uint32_t y1,uint32_t x2,uint32_t y2) {
    outFile << "newpath "
            << x1 << ' ' << y1 << " moveto "
            << x2 << ' ' << y2 << " lineto stroke\n";
}

/*
void drawLine2(ofstream outFile,int r1,int c1,int r2,int c2) {

    outFile << "newpath\n"
            << c1 * 5 + 54 + 5 << ' ' << 762 - (r1 * 5 + 54 + 5) << " moveto\n"
            << c2 * 5 + 54 + 5 << ' ' << 762 - (r2 * 5 + 54 + 5) << " lineto\n"
            << "stroke\n";
}
*/

void drawMaze(ofstream &outFile,uint8_t maze[][MAX_COLS],uint32_t nR,uint32_t nC,
              bool drawSolution,bool drawDeadEnds) {
    uint32_t
        r,c,
        r2,c2,
        x,y,
        x2,y2;

    /*
    outFile << "newpath\n"
            << "54 " << 762 - (nR * 10 + 54) << " moveto\n"
            << "54 708 lineto\n"
            << nC * 10 + 54 << " 708 lineto\nstroke\n";
*/

    outFile << "0.25 setlinewidth\n";

    // draw all existing up-right, down-right and down walls; most of these are interior, some exterior

    for (r=0;r<nR;r++)
        for (c=0;c<nC;c++) {
            x = computeX(c);
            y = computeY(r,c);
            if (maze[r][c] & WALL_UP_RIGHT)
                drawLine(outFile,x+DRAW_E/2,y+DRAW_V,x+DRAW_E,y);
            if (maze[r][c] & WALL_DOWN_RIGHT)
                drawLine(outFile,x+DRAW_E,y,x+DRAW_E/2,y-DRAW_V);
            if (maze[r][c] & WALL_DOWN)
                drawLine(outFile,x+DRAW_E/2,y-DRAW_V,x-DRAW_E/2,y-DRAW_V);
        }

    // remaining walls are all exterior

    // draw the up-left and down-left walls in column 0

    for (r=0;r<nR;r++) {
        x = computeX(0);
        y = computeY(r,0u);
        drawLine(outFile,x-DRAW_E/2,y+DRAW_V,x-DRAW_E,y);
        drawLine(outFile,x-DRAW_E,y,x-DRAW_E/2,y-DRAW_V);
    }

    // draw the top walls in row 0

    for (c=0;c<nC;c++) {
        x = computeX(c);
        y = computeY(0,c);
        drawLine(outFile,x-DRAW_E/2,y+DRAW_V,x+DRAW_E/2,y+DRAW_V);
    }

    // draw the up-left walls in row 0 even columns after 0

    for (c=2;c<nC;c+=2) {
        x = computeX(c);
        y = computeY(0,c);
        drawLine(outFile,x-DRAW_E/2,y+DRAW_V,x-DRAW_E,y);
    }

    // draw the down-left walls in bottom row odd columns

    for (c=1;c<nC;c+=2) {
        x = computeX(c);
        y = computeY(nR-1,c);
        drawLine(outFile,x-DRAW_E/2,y-DRAW_V,x-DRAW_E,y);
    }

    if (drawDeadEnds) {
        outFile << "1 0 0 setrgbcolor\n";
        for (r=0;r<nR;r++)
            for (c=0;c<nC;c++) {
                x = computeX(c);
                y = computeY(r, c);
                if ((maze[r][c] & DEAD_END) != 0) {
                    if ((maze[r][c] & WALL_UP) == 0) {
                        r2 = r - 1;
                        c2 = c;
                        x2 = computeX(c2);
                        y2 = computeY(r2, c2);
//                        x2 = (x + x2) / 2;
//                        y2 = (y + y2) / 2;
                        drawLine(outFile, x, y, x2, y2);
                    }
                    if ((maze[r][c] & WALL_DOWN) == 0) {
                        r2 = r + 1;
                        c2 = c;
                        x2 = computeX(c2);
                        y2 = computeY(r2, c2);
//                        x2 = (x + x2) / 2;
//                        y2 = (y + y2) / 2;
                        drawLine(outFile, x, y, x2, y2);
                    }
                    if ((maze[r][c] & WALL_UP_RIGHT) == 0) {
                        r2 = r - 1 + (c & 1u);
                        c2 = c + 1;
                        x2 = computeX(c2);
                        y2 = computeY(r2, c2);
//                        x2 = (x + x2) / 2;
//                        y2 = (y + y2) / 2;
                        drawLine(outFile, x, y, x2, y2);
                    }
                    if ((maze[r][c] & WALL_DOWN_RIGHT) == 0) {
                        r2 = r + (c & 1u);
                        c2 = c + 1;
                        x2 = computeX(c2);
                        y2 = computeY(r2, c2);
//                        x2 = (x + x2) / 2;
//                        y2 = (y + y2) / 2;
                        drawLine(outFile, x, y, x2, y2);
                    }
                    if ((maze[r][c] & WALL_UP_LEFT) == 0) {
                        r2 = r - 1 + (c & 1u);
                        c2 = c - 1;
                        x2 = computeX(c2);
                        y2 = computeY(r2, c2);
//                        x2 = (x + x2) / 2;
//                        y2 = (y + y2) / 2;
                        drawLine(outFile, x, y, x2, y2);
                    }
                    if ((maze[r][c] & WALL_DOWN_LEFT) == 0) {
                        r2 = r + (c & 1u);
                        c2 = c - 1;
                        x2 = computeX(c2);
                        y2 = computeY(r2, c2);
//                        x2 = (x + x2) / 2;
//                        y2 = (y + y2) / 2;
                        drawLine(outFile, x, y, x2, y2);
                    }
                }
            }
    }

    if (drawSolution) {
        outFile << "0 0 1 setrgbcolor gsave currentlinewidth 5 mul setlinewidth "
                   " 1 setlinecap\n";
        for (r=0;r<nR;r++)
            for (c=0;c<nC;c++) {
                x = computeX(c);
                y = computeY(r,c);
                if ((maze[r][c] & (uint8_t)(VISITED | DEAD_END)) == VISITED) {
                    if ((maze[r][c] & WALL_UP) == 0) {
                        r2 = r - 1;
                        c2 = c;
                        if ((maze[r2][c2] & (uint8_t)(VISITED | DEAD_END)) == VISITED) {
                            x2 = computeX(c2);
                            y2 = computeY(r2, c2);
                            x2 = (x + x2) / 2;
                            y2 = (y + y2) / 2;
                            drawLine(outFile, x, y, x2, y2);
                        }
                    }
                    if ((maze[r][c] & WALL_DOWN) == 0) {
                        r2 = r + 1;
                        c2 = c;
                        if ((maze[r2][c2] & (uint8_t)(VISITED | DEAD_END)) == VISITED) {
                            x2 = computeX(c2);
                            y2 = computeY(r2, c2);
                            x2 = (x + x2) / 2;
                            y2 = (y + y2) / 2;
                            drawLine(outFile, x, y, x2, y2);
                        }
                    }
                    if ((maze[r][c] & WALL_UP_RIGHT) == 0) {
                        r2 = r - 1 + (c & 1u);
                        c2 = c + 1;
                        if ((maze[r2][c2] & (uint8_t)(VISITED | DEAD_END)) == VISITED) {
                            x2 = computeX(c2);
                            y2 = computeY(r2, c2);
                            x2 = (x + x2) / 2;
                            y2 = (y + y2) / 2;
                            drawLine(outFile, x, y, x2, y2);
                        }
                    }
                    if ((maze[r][c] & WALL_DOWN_RIGHT) == 0) {
                        r2 = r + (c & 1u);
                        c2 = c + 1;
                        if ((maze[r2][c2] & (uint8_t)(VISITED | DEAD_END)) == VISITED) {
                            x2 = computeX(c2);
                            y2 = computeY(r2, c2);
                            x2 = (x + x2) / 2;
                            y2 = (y + y2) / 2;
                            drawLine(outFile, x, y, x2, y2);
                        }
                    }
                    if ((maze[r][c] & WALL_UP_LEFT) == 0) {
                        r2 = r - 1 + (c & 1u);
                        c2 = c - 1;
                        if ((maze[r2][c2] & (uint8_t)(VISITED | DEAD_END)) == VISITED) {
                            x2 = computeX(c2);
                            y2 = computeY(r2, c2);
                            x2 = (x + x2) / 2;
                            y2 = (y + y2) / 2;
                            drawLine(outFile, x, y, x2, y2);
                        }
                    }
                    if ((maze[r][c] & WALL_DOWN_LEFT) == 0) {
                        r2 = r + (c & 1u);
                        c2 = c - 1;
                        if ((maze[r2][c2] & (uint8_t)(VISITED | DEAD_END)) == VISITED) {
                            x2 = computeX(c2);
                            y2 = computeY(r2, c2);
                            x2 = (x + x2) / 2;
                            y2 = (y + y2) / 2;
                            drawLine(outFile, x, y, x2, y2);
                        }
                    }
                }
            }
        outFile << "grestore\n";
    }

}

void printMaze(uint8_t maze[][MAX_COLS],uint32_t nR,uint32_t nC) {
    ofstream
        outFile;

    outFile.open("maze.ps");
    if (!outFile) {
        cout << "Error: cannot open maze.ps" << endl;
        return;
    }

    outFile << "%!PS-Adobe-2.0\n\n%%Pages: 2\n%%Page: 1 1\n";

    outFile << "/Arial findfont 20 scalefont setfont\n"
               "54 730 moveto (Random Maze) show\n";

    drawMaze(outFile,maze,nR,nC,false,false);

    outFile << "showpage\n";
    outFile << "%%Page: 2 2\n";

    outFile << "/Arial findfont 20 scalefont setfont\n"
               "54 730 moveto (Random Maze With Solution) show\n";

    drawMaze(outFile,maze,nR,nC,true,false);

    outFile << "showpage\n";
    /*
    outFile << "%%Page: 3 3\n";

    outFile << "/Arial findfont 20 scalefont setfont\n"
               "54 730 moveto (Random Maze With Solution "
               "and Dead Ends) show\n";

    drawMaze(outFile,maze,nR,nC,true,true);

    outFile << "showpage\n";
    */
}
