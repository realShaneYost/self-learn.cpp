#include <iostream>

/*
 * Interface Class
 * Declares all methods (the API) that all concrete class must implement
 * - You cannot instantiate abstract classes.
 * */
class Device
{
public:
    virtual void run() = 0;
    virtual ~Device() = default;
};

/*
 * Concrete Class
 * Provides a specific implementation of the interface
 * */
class Gps : public Device
{
public:
    void run() override
    {
        std::cout << "Running Gps" << std::endl; 
    }
};
class Imu : public Device
{
public:
    void run() override
    {
        std::cout << "Running Imu" << std::endl; 
    }
};

/*
 * Creator class
 * Defines the factory method that creates objects based on type
 * */
class DeviceFactory
{
public:
    static std::unique_ptr<Device> create(std::string_view dev)
    {
        if (dev == "gps") return std::make_unique<Gps>();
        if (dev == "imu") return std::make_unique<Imu>();
        return nullptr;
    }
};

int main ()
{
    auto imu_device = DeviceFactory::create("imu");
    auto gps_device = DeviceFactory::create("gps");

    if (imu_device) imu_device->run();
    if (gps_device) gps_device->run();
}
