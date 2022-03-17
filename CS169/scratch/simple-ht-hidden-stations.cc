/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2015 Sébastien Deronne
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Sébastien Deronne <sebastien.deronne@gmail.com>
 */


#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/internet-module.h"

// This example considers two hidden stations in an 802.11n network which supports MPDU aggregation.
// The user can specify whether RTS/CTS is used and can set the number of aggregated MPDUs.
//
// Example: ./waf --run "simple-ht-hidden-stations --enableRts=1 --nMpdus=8"
//
//   Wifi 192.168.1.0
//
// Packets in this simulation aren't marked with a QosTag so they are considered
// belonging to BestEffort Access Class (AC_BE).

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("SimplesHtHiddenStations");


uint32_t port9_packetsReceived = 0;
uint32_t port10_packetsReceived = 0;
uint32_t port11_packetsReceived = 0;
uint32_t port12_packetsReceived = 0;

uint32_t node1_packetsSent = 0;
uint32_t node2_packetsSent = 0;
uint32_t node3_packetsSent = 0;
uint32_t node4_packetsSent = 0;

void RxTraceNode1(std::string context, Ptr<const Packet> p) {
 	port9_packetsReceived++;
	NS_LOG_UNCOND(context << " " << p << " sent " << p->GetSize() << " bytes at " << Simulator::Now().GetSeconds() << " seconds.");
}

void RxTraceNode2(std::string context, Ptr<const Packet> p) {
	port10_packetsReceived++;
}

void RxTraceNode3(std::string context, Ptr<const Packet> p) {
 	port11_packetsReceived++;
	//NS_LOG_UNCOND(context << " " << p << "at t = " << Simulator::Now().GetSeconds());
}

void RxTraceNode4(std::string context, Ptr<const Packet> p) {
	port12_packetsReceived++;
	//NS_LOG_UNCOND(context << " " << p << "at t = " << Simulator::Now().GetSeconds());
}

void TxTraceNode1(std::string context, Ptr<const Packet> p) {
	//NS_LOG_UNCOND(context << " " << p << "at t = " << Simulator::Now().GetSeconds());
	node1_packetsSent++;
}

void TxTraceNode2(std::string context, Ptr<const Packet> p) {
	//NS_LOG_UNCOND(context << " " << p << "at t = " << Simulator::Now().GetSeconds());
	node2_packetsSent++;
}

void TxTraceNode3(std::string context, Ptr<const Packet> p) {
	//NS_LOG_UNCOND(context << " " << p << "at t = " << Simulator::Now().GetSeconds());
	node3_packetsSent++;
}

void TxTraceNode4(std::string context, Ptr<const Packet> p) {
	//NS_LOG_UNCOND(context << " " << p << "at t = " << Simulator::Now().GetSeconds());
	node4_packetsSent++;
}

