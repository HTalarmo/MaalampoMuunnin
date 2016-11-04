#include "dataprocessor.h"

DataProcessor::DataProcessor(std::string ownName, std::string fileName)
{
    // set the output file name
    if(fileName.size() == 0) outFileName = defaultOutFileName + ".csv";
    else outFileName = fileName + ".csv";

    int index = ownName.find_last_of('\\');
    ownName_ = ownName.substr(index+1);

    // scan all the files in the directory
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(".")) != NULL)
    {
        while((ent=readdir(dir)) != NULL)
        {
            std::string name(ent->d_name);
            if(ent->d_name[0] == '.' || ent->d_name == ownName_ || name.find(".csv") == std::string::npos)
            {
                continue;
            }

            fileList_.push_back(ent->d_name);
        }
    }
    else
    {
        perror("Could not open directory.");
    }
}

bool DataProcessor::run()
{
    if(fileList_.size() == 0)
    {
        return false;
    }
    scanHeaders();

    // the main loop
    for(std::string fileName : fileList_)
    {
        processFile(fileName);
    }

    writeToFile();

    std::cout << "Data kirjoitettu tiedostoon " << outFileName << "" << std::endl;
}

void DataProcessor::scanHeaders()
{
    std::ifstream file;
    file.open(fileList_.at(0));

    std::string line;
    headerList_ = {"PVM"};

    // skip first 3 lines
    for(int i = 0; i < 3; ++i)
    {
        std::getline(file, line);
    }

    // check each line
    while(getline(file, line))
    {
        size_t index = line.find(';');

        // if no ; is found or the line is empty, skip
        if(line.size() == 0 || index == std::string::npos) continue;

        std::string hdr = line.substr(0, index);
        std::string val = line.substr(index+1);
        int i;

        // if header is in the unit header list
        if(find(unitHeaders.begin(), unitHeaders.end(), hdr) != unitHeaders.end())
        {
            // separate the unit from the value to add to the header
            std::string unit;

            // find where the unit ends
            for(i = val.size(); i > 0; i--)
            {
                if(isdigit(val[i]))
                {
                    i++;
                    break;
                }
            }

            // if i != 0, throw the rest of the value to the end of the header
            // otherwise will be skipped to avoid problems
            if(i != 0)
            {
                hdr += " (" + val.substr(i) + ")";
            }
        }

        // add header to the list
        headerList_.push_back(hdr);
    }
}

bool DataProcessor::processFile(std::string fileName)
{

    // open file and get all the contents into a string
    std::ifstream file;
    file.open(fileName, std::ios::in);

    std::string line;

    // skip first two lines
    for(int i = 0; i < 2; ++i)
    {
        std::getline(file, line);
    }

    // setup variables
    Time time;
    std::vector<std::string> data;

    // read the date line and set the date
    std::getline(file, line);

    // if the date line was empty, something wrong with file
    if(line.size() == 0) return false;

    time = toDate(line);

    // the main file read loop
    while(getline(file, line))
    {
        // if line is empty, skip
        if(line.size() == 0) continue;

        // split line by the ; that separates the csv. If not 2+ parts, skip
        size_t index = line.find(";");
        if(index == std::string::npos) continue; // No ; in the string
        size_t index2 = line.find(";", index+1);

        std::string head;
        std::string val;

        head = line.substr(0, index);
        val = line.substr(index+1, index2-index-1);

        // add the data to the correct place in the vector
        data.push_back(val);
    }

    dataStorage_[time] = data;

    // all file lines have been read. Return true and plop data in
    file.close();
    return true;
}

bool DataProcessor::writeToFile()
{
    std::ofstream file;
    file.open(outFileName);

    // write the headers
    for(std::string head : headerList_)
    {
        file << ";" << head;
    }

    file << "\n";

    // start writing the data in
    std::map<Time, std::vector< std::string> >::iterator it;
    for(it = dataStorage_.begin(); it != dataStorage_.end(); it++)
    {
        // the timestamp
        file << it->first.toString();

        // loop through the values
        for(std::string val : it->second)
        {
            file << ";" << val;
        }

        file << "\n";
    }

    file.close();
}

Time DataProcessor::toDate(std::string str)
{
    size_t index;
    size_t oldIndex;
    Time time;

    // get days
    index = str.find('.');
    time.d = stoi(str.substr(0, index));

    // get months
    oldIndex = index+1;
    index = str.find('.', oldIndex);
    time.m = stoi(str.substr(oldIndex, index-oldIndex));

    // get years
    oldIndex = index+1;
    index = str.find(';', oldIndex);
    time.y = stoi(str.substr(oldIndex, index-oldIndex));

    // get h ours
    oldIndex = index+1;
    index = str.find(':', oldIndex);
    time.h = stoi(str.substr(oldIndex, index-oldIndex));

    // get mins
    oldIndex = index+1;
    time.min = stoi(str.substr(oldIndex, str.length()-oldIndex ));

    return time;
}
