//
// Created by konfe on 12.01.2026.
//

#ifndef NODES_HPP
#define NODES_HPP
#include "storage_types.hpp"
#include <map>
#include <functional>
#include <cmath>
#include <memory>
#include <optional>

extern std::random_device rd;
extern std::mt19937 rng;
double probability_generator();

enum class ReceiverType {
    WORKER, STOREHOUSE
};


class IPackageReceiver {
  public:
  virtual void receive_package(Package&& package) = 0;
  virtual IPackageStockpile::const_iterator begin() =0;
  virtual IPackageStockpile::const_iterator end() =0;
  virtual const IPackageStockpile::const_iterator cbegin() const =0;
  virtual const IPackageStockpile::const_iterator cend() const =0;
  virtual ElementID get_id() const =0;
  virtual ReceiverType get_receiver_type() const = 0;

  virtual ~IPackageReceiver() = default;

  };

class ReceiverPreferences {
  public:
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;
    ReceiverPreferences() {pg = probability_generator;};
    ReceiverPreferences(ProbabilityGenerator prob_gen) {pg=prob_gen;};

    void add_receiver(IPackageReceiver* receiver);
    void remove_receiver(IPackageReceiver* receiver);
    IPackageReceiver* choose_receiver();
    preferences_t& get_preferences() {return prefs;};

    const_iterator begin() const {return prefs.begin();}
    const_iterator end() const {return prefs.end();}
    const const_iterator cbegin() const {return prefs.cbegin();}
    const const_iterator cend() const {return prefs.cend();}

  private:
    preferences_t prefs;
    ProbabilityGenerator pg;
  };

///ONLY FOR TESTS
class Receiver:public IPackageReceiver {
   public:
     Receiver() = default;
     Receiver& operator=(Receiver& other) = default;
     void receive_package(Package&& package) override {;};
    IPackageStockpile::const_iterator begin() override {return packages.begin();}
    IPackageStockpile::const_iterator end() override {return packages.end();}
    const IPackageStockpile::const_iterator cbegin() const override {return packages.cbegin();}
    const IPackageStockpile::const_iterator cend() const override {return packages.cend();}
    ElementID get_id() const override {return 1;}
    ReceiverType get_receiver_type() const override {return ReceiverType::WORKER;};
  private:
  std::list<Package> packages;
};


class PackageSender {
  public:
  PackageSender() = default;
  PackageSender(PackageSender&&) = default;
  void send_package();
  std::optional<Package>& get_sending_buffer(){return buffer;}
  ReceiverPreferences receiver_preferences;
  protected:
  void push_package(Package&& package);
  private:
  std::optional<Package> buffer;
};

class Storehouse:public IPackageReceiver {
  public:
  Storehouse(ElementID i, std::unique_ptr<IPackageStockpile> s = std::make_unique<PackageQueue>(QueueType::Fifo)) {id=i;packages=std::move(s);};
  ReceiverType get_receiver_type() const override {return ReceiverType::STOREHOUSE;};
  void receive_package(Package&& package) override;
  IPackageStockpile::const_iterator begin() override {return packages->begin();}
  IPackageStockpile::const_iterator end() override {return packages->end();}
  const IPackageStockpile::const_iterator cbegin() const override {return packages->cbegin();}
  const IPackageStockpile::const_iterator cend() const override {return packages->cend();}
  ElementID get_id() const override {return id;}
  private:
  ElementID id;
  std::unique_ptr<IPackageStockpile> packages;
};

//ONLY FOR TESTS
class ExampleSender:public PackageSender {
  public:
  ExampleSender() = default;
  void pusher() {push_package(Package(7));}
};


#endif //NODES_HPP
