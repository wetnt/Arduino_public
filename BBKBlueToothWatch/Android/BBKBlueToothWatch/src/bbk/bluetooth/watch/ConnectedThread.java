package bbk.bluetooth.watch;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import android.bluetooth.BluetoothSocket;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
/*
已建立连接后启动的线程，需要传进来两个参数
socket用来获取输入流，读取远程蓝牙发送过来的消息
handler用来在收到数据时发送消息
*/
public class ConnectedThread extends Thread {
	
	private static final int RECEIVE_MSG = 7;
	private static final int SEND_MSG=8;
	private boolean isStop;
	private BluetoothSocket socket;
	private Handler handler;
	private InputStream is;
	private OutputStream os;
	
	public ConnectedThread(BluetoothSocket s,Handler h){
		socket=s;
		handler=h;
		isStop=false;
	}
	public void run(){
		System.out.println("connectedThread.run()");
		byte[] buf;
		int size;
		while(!isStop){
			size=0;
			buf=new byte[1024];
			try {
				is=socket.getInputStream();
				System.out.println("等待数据");
				size=is.read(buf);
				System.out.println("读取了一次数据");
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				isStop=true;
			}
			if(size>0){
				//把读取到的数据放进Bundle再放进Message，然后发送出去
				sendMessageToHandler(buf, RECEIVE_MSG);
			}
		}
	}
	
	public void write(byte[] buf){
		try {
			os=socket.getOutputStream();
			os.write(buf);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		System.out.println(buf.length+"---");
		sendMessageToHandler(buf, SEND_MSG);
	}
	
	private void sendMessageToHandler(byte[] buf,int mode){
		String msgStr=new String(buf);
		Bundle bundle=new Bundle();
		bundle.putString("str", msgStr);
		Message msg=new Message();
		msg.setData(bundle);
		msg.what=mode;
		handler.sendMessage(msg);
	}
}
