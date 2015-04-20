package bbk.bluetooth.watch;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.app.Activity;
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
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.ProgressBar;
import android.widget.RadioButton;
import android.widget.ScrollView;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.AdapterView.OnItemClickListener;

public class BBK extends Activity {

	// 消息处理器使用的常量
	private static final int FOUND_DEVICE = 1; // 发现设备
	private static final int START_DISCOVERY = 2; // 开始查找设备
	private static final int FINISH_DISCOVERY = 3; // 结束查找设备
	private static final int CONNECT_FAIL = 4; // 连接失败
	private static final int CONNECT_SUCCEED_P = 5; // 主动连接成功
	private static final int CONNECT_SUCCEED_N = 6; // 收到连接成功
	private static final int RECEIVE_MSG = 7; // 收到消息
	private static final int SEND_MSG = 8; // 发送消息

	ConnectedThread connectedThread; // 与远程蓝牙连接成功时启动
	ConnectThread connectThread; // 用户点击列表中某一项，要与远程蓝牙连接时启动
	AcceptThread acceptThread; // 用户选择蓝牙聊天时立即启动

	// 布局控件
	private Button bLink, bSend, bShow;
	private TextView stateText;
	private EditText sendText;
	private ScrollView scrollView;
	private LinearLayout chatContent;

	// 连接设备对话框相关控件
	private Dialog dialog;
	private ProgressBar discoveryPro;
	private ListView foundList;
	List<BluetoothDevice> foundDevices;

