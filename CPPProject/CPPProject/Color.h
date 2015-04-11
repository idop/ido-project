//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Color.h
// ----------
// enum for colors.
//
// Author: Amir Kirsh
// First version: 2014-12-09
// 
// This code is part of a solution for "the space ships game" excercise 1 in C++ course, Semester A 2015
// at the Academic College of Tel-Aviv-Yaffo.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Changes and additions:
// ------------------------
// DATE           Authors                 Change / Addition
// ----           --------                -----------------
// In the file itself, add above each change/addition a remark saying: "NEW CODE EX2, author=<name>, date=<YYYY-MM-DD>"
// and close it at the end with a remark saying "END of NEW CODE EX2" 
//2014-04-10     Ido Perry And Alex Odesser Removed Black Color From enum 
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#ifndef _COLOR_H_
#define _COLOR_H_

enum Color
{
	//NEW CODE EX 1 2014-04-10     Ido Perry And Alex Odesser Removed Black Color From enum 
	//BLACK=0, we dont want black color
	BLUE=1,
	GREEN=2,
	CYAN=3,
	RED=4,
	MAGENTA=5,
	BROWN=6,
	LIGHTGREY=7,
	DARKGREY=8,
	LIGHTBLUE=9,
	LIGHTGREEN=10,
	LIGHTCYAN=11,
	LIGHTRED=12,
	LIGHTMAGENTA=13,
	YELLOW=14,
	WHITE=15
	//END of NEW CODE EX1
};

#endif