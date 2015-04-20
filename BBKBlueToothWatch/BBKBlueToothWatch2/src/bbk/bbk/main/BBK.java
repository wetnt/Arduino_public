package bbk.bbk.main;

import bbk.sys.bluetooth.BBKBlueTooth;
import bbk.sys.math.DigitalTrans;
import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.Bitmap.Config;
import android.graphics.BitmapFactory.Options;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.Paint.Align;
import android.os.Bundle;
import android.os.Handler;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

public class BBK extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		// ----------------------------------------------------
		SoftInt();
		handler.postDelayed(runnable, 300);
		// ----------------------------------------------------
	}

	// @Override
	// public boolean onCreateOptionsMenu(Menu menu) {
	// getMenuInflater().inflate(R.menu.bbk, menu);
	// return true;
	// }

	// ----------------------------------------------------
	Button bText;
	TextView textinfo;
	ImageView vmd, v50, vll;
	Button bTurn, bClrs, bSend;
	Button bNews, bBack, bSave;
	Button bBlue, bExit;
	EditText tTime;
	Button bRuns;
	// ----------------------------------------------------
	Bitmap mmd, m50, m88, mll;
	Canvas cmd, c50, c88, cll;
	// ----------------------------------------------------
	Config bmpCfg = null;// Config.RGB_565;
	Options bmpOpts = null;
	int whiteColor = 0xFFFFFFFF;
	int mapTextS = 24, mapLineW = 3;
	Paint mPaintBlu, mPaintRed, mPaintWrt;
	// ----------------------------------------------------
	int MapW, MapH;

	public static BBKBlueTooth bbl = new BBKBlueTooth();

	// ----------------------------------------------------

	public void SoftInt() {
		// ----------------------------------------------------
		bText = (Button) findViewById(R.id.bText);
		// ----------------------------------------------------
		textinfo = (TextView) findViewById(R.id.textinfo);
		bSend = (Button) findViewById(R.id.bSend);
		// ----------------------------------------------------
		tTime = (EditText) findViewById(R.id.tTime);
		bRuns = (Button) findViewById(R.id.bRuns);
		// ----------------------------------------------------
		bTurn = (Button) findViewById(R.id.bTurn);
		bClrs = (Button) findViewById(R.id.bClrs);
		bSave = (Button) findViewById(R.id.bSave);
		// ----------------------------------------------------
		bBlue = (Button) findViewById(R.id.bBlue);
		bExit = (Button) findViewById(R.id.bExit);
		// ----------------------------------------------------
		bNews = (Button) findViewById(R.id.bNews);
		bBack = (Button) findViewById(R.id.bBack);
		// ----------------------------------------------------
		bTurn.setTextColor(Color.RED);
		// ----------------------------------------------------
		vmd = (ImageView) findViewById(R.id.imageView);
		vmd.setBackgroundColor(-1);
		v50 = (ImageView) findViewById(R.id.imageView50);
		v50.setBackgroundColor(-1);
		vll = (ImageView) findViewById(R.id.imageLine);
		vll.setBackgroundColor(-1);
		// ----------------------------------------------------
		bSend.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				bSendClick();
			}
		});
		// ----------------------------------------------------
		bClrs.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				MapDrawCls();
			}
		});
		bTurn.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				rPaintYes = !rPaintYes;
				if (rPaintYes) {
					bTurn.setTextColor(Color.RED);
				} else {
					bTurn.setTextColor(Color.WHITE);
				}
			}
		});
		bSave.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				bSendClick();
			}
		});
		// ----------------------------------------------------
		bExit.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				bbl.BBKBlueToothDestroy();
				System.exit(0);// 正常退出App
			}
		});
		bBlue.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				// bbl.layshow(true);
				bbl.BBKBlueToothLink();
			}
		});
		// ----------------------------------------------------
		bNews.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				mmClrs();
			}
		});
		bBack.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				mmBack();
			}
		});
		// ----------------------------------------------------
		bRuns.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View arg0) {
				bRunsClick();
			}
		});
		// ----------------------------------------------------
		bmpCfg = Config.RGB_565;
		// bmpCfg = Config.ARGB_4444;
		// bmpCfg = Config.ARGB_8888;
		// ----------------------------------------------------
		mPaintBlu = colorSet(Color.BLUE, mapTextS, mapLineW, 255);
		mPaintRed = colorSet(Color.RED, mapTextS, mapLineW, 255);
		mPaintWrt = colorSet(Color.WHITE, mapTextS, mapLineW, 255);
		// ----------------------------------------------------
		bText.setText("BOBOKing 蓝牙手表  V1.0");
		bbl.BBKBlueToothInt(BBK.this);
		// ----------------------------------------------------
	}

	public void MapDrawInt() {
		// ----------------------------------------------------
		MapW = vmd.getWidth();
		MapH = vmd.getHeight();
		// ----------------------------------------------------
		mmd = Bitmap.createBitmap(MapW, MapH, bmpCfg);
		cmd = new Canvas();
		cmd.setBitmap(mmd);
		cmd.drawColor(whiteColor);
		// ------------------------------
		m50 = Bitmap.createBitmap(50, 50, bmpCfg);
		c50 = new Canvas();
		c50.setBitmap(m50);
		c50.drawColor(whiteColor);
		v50.setImageBitmap(m50);
		// ------------------------------
		mll = Bitmap.createBitmap(800, 50, bmpCfg);
		cll = new Canvas();
		cll.setBitmap(mll);
		cll.drawColor(whiteColor);
		vll.setImageBitmap(mll);
		// ------------------------------
		m88 = Bitmap.createBitmap(8, 8, bmpCfg);
		c88 = new Canvas();
		c88.setBitmap(m88);
		c88.drawColor(whiteColor);
		// ----------------------------------------------------
		int wd = MapW / 8;
		int hd = MapW / 8;
		int xx, yy;
		for (int y = 0; y <= 8; y++) {
			yy = y * hd;
			cmd.drawLine(0, yy, MapW, yy, mPaintBlu);
		}
		for (int x = 0; x <= 8; x++) {
			xx = x * wd;
			cmd.drawLine(xx, 0, xx, MapW, mPaintBlu);
			// --------------------------------------------
		}
		vmd.setImageBitmap(mmd);
		// ----------------------------------------------------
		ImgViewTouchSet(vmd);
		// ----------------------------------------------------
	}

	public static int penw = 26;

	public void MapDrawCls() {
		// ----------------------------------------------------
		cmd.drawColor(whiteColor);
		// ----------------------------------------------------
		int wd = MapW / 8, hd = MapW / 8;
		for (int y = 0; y <= 8; y++) {
			int yy = y * hd;
			cmd.drawLine(0, yy, MapW, yy, mPaintBlu);
		}
		for (int x = 0; x <= 8; x++) {
			int xx = x * wd;
			cmd.drawLine(xx, 0, xx, MapW, mPaintBlu);
		}
		vmd.setImageBitmap(mmd);
		// ----------------------------------------------------
		c50.drawColor(whiteColor);
		v50.setImageBitmap(m50);
		// ----------------------------------------------------
		c88.drawColor(whiteColor);
		// ----------------------------------------------------
		String sendStr = BBKRadioRun();
		textinfo.setText(sendStr);
		// ----------------------------------------------------
		//ImgViewTouchSet(vmd);
		// ----------------------------------------------------
	}

	// ====================================================================================
	// ====================================================================================
	public void bSendClick() {
		// ----------------------------------------------------
		if (mmAdd(m50)) {
			// ----------------------------------------------------
			String sendStr = BBKRadioRun();
			textinfo.setText(sendStr);
			bbl.BBKBlueToothSend(sendStr);
			// ----------------------------------------------------
			bstr[mmn] = sendStr;
			// ----------------------------------------------------
		}
		// ----------------------------------------------------
	}

	// ====================================================================================
	public int mmn = -1;

	public boolean mmAdd(Bitmap mz) {
		// -------------------------------------------------------------------
		if (mmn > 9) {
			return false;
		}
		mmn++;
		// -------------------------------------------------------------------
		cll.drawBitmap(mz, mmn * 60, 0, null);
		vll.setImageBitmap(mll);
		// -------------------------------------------------------------------
		return true;
		// -------------------------------------------------------------------
	}

	public void mmBack() {
		// ---------------------------------------------
		MapDrawCls();
		// ---------------------------------------------
		cll.drawBitmap(m50, mmn * 60, 0, null);
		vll.setImageBitmap(mll);
		// ---------------------------------------------
		mmn--;
		if (mmn < 0)
			return;
		// ---------------------------------------------
	}

	public void mmClrs() {
		mmn = -1;
		// ---------------------------------------------
		MapDrawCls();
		// ---------------------------------------------
		cll.drawColor(whiteColor);
		vll.setImageBitmap(mll);
		// ---------------------------------------------
	}

	// ====================================================================================
	// ====================================================================================
	// ====================================================================================

	public Paint colorSet(int color, int TextSize, int LineW, int Alpha) {
		// ----------------------------------------------------
		Paint p = new Paint();
		// ----------------------------------------------------
		p.setColor(color); // 设置的颜色Color.RED
		// ----------------------------------------------------
		p.setAntiAlias(true);// 去锯齿
		p.setStyle(Paint.Style.FILL); // Paint.Style.STROKE设置为空心
		p.setStrokeWidth(LineW); // 设置外框宽度
		p.setFilterBitmap(true); // 对位图抗锯齿滤波
		p.setTextSize(TextSize); // 字体尺寸
		p.setSubpixelText(true); // 文字抗锯齿
		p.setTextAlign(Align.LEFT); // 字体对齐方式
		// ----------------------------------------------------
		p.setAlpha(Alpha);// 透明通道
		// ----------------------------------------------------
		return p;
		// ----------------------------------------------------
	}

	// ====================================================================================
	public void ImgViewTouchSet(ImageView myImageView) {
		myImageView.setOnTouchListener(new OnTouchListener() {
			// ====================================================================================
			public boolean onTouch(View v, MotionEvent event) {
				// ====================================================================================
				ImageView view = (ImageView) v;
				// ====================================================================================
				switch (event.getAction() & MotionEvent.ACTION_MASK) {
				// 设置拖拉模式
				case MotionEvent.ACTION_DOWN:
					// ddd("1 = ACTION_DOWN");
					break;
				case MotionEvent.ACTION_UP:
					// ddd("2 = ACTION_UP");
					break;
				case MotionEvent.ACTION_POINTER_UP:
					// ddd("3 = ACTION_POINTER_UP");
					break;
				// 设置多点触摸模式
				case MotionEvent.ACTION_POINTER_DOWN:
					// ddd("4 = ACTION_POINTER_DOWN");
					break;
				// 若为DRAG模式，则点击移动图片
				case MotionEvent.ACTION_MOVE:
					// ddd("5 = ACTION_MOVE");
					MapDrawSize(event.getX(), event.getY());
					// LabInf.setText("ACTION_MOVE");
					break;
				}
				// view.setImageMatrix(mapVwMatrix);
				return true; // indicate event was handled
			}
			// ====================================================================================
			// ====================================================================================
		});
	}

	Matrix matrix = new Matrix();
	public boolean rPaintYes = true;

	public void MapDrawSize(float cx, float cy) {
		// ----------------------------------------------------
		// float radius = 30;
		if (rPaintYes) {
			// cmd.drawRect(cx, cy, penw, penw, mPaintRed);
			cmd.drawCircle(cx, cy, penw, mPaintRed);
		} else {
			// cmd.drawRect(cx, cy, cx+penw, cy+penw, mPaintWrt);
			cmd.drawCircle(cx, cy, penw, mPaintWrt);
		}
		vmd.setImageBitmap(mmd);
		// ----------------------------------------------------
		matrix.reset();
		float sx = 8f / mmd.getWidth();
		float sy = sx;
		matrix.setScale(sx, sy);
		c88.drawBitmap(mmd, matrix, null);
		// ----------------------------------------------------
		matrix.reset();
		sx = 50f / 8;
		sy = sx;
		matrix.setScale(sx, sy);
		c50.drawBitmap(m88, matrix, null);
		v50.setImageBitmap(m50);
		// ----------------------------------------------------
		String sendStr = BBKRadioRun();
		textinfo.setText(sendStr);
		// ----------------------------------------------------
	}

	public String BBKRadioRun() {
		// ================================================================
		String allstr = "";
		// ================================================================
		for (int y = 0; y < 8; y++) {
			// ----------------------------------------------------
			String linestr = "";
			// ----------------------------------------------------
			for (int x = 0; x < 8; x++) {
				// ----------------------------------------------------
				int z = m88.getPixel(x, y);
				if (z == -1) {
					linestr = "0" + linestr;
				} else {
					linestr = "1" + linestr;
				}
				// ----------------------------------------------------
			}
			// ----------------------------------------------------
			// ddd(linestr);
			int lineint = DigitalTrans.binaryToAlgorism(linestr);
			allstr += DigitalTrans.algorismToHEXString(lineint);
			// ----------------------------------------------------
		}
		// ================================================================
		return allstr;
		// ================================================================
	}

	// public void BBK8X8Send() {
	// // ----------------------------------------------------
	// String sendStr = textinfo.getText().toString();
	// textinfo.setText(sendStr);
	// // bbl.BBKBlueToothSend(sendStr);
	// // ----------------------------------------------------
	// }

	// ====================================================================================
	// ====================================================================================
	public Handler handler = new Handler();
	public Runnable runnable = new Runnable() {
		public void run() {
			// -------------------------------------------------------------------
			MapDrawInt();
			// mmInt();
			// GalleryLoad();
			// ----------------------------------------------------
			// handler.postDelayed(this, Timers);
			// -------------------------------------------------------------------
			// postDelayed(this,1000) 方法安排一个Runnable对象到主线程队列中
			// handler.postDelayed(runnable,Timers); // 开始Timer
			// handler.removeCallbacks(runnable); //停止Timer
			// -------------------------------------------------------------------
		}
	};

	private Toast toast;

	public void ToastShow(String str) {
		if (toast == null) {
			toast = Toast.makeText(this, str, Toast.LENGTH_SHORT);
		} else {
			toast.cancel();
			toast.setText(str);
		}
		toast.show();
		// Toast.makeText(this, str, Toast.LENGTH_SHORT).show();
	}

	// ====================================================================================
	public static void ddd(String str) {
		String s = "=== " + str;
		System.out.println(s);
	}

	public static void ddd(int str) {
		String s = "=== " + str;
		System.out.println(s);
	}

	// ====================================================================================
	public int bstrn = 0;
	public String bstr[] = new String[11];
	// ====================================================================================
	public int BlueTimers = 600;
	public boolean bRunsYes = false;

	public void bRunsClick() {
		bRunsYes = !bRunsYes;
		if (bRunsYes) {
			// ----------------------------------------------------
			String s = tTime.getText().toString();
			BlueTimers = Integer.parseInt(s);
			if (BlueTimers < 200)
				BlueTimers = 200;
			// ----------------------------------------------------
			bstrn = -1;
			Bluehandler.removeCallbacks(Bluerunnable);
			Bluehandler.postDelayed(Bluerunnable, BlueTimers);
			// ----------------------------------------------------
			bRuns.setText("停止");
			// ----------------------------------------------------
		} else {
			// ----------------------------------------------------
			Bluehandler.removeCallbacks(Bluerunnable);
			// ----------------------------------------------------
			bRuns.setText("循环");
			// ----------------------------------------------------
		}
	}

	// ====================================================================================
	public Handler Bluehandler = new Handler();
	public Runnable Bluerunnable = new Runnable() {
		public void run() {
			// -------------------------------------------------------------------
			bstrn++;
			if (bstrn > mmn)
				bstrn = 0;
			ddd(bstrn + " " + bstr[bstrn]);
			bbl.BBKBlueToothSend(bstr[bstrn]);
			Bluehandler.postDelayed(this, BlueTimers);
			// -------------------------------------------------------------------
			// postDelayed(this,1000) 方法安排一个Runnable对象到主线程队列中
			// handler.postDelayed(runnable,Timers); // 开始Timer
			// handler.removeCallbacks(runnable); //停止Timer
			// -------------------------------------------------------------------
		}
	};
	// ====================================================================================

	// boolean RadioIs = false;

	// public void BBKRadioClear() {
	// RadioIs = !RadioIs;
	// for (int y = 0; y < 8; y++) {
	// for (int x = 0; x < 8; x++) {
	// int n = y * 8 + x;
	// r[n].setChecked(RadioIs);
	// }
	// }
	// }

	// public String BBKRadioRun() {
	// // ================================================================
	// String allstr = "";
	// // ================================================================
	// for (int y = 0; y < 8; y++) {
	// // ----------------------------------------------------
	// String linestr = "";
	// // ----------------------------------------------------
	// for (int x = 0; x < 8; x++) {
	// // ----------------------------------------------------
	// int n = y * 8 + x;
	// if (r[n].isChecked()) {
	// linestr = "1" + linestr;
	// } else {
	// linestr = "0" + linestr;
	// }
	// // ----------------------------------------------------
	// }
	// // ----------------------------------------------------
	// int lineint = DigitalTrans.binaryToAlgorism(linestr);
	// allstr += DigitalTrans.algorismToHEXString(lineint);
	// // ----------------------------------------------------
	// }
	// // ================================================================
	// return allstr;
	// // ================================================================
	// }

	// ====================================================================================

}