	BluetoothSocket socket;
	BluetoothAdapter bluetoothAdapter = null;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);

		SoftInt();
		BBK8X8Int();
		BlueToothInt();
		BroadcastInt();
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.bbk, menu);
		return true;
	}

	public void SoftInt() {
		bLink = (Button) findViewById(R.id.bLink);
		bSend = (Button) findViewById(R.id.bSend);
		bShow = (Button) findViewById(R.id.bShow);
		stateText = (TextView) findViewById(R.id.stateText);
		sendText = (EditText) findViewById(R.id.sendText);
		scrollView = (ScrollView) findViewById(R.id.scrollView);
		chatContent = (LinearLayout) findViewById(R.id.chatContent);

		// 连接设备按钮监听器
		bLink.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View arg0) {
				// TODO Auto-generated method stub
				bluetoothAdapter.cancelDiscovery();
				bluetoothAdapter.startDiscovery();

				/*
				 * 通过LayoutInflater得到对话框中的三个控件
				 * 第一个ListView为局部变量，因为它显示的是已配对的蓝牙设备，不需随时改变
				 * 第二个ListView和ProgressBar为全局变量
				 */
				LayoutInflater inflater = getLayoutInflater();
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
				bondedList.setAdapter(new MyAdapter(BBK.this, bondedDevices));

				// 将找到的蓝牙设备显示到第二个ListView中
				foundDevices = new ArrayList<BluetoothDevice>();
				foundList.setAdapter(new MyAdapter(BBK.this, foundDevices));

				// 两个ListView绑定监听器
				bondedList.setOnItemClickListener(new OnItemClickListener() {

					@Override
					public void onItemClick(AdapterView<?> arg0, View arg1,
							int arg2, long arg3) {
						// TODO Auto-generated method stub
						BluetoothDevice device = bondedDevices.get(arg2);
						connect(device);
					}
				});
				foundList.setOnItemClickListener(new OnItemClickListener() {

					@Override
					public void onItemClick(AdapterView<?> arg0, View arg1,
							int arg2, long arg3) {
						// TODO Auto-generated method stub
						BluetoothDevice device = foundDevices.get(arg2);
						connect(device);

					}
				});

				AlertDialog.Builder builder = new AlertDialog.Builder(BBK.this);
				builder.setMessage("请选择要连接的蓝牙设备").setPositiveButton("取消",
						new DialogInterface.OnClickListener() {

							@Override
							public void onClick(DialogInterface dialog,
									int which) {
								// TODO Auto-generated method stub
								bluetoothAdapter.cancelDiscovery();
							}
						});
				builder.setView(view);
				builder.create();
				dialog = builder.show();
			}
		});

		// 发送消息按钮监听器
		bSend.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View arg0) {
				
				BBKRadioRun();
				BBKRadioClear();
				
				// TODO Auto-generated method stub
				if (socket == null) {
					Toast.makeText(BBK.this, "请先连接蓝牙设备", Toast.LENGTH_SHORT)
							.show();
				} else if (sendText.getText().toString().equals("")) {
					Toast.makeText(BBK.this, "发送内容不能为空", Toast.LENGTH_SHORT)
							.show();
				} else {
					
					String sendStr = sendText.getText().toString();
					
					byte[] z = DigitalTrans.hex2byte(sendStr);

					connectedThread.write(z);
					
//					connectedThread.write(sendStr.getBytes());					
					//sendText.setText("");
				}

			}
		});

		// 使蓝牙可被发现
		bShow.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View arg0) {
				// TODO Auto-generated method stub
				Intent intent = new Intent(
						BluetoothAdapter.ACTION_REQUEST_DISCOVERABLE);
				startActivity(intent);
			}
		});

	}

	RadioButton r11, r21, r31, r41, r51, r61, r71, r81;
	RadioButton r12, r22, r32, r42, r52, r62, r72, r82;
	RadioButton r13, r23, r33, r43, r53, r63, r73, r83;
	RadioButton r14, r24, r34, r44, r54, r64, r74, r84;
	RadioButton r15, r25, r35, r45, r55, r65, r75, r85;
	RadioButton r16, r26, r36, r46, r56, r66, r76, r86;
	RadioButton r17, r27, r37, r47, r57, r67, r77, r87;
	RadioButton r18, r28, r38, r48, r58, r68, r78, r88;

	public void BBK8X8Int() {
		// ================================================================
		r11 = (RadioButton) findViewById(R.id.rd11);
		r12 = (RadioButton) findViewById(R.id.rd12);
		r13 = (RadioButton) findViewById(R.id.rd13);
		r14 = (RadioButton) findViewById(R.id.rd14);
		r15 = (RadioButton) findViewById(R.id.rd15);
		r16 = (RadioButton) findViewById(R.id.rd16);
		r17 = (RadioButton) findViewById(R.id.rd17);
		r18 = (RadioButton) findViewById(R.id.rd18);

		r21 = (RadioButton) findViewById(R.id.rd21);
		r22 = (RadioButton) findViewById(R.id.rd22);
		r23 = (RadioButton) findViewById(R.id.rd23);
		r24 = (RadioButton) findViewById(R.id.rd24);
		r25 = (RadioButton) findViewById(R.id.rd25);
		r26 = (RadioButton) findViewById(R.id.rd26);
		r27 = (RadioButton) findViewById(R.id.rd27);
		r28 = (RadioButton) findViewById(R.id.rd28);

		r31 = (RadioButton) findViewById(R.id.rd31);
		r32 = (RadioButton) findViewById(R.id.rd32);
		r33 = (RadioButton) findViewById(R.id.rd33);
		r34 = (RadioButton) findViewById(R.id.rd34);
		r35 = (RadioButton) findViewById(R.id.rd35);
		r36 = (RadioButton) findViewById(R.id.rd36);
		r37 = (RadioButton) findViewById(R.id.rd37);
		r38 = (RadioButton) findViewById(R.id.rd38);

		r41 = (RadioButton) findViewById(R.id.rd41);
		r42 = (RadioButton) findViewById(R.id.rd42);
		r43 = (RadioButton) findViewById(R.id.rd43);
		r44 = (RadioButton) findViewById(R.id.rd44);
		r45 = (RadioButton) findViewById(R.id.rd45);
		r46 = (RadioButton) findViewById(R.id.rd46);
		r47 = (RadioButton) findViewById(R.id.rd47);
		r48 = (RadioButton) findViewById(R.id.rd48);

		r51 = (RadioButton) findViewById(R.id.rd51);
		r52 = (RadioButton) findViewById(R.id.rd52);
		r53 = (RadioButton) findViewById(R.id.rd53);
		r54 = (RadioButton) findViewById(R.id.rd54);
		r55 = (RadioButton) findViewById(R.id.rd55);
		r56 = (RadioButton) findViewById(R.id.rd56);
		r57 = (RadioButton) findViewById(R.id.rd57);
		r58 = (RadioButton) findViewById(R.id.rd58);

		r61 = (RadioButton) findViewById(R.id.rd61);
		r62 = (RadioButton) findViewById(R.id.rd62);
		r63 = (RadioButton) findViewById(R.id.rd63);
		r64 = (RadioButton) findViewById(R.id.rd64);
		r65 = (RadioButton) findViewById(R.id.rd65);
		r66 = (RadioButton) findViewById(R.id.rd66);
		r67 = (RadioButton) findViewById(R.id.rd67);
		r68 = (RadioButton) findViewById(R.id.rd68);

		r71 = (RadioButton) findViewById(R.id.rd71);
		r72 = (RadioButton) findViewById(R.id.rd72);
		r73 = (RadioButton) findViewById(R.id.rd73);
		r74 = (RadioButton) findViewById(R.id.rd74);
		r75 = (RadioButton) findViewById(R.id.rd75);
		r76 = (RadioButton) findViewById(R.id.rd76);
		r77 = (RadioButton) findViewById(R.id.rd77);
		r78 = (RadioButton) findViewById(R.id.rd78);

		r81 = (RadioButton) findViewById(R.id.rd81);
		r82 = (RadioButton) findViewById(R.id.rd82);
		r83 = (RadioButton) findViewById(R.id.rd83);
		r84 = (RadioButton) findViewById(R.id.rd84);
		r85 = (RadioButton) findViewById(R.id.rd85);
		r86 = (RadioButton) findViewById(R.id.rd86);
		r87 = (RadioButton) findViewById(R.id.rd87);
		r88 = (RadioButton) findViewById(R.id.rd88);
		// ================================================================
	}

	// ====================================================================================

	public void BBKRadioRun() {
		// ================================================================
		String x1="",x2="",x3="",x4="",x5="",x6="",x7="",x8="";
		// ================================================================
		
		if (r11.isChecked()) { x1 += "1"; } else { x1 += "0"; }
		if (r12.isChecked()) { x1 += "1"; } else { x1 += "0"; }
		if (r13.isChecked()) { x1 += "1"; } else { x1 += "0"; }
		if (r14.isChecked()) { x1 += "1"; } else { x1 += "0"; }
		if (r15.isChecked()) { x1 += "1"; } else { x1 += "0"; }
		if (r16.isChecked()) { x1 += "1"; } else { x1 += "0"; }
		if (r17.isChecked()) { x1 += "1"; } else { x1 += "0"; }
		if (r18.isChecked()) { x1 += "1"; } else { x1 += "0"; }
		
		if (r21.isChecked()) { x2 += "1"; } else { x2 += "0"; }
		if (r22.isChecked()) { x2 += "1"; } else { x2 += "0"; }
		if (r23.isChecked()) { x2 += "1"; } else { x2 += "0"; }
		if (r24.isChecked()) { x2 += "1"; } else { x2 += "0"; }
		if (r25.isChecked()) { x2 += "1"; } else { x2 += "0"; }
		if (r26.isChecked()) { x2 += "1"; } else { x2 += "0"; }
		if (r27.isChecked()) { x2 += "1"; } else { x2 += "0"; }
		if (r28.isChecked()) { x2 += "1"; } else { x2 += "0"; }
		
		if (r31.isChecked()) { x3 += "1"; } else { x3 += "0"; }
		if (r32.isChecked()) { x3 += "1"; } else { x3 += "0"; }
		if (r33.isChecked()) { x3 += "1"; } else { x3 += "0"; }
		if (r34.isChecked()) { x3 += "1"; } else { x3 += "0"; }
		if (r35.isChecked()) { x3 += "1"; } else { x3 += "0"; }
		if (r36.isChecked()) { x3 += "1"; } else { x3 += "0"; }
		if (r37.isChecked()) { x3 += "1"; } else { x3 += "0"; }
		if (r38.isChecked()) { x3 += "1"; } else { x3 += "0"; }
		
		if (r41.isChecked()) { x4 += "1"; } else { x4 += "0"; }
		if (r42.isChecked()) { x4 += "1"; } else { x4 += "0"; }
		if (r43.isChecked()) { x4 += "1"; } else { x4 += "0"; }
		if (r44.isChecked()) { x4 += "1"; } else { x4 += "0"; }
		if (r45.isChecked()) { x4 += "1"; } else { x4 += "0"; }
		if (r46.isChecked()) { x4 += "1"; } else { x4 += "0"; }
		if (r47.isChecked()) { x4 += "1"; } else { x4 += "0"; }
		if (r48.isChecked()) { x4 += "1"; } else { x4 += "0"; }
		
		if (r51.isChecked()) { x5 += "1"; } else { x5 += "0"; }
		if (r52.isChecked()) { x5 += "1"; } else { x5 += "0"; }
		if (r53.isChecked()) { x5 += "1"; } else { x5 += "0"; }
		if (r54.isChecked()) { x5 += "1"; } else { x5 += "0"; }
		if (r55.isChecked()) { x5 += "1"; } else { x5 += "0"; }
		if (r56.isChecked()) { x5 += "1"; } else { x5 += "0"; }
		if (r57.isChecked()) { x5 += "1"; } else { x5 += "0"; }
		if (r58.isChecked()) { x5 += "1"; } else { x5 += "0"; }
		
		if (r61.isChecked()) { x6 += "1"; } else { x6 += "0"; }
		if (r62.isChecked()) { x6 += "1"; } else { x6 += "0"; }
		if (r63.isChecked()) { x6 += "1"; } else { x6 += "0"; }
		if (r64.isChecked()) { x6 += "1"; } else { x6 += "0"; }
		if (r65.isChecked()) { x6 += "1"; } else { x6 += "0"; }
		if (r66.isChecked()) { x6 += "1"; } else { x6 += "0"; }
		if (r67.isChecked()) { x6 += "1"; } else { x6 += "0"; }
		if (r68.isChecked()) { x6 += "1"; } else { x6 += "0"; }
		
		if (r71.isChecked()) { x7 += "1"; } else { x7 += "0"; }
		if (r72.isChecked()) { x7 += "1"; } else { x7 += "0"; }
		if (r73.isChecked()) { x7 += "1"; } else { x7 += "0"; }
		if (r74.isChecked()) { x7 += "1"; } else { x7 += "0"; }
		if (r75.isChecked()) { x7 += "1"; } else { x7 += "0"; }
		if (r76.isChecked()) { x7 += "1"; } else { x7 += "0"; }
		if (r77.isChecked()) { x7 += "1"; } else { x7 += "0"; }
		if (r78.isChecked()) { x7 += "1"; } else { x7 += "0"; }
		
		if (r81.isChecked()) { x8 += "1"; } else { x8 += "0"; }
		if (r82.isChecked()) { x8 += "1"; } else { x8 += "0"; }
		if (r83.isChecked()) { x8 += "1"; } else { x8 += "0"; }
		if (r84.isChecked()) { x8 += "1"; } else { x8 += "0"; }
		if (r85.isChecked()) { x8 += "1"; } else { x8 += "0"; }
		if (r86.isChecked()) { x8 += "1"; } else { x8 += "0"; }
		if (r87.isChecked()) { x8 += "1"; } else { x8 += "0"; }
		if (r88.isChecked()) { x8 += "1"; } else { x8 += "0"; }
		
		// ================================================================
		String y = x1+"\r\n"+x2+"\r\n"+x3+"\r\n"+x4+"\r\n"+x5+"\r\n"+x6+"\r\n"+x7+"\r\n"+x8+"\r\n";
		Log.d("===", y);
		// ================================================================	
		int xx1 = DigitalTrans.binaryToAlgorism(x1);
		int xx2 = DigitalTrans.binaryToAlgorism(x2);
		int xx3 = DigitalTrans.binaryToAlgorism(x3);
		int xx4 = DigitalTrans.binaryToAlgorism(x4);
		int xx5 = DigitalTrans.binaryToAlgorism(x5);
		int xx6 = DigitalTrans.binaryToAlgorism(x6);
		int xx7 = DigitalTrans.binaryToAlgorism(x7);
		int xx8 = DigitalTrans.binaryToAlgorism(x8);
		
//        xx1=xx1-48;
//        xx2=xx2-48;
//		xx3=xx3-48;
//		xx4=xx4-48;
//		xx5=xx5-48;
//		xx6=xx6-48;
//		xx7=xx7-48;
//		xx8=xx8-48;
		
				
		String xxx = "";
		xxx+=DigitalTrans.algorismToHEXString(xx8);
		xxx+=DigitalTrans.algorismToHEXString(xx7);
		xxx+=DigitalTrans.algorismToHEXString(xx6);
		xxx+=DigitalTrans.algorismToHEXString(xx5);
		xxx+=DigitalTrans.algorismToHEXString(xx4);
		xxx+=DigitalTrans.algorismToHEXString(xx3);
		xxx+=DigitalTrans.algorismToHEXString(xx2);
		xxx+=DigitalTrans.algorismToHEXString(xx1);
		
				
//		xxx+=xx1;
//		xxx+=xx2;
//		xxx+=xx3;
//		xxx+=xx4;
//		xxx+=xx5;
//		xxx+=xx6;
//		xxx+=xx7;
//		xxx+=xx8;
		
		// ================================================================		
		sendText.setText(xxx);
		// ================================================================	

	}
	
	public void BBKRadioClear() {

		if (r11.isChecked()) { r11.setChecked(false); }
		if (r12.isChecked()) { r12.setChecked(false); }
		if (r13.isChecked()) { r13.setChecked(false); }
		if (r14.isChecked()) { r14.setChecked(false); }
		if (r15.isChecked()) { r15.setChecked(false); }
		if (r16.isChecked()) { r16.setChecked(false); }
		if (r17.isChecked()) { r17.setChecked(false); }
		if (r18.isChecked()) { r18.setChecked(false); }

		if (r21.isChecked()) { r21.setChecked(false); }
		if (r22.isChecked()) { r22.setChecked(false); }
		if (r23.isChecked()) { r23.setChecked(false); }
		if (r24.isChecked()) { r24.setChecked(false); }
		if (r25.isChecked()) { r25.setChecked(false); }
		if (r26.isChecked()) { r26.setChecked(false); }
		if (r27.isChecked()) { r27.setChecked(false); }
		if (r28.isChecked()) { r28.setChecked(false); }

		if (r31.isChecked()) { r31.setChecked(false); }
		if (r32.isChecked()) { r32.setChecked(false); }
		if (r33.isChecked()) { r33.setChecked(false); }
		if (r34.isChecked()) { r34.setChecked(false); }
		if (r35.isChecked()) { r35.setChecked(false); }
		if (r36.isChecked()) { r36.setChecked(false); }
		if (r37.isChecked()) { r37.setChecked(false); }
		if (r38.isChecked()) { r38.setChecked(false); }
		                       
		if (r41.isChecked()) { r41.setChecked(false); }
		if (r42.isChecked()) { r42.setChecked(false); }
		if (r43.isChecked()) { r43.setChecked(false); }
		if (r44.isChecked()) { r44.setChecked(false); }
		if (r45.isChecked()) { r45.setChecked(false); }
		if (r46.isChecked()) { r46.setChecked(false); }
		if (r47.isChecked()) { r47.setChecked(false); }
		if (r48.isChecked()) { r48.setChecked(false); }
		                       
		if (r51.isChecked()) { r51.setChecked(false); }
		if (r52.isChecked()) { r52.setChecked(false); }
		if (r53.isChecked()) { r53.setChecked(false); }
		if (r54.isChecked()) { r54.setChecked(false); }
		if (r55.isChecked()) { r55.setChecked(false); }
		if (r56.isChecked()) { r56.setChecked(false); }
		if (r57.isChecked()) { r57.setChecked(false); }
		if (r58.isChecked()) { r58.setChecked(false); }
		                       
		if (r61.isChecked()) { r61.setChecked(false); }
		if (r62.isChecked()) { r62.setChecked(false); }
		if (r63.isChecked()) { r63.setChecked(false); }
		if (r64.isChecked()) { r64.setChecked(false); }
		if (r65.isChecked()) { r65.setChecked(false); }
		if (r66.isChecked()) { r66.setChecked(false); }
		if (r67.isChecked()) { r67.setChecked(false); }
		if (r68.isChecked()) { r68.setChecked(false); }
		                       
		if (r71.isChecked()) { r71.setChecked(false); }
		if (r72.isChecked()) { r72.setChecked(false); }
		if (r73.isChecked()) { r73.setChecked(false); }
		if (r74.isChecked()) { r74.setChecked(false); }
		if (r75.isChecked()) { r75.setChecked(false); }
		if (r76.isChecked()) { r76.setChecked(false); }
		if (r77.isChecked()) { r77.setChecked(false); }
		if (r78.isChecked()) { r78.setChecked(false); }
		                       
		if (r81.isChecked()) { r81.setChecked(false); }
		if (r82.isChecked()) { r82.setChecked(false); }
		if (r83.isChecked()) { r83.setChecked(false); }
		if (r84.isChecked()) { r84.setChecked(false); }
		if (r85.isChecked()) { r85.setChecked(false); }
		if (r86.isChecked()) { r86.setChecked(false); }
		if (r87.isChecked()) { r87.setChecked(false); }
		if (r88.isChecked()) { r88.setChecked(false); }
		
		// ================================================================
		
	}
	

	// 判断本机是否有蓝牙和是否处于可用状态
	public void BlueToothInt() {
		// 判断本机是否有蓝牙和是否处于可用状态
		bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
		if (bluetoothAdapter == null) {
			Toast.makeText(this, "本机没有蓝牙设备！", Toast.LENGTH_SHORT).show();
			finish();
		}
		if (!bluetoothAdapter.isEnabled()) {
			Intent enableIntent = new Intent(
					BluetoothAdapter.ACTION_REQUEST_ENABLE);
			startActivityForResult(enableIntent, 1);
		} else {
			// chooseMode();
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
					Toast.makeText(BBK.this, "找到蓝牙设备：" + device.getName(),
							Toast.LENGTH_SHORT).show();
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

		registerReceiver(mReceiver, filter1);
		registerReceiver(mReceiver, filter2);
		registerReceiver(mReceiver, filter3);
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
				foundList.setAdapter(new MyAdapter(BBK.this, foundDevices));
				break;
			case START_DISCOVERY:
				discoveryPro.setVisibility(View.VISIBLE);
				break;
			case FINISH_DISCOVERY:
				discoveryPro.setVisibility(View.GONE);
				break;
			case CONNECT_FAIL:
				Toast.makeText(BBK.this, "连接失败", Toast.LENGTH_SHORT).show();
				break;
			case CONNECT_SUCCEED_P:
			case CONNECT_SUCCEED_N:
				System.out.println("连接成功-----");
				if (msg.what == CONNECT_SUCCEED_P) {
					if (acceptThread != null) {
						acceptThread.interrupt();
					}
					socket = connectThread.getSocket();
					connectedThread = new ConnectedThread(socket, mHandler);
					connectedThread.start();
				} else {
					if (connectThread != null) {
						connectThread.interrupt();
					}
					socket = acceptThread.getSocket();
					connectedThread = new ConnectedThread(socket, mHandler);
					connectedThread.start();
				}

				String stateStr = msg.getData().getString("name");
				stateStr = "串口工具：" + "与" + stateStr + "连接中";

				stateText.setText(stateStr);
				Toast.makeText(BBK.this, "连接成功", Toast.LENGTH_SHORT).show();

				break;
			case RECEIVE_MSG:
			case SEND_MSG:
				String chatStr = msg.getData().getString("str");
				TextView text = new TextView(BBK.this);
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
	// Toast.makeText(BBK.this, "你选择了使用串口工具",
	// Toast.LENGTH_SHORT).show();
	// }
	// });
	// builder.create().show();
	// }

	/*
	 * 退出程序时处理一下后事，取消注册广播接收器，中止线程，关闭socket
	 */
	@Override
	protected void onDestroy() {
		// TODO Auto-generated method stub
		super.onDestroy();
		unregisterReceiver(mReceiver);
		if (socket != null) {
			try {
				socket.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		if (connectThread != null) {
			connectThread.interrupt();
		}
		if (connectedThread != null) {
			connectedThread.interrupt();
		}
		if (acceptThread != null) {
			acceptThread.interrupt();
		}
		if (bluetoothAdapter.isEnabled()) {
			Toast.makeText(this, "请手动关闭蓝牙", Toast.LENGTH_SHORT).show();
		}

	}

	public void connect(BluetoothDevice device) {
		bluetoothAdapter.cancelDiscovery();
		dialog.dismiss();
		Toast.makeText(this, "正在与 " + device.getName() + " 连接 .... ",
				Toast.LENGTH_LONG).show();
		connectThread = new ConnectThread(device, mHandler, false);
		connectThread.start();

	}

}
