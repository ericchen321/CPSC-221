#define CATCH_CONFIG_MAIN
#include <iostream>
#include "cs221util/catch.hpp"
#include "stack.h"
#include "queue.h"
//using namespace cs221util;
using namespace std;

TEST_CASE("deque::isEmpty"){
    cout << "testing isEmpty..." << endl;
    Deque<int> d;
    REQUIRE(d.isEmpty()==true);
    d.pushR(100);
    REQUIRE(d.isEmpty()==false);
}

TEST_CASE("deque::pushR and peekR"){
    cout << "testing pushR and peekR" << endl;
    Deque<int> d;
    d.pushR(100);
    REQUIRE(d.peekR()==100);
    REQUIRE(d.isEmpty()==false);
    d.pushR(200);
    REQUIRE(d.peekR()==200);
    REQUIRE(d.isEmpty()==false);
}

TEST_CASE("deque::popR"){
    cout << "testing popR" << endl;
    Deque<int> d;
    for(int i=10; i<=80; i+=10){
        d.pushR(i);
    }
    REQUIRE(d.popL()==10);
    REQUIRE(d.isEmpty()==false);
    REQUIRE(d.popL()==20);
    REQUIRE(d.isEmpty()==false);
    REQUIRE(d.popL()==30);
    REQUIRE(d.isEmpty()==false);
    REQUIRE(d.popR()==80);
    REQUIRE(d.isEmpty()==false);
    REQUIRE(d.popR()==70);
    REQUIRE(d.isEmpty()==false);
    REQUIRE(d.popR()==60);
    REQUIRE(d.isEmpty()==false);
    REQUIRE(d.popR()==50);
    REQUIRE(d.isEmpty()==false);
    REQUIRE(d.popR()==40);
    REQUIRE(d.isEmpty()==true);
    d.pushR(90);
    REQUIRE(d.peekR()==90);
    REQUIRE(d.isEmpty()==false);
    REQUIRE(d.popR()==90);
    REQUIRE(d.isEmpty()==true);
}

TEST_CASE("deque::popL and peekL"){
    cout << "testing popL and peekL" << endl;
    Deque<int> d;
    for(int i=10; i<=50; i+=10){
        d.pushR(i);
    }
    REQUIRE(d.peekL()==10);
    REQUIRE(d.popL()==10);
    REQUIRE(d.isEmpty()==false);
    REQUIRE(d.peekL()==20);
    REQUIRE(d.popL()==20);
    REQUIRE(d.isEmpty()==false);
    REQUIRE(d.popL()==30);
    REQUIRE(d.isEmpty()==false);
    REQUIRE(d.popL()==40);
    REQUIRE(d.isEmpty()==false);
    REQUIRE(d.popL()==50);
    REQUIRE(d.isEmpty()==true);
    d.pushR(60);
    REQUIRE(d.peekR()==60);
    REQUIRE(d.peekL()==60);
    REQUIRE(d.isEmpty()==false);
    REQUIRE(d.popL()==60);
    REQUIRE(d.isEmpty()==true);
}

/*
TEST_CASE("stack::basic functions","[weight=1][part=stack]"){
    cout << "Testing Stack..." << endl;
    Stack<int> intStack;
    vector<int> result;
    vector<int> expected;
    for (int i = 10; i > 0; i--) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intStack.push(i);
    }
    while (!intStack.isEmpty()) {
        result.push_back(intStack.pop());
    }
    REQUIRE( result == expected);
}
TEST_CASE("queue::basic functions","[weight=1][part=queue]"){
    Queue<int> intQueue;
    vector<int> result;
    vector<int> expected;
    for (int i = 1; i <= 10; i++) {
        expected.push_back(i);
    }
    for (int i = 1; i <= 10; i++) {
        intQueue.enqueue(i);
    }
    while (!intQueue.isEmpty()) {
        result.push_back(intQueue.dequeue());
    }
    REQUIRE( result == expected);
}
*/
