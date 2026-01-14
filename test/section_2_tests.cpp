#include <gtest/gtest.h>

#include "storage_types.hpp"
#include "Package.hpp"
#include "nodes.hpp"
#include "types.hpp"

TEST(ReceiverPreferencesTest, probability_correctness){
  using preferences_t = std::map<IPackageReceiver*, double>;
  Receiver R1{};
  Receiver R2{};
  Receiver R3{};
  ReceiverPreferences RP(probability_generator);
  RP.add_receiver(&R1);
  preferences_t& prefs = RP.get_preferences();
  EXPECT_EQ(prefs.begin()->second,1);
  RP.add_receiver(&R2);
  prefs = RP.get_preferences();
  EXPECT_EQ(prefs.begin()->second,prefs.end()->second);
  EXPECT_EQ(prefs.begin()->second,1/2);
  RP.add_receiver(&R3);
  RP.remove_receiver(&R1);
  prefs = RP.get_preferences();
  EXPECT_EQ(prefs.begin()->second,prefs.end()->second);
  EXPECT_EQ(prefs.begin()->second,1/2);
  RP.remove_receiver(&R2);
  prefs = RP.get_preferences();
  EXPECT_EQ(prefs.begin()->second,1);

 }
