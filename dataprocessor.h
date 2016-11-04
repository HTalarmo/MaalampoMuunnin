#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <iostream>
#include <fstream>
#include <dirent.h>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>

#include "utils.h"
// Käy läpi kaiken datan mitä kansiosta löytyy ja parsee sen tiedostoon


class DataProcessor
{
public:
    // takes in the output filename
    DataProcessor(std::string ownName, std::string fileName = "");

    bool run(); // returns false if failed

private:

    const std::string defaultOutFileName = "MaalampoData";
    const std::vector< std::string > unitHeaders = {"Pumpun optimointi", "Lisälämpöraja", "Lisäkäyttövesi jakso", "Lisäkäyttövesi jakso", "Sähkövastuksen teho", "Paluurajoitus",
                                                    "Hystereesi: Lämmitys", "Hystereesi: Lämm maks", "Lisälämpöraja", "Desinfiointi LT", "Hystereesi:Käyttövesi",
                                                    "Min Liuos LT", "Kuumakaasuraja", "Yöpudotus pois ulkoLT", "Maks menovesi", "Min. lämmönlähdeLT", "Virtauksen rajoitus",
                                                    "Käyttöveden max. LT", "Minimi järjestelmäLT", "Teho: lämmitys (nim)", "Teho: Lämmitys (min)", "Teho: Käyttövesi",
                                                    "Teho: Liuospumppu", "Lämmönsäätökäyrä Lämmitys", "Lämmönsäätökäyrä 1. Shunttaus", "1.Komp käyntiaika", "1.Komp käynnistykset",
                                                    "Keskim. käyntiaika", "Käyntiaika: 1.Lisäl", "Käyntiaika: Kompres", "Käyntiaika: Lämmitys", "Käyntiaika: Lämminv",
                                                    "Meno", "Paluu", "Paluu asetus", "Kuumakaasu", "Ulkolämpötila", "Käyttövesi", "Käyttövesi asetus", "Liuos sisään",
                                                    "Liuos ulos", "1. Shunttaus meno", "1. Shunttaus asetus", "Maks menovesi", "Imu kompressorille", "Tulistus", "Tulistuksen asetus"};
    std::string outFileName;
    std::string ownName_;

    std::vector<std::string> fileList_; // list of all the files in the directory

    // headerList_ is where all the headers are stored in to make sure that they all stay in the same order
    std::vector<std::string> headerList_;

    // dataStorage saves the data vectors by their date
    std::map<Time, std::vector< std::string> > dataStorage_;

    // methods

    void scanHeaders();
    bool processFile(std::string fileName); // returns false if problems happened
    bool writeToFile(); // returns false if problems

    // turns the string format time into the time struct
    Time toDate(std::string str);

};

#endif // DATAPROCESSOR_H
