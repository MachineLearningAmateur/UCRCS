/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
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
 */

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");

int
main (int argc, char *argv[])
{
  Time::SetResolution (Time::NS);
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
  
  const int NUM_CLIENTS = 3;
  NodeContainer nodes;
  nodes.Create (NUM_CLIENTS + 1); //need to create 1 more node to represent the server (3 clients and 1 server)

  PointToPointHelper pointToPoint; //creates a channel
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("10Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("4ms"));

  InternetStackHelper stack; //tells what protocol the device is using, you can also use ip for protocols
  stack.Install (nodes);

  Ipv4AddressHelper address;
  address.SetBase ("10.1.1.0", "255.255.255.0");
  
  Ipv4AddressHelper address1;
  address1.SetBase("10.1.2.0", "255.255.255.0");

  Ipv4AddressHelper address2;
  address2.SetBase("10.1.3.0", "255.255.255.0");
	
  UdpEchoServerHelper echoServer (9);

  ApplicationContainer serverApps = echoServer.Install (nodes.Get (0));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (20.0));
  
  for (int i = 1; i <= NUM_CLIENTS; i++) 
 {
	NetDeviceContainer devices;
	devices = pointToPoint.Install(nodes.Get(0), nodes.Get(i));
	
	Ipv4InterfaceContainer interface = address.Assign(devices);
	address.NewNetwork();

	UdpEchoClientHelper echoClient(interface.GetAddress(0), 9);
	echoClient.SetAttribute("MaxPackets", UintegerValue(4));
	echoClient.SetAttribute("Interval", TimeValue(Seconds(1.0)));
	echoClient.SetAttribute("PacketSize", UintegerValue(16384));

	ApplicationContainer clientApps = echoClient.Install(nodes.Get(i));
	clientApps.Start(Seconds(2.0 + i));
	clientApps.Stop(Seconds(20.0));
 } 

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
