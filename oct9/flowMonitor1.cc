
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
 #include "ns3/flow-monitor-module.h"
 
 using namespace ns3;
 
 NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");
 
 int
 main (int argc, char *argv[])
 {
   CommandLine cmd;
   cmd.Parse (argc, argv);
   
   Time::SetResolution (Time::NS);
   LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
   LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
 
   NodeContainer nodes;
   nodes.Create (2);
 
   PointToPointHelper pointToPoint;
   pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
   pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));
 
   NetDeviceContainer devices;
   devices = pointToPoint.Install (nodes);
 
   InternetStackHelper stack;
   stack.Install (nodes);
 
   Ipv4AddressHelper address;
   address.SetBase ("10.1.1.0", "255.255.255.0");
 
   Ipv4InterfaceContainer interfaces;
   interfaces = address.Assign (devices);
 
   UdpEchoServerHelper echoServer (9);
 
   ApplicationContainer serverApps = echoServer.Install (nodes.Get (1));
   serverApps.Start (Seconds (1.0));
   serverApps.Stop (Seconds (5.0));
 
   UdpEchoClientHelper echoClient(interfaces.GetAddress(1), 9);
   echoClient.SetAttribute ("MaxPackets", UintegerValue (100));
   echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
   echoClient.SetAttribute ("PacketSize", UintegerValue (1024));
 
   ApplicationContainer clientApps = echoClient.Install (nodes.Get(0));
   clientApps.Start (Seconds (2.0));
   clientApps.Stop (Seconds (5.0));


    std::cout<<std::endl;
    FlowMonitorHelper flowmon;
    Ptr<FlowMonitor> monitor = flowmon.InstallAll();
    // Now, do the actual simulation.
    NS_LOG_INFO ("Run Simulation.");
    Simulator::Stop (Seconds(11.0));
    Simulator::Run ();
    monitor->CheckForLostPackets ();
    Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier>(flowmon.GetClassifier ( ));
    std::map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats ();
    for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator i = stats.begin(); i != stats.end(); ++i)
    {
      Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow (i->first);
      std::cout<<" t.sourceAddress = "<<t.sourceAddress<<", t.destinationAddress = "<<t.destinationAddress<<" Source port:"<<t.sourcePort<<" "<<"Destination port:"<<t.destinationPort<<"\n";

        std::cout << "Flow " << i->first << " (" << t.sourceAddress << " -> " <<t.destinationAddress << ")\n";
        std::cout << " Tx Bytes: " << i->second.txBytes << "\n";
        std::cout << " Rx Bytes: " << i->second.rxBytes << "\n";
        std::cout << " Tx Packets: " << i->second.txPackets << "\n";
        std::cout << " Rx Packets: " << i->second.rxPackets << "\n";
        std::cout << " Throughput: " << i->second.rxBytes * 8.0 / (i->second.timeLastRxPacket.GetSeconds() - i->second.timeFirstTxPacket.GetSeconds()) / 1000 / 1000 << "Mbps\n";
    }
    monitor->SerializeToXmlFile("lab-1.flowmon", true, true);
    Simulator::Destroy ();
    NS_LOG_INFO ("Done.");

    return 0;
 }
