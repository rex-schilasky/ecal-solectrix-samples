#include <ecal/ecal.h>
#include <ecal/ecal_publisher.h>

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

int main(int argc, char **argv)
{
  std::cout << "--------------------------------------" << std::endl;
  std::cout << " SOLECTRIX / eCAL RAW IMAGE PUBLISHER " << std::endl;
  std::cout << "--------------------------------------" << std::endl;

  // initialize eCAL API
  eCAL::Initialize(argc, argv, "raw image publisher");

  // create the publisher
  eCAL::CPublisher pub("image_raw", "solectrix binary image");

  // vector that contains the image binary data
  std::vector<char> image_buf;
  image_buf.resize(1024);

  // send updates
  while (eCAL::Ok())
  {
    // log it
    std::cout << "Send image .." << std::endl;

    // send content
    pub.Send(image_buf.data(), image_buf.size());

    // sleep 500 ms
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }

  // finalize eCAL API
  eCAL::Finalize();

  return(0);
}
