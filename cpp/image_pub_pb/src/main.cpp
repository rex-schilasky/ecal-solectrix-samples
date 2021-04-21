#include <ecal/ecal.h>
#include <ecal/msg/protobuf/publisher.h>

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "image.pb.h"

int main(int argc, char **argv)
{
  std::cout << "-------------------------------------------" << std::endl;
  std::cout << " SOLECTRIX / eCAL PROTOBUF IMAGE PUBLISHER " << std::endl;
  std::cout << "-------------------------------------------" << std::endl;

  // initialize eCAL API
  eCAL::Initialize(argc, argv, "protobuf image publisher");

  // create the publisher
  eCAL::protobuf::CPublisher<solectrix::Image> pub("image_pb");

  // generate a class instance of Image
  solectrix::Image image;

  // vector that contains the image binary data
  std::vector<char> image_buf;
  image_buf.resize(1024);

  // send updates
  while(eCAL::Ok())
  {
    // log it
    std::cout << "Send image .." << std::endl;

    // set image content
    image.set_width(1920);
    image.set_height(1080);
    image.set_payload(image_buf.data(), image_buf.size());

    // send the person object
    pub.Send(image);

    // sleep 500 ms
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }

  // finalize eCAL API
  eCAL::Finalize();

  return(0);
}
