#ifndef HANDLEUST_H
#define HANDLEUST_H

/*#include <QtCore/qglobal.h>
#if defined(LIBCANTAMUS)
#   define LIBCANTAMUS_EXPORT Q_DECL_EXPORT
#else
#   define LIBCANTAMUS_EXPORT Q_DECL_IMPORT
#endif

#include <QFileOpenEvent>
#include <QFileDevice>
#include <QTextStream>*/
#include <string>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <wchar.h>
namespace ust
{
    class ustHandler;
}

class ustHandler
{
    public:
        explicit ustHandler();
        std::string ustNoteLyric[10000];
        int ustNoteLength[10000];
        int ustNoteCount;
        int ustNotePos[10000];
        int i;
        int l;
        int pi;
        int ustNoteID;
        int isRest[10000];
        char ustDoc[9999];
        std::string ustOFile;
        FILE file;
        FILE saveCVS;
        std::ifstream in;
        std::string readed;
        std::string lineScan;
        int lines = 0;
        std::string l1 = "";
    //enum countOfLyrics;
        void ustLoader(const std::string &ustFile);
        void printToCVS(const std::string &saveFile);
        void closeFile(int state = 0);
    protected:

        void parseText(const std::string &notereader);
        void initializeValues();

};
#endif // HANDLEUST_H
