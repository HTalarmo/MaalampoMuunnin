#include "dataprocessor.h"

int main(int argc, char *argv[])
{
    DataProcessor* processor;

    if(argc == 2)
    {
        processor = new DataProcessor(argv[0], argv[1]);
    }
    else
    {
        processor = new DataProcessor(argv[0]);
    }
    if(!processor->run())
    {
        std::cout << "An error occurred." << std::endl;
    }

}

