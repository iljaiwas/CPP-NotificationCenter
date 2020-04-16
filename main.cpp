/*
 *  main.cpp
 *  Notification Center CPP
 *
 *  Created by Jonathan Goodman on 11/23/13.
 *  Copyright (c) 2013 Jonathan Goodman. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <iostream>
#include "NotificationCenter.hpp"

class Foo {
    
public:
    typedef NotificationCenter::notification_user_info_t userInfo_t;

    void func(userInfo_t userInfo)
    {
        printf("Hello std::bind!\n");
        printf("Recieved notification %s!\n", userInfo["key"]);
    }
};

void runNotification()
{
    typedef NotificationCenter::notification_user_info_t userInfo_t;

    auto i1 = NotificationCenter::defaultNotificationCenter()->addObserver([](userInfo_t userInfo){
        printf("Recieved notification %s!\n", userInfo["key"]);},
        "Poster");


    auto i2 = NotificationCenter::defaultNotificationCenter()->addObserver([](const userInfo_t& userInfo){printf("Recieved notification %d!\n", 2);}, "Poster");
    auto i3 = NotificationCenter::defaultNotificationCenter()->addObserver([](const userInfo_t& userInfo){printf("Recieved notification %d!\n", 3);}, "Poster");
    auto i4 = NotificationCenter::defaultNotificationCenter()->addObserver([](const userInfo_t& userInfo){printf("Recieved notification %d!\n", 4);}, "Poster");
    auto i5 = NotificationCenter::defaultNotificationCenter()->addObserver([](const userInfo_t& userInfo){printf("Recieved notification %d!\n", 5);}, "Poster");
    NotificationCenter::defaultNotificationCenter()->addObserver([](const userInfo_t& userInfo){printf("Recieved notification %d!\n", 6);}, "Poster");
    NotificationCenter::defaultNotificationCenter()->addObserver([](const userInfo_t& userInfo){printf("Recieved notification %d!\n", 7);}, "Poster");
    NotificationCenter::defaultNotificationCenter()->addObserver([](const userInfo_t& userInfo){printf("Recieved notification %d!\n", 8);}, "Poster");

    userInfo_t userInfo;
    const char* value = "value 1";

    userInfo["key"] = (void*) value;
    NotificationCenter::defaultNotificationCenter()->postNotification("Poster", userInfo);
    
    printf("============\n");
    
    NotificationCenter::defaultNotificationCenter()->removeObserver("Poster", i1);
    
    NotificationCenter::defaultNotificationCenter()->postNotification("Poster");
    
    printf("============\n");
    
    NotificationCenter::defaultNotificationCenter()->removeObserver("Poster", i2);
    
    NotificationCenter::defaultNotificationCenter()->postNotification("Poster");
    
    printf("============\n");
    
    NotificationCenter::defaultNotificationCenter()->removeObserver("Poster", i3);
    
    NotificationCenter::defaultNotificationCenter()->postNotification("Poster");
    
    printf("============\n");
    
    NotificationCenter::defaultNotificationCenter()->removeObserver("Poster", i4);
    
    NotificationCenter::defaultNotificationCenter()->postNotification("Poster");
    
    printf("============\n");
    
    NotificationCenter::defaultNotificationCenter()->removeObserver("Poster", i5);
    
    NotificationCenter::defaultNotificationCenter()->postNotification("Poster");
    
    printf("============\n");
    
    NotificationCenter::defaultNotificationCenter()->removeAllObservers("Poster");
    
    NotificationCenter::defaultNotificationCenter()->postNotification("Poster");
    
    printf("============\n");
    
    NotificationCenter::defaultNotificationCenter()->addObserver([](const userInfo_t& userInfo){printf("Called by iterator!\n");}, "Second Poster");
    NotificationCenter::notification_const_itr_t itr = NotificationCenter::defaultNotificationCenter()->getNotificationIterator("Second Poster");
    NotificationCenter::defaultNotificationCenter()->postNotification(itr);
    printf("============\n");
    
    Foo myFoo;
    
    NotificationCenter::defaultNotificationCenter()->addObserver(std::bind(&Foo::func, myFoo, std::placeholders::_1 ), "Second Poster");
    NotificationCenter::defaultNotificationCenter()->postNotification("Second Poster", userInfo);
    
}

int main(int argc, const char * argv[])
{
    runNotification();
    
    return 0;
}

