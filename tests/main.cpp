#include <iostream>

#include "../templates/dictionary.h"

int main()
{

    {//test constructors
        Dictionary<int, int> test;
        if(!test.is_empty())
            std::cerr << "Log : default constructor error is_empty() == false\n";

        if(test.height())
            std::cerr << "Log : default constructor error height() != 0\n";

        test.insert(1, 1);
        Dictionary<int, int> test2(test);
        if(test2.is_empty())
            std::cerr << "Log : copy constructor error is_empty() == true\n";

        if(test2.height())
            std::cerr << "Log : copy constructor error height() != 1\n";

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

        try{
            test.insert(2, 2);
            std::cerr << "Log : insert method exception expected\n";
        }
        catch(Dictionary<int, int>::DictionaryException& ex)
        {}
    }

    {//test contain method
        Dictionary<int, int> test;
        test.insert(1, 1);

        if(!test.contain(1))
            std::cerr << "Log : constain method error contain(1) == false\n";
        if(test.contain(2))
            std::cerr << "Log : constain method error contain(2) == true\n";
    }

    {//test op=
        Dictionary<int, int> test;
        for(int i = 0; i < 10; i++)
            test.insert(i, i);

        Dictionary<int, int> test2;
        test2 = test;

        if(test2.height() != 3)
            std::cerr << "Log : op= error height() != 3\n";
    }

    {//test get_min get_max get_value methods
        Dictionary<int, int> test;
        for(int i = 0; i < 10; i++)
            test.insert(i, i);

        if(test.get_max() != 9)
            std::cerr << "Log : get_max error returned != 9\n";
        if(test.get_min() != 0)
            std::cerr << "Log : get_min error returned != 0\n";

        if(test.get_value(4) != 4)
            std::cerr << "Log : get_value error\n";
    }

    {//test remove method
        Dictionary<int, int> test;
        for(int i = 0; i < 10; i++)
            test.insert(i, i);

        try{
            test.remove(3);
        }
        catch(Dictionary<int, int>::DictionaryException& ex){
            std::cout << ex.what() << '\n';
        }
        test.graph(std::cout);
    }


    {//test graph
        Dictionary<int, int> test;
        for(int i = 0; i < 10; i++)
            test.insert(i, i);

        //test.graph(std::cout);
    }

    return 0;
}
