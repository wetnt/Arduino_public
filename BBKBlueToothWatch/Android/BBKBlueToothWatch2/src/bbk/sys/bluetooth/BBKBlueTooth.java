package bbk.sys.bluetooth;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

import bbk.bbk.main.R;
import bbk.sys.math.DigitalTrans;
import bbk.sys.ui.BBKLayView;

import android.app.AlertDialog;
import android.app.Dialog;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.graphics.Color;
import android.os.Handler;
import android.os.Message;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.ProgressBar;
import android.widget.ScrollView;
import android.widget.TextView;

public class BBKBlueTooth extends BBKLayView {

	// ========================================================================
	// 消息处理器使用的常量
	private static final int FOUND_DEVICE = 1; // 发现设备
	private static final int START_DISCOVERY = 2; // 开始查找设备
	private static final int FINISH_DISCOVERY = 3; // 结束查找设备
	private static final int CONNECT_FAIL = 4; // 连接失败
	private static final int CONNECT_SUCCEED_P = 5; // 主动连接成功
	private static final int CONNECT_SUCCEED_N = 6; // 收到连接成功
	private static final int RECEIVE_MSG = 7; // 收到消息
	private static final int SEND_MSG = 8; // 发送消息

	// ========================================================================
	ConnectedThread connectedThread; // 与远程蓝牙连接成功时启动
	ConnectThread connectThread; // 用户点击列表中某一项，要与远程蓝牙连接时启动
	// ========================================================================
	BluetoothSocket socket;
	BluetoothAdapter bluetoothAdapter = null;
	// ========================================================================
	// 布局控件
	Button bLink, bSend, bShow, bExit;
	TextView stateText;
	EditText sendText;
	ScrollView scrollView;
	LinearLayout chatContent;

	// 连接设备对话框相关控件
	Dialog dialog;
	ProgressBar discoveryPro;
	ListView foundList;
	List<BluetoothDevice> foundDevices;

	// ========================================================================

	public void BBKBlueToothInt(Context context) {
		// ================================================================
		LayoutInt(context, R.layout.mainbluttooth);
		// ================================================================
		BBKBlueToothSoftInt();
		BBKBlueToothHasDevices();
		BroadcastInt();
		// ================================================================
		layshow(false);
		// ================================================================
	}

