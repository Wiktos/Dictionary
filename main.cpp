#include <iostream>

#include "dictionary.h"

int main()
{

    {//test constructor
        Dictionary<int, int> test;
        if(!test.is_empty())
            std::cerr << "Log : default constructor error is_empty() == false\n";

        if(test.height())
            std::cerr << "Log : default constructor error height() != 0\n";
    }

    {//test insert method
        Dictionary<int, int> test;
        test.insert(1, 1);

        if(test.is_empty())
            std::cerr << "Log : insert method error is_empty() == true\n";
        if(test.height() != 0)
            std::cerr << "Log : insert method error height() != 0\n";

        test.insert(2, 2);
        if(test.height() != 1)
            std::cerr << "Log : insert method error height() != 1\n";
    }

    {//test graph
        Dictionary<int, int> test;
        for(int i = 0; i < 10; i++)
            test.insert(i, i);

        test.graph();
    }

    {//test contain method
        Dictionary<int, int> test;
        test.insert(1, 1);

        if(!test.contain(1))
            std::cerr << "Log : constain method error contain(1) == false\n";
        if(test.contain(2))
            std::cerr << "Log : constain method error contain(2) == true\n";
    }

    return 0;
}
