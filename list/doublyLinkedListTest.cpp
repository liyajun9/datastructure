//
// Created by ralph on 4/1/20.
//

#include <gtest/gtest.h>
#include "doublyLinkedList.h"

TEST(DoublyLinkedListTest, insertAsLast)
{
    List<int> listi;

    listi.insertAsLast(34);
    listi.insertAsLast(23);
    listi.insertAsLast(33);
    listi.insertAsLast(87);
    listi.insertAsLast(51);

    EXPECT_EQ(listi.size(), 5)<<"list size should be 5";
    EXPECT_EQ(listi[0], 34);
    EXPECT_EQ(listi[1], 23);
    EXPECT_EQ(listi[2], 33);
    EXPECT_EQ(listi[3], 87);
    EXPECT_EQ(listi[4], 51);

    listi.sort();
    EXPECT_EQ(listi.size(), 5);
    EXPECT_EQ(listi[0], 23);
    EXPECT_EQ(listi[1], 33);
    EXPECT_EQ(listi[2], 34);
    EXPECT_EQ(listi[3], 51);
    EXPECT_EQ(listi[4], 87);


    List<std::string> list;
    list.insertAsLast("34");
    list.insertAsLast("23");
    list.insertAsLast("33");
    list.insertAsLast("87");
    list.insertAsLast("51");

    EXPECT_EQ(list.size(), 5);
    EXPECT_STREQ(list[0].c_str(), "34");
    EXPECT_STREQ(list[1].c_str(), "23");
    EXPECT_STREQ(list[2].c_str(), "33");
    EXPECT_STREQ(list[3].c_str(), "87");
    EXPECT_STREQ(list[4].c_str(), "51");

    list.sort();
    EXPECT_EQ(list.size(), 5);
    EXPECT_STREQ(list[0].c_str(), "23");
    EXPECT_STREQ(list[1].c_str(), "33");
    EXPECT_STREQ(list[2].c_str(), "34");
    EXPECT_STREQ(list[3].c_str(), "51");
    EXPECT_STREQ(list[4].c_str(), "87");
}