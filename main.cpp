#include <iostream>

#include "dictionary.h"

int main()
{

    {//test constructor
        Dictionary test;
        if(!test.is_empty())
            std::cerr << "Log : default constructor error is_empty() == false\n";

        if(test.height())
            std::cerr << "Log : default constructor error height() != 0\n";

    }

    {//test insert method
        Dictionary test;
        test.insert(1, 1);

        if(test.is_empty())
            std::cerr << "Log : insert method error is_empty() == true\n";
        if(test.height() != 1)
            std::cerr << "Log : insert method error height() != 1\n";

        test.insert(2, 2);
        if(test.height() != 2)
            std::cerr << "Log : insert method error height() != 1\n";

        try{
            test.insert(1, 1);
            std::cerr << "Log : insert method DictionaryException should be thrown\n";
        }
        catch(Dictionary::DictionaryException& ex)
        {}

    }

    return 0;
}