	public void BBKBlueToothSoftInt() {
		// -----------------------------------------------------------------
		bLink = (Button) BBKLay.findViewById(R.id.bLink);
		bSend = (Button) BBKLay.findViewById(R.id.bSend);
		bShow = (Button) BBKLay.findViewById(R.id.bShow);
		bExit = (Button) BBKLay.findViewById(R.id.bExit);
		stateText = (TextView) BBKLay.findViewById(R.id.stateText);
		sendText = (EditText) BBKLay.findViewById(R.id.sendText);
		scrollView = (ScrollView) BBKLay.findViewById(R.id.scrollView);
		chatContent = (LinearLayout) BBKLay.findViewById(R.id.chatContent);
		// -----------------------------------------------------------------

		// 连接设备按钮监听器
		bLink.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				BBKBlueToothLink();
			}
		});

		// 发送消息按钮监听器
		bSend.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				BBKBlueToothSend(sendText.getText().toString());
			}
		});

		// 使蓝牙可被发现
		bShow.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				BBKBlueToothCanFind();
			}
		});

		bExit.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				layshow(false);
			}
		});

	}

	// ====================================================================================
	// 蓝牙Link
	public void BBKBlueToothLink() {
		// -----------------------------------------------------------------
		bluetoothAdapter.cancelDiscovery();
		bluetoothAdapter.startDiscovery();
		// -----------------------------------------------------------------
		/*
		 * 通过LayoutInflater得到对话框中的三个控件
		 * 第一个ListView为局部变量，因为它显示的是已配对的蓝牙设备，不需随时改变
		 * 第二个ListView和ProgressBar为全局变量
		 */
		LayoutInflater inflater = bbkAct.getLayoutInflater();
		View view = inflater.inflate(R.layout.dialog, null);
		discoveryPro = (ProgressBar) view
				.findViewById(R.id.discoveryPro);
		ListView bondedList = (ListView) view
				.findViewById(R.id.bondedList);
		foundList = (ListView) view.findViewById(R.id.foundList);

		// 将已配对的蓝牙设备显示到第一个ListView中
		Set<BluetoothDevice> deviceSet = bluetoothAdapter
				.getBondedDevices();
		final List<BluetoothDevice> bondedDevices = new ArrayList<BluetoothDevice>();
		if (deviceSet.size() > 0) {
			for (Iterator<BluetoothDevice> it = deviceSet.iterator(); it
					.hasNext();) {
				BluetoothDevice device = (BluetoothDevice) it.next();
				bondedDevices.add(device);
			}
		}
		bondedList.setAdapter(new MyAdapter(bbkAct, bondedDevices));

		// 将找到的蓝牙设备显示到第二个ListView中
		foundDevices = new ArrayList<BluetoothDevice>();
		foundList.setAdapter(new MyAdapter(bbkAct, foundDevices));

		// 两个ListView绑定监听器
		bondedList.setOnItemClickListener(new OnItemClickListener() {
			@Override
			public void onItemClick(AdapterView<?> arg0, View arg1,
					int arg2, long arg3) {
				BluetoothDevice device = bondedDevices.get(arg2);
				BBKBlueToothConnect(device);
			}
		});
		foundList.setOnItemClickListener(new OnItemClickListener() {
			@Override
			public void onItemClick(AdapterView<?> arg0, View arg1,
					int arg2, long arg3) {
				BluetoothDevice device = foundDevices.get(arg2);
				BBKBlueToothConnect(device);
			}
		});

		AlertDialog.Builder builder = new AlertDialog.Builder(bbkAct);
		builder.setMessage("请选择要连接的蓝牙设备").setPositiveButton("取消",
				new DialogInterface.OnClickListener() {

					@Override
					public void onClick(DialogInterface dialog,
							int which) {
						bluetoothAdapter.cancelDiscovery();
					}
				});
		builder.setView(view);
		builder.create();
		dialog = builder.show();
	}
	// 判断本机是否有蓝牙和是否处于可用状态
	public void BBKBlueToothHasDevices() {
		// 判断本机是否有蓝牙和是否处于可用状态
		bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
		if (bluetoothAdapter == null) {
			toastShow("本机没有蓝牙设备！");
		}
		if (!bluetoothAdapter.isEnabled()) {
			Intent enableIntent = new Intent(
					BluetoothAdapter.ACTION_REQUEST_ENABLE);
			bbkAct.startActivityForResult(enableIntent, 1);
		} else {
			// chooseMode();
		}

	}

	// 使蓝牙可被发现
	public void BBKBlueToothCanFind() {
		Intent intent = new Intent(BluetoothAdapter.ACTION_REQUEST_DISCOVERABLE);
		bbkAct.startActivity(intent);
	}

	// 发送内容
	public void BBKBlueToothSend(String sendStr) {
		if (socket == null) {
			toastShow("请先连接蓝牙设备");
		} else if (sendStr.equals("")) {
			toastShow("发送内容不能为空");
		} else {
			byte[] z = DigitalTrans.hex2byte(sendStr);
			connectedThread.write(z);
		}
	}

	// 注册广播接收器
	public void BroadcastInt() {
		// 注册广播接收器
		mReceiver = new BroadcastReceiver() {

			@Override
			public void onReceive(Context arg0, Intent arg1) {
				// TODO Auto-generated method stub
				String actionStr = arg1.getAction();
				if (actionStr.equals(BluetoothDevice.ACTION_FOUND)) {
					BluetoothDevice device = arg1
							.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
					foundDevices.add(device);
					toastShow("找到蓝牙设备：" + device.getName());
					mHandler.sendEmptyMessage(FOUND_DEVICE);
				} else if (actionStr
						.equals(BluetoothAdapter.ACTION_DISCOVERY_STARTED)) {
					mHandler.sendEmptyMessage(START_DISCOVERY);
				} else if (actionStr
						.equals(BluetoothAdapter.ACTION_DISCOVERY_FINISHED)) {
					mHandler.sendEmptyMessage(FINISH_DISCOVERY);
				}
			}

		};
		IntentFilter filter1 = new IntentFilter(BluetoothDevice.ACTION_FOUND);
		IntentFilter filter2 = new IntentFilter(
				BluetoothAdapter.ACTION_DISCOVERY_STARTED);
		IntentFilter filter3 = new IntentFilter(
				BluetoothAdapter.ACTION_DISCOVERY_FINISHED);

		bbkAct.registerReceiver(mReceiver, filter1);
		bbkAct.registerReceiver(mReceiver, filter2);
		bbkAct.registerReceiver(mReceiver, filter3);
	}

	// 广播接收器，主要是接收蓝牙状态改变时发出的广播
	private BroadcastReceiver mReceiver;

	// 消息处理器..日理万鸡的赶脚...
	private Handler mHandler = new Handler() {

		@Override
		public void handleMessage(Message msg) {
			// TODO Auto-generated method stub
			switch (msg.what) {
			case FOUND_DEVICE:
				foundList.setAdapter(new MyAdapter(bbkAct, foundDevices));
				break;
			case START_DISCOVERY:
				discoveryPro.setVisibility(View.VISIBLE);
				break;
			case FINISH_DISCOVERY:
				discoveryPro.setVisibility(View.GONE);
				break;
			case CONNECT_FAIL:
				toastShow("连接失败");
				break;
			case CONNECT_SUCCEED_P:
			case CONNECT_SUCCEED_N:
				toastShow("连接成功-----");
				if (msg.what == CONNECT_SUCCEED_P) {
					socket = connectThread.getSocket();
					connectedThread = new ConnectedThread(socket, mHandler);
					connectedThread.start();
				} else {
					if (connectThread != null) {
						connectThread.interrupt();
					}
					connectedThread = new ConnectedThread(socket, mHandler);
					connectedThread.start();
				}

				String stateStr = msg.getData().getString("name");
				stateStr = "串口工具：" + "与" + stateStr + "连接中";
				stateText.setText(stateStr);
				toastShow("连接成功");
				break;
			case RECEIVE_MSG:
			case SEND_MSG:
				String chatStr = msg.getData().getString("str");
				TextView text = new TextView(bbkAct);
				text.setText(chatStr);
				if (msg.what == SEND_MSG) {
					text.setBackgroundResource(R.drawable.chat_i);
					text.setPadding(40, 10, 30, 10);
				} else {
					text.setBackgroundResource(R.drawable.chat_u);
					text.setPadding(80, 10, 30, 10);
				}
				text.setTextSize(20);
				text.setTextColor(Color.BLACK);
				chatContent.addView(text);
				scrollView.scrollTo(0, chatContent.getHeight());
				break;
			}
		}

	};

	// /*
	// * 显示对话框，选择使用蓝牙聊天还是串口工具 两都的区别在于连接时使用的UUID不同
	// 而且作为串口工具时无须启动监听远程连接的acceptThread
	// */
	// public void chooseMode() {
	// AlertDialog.Builder builder = new AlertDialog.Builder(this);
	// builder.setNegativeButton("串口工具",
	// new DialogInterface.OnClickListener() {
	// @Override
	// public void onClick(DialogInterface dialog, int which) {
	// // TODO Auto-generated method stub
	// Toast.makeText(bbkAct, "你选择了使用串口工具",
	// Toast.LENGTH_SHORT).show();
	// }
	// });
	// builder.create().show();
	// }

	/*
	 * 退出程序时处理一下后事，取消注册广播接收器，中止线程，关闭socket
	 */
	public void BBKBlueToothDestroy() {		
		bbkAct.unregisterReceiver(mReceiver);
		if (socket != null) {
			try {
				socket.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		if (connectThread != null) {
			connectThread.interrupt();
		}
		if (connectedThread != null) {
			connectedThread.interrupt();
		}
		if (bluetoothAdapter.isEnabled()) {
			toastShow("请手动关闭蓝牙");
		}

	}

	public void BBKBlueToothConnect(BluetoothDevice device) {
		bluetoothAdapter.cancelDiscovery();
		dialog.dismiss();
		toastShow("正在与 " + device.getName() + " 连接 .... ");
		connectThread = new ConnectThread(device, mHandler, false);
		connectThread.start();
	}

}