int main (int argc, char *argv[])
{
  uint32_t payloadSize = 1472; //bytes
  uint64_t simulationTime = 10; //seconds -- leave at 10 seconds according to instructions
  uint32_t nMpdus = 1;
  uint32_t maxAmpduSize = 0;
  uint32_t staNodes = 4; //number of mobile stations
  bool enableRts = 0;
  bool tracing = false; 

   
  CommandLine cmd;
  cmd.AddValue ("nMpdus", "Number of aggregated MPDUs", nMpdus);
  cmd.AddValue ("payloadSize", "Payload size in bytes", payloadSize);
  cmd.AddValue ("enableRts", "Enable RTS/CTS", enableRts); // 1: RTS/CTS enabled; 0: RTS/CTS disabled
  cmd.AddValue ("simulationTime", "Simulation time in seconds", simulationTime);
  cmd.AddValue ("tracing", "enable pcap", tracing);
  cmd.Parse (argc, argv);

  if (!enableRts)
    {
      Config::SetDefault ("ns3::WifiRemoteStationManager::RtsCtsThreshold", StringValue ("999999"));
    } 
  else
    {
      Config::SetDefault ("ns3::WifiRemoteStationManager::RtsCtsThreshold", StringValue ("0"));
    }

  Config::SetDefault ("ns3::WifiRemoteStationManager::FragmentationThreshold", StringValue ("990000"));

  //Set the maximum size for A-MPDU with regards to the payload size
  maxAmpduSize = nMpdus * (payloadSize + 200);

  // Set the maximum wireless range to 5 meters in order to reproduce a hidden nodes scenario, i.e. the distance between hidden stations is larger than 5 meters
  Config::SetDefault ("ns3::RangePropagationLossModel::MaxRange", DoubleValue (5)); //leave at 5 meters according to instructions

  NodeContainer wifiStaNodes; //list of node pointers
  wifiStaNodes.Create (staNodes); //staNodes is intitialized to 4 for 4 mobile stations
  NodeContainer wifiApNode;
  wifiApNode.Create (1); //only need 1 access point
  
  YansWifiChannelHelper channel = YansWifiChannelHelper::Default ();
  channel.AddPropagationLoss ("ns3::RangePropagationLossModel"); //wireless range limited to 5 meters!

  YansWifiPhyHelper phy = YansWifiPhyHelper::Default ();
  phy.SetPcapDataLinkType (YansWifiPhyHelper::DLT_IEEE802_11_RADIO);
  phy.SetChannel (channel.Create ());

  WifiHelper wifi;
  wifi.SetStandard (WIFI_PHY_STANDARD_80211n_5GHZ);
  wifi.SetRemoteStationManager ("ns3::ConstantRateWifiManager", "DataMode", StringValue ("HtMcs7"), "ControlMode", StringValue ("HtMcs0"));
  WifiMacHelper mac;

  Ssid ssid = Ssid ("simple-mpdu-aggregation");
  mac.SetType ("ns3::StaWifiMac",
               "Ssid", SsidValue (ssid),
               "ActiveProbing", BooleanValue (false),
               "BE_MaxAmpduSize", UintegerValue (maxAmpduSize));

  NetDeviceContainer staDevices; //creates NetDeviceContainer for mobile station
  staDevices = wifi.Install (phy, mac, wifiStaNodes);

  mac.SetType ("ns3::ApWifiMac",
               "Ssid", SsidValue (ssid),
               "BeaconInterval", TimeValue (MicroSeconds (102400)),
               "BeaconGeneration", BooleanValue (true),
               "BE_MaxAmpduSize", UintegerValue (maxAmpduSize));

  NetDeviceContainer apDevice; //creates NetDeviceContainer for Access Point
  apDevice = wifi.Install (phy, mac, wifiApNode);

  // Setting mobility model
  MobilityHelper mobility;
  Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();

  // AP is between the two stations, each station being located at 5 meters from the AP.
  // The distance between the two stations is thus equal to 10 meters.
  // Since the wireless range is limited to 5 meters, the two stations are hidden from each other.
  positionAlloc->Add (Vector (5.0, 5.0, 0.0)); //initial position represents location of access point
  positionAlloc->Add (Vector (5.0, 10.0, 0.0)); //n1
  positionAlloc->Add (Vector (0.0, 5.0, 0.0)); //n2
  positionAlloc->Add (Vector (5.0, 0.0, 0.0)); //n3
  positionAlloc->Add (Vector (10.0, 5.0, 0.0));//n4

  mobility.SetPositionAllocator (positionAlloc); //sets the first position as initial position (5.0, 5.0, 0.0)

  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");

  mobility.Install (wifiApNode); //install access point first since the initial position is set to (5.0, 5.0, 0.0)
  mobility.Install (wifiStaNodes);

  // Internet stack
  InternetStackHelper stack;
  stack.Install (wifiApNode);
  stack.Install (wifiStaNodes);

  Ipv4AddressHelper address;

  address.SetBase ("192.168.1.0", "255.255.255.0");
  Ipv4InterfaceContainer StaInterface;
  StaInterface = address.Assign (staDevices); //assigns all netdevices within the container with an ipv4 address
  Ipv4InterfaceContainer ApInterface;
  ApInterface = address.Assign (apDevice); 

  // Setting applications -- need to set up an echo server and echo client 
  //UdpServerHelper myServer (9); //server is for access point
  //ApplicationContainer serverApp = myServer.Install (wifiApNode);
  //serverApp.Start (Seconds (0.0));
  //serverApp.Stop (Seconds (simulationTime + 1));

  //UdpClientHelper myClient (ApInterface.GetAddress (0), 9); //client is for mobile stations
  //myClient.SetAttribute ("MaxPackets", UintegerValue (4294967295u));
  //myClient.SetAttribute ("Interval", TimeValue (Time ("0.00002"))); //packets/s
  //myClient.SetAttribute ("PacketSize", UintegerValue (payloadSize));

  //set up echo server
  UdpEchoServerHelper myServer9 (9); //sets server on port 9
  ApplicationContainer serverApp1 = myServer9.Install (wifiApNode); //only 1 ap node
  serverApp1.Start(Seconds (0.0));
  serverApp1.Stop (Seconds(simulationTime + 1));
  
  UdpEchoServerHelper myServer10 (10);
  ApplicationContainer serverApp2 = myServer10.Install (wifiApNode);
  serverApp2.Start(Seconds (0.0));
  serverApp2.Stop (Seconds(simulationTime + 1)); 

  UdpEchoServerHelper myServer11 (11);
  ApplicationContainer serverApp3 = myServer11.Install (wifiApNode);
  serverApp3.Start(Seconds (0.0));
  serverApp3.Stop (Seconds (simulationTime + 1)); 
   
  UdpEchoServerHelper myServer12 (12); 
  ApplicationContainer serverApp4 = myServer12.Install(wifiApNode);
  serverApp4.Start(Seconds (0.0));
  serverApp4.Stop (Seconds (simulationTime + 1)); 
  
  //set up echo clients
  UdpEchoClientHelper myClient9 (ApInterface.GetAddress(0), 9); //uses port 9 and points to the first address of ap interface
  myClient9.SetAttribute ("MaxPackets", UintegerValue(UINT32_MAX));
  myClient9.SetAttribute ("Interval", TimeValue (Seconds(0.004))); 
  myClient9.SetAttribute ("PacketSize", UintegerValue (payloadSize)); 
  
  UdpEchoClientHelper myClient10 (ApInterface.GetAddress(0), 10); //uses port 10 and points to the first address of ap interface
  myClient10.SetAttribute ("MaxPackets", UintegerValue(UINT32_MAX));
  myClient10.SetAttribute ("Interval", TimeValue (Seconds(0.004))); 
  myClient10.SetAttribute ("PacketSize", UintegerValue (payloadSize));
  
  UdpEchoClientHelper myClient11 (ApInterface.GetAddress(0), 11); //uses port 11 and points to the first address of ap interface
  myClient11.SetAttribute ("MaxPackets", UintegerValue(UINT32_MAX));
  myClient11.SetAttribute ("Interval", TimeValue (Seconds(0.004))); 
  myClient11.SetAttribute ("PacketSize", UintegerValue (payloadSize));

  UdpEchoClientHelper myClient12 (ApInterface.GetAddress(0), 12); //uses port 12 and points to the first address of ap interface
  myClient12.SetAttribute ("MaxPackets", UintegerValue(UINT32_MAX));
  myClient12.SetAttribute ("Interval", TimeValue (Seconds(0.004))); //10 packets per second
  myClient12.SetAttribute ("PacketSize", UintegerValue (payloadSize));
  
  
    
  // Saturated UDP traffic from stations to AP
  
  ApplicationContainer clientApp9 = myClient9.Install(wifiStaNodes.Get(0)); //it should automatically install for each ptr node in the nodeContainer
  clientApp9.Start(Seconds(1.0));
  clientApp9.Stop(Seconds(simulationTime + 1));
    
  ApplicationContainer clientApp10 = myClient10.Install(wifiStaNodes.Get(1)); //it should automatically install for each ptr node in the nodeContainer
  clientApp10.Start(Seconds(1.0));
  clientApp10.Stop(Seconds(simulationTime + 1));

  ApplicationContainer clientApp11 = myClient11.Install(wifiStaNodes.Get(2)); //it should automatically install for each ptr node in the nodeContainer
  clientApp11.Start(Seconds(1.0));
  clientApp11.Stop(Seconds(simulationTime + 1));
 
  ApplicationContainer clientApp12 = myClient12.Install(wifiStaNodes.Get(3)); //it should automatically install for each ptr node in the nodeContainer
  clientApp12.Start(Seconds(1.0));
  clientApp12.Stop(Seconds(simulationTime + 1));
  
  
  //for (uint32_t i = 0; i < staNodes; i++) {
  //	ApplicationContainer clientApp = myClient.Install(wifiStaNodes.Get(i));
  //	clientApp.Start(Seconds(1.0));
  //	clientApp.Stop(Seconds(simulationTime + 1));
  //}

  //ApplicationContainer clientApp1 = myClient.Install (wifiStaNodes);
  //clientApp1.Start (Seconds (1.0));
  //clientApp1.Stop (Seconds (simulationTime + 1));
  if (tracing == true) {
  	phy.EnablePcap ("SimpleHtHiddenStations_Ap", apDevice.Get (0));
  	phy.EnablePcap ("SimpleHtHiddenStations_Sta1", staDevices.Get (0));
  	phy.EnablePcap ("SimpleHtHiddenStations_Sta2", staDevices.Get (1));
  	phy.EnablePcap ("SimpleHtHiddenStations_Sta3", staDevices.Get (2));
  	phy.EnablePcap ("SimpleHtHiddenStations_Sta4", staDevices.Get (3));
  } 
  
  //Config::Set("/NodeList/*/ApplicationList/*/$ns3::UdpEchoServer/Port", UintegerValue(9)); //sets observed port number to 9 only -- does not work so don't use Config::Set

  Config::Connect("/NodeList/*/ApplicationList/0/$ns3::UdpEchoServer/Rx", MakeCallback(&RxTraceNode1)); //not sure how to track a specific port, but this should be port 9?
  Config::Connect("/NodeList/0/ApplicationList/*/$ns3::UdpEchoClient/Tx", MakeCallback(&TxTraceNode1)); //tracks packets sent on node1
  
  Config::Connect("/NodeList/*/ApplicationList/1/$ns3::UdpEchoServer/Rx", MakeCallback(&RxTraceNode2)); //tracks received packets on port 10
  Config::Connect("/NodeList/0/ApplicationList/*/$ns3::UdpEchoClient/Tx", MakeCallback(&TxTraceNode2)); //tracks packets sent on node2
  
  Config::Connect("/NodeList/*/ApplicationList/2/$ns3::UdpEchoServer/Rx", MakeCallback(&RxTraceNode3)); //tracks received packets on port 11
  Config::Connect("/NodeList/0/ApplicationList/*/$ns3::UdpEchoClient/Tx", MakeCallback(&TxTraceNode3)); //tracks packets sent on node3
    
  Config::Connect("/NodeList/*/ApplicationList/3/$ns3::UdpEchoServer/Rx", MakeCallback(&RxTraceNode4)); //tracks received packets on port 12  
  Config::Connect("/NodeList/0/ApplicationList/*/$ns3::UdpEchoClient/Tx", MakeCallback(&TxTraceNode4)); //tracks packets sent on node4

  Simulator::Stop (Seconds (simulationTime + 1));
  
  Simulator::Run ();
  Simulator::Destroy ();

  //uint32_t totalPacketsThrough = DynamicCast<UdpEchoServer> (serverApp1.Get (0))->GetReceived ();
  double throughput9 = port9_packetsReceived * payloadSize * 8 / (simulationTime * 1000000.0);
  std::cout << "Throughput for Node 1 (Port 9): " << throughput9 << " Mbit/s" << " | " << "packet loss: " << static_cast<float>(node1_packetsSent - port9_packetsReceived)/static_cast<float>(node1_packetsSent) * 100 << "%" << '\n';
  
  //uint32_t totalPacketsThrough = DynamicCast<UdpEchoServer> (serverApp2.Get (0))->GetReceived ();
  double throughput10 = port10_packetsReceived * payloadSize * 8 / (simulationTime * 1000000.0);
  std::cout << "Throughput for Node 2 (Port 10): " << throughput10 << " Mbit/s" << " | " << "packet loss: " << static_cast<float>(node2_packetsSent - port10_packetsReceived)/static_cast<float>(node2_packetsSent) * 100 << "%" << '\n';
  
  //uint32_t totalPacketsThrough = DynamicCast<UdpEchoServer> (serverApp3.Get (0))->GetReceived ();
  double throughput11 = port11_packetsReceived * payloadSize * 8 / (simulationTime * 1000000.0);
  std::cout << "Throughput for Node 3 (Port 11): " << throughput11 << " Mbit/s" << " | " << "packet loss: " << static_cast<float>(node3_packetsSent - port11_packetsReceived)/static_cast<float>(node3_packetsSent) * 100 << "%" << '\n';
 
  //uint32_t totalPacketsThrough = DynamicCast<UdpEchoServer> (serverApp4.Get (0))->GetReceived ();
  double throughput12 = port12_packetsReceived * payloadSize * 8 / (simulationTime * 1000000.0);
  std::cout << "Throughput for Node 4 (Port 12): " << throughput12 << " Mbit/s" << " | " << "packet loss: " << static_cast<float>(node4_packetsSent - port12_packetsReceived)/static_cast<float>(node4_packetsSent) * 100 << "%" << '\n'; 
  return 0;
}
