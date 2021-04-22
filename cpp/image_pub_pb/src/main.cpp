#include <ecal/ecal.h>
#include <ecal/msg/protobuf/publisher.h>

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "camera_image.pb.h"

int main(int argc, char **argv)
{
  std::cout << "-------------------------------------------" << std::endl;
  std::cout << " SOLECTRIX / eCAL PROTOBUF IMAGE PUBLISHER " << std::endl;
  std::cout << "-------------------------------------------" << std::endl;

  // initialize eCAL API
  eCAL::Initialize(argc, argv, "solectrix image publisher (protobuf)");

  // create the publisher
  eCAL::protobuf::CPublisher<pb::solectrix::CameraImage> pub("image_pb");

  // generate a class instance of Image
  pb::solectrix::CameraImage image;

  // vector that contains the image binary data
  std::vector<char> image_data;
  image_data.resize(1024);

  // send updates
  while(eCAL::Ok())
  {
    // log it
    std::cout << "Send image .." << std::endl;

    // set image header
    auto iheader = image.mutable_header();
    iheader->set_timestamp(1234);
    iheader->set_timestamp_source(pb::solectrix::Header_TimeStampSource::Header_TimeStampSource_SENSOR);
    iheader->set_timestamp_sync_state(pb::solectrix::Header_TimeStampSyncState::Header_TimeStampSyncState_SYNCED_PTP);

    // set image data
    auto idata = image.mutable_camera_data();
    idata->set_width(1920);
    idata->set_height(1080);
    idata->set_imagedata(image_data.data(), image_data.size());

    // send image
    pub.Send(image);

    // sleep 500 ms
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }

  // finalize eCAL API
  eCAL::Finalize();

  return(0);
}
