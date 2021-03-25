/*
libcantumus: foundation library for Cantamus
License: MIT
libcantamus provides read/write functionality for UST and CVS files
TODO:
- complete UST mechanism;
- complete CVS mechanism;
Possible features:
- oto handling;
- undo/redo system*/

#include "handleust.h"
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <strings.h>
#include <string>

using namespace std;

ustHandler::ustHandler()
{
    i=0;
    l=0;
    ustNoteID=0;
    pi=0; //Is not a pie
    //ustNoteLyric.resize(10000);
    //isRest.resize(10000);
}

void ustHandler::parseText(const std::string &notereader)
{

}
void ustHandler::ustLoader(const std::string &ustFile)
{
    closeFile();
    //file.setFileName(ustFile);
    //file.open(QFile::ReadOnly | QFile::Text);
    std::ifstream ustString;
    ustString.open(ustFile.c_str());
    ustOFile = ustFile;
    int noteNumber = 0;
    std::string actualLine;
    int mil = 0;
    int cent = 0;
    int dec = 0;
    int un = 0;
    int cvsNum = 0;
    std::string mil2 = std::to_string(mil);
    std::string cent2 = std::to_string(cent);
    std::string dec2 = std::to_string(dec);
    std::string un2 = std::to_string(un);
    std::string cvsNum2 = std::to_string(cvsNum);
    std::getline(ustString,actualLine);
    while(actualLine!=l1)
    {
        l1=actualLine;
        std::getline(ustString,actualLine);
        lines++;
        std::cout << actualLine<<std::endl;

    }
    ustString.close();
    ustString.open(ustFile.c_str());
/*=std::string("[#TRACKEND]"*/
    //while(!(actualLine.size()>0))
    for (int j=0;j<=lines;j++)
    {
        std::getline(ustString,actualLine);

        if(ustFile.substr(ustFile.length()-3)==std::string("ust"))
        {
            if (actualLine.substr(0,7) ==std::string("[#")+mil2+cent2+dec2+un2+std::string("]"))
            {
                ustNoteCount=ustNoteCount+1;
                un = un + 1;
                un2 = std::to_string(un);
                if (un==10)
                {
                    un=0;
                    un2=std::to_string(un);
                    dec = dec+1;
                    dec2= std::to_string(dec);

                }
                else
                {
                }
                if(dec==10)
                {
                    dec=0;
                    dec2=std::to_string(dec);
                    cent=cent+1;
                    cent2=std::to_string(cent);

                }
                else
                {
                }
                if (cent==10)
                {
                    cent=0;
                    cent2=std::to_string(cent);
                    mil=mil+1;
                    mil2=std::to_string(mil);

                }
                else
                {
                }

            }
            else
            {
            }
            if (actualLine.substr(0,7)=="Length=")
            {
                bool ok;
                std::string str(actualLine.substr(7));

                ustNoteLength[i]=std::stoi(str);
                i=i+1;

            }
            else
            {
            }
            if (actualLine.substr(0,6)=="Lyric=")
            {
                std::string lir(actualLine.substr(6));

                ustNoteLyric[l]=lir;
                //std::cout<<lir<<std::endl;

                if(actualLine.substr(6,1)==std::string("R")||lir==std::string("r")||lir==std::string(" "))
                {
                    isRest[l] = 0;
                }
                else
                {
                    isRest[l] = 1;
                }
                l=l+1;
                //std::cout<<ustNoteLyric[l]<<" "<<isRest[l]<<std::endl;
            }
            else
            {

            }
            if (actualLine.substr(0,8)=="NoteNum=")
            {
                bool ok;
                std::string pitch(actualLine.substr(8));
                ustNotePos[pi]=stoi(pitch);
                ustNotePos[pi]-=23;
                pi=pi+1;
            }

        //i=0;
        }
//}
//}
        if(ustFile.substr(ustFile.length()-3)==std::string("cvs"))
        {
            if(actualLine.substr(0,10)==std::string("<note num="))
            {
                ustNoteCount=ustNoteCount+1;
                cvsNum=cvsNum+1;
                cvsNum2=std::to_string(cvsNum);
            }
            else
            {
            }
            if(actualLine.substr(0,10)==std::string("<rest num="))
            {
                ustNoteCount=ustNoteCount+1;
                std::string cvsRest("R");
                ustNoteLyric[l]=cvsRest.c_str();
                isRest[l]=0;
                l=l+1;

                cvsNum=cvsNum+1;
                cvsNum2=std::to_string(cvsNum);
            }
            else
            {}
            if(actualLine.substr(0,6)=="lyric=")
            {
                std::string cvsLir(actualLine.substr(6));
                ustNoteLyric[l]=cvsLir.c_str();
                isRest[l] = 1;
                l=l+1;
            }
            else
            {}
            if(actualLine.substr(0,6)=="pitch=")
            {
                bool ok;
                std::string cvsPitch(actualLine.substr(6));
                ustNotePos[pi]=std::stoi(cvsPitch);
                pi=pi+1;
            }
            else
            {}
            if(actualLine.substr(0,7)=="length=")
            {
                bool ok;
                std::string cvsLength(actualLine.substr(7));
                ustNoteLength[i]=std::stoi(cvsLength);
                i=i+1;
            }
            else{}
            if(j>sizeof(ustString)||actualLine.substr(0,11)=="[#TRACKEND]")
            {
               break;
            }
        }
        //std::cout << actualLine << endl;
    }
        //std::cout << ustNoteCount <<endl;
}
void ustHandler::printToCVS(const std::string &saveFile)
{
    //saveCVS.setFileName(saveFile);
    //saveCVS.open(QFile::WriteOnly | QFile::Text);
    std::ofstream saveStream;
    saveStream.open(saveFile.c_str());
    ustOFile = saveFile;
    //saveStream.resize(0);
    saveStream.seekp(0);
    std::cout<< saveFile<<" "<<saveFile.length()-3<<endl;

    if(!(saveFile.substr(saveFile.length()-3)==std::string("ust")))
    {
        saveStream << "<sheet type = snippet>\n";
    }
    for(ustNoteID=0;ustNoteID<ustNoteCount;++ustNoteID)
    {
        std::string z;
        if(ustNoteID<10)
        {
            z = "000";
        }
        else if(ustNoteID<100)
        {
            z = "00";
        }
        else if(ustNoteID<1000)
        {
            z = "0";
        }
        else
        {
            z = "";
        }
        std::cout << isRest[ustNoteID] << "\n";
        if(isRest[ustNoteID]==0)
        {
                if(saveFile.substr(saveFile.length()-3)==std::string("ust"))
                {

                    saveStream << "[#" << z << (ustNoteID) <<"]\n"
                            <<"Length=" << ustNoteLength[ustNoteID] << "\n"
                            <<"Lyric=R\n" << "NoteNum="<<ustNotePos[ustNoteID+23]<<"\n";
                }
                else
                {
                    saveStream << "<rest num="<<(ustNoteID)<<">\n"
                    <<"length="<<ustNoteLength[ustNoteID]<<"\n"
                    <<"</rest>\n";
                }
        }
        else
        {
            if(saveFile.substr(saveFile.length()-3)==std::string("ust"))
            {
                ustNotePos[ustNoteID] = ustNotePos[ustNoteID] + 23;

                saveStream << "[#" << z << (ustNoteID) <<"]\n"
                            <<"Length=" << ustNoteLength[ustNoteID] << "\n"
                            <<"Lyric=" << ustNoteLyric[ustNoteID] << "\n"
                            << "NoteNum="<<ustNotePos[ustNoteID]<<"\n";
            }
            else
            {
                saveStream << "<note num="<<(ustNoteID)<<">\n"
                                <<"lyric="<<ustNoteLyric[ustNoteID]<<"\n"
                                <<"pitch="<<ustNotePos[ustNoteID]<<"\n"
                                <<"length="<<ustNoteLength[ustNoteID]<<"\n"
                                    <<"</note>\n";
            }
        }

    }
    if(!(saveFile.substr(saveFile.length()-3)==std::string("ust")))
    {
        saveStream << "</sheet>";
    }
    else
    {
        saveStream << "[#TRACKEND]";
    }
}
void ustHandler::initializeValues()
{

}
void ustHandler::closeFile(int state)
{
    //file.close();
    //saveCVS.close();
    i=0;
    l=0;
    pi=0;
    ustNoteCount=0;

}
