#include "io-tea/node/node.h"
#include "mbed.h"
#include "DS18B20.h"

int main() {
  iotea::node::Node node(iotea::NodeName::NODE_YERBA);
  node.addSensor(std::make_unique<iotea::yerba::TemperatureSensor>(D3));
  node.addSensor(std::make_unique<iotea::yerba::LiquidLevelSensor>(A0));
  node.run();
}
