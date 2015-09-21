#ifndef _PDOLLARFORCPP_H_
#define _PDOLLARFORCPP_H_

#ifdef PDOLLARFORCPP_EXPORTS
#define PDOLLARFORCPP_API _declspec(dllexport)
#else
#define PDOLLARFORCPP_API _declspec(dllimport)
#endif

#include "Gesture.h"

extern "C" PDOLLARFORCPP_API Gesture *createGesture(vector<Point *> point, string gestureName);
extern "C" PDOLLARFORCPP_API string classify(Gesture *gesture, vector<Gesture *> gestureSet);
extern "C" PDOLLARFORCPP_API double cloudMatch(vector<Point *> points1, vector<Point *> points2);
extern "C" PDOLLARFORCPP_API double cloudDistance(vector<Point *> points1, vector<Point *> points2, int index);

#endif