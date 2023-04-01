#include "TestWrapper.h"


// implementation code of WrapperFactory - do NOT modify the next 5 lines
AbstractWrapper* WrapperFactory::wrapper = 0;
AbstractWrapper* WrapperFactory::createWrapper() {
    if (wrapper == 0)
        wrapper = new TestWrapper;
    return wrapper;
}
// Do not modify the following line
volatile bool AbstractWrapper::GlobalStop = false;

// a default constructor
TestWrapper::TestWrapper() {
    // create any objects here as instance variables of this class
    // as well as any initialization required for your spa program
    pkb.initializePkb();
    writePKB.setInstancePKB(pkb);
    readPKB.setInstancePKB(pkb);
}

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename) {
    auto start = std::chrono::high_resolution_clock::now();

    try {
        sourceProcessor.processFile(filename, &writePKB, &readPKB);
    } catch (std::exception e) {
        ::exit(0);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto difference = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "\n--------------------------------------------------------------------------------------\n";
    std::cout << "Time taken to parse source code: " << difference << "ms";
    std::cout << "\n--------------------------------------------------------------------------------------\n\n";
}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results) {

    auto start = std::chrono::high_resolution_clock::now();

    // call your evaluator to evaluate the query here
    // ...code to evaluate query..
    vector<string> res = qps.processQueries(query, readPKB);
    for (std::string val : res) {
        results.push_back(val);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto difference = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    pkb.clearCache();
    auto end2 = std::chrono::high_resolution_clock::now();
    auto difference2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - end).count();
    std::cout << "\n--------------------------------------------------------------------------------------\n";
    std::cout << "Time taken to evaluate query: " << difference << "ms\n";
    std::cout << "Time taken to clear PKB's cache: " << difference2 << "ms";
    std::cout << "\n--------------------------------------------------------------------------------------\n\n";

    // store the answers to the query in the results list (it is initially empty)
    // each result must be a string.
}
