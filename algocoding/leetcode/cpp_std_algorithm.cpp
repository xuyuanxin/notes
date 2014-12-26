bool IsOdd (int i) {
  return ((i%2)==1);
}

/* 
 find_if example
 Output:
 The first odd value is 25
*/
int cpp_algorithm_find_if () 
{
    std::vector<int> myvector;

    myvector.push_back(10);
    myvector.push_back(25);
    myvector.push_back(40);
    myvector.push_back(55);

    std::vector<int>::iterator it = std::find_if (myvector.begin(), myvector.end(),IsOdd);
    std::cout << "The first odd value is " << *it << '\n';

    return 0;
}


/************************ transform algorithm example *************************/
int op_increase (int i) { return ++i; }

/* output:foo contains: 21 41 61 81 101*/
int cpp_algorithm_transform () 
{
    std::vector<int> foo;
    std::vector<int> bar;

    for (int i=1; i<6; i++)
        foo.push_back (i*10);  // foo: 10 20 30 40 50

    bar.resize(foo.size());   // allocate space

    std::transform (foo.begin(), foo.end(), bar.begin(), op_increase);
                                                  // bar: 11 21 31 41 51

    // std::plus adds together its two arguments:
    std::transform (foo.begin(), foo.end(), bar.begin(), foo.begin(), std::plus<int>());
                                                  // foo: 21 41 61 81 101

    std::cout << "foo contains:";
												  
    for (std::vector<int>::iterator it=foo.begin(); it!=foo.end(); ++it)
        std::cout << ' ' << *it;
	
    std::cout << '\n';

    return 0;
}
