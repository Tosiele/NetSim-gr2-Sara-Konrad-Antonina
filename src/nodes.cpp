//
// Created by konfe on 12.01.2026.
//
#include <iostream>
#include <map>
#include "nodes.hpp"



std::random_device rd;
std::mt19937 rng(rd());
double probability_generator() {
  return std::generate_canonical<double, 10>(rng);
}
void ReceiverPreferences::add_receiver(IPackageReceiver* receiver) {
  prefs.insert(std::pair{receiver,1});
  if (prefs.size()>1) {
    double val = 1.0/static_cast<double>(prefs.size());
    for (auto it = prefs.begin(); it != prefs.end(); ++it) {
      it->second=val;
    }
  }
}
void ReceiverPreferences::remove_receiver(IPackageReceiver* receiver) {
  prefs.erase(receiver);
  if (not prefs.empty()) {
    double val = 1.0/static_cast<double>(prefs.size());
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

void PackageSender::push_package(Package&& package) {
  buffer = std::move(package);
}

void PackageSender::send_package() {
  IPackageReceiver* R = receiver_preferences.choose_receiver();
  R->receive_package(buffer.value());
  buffer.reset();
}

void Storehouse::receive_package(Package& package) {
  d->push(std::move(package));
}