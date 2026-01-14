//
// Created by konfe on 12.01.2026.
//
#include <iostream>
#include <map>
#include "nodes.hpp"

void ReceiverPreferences::add_receiver(IPackageReceiver* receiver) {
  prefs.insert(std::pair{receiver,1});
  if (prefs.size()>1) {
    double val = 1/prefs.size();
    for (auto it = prefs.begin(); it != prefs.end(); ++it) {
      it->second=val;
    }
  }
  return;
}
void ReceiverPreferences::remove_receiver(IPackageReceiver* receiver) {
  prefs.erase(receiver);
  if (not prefs.empty()) {
    double val = 1/prefs.size();
    for (auto it = prefs.begin(); it != prefs.end(); ++it) {
      it->second=val;
    }
  }
}
IPackageReceiver* ReceiverPreferences::choose_receiver() {
  double rand = pg();
  double threshold = prefs.begin()->second;
  int index = floor(rand/threshold);
  return std::next(prefs.begin(), index)->first;
}

