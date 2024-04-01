#include <map>

#include "tests_init.h"

TEST(map, DefaultContructor) {
  s21::map<int, char> s21_map;
  std::map<int, char> std_map;
  EXPECT_EQ(s21_map.size(), std_map.size());
}

TEST(map, InitListConstructor) {
  s21::map<int, char> s21_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> std_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  EXPECT_EQ(s21_map.size(), std_map.size());

  auto s21_it = s21_map.begin();
  auto std_it = std_map.begin();

  for (; s21_it != s21_map.end(); ++s21_it, ++std_it) {
    EXPECT_TRUE((*s21_it).first == (*std_it).first);
    EXPECT_TRUE((*s21_it).second == (*std_it).second);
  }
}

TEST(map, CopyConstructor) {
  s21::map<int, char> s21_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::map<int, char> s21_map_copy(s21_map);
  std::map<int, char> std_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> std_map_copy(std_map);

  EXPECT_EQ(s21_map_copy.size(), std_map_copy.size());

  auto s21_it = s21_map_copy.begin();
  auto std_it = std_map_copy.begin();

  for (; s21_it != s21_map_copy.end(); ++s21_it, ++std_it) {
    EXPECT_TRUE((*s21_it).first == (*std_it).first);
    EXPECT_TRUE((*s21_it).second == (*std_it).second);
  }
}

TEST(map, MoveConstructor) {
  s21::map<int, char> s21_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::map<int, char> s21_map_copy(std::move(s21_map));
  std::map<int, char> std_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> std_map_copy(std::move(std_map));

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map_copy.size(), std_map_copy.size());

  auto s21_it = s21_map_copy.begin();
  auto std_it = std_map_copy.begin();

  for (; s21_it != s21_map_copy.end(); ++s21_it, ++std_it) {
    EXPECT_TRUE((*s21_it).first == (*std_it).first);
    EXPECT_TRUE((*s21_it).second == (*std_it).second);
  }
}

TEST(map, CopyAssignment) {
  s21::map<int, char> s21_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::map<int, char> s21_map_copy = s21_map;
  std::map<int, char> std_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> std_map_copy = std_map;

  EXPECT_EQ(s21_map_copy.size(), std_map_copy.size());

  auto s21_it = s21_map_copy.begin();
  auto std_it = std_map_copy.begin();

  for (; s21_it != s21_map_copy.end(); ++s21_it, ++std_it) {
    EXPECT_TRUE((*s21_it).first == (*std_it).first);
    EXPECT_TRUE((*s21_it).second == (*std_it).second);
  }
}

TEST(map, MoveAssignment) {
  s21::map<int, char> s21_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::map<int, char> s21_map_copy = std::move(s21_map);
  std::map<int, char> std_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> std_map_copy = std::move(std_map);

  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map_copy.size(), std_map_copy.size());

  auto s21_it = s21_map_copy.begin();
  auto std_it = std_map_copy.begin();

  for (; s21_it != s21_map_copy.end(); ++s21_it, ++std_it) {
    EXPECT_TRUE((*s21_it).first == (*std_it).first);
    EXPECT_TRUE((*s21_it).second == (*std_it).second);
  }
}

TEST(map, MapAtOperator) {
  s21::map<char, std::string> s21_map = {{1, "Hi"}, {2, "Hola"}, {3, "Privet"}};
  std::map<char, std::string> std_map = {{1, "Hi"}, {2, "Hola"}, {3, "Privet"}};

  s21_map[1] = "abc";
  s21_map[2] = "def";
  std_map[1] = "abc";

  EXPECT_TRUE(s21_map[1] == std_map[1]);
  EXPECT_FALSE(s21_map[2] == std_map[2]);
  EXPECT_TRUE(s21_map[3] == std_map[3]);

  s21_map[4] = "zxc";
  std_map[4] = "zxc";

  EXPECT_TRUE(s21_map[4] == std_map[4]);
}

TEST(map, MapAtOutOfRange) {
  s21::map<char, std::string> s21_map = {{1, "Hi"}, {2, "Hola"}, {3, "Privet"}};

  EXPECT_THROW(s21_map.at(5), std::out_of_range);
}

TEST(map, MapAT) {
  s21::map<char, std::string> s21_map = {{1, "Hi"}, {2, "Hola"}, {3, "Privet"}};
  std::map<char, std::string> std_map = {{1, "Hi"}, {2, "Hola"}, {3, "Privet"}};

  s21_map.at(1) = "abc";
  s21_map.at(2) = "def";
  std_map.at(1) = "abc";

  EXPECT_TRUE(s21_map[1] == std_map[1]);
  EXPECT_FALSE(s21_map[2] == std_map[2]);
  EXPECT_TRUE(s21_map[3] == std_map[3]);
}

