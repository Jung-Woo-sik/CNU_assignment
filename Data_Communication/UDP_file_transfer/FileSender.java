

import java.io.*;
import java.lang.*;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.UnknownHostException;

public class FileSender {
	
	private static final int PACKETSIZE = 64000;
	public byte[] b=new byte[PACKETSIZE];
	
	public boolean send(String file, InetAddress destIP, int destPort){
		DatagramSocket socket = null;
		DatagramPacket packet;
		
		try{
			socket = new DatagramSocket();
			
			//Prepare a file and file header for send
			InputStream fileIn = new BufferedInputStream(new FileInputStream(file));
			
			
			int readBytes=0;
			
			long fileSize = new File(file).length();
			String fileName = file;
			String fileHeader = fileName + ","+fileSize;
			int fileHeaderSize = fileHeader.length();
			
			//Send a file header
			packet = new DatagramPacket(fileHeader.getBytes(),fileHeaderSize,destIP,destPort);
			socket.send(packet);
			
			
			//Send a file
		//	readBytes = fileIn.read(b, 0, PACKETSIZE);
		//	packet = new DatagramPacket(b,PACKETSIZE, destIP,destPort);
			int a=1;
			
			
			while(fileSize>0){
				if(fileSize > PACKETSIZE){
					readBytes = fileIn.read(b,0,PACKETSIZE);
					packet = new DatagramPacket(b,readBytes,destIP,destPort);
					a+=1;
				}
				else{
					readBytes = fileIn.read(b,0,(int)(fileSize));
					packet = new DatagramPacket(b,readBytes,destIP,destPort);
				}
				
				try{
					Thread.sleep(100);
				}
				catch(InterruptedException e){
					
				}
				socket.send(packet);
				System.out.println(fileSize);
				fileSize-=readBytes;
				System.out.println("SEND : "+a+"¹øÂ°"+readBytes);
		
			}
			fileIn.close();
			
		}
		
		catch(IOException e){
			System.err.println(e);
		}
		finally{
			if(socket!=null)
				socket.close();
			System.out.println("socket close");
		}
		
		return true;
	}
	
	public static void main(String args[]){
		try{
			new FileSender().send("test.jpg",InetAddress.getByName("127.0.0.1") , 6000);
			System.out.println("send end");
		
		}
		catch(UnknownHostException e){
			System.err.println(e);
		}
	}
}
