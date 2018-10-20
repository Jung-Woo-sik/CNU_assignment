

import java.io.FileOutputStream;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;

public class FileReceiver {
	private static final int PACKETSIZE = 64000;
	
	public void receive(int listenPort){
		FileOutputStream fileOut = null;
		FileSender a = new FileSender();
		try{
			//Construct the socket
			DatagramSocket socket = new DatagramSocket(listenPort);
			System.out.println("The server is ready...");
			
			//Create a Packet
			DatagramPacket packet = new DatagramPacket(new byte[PACKETSIZE],PACKETSIZE);
			
			//Receive a file header
			socket.receive(packet);
			byte[] receiveData = packet.getData();
			int receiveDataSize = packet.getLength();
			
			String receiveFileHeader = new String(receiveData, 0, receiveDataSize);
			//파일 헤더의 String
			String fileName = receiveFileHeader.split(",")[0];
			long fileSize = Long.parseLong(receiveFileHeader.split(",")[1]);
			
			//Print sender and file info
			System.out.println("From "+packet.getAddress()+":"+packet.getPort());
			System.out.println("File name: "+fileName);
			System.out.println("File size: "+fileSize);
			
			//Receive a packet
			fileOut = new FileOutputStream("received_"+fileName);
			/**/
			int b=1;
			packet = new DatagramPacket(receiveData,PACKETSIZE);
			while(fileSize >= 0){
				System.out.println(fileSize);
				socket.receive(packet);
				receiveDataSize = packet.getLength();
				fileOut.write(receiveData,0,receiveDataSize);
				fileOut.flush();
				System.out.println("RECEIVE : "+b+"번째 "+receiveDataSize);
				fileSize-=PACKETSIZE;
				b+=1;
			//	if(fileSize>PACKETSIZE){
		//			packet = new DatagramPacket(receiveData,PACKETSIZE);
			//	}
			//	else{
			//		packet = new DatagramPacket(receiveData,(int)(fileSize+1));
			//	}
				
			}
			/*socket.receive(packet);
			receiveData = packet.getData();
			receiveDataSize = packet.getLength();
			System.out.println("reciveDataSize : "+receiveDataSize);
			*/
			
		} catch(Exception e){
			System.out.println(e);
		} finally{
			if(fileOut != null){
				try{
					fileOut.flush();
					fileOut.close();
					System.out.println("file close");
				}
				catch(IOException e){
					System.err.println(e);
				}
			}
		}
	}
	
	public static void main(String args[]){
		FileReceiver a =new FileReceiver();
		a.receive(6000);
		System.out.println("receive end");
	}
}