TEST(map, Size) {
  s21::map<int, char> s21_map;
  std::map<int, char> std_map;

  EXPECT_TRUE(s21_map.empty() == std_map.empty());
  s21_map.insert({1, 'a'});
  EXPECT_FALSE(s21_map.empty() == std_map.empty());
  EXPECT_EQ(s21_map.size(), 1);
  s21_map.clear();
  EXPECT_TRUE(s21_map.empty() == std_map.empty());
}

TEST(map, Insertion) {
  s21::map<int, char> s21_map;
  std::map<int, char> std_map;

  s21_map.insert({1, 'a'});
  s21_map.insert({2, 'b'});
  s21_map.insert({3, 'c'});

  std_map.insert({1, 'a'});
  std_map.insert({2, 'b'});
  std_map.insert({3, 'c'});

  auto s21_it = s21_map.begin();
  auto std_it = std_map.begin();

  for (; s21_it != s21_map.end(); ++s21_it, ++std_it) {
    EXPECT_TRUE((*s21_it).first == (*std_it).first);
    EXPECT_TRUE((*s21_it).second == (*std_it).second);
  }

  auto s21_dup_check = s21_map.insert({1, 'a'});
  auto std_dup_check = std_map.insert({1, 'a'});
  EXPECT_TRUE(s21_dup_check.second == std_dup_check.second);
}

TEST(map, Erase) {
  s21::map<int, char> s21_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> std_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  EXPECT_EQ(s21_map.size(), std_map.size());

  s21_map.erase(s21_map.begin());
  std_map.erase(std_map.begin());

  EXPECT_EQ(s21_map.size(), std_map.size());

  auto s21_it = s21_map.begin();
  auto std_it = std_map.begin();

  for (; s21_it != s21_map.end(); ++s21_it, ++std_it) {
    EXPECT_TRUE((*s21_it).first == (*std_it).first);
    EXPECT_TRUE((*s21_it).second == (*std_it).second);
  }
}

TEST(map, Swap) {
  s21::map<int, char> s21_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::map<int, char> s21_swap = {{4, 'd'}, {5, 'e'}};

  s21::map<int, char> s21_map_check = {{4, 'd'}, {5, 'e'}};
  s21::map<int, char> s21_swap_check = {{1, 'a'}, {2, 'b'}, {3, 'c'}};

  s21_map.swap(s21_swap);
  EXPECT_EQ(s21_map.size(), 2);
  EXPECT_EQ(s21_swap.size(), 3);

  auto s21_it = s21_map.begin();
  auto s21_it_check = s21_map_check.begin();

  for (; s21_it != s21_map.end(); ++s21_it, ++s21_it_check) {
    EXPECT_TRUE((*s21_it).first == (*s21_it_check).first);
    EXPECT_TRUE((*s21_it).second == (*s21_it_check).second);
  }

  auto s21_swap_it = s21_swap.begin();
  auto s21_swap_check_it = s21_swap_check.begin();

  for (; s21_swap_it != s21_swap.end(); ++s21_swap_it, ++s21_swap_check_it) {
    EXPECT_TRUE((*s21_swap_it).first == (*s21_swap_check_it).first);
    EXPECT_TRUE((*s21_swap_it).second == (*s21_swap_check_it).second);
  }
}

TEST(map, Merge) {
  s21::map<int, char> s21_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  s21::map<int, char> s21_merge = {{4, 'd'}, {5, 'e'}};

  std::map<int, char> std_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> std_merge = {{4, 'd'}, {5, 'e'}};

  s21_map.merge(s21_merge);
  std_map.merge(std_merge);

  auto s21_it = s21_map.begin();
  auto std_it = std_map.begin();

  for (; s21_it != s21_map.end(); ++s21_it, ++std_it) {
    EXPECT_TRUE((*s21_it).first == (*std_it).first);
    EXPECT_TRUE((*s21_it).second == (*std_it).second);
  }
}

TEST(map, Cointains) {
  s21::map<int, char> s21_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
  std::map<int, char> std_map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};

  EXPECT_TRUE(s21_map.contains(1));
  EXPECT_FALSE(s21_map.contains(4));
}

TEST(map, InsertMany) {
  s21::map<int, std::string> myMap;
  auto result =
      myMap.insert_many(std::make_pair(1, "one"), std::make_pair(2, "two"),
                        std::make_pair(3, "three"));

  ASSERT_EQ(result.size(), 3);

  EXPECT_TRUE(result[0].second);
  EXPECT_TRUE(result[1].second);
  EXPECT_TRUE(result[2].second);

  EXPECT_EQ(myMap[1], "one");
  EXPECT_EQ(myMap[2], "two");
  EXPECT_EQ(myMap[3], "three");

  EXPECT_EQ(myMap.size(), 3);
}
